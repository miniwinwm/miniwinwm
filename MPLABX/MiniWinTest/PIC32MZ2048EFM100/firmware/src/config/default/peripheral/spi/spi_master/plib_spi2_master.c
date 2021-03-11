/*******************************************************************************
  SPI PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_spi2_master.c

  Summary:
    SPI2 Master Source File

  Description:
    This file has implementation of all the interfaces provided for particular
    SPI peripheral.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2018-2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#include "plib_spi2_master.h"

// *****************************************************************************
// *****************************************************************************
// Section: SPI2 Implementation
// *****************************************************************************
// *****************************************************************************


#define SPI2_CON_MSTEN                      (1 << _SPI2CON_MSTEN_POSITION)
#define SPI2_CON_CKP                        (0 << _SPI2CON_CKP_POSITION)
#define SPI2_CON_CKE                        (1 << _SPI2CON_CKE_POSITION)
#define SPI2_CON_MODE_32_MODE_16            (0 << _SPI2CON_MODE16_POSITION)
#define SPI2_CON_ENHBUF                     (1 << _SPI2CON_ENHBUF_POSITION)
#define SPI2_CON_MCLKSEL                    (0 << _SPI2CON_MCLKSEL_POSITION)
#define SPI2_CON_MSSEN                      (0 << _SPI2CON_MSSEN_POSITION)
#define SPI2_CON_SMP                        (0 << _SPI2CON_SMP_POSITION)

void SPI2_Initialize ( void )
{
    uint32_t rdata;

    /* Disable SPI2 Interrupts */
    IEC4CLR = 0x4000;
    IEC4CLR = 0x8000;
    IEC4CLR = 0x10000;

    /* STOP and Reset the SPI */
    SPI2CON = 0;

    /* Clear the Receiver buffer */
    rdata = SPI2BUF;
    rdata = rdata;

    /* Clear SPI2 Interrupt flags */
    IFS4CLR = 0x4000;
    IFS4CLR = 0x8000;
    IFS4CLR = 0x10000;

    /* BAUD Rate register Setup */
    SPI2BRG = 62;

    /* CLear the Overflow */
    SPI2STATCLR = _SPI2STAT_SPIROV_MASK;

    /*
    MSTEN = 1
    CKP = 0
    CKE = 1
    MODE<32,16> = 0
    ENHBUF = 1
    MSSEN = 0
    MCLKSEL = 0
    */
    SPI2CONSET = (SPI2_CON_MSSEN | SPI2_CON_MCLKSEL | SPI2_CON_ENHBUF | SPI2_CON_MODE_32_MODE_16 | SPI2_CON_CKE | SPI2_CON_CKP | SPI2_CON_MSTEN | SPI2_CON_SMP);

    /* Enable transmit interrupt when transmit buffer is completely empty (STXISEL = '01') */
    /* Enable receive interrupt when the receive buffer is not empty (SRXISEL = '01') */
    SPI2CONSET = 0x00000005;


    /* Enable SPI2 */
    SPI2CONSET = _SPI2CON_ON_MASK;
}

bool SPI2_TransferSetup (SPI_TRANSFER_SETUP* setup, uint32_t spiSourceClock )
{
    uint32_t t_brg;
    uint32_t baudHigh;
    uint32_t baudLow;
    uint32_t errorHigh;
    uint32_t errorLow;

    if ((setup == NULL) || (setup->clockFrequency == 0))
    {
        return false;
    }

    if(spiSourceClock == 0)
    {
        // Use Master Clock Frequency set in GUI
        spiSourceClock = 126000000;
    }

    t_brg = (((spiSourceClock / (setup->clockFrequency)) / 2u) - 1u);
    baudHigh = spiSourceClock / (2u * (t_brg + 1u));
    baudLow = spiSourceClock / (2u * (t_brg + 2u));
    errorHigh = baudHigh - setup->clockFrequency;
    errorLow = setup->clockFrequency - baudLow;

    if (errorHigh > errorLow)
    {
        t_brg++;
    }

    if(t_brg > 511)
    {
        return false;
    }

    SPI2BRG = t_brg;
    SPI2CON = (SPI2CON & (~(_SPI2CON_MODE16_MASK | _SPI2CON_MODE32_MASK | _SPI2CON_CKP_MASK | _SPI2CON_CKE_MASK))) |
                            (setup->clockPolarity | setup->clockPhase | setup->dataBits);

    return true;
}

bool SPI2_Write(void* pTransmitData, size_t txSize)
{
    return(SPI2_WriteRead(pTransmitData, txSize, NULL, 0));
}

bool SPI2_Read(void* pReceiveData, size_t rxSize)
{
    return(SPI2_WriteRead(NULL, 0, pReceiveData, rxSize));
}

bool SPI2_WriteRead(void* pTransmitData, size_t txSize, void* pReceiveData, size_t rxSize)
{
    size_t txCount = 0;
    size_t rxCount = 0;
    size_t dummySize = 0;
    size_t dummyRxCntr = 0;
    size_t receivedData;
    bool isSuccess = false;

    /* Verify the request */
    if (((txSize > 0) && (pTransmitData != NULL)) || ((rxSize > 0) && (pReceiveData != NULL)))
    {
        if (pTransmitData == NULL)
        {
            txSize = 0;
        }
        if (pReceiveData == NULL)
        {
            rxSize = 0;
        }

        /* Clear the receive overflow error if any */
        SPI2STATCLR = _SPI2STAT_SPIROV_MASK;

        /* Flush out any unread data in SPI read buffer from the previous transfer */
        while ((bool)(SPI2STAT & _SPI2STAT_SPIRBE_MASK) == false)
        {
            receivedData = SPI2BUF;
        }

        if (rxSize > txSize)
        {
            dummySize = rxSize - txSize;
        }

        /* If dataBit size is 32 bits */
        if (_SPI2CON_MODE32_MASK == (SPI2CON & _SPI2CON_MODE32_MASK))
        {
            rxSize >>= 2;
            txSize >>= 2;
            dummySize >>= 2;
        }
        /* If dataBit size is 16 bits */
        else if (_SPI2CON_MODE16_MASK == (SPI2CON & _SPI2CON_MODE16_MASK))
        {
            rxSize >>= 1;
            txSize >>= 1;
            dummySize >>= 1;
        }

        /* Make sure transmit buffer is empty */
        while((bool)(SPI2STAT & _SPI2STAT_SPITBE_MASK) == false);

        while ((txCount != txSize) || (dummySize != 0))
        {
            if (txCount != txSize)
            {
                if((_SPI2CON_MODE32_MASK) == (SPI2CON & (_SPI2CON_MODE32_MASK)))
                {
                    SPI2BUF = ((uint32_t*)pTransmitData)[txCount++];
                }
                else if((_SPI2CON_MODE16_MASK) == (SPI2CON & (_SPI2CON_MODE16_MASK)))
                {
                    SPI2BUF = ((uint16_t*)pTransmitData)[txCount++];
                }
                else
                {
                    SPI2BUF = ((uint8_t*)pTransmitData)[txCount++];
                }
            }
            else if (dummySize > 0)
            {
                SPI2BUF = 0xff;
                dummySize--;
            }

            if (rxCount == rxSize)
            {
                /* If inside this if condition, then it means that txSize > rxSize and all RX bytes are received */

                /* For transmit only request, wait for buffer to become empty */
                while((bool)(SPI2STAT & _SPI2STAT_SPITBE_MASK) == false);

                /* Read until the receive buffer is not empty */
                while ((bool)(SPI2STAT & _SPI2STAT_SPIRBE_MASK) == false)
                {
                    receivedData = SPI2BUF;
                    dummyRxCntr++;
                }
            }
            else
            {
                /* If data is read, wait for the Receiver Data the data to become available */
                while((SPI2STAT & _SPI2STAT_SPIRBE_MASK) == _SPI2STAT_SPIRBE_MASK);

                /* We have data waiting in the SPI buffer */
                receivedData = SPI2BUF;

                if (rxCount < rxSize)
                {
                    if((_SPI2CON_MODE32_MASK) == (SPI2CON & (_SPI2CON_MODE32_MASK)))
                    {
                        ((uint32_t*)pReceiveData)[rxCount++]  = receivedData;
                    }
                    else if((_SPI2CON_MODE16_MASK) == (SPI2CON & (_SPI2CON_MODE16_MASK)))
                    {
                        ((uint16_t*)pReceiveData)[rxCount++]  = receivedData;
                    }
                    else
                    {
                        ((uint8_t*)pReceiveData)[rxCount++]  = receivedData;
                    }
                }
            }
        }

        /* Make sure no data is pending in the shift register */
        while ((bool)((SPI2STAT & _SPI2STAT_SRMT_MASK) == false));

        /* Make sure for every character transmitted a character is also received back.
         * If this is not done, we may prematurely exit this routine with the last bit still being
         * transmitted out. As a result, the application may prematurely deselect the CS line and also
         * the next request can receive last character of previous request as its first character.
         */
        if (txSize > rxSize)
        {
            while (dummyRxCntr != (txSize - rxSize))
            {
                /* Wait for all the RX bytes to be received. */
                while ((bool)(SPI2STAT & _SPI2STAT_SPIRBE_MASK) == false)
                {
                    receivedData = SPI2BUF;
                    dummyRxCntr++;
                }
            }
        }

        isSuccess = true;
    }

    return isSuccess;
}
