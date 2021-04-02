/*******************************************************************************
  SPI PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_spi1_master.c

  Summary:
    SPI1 Master Source File

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

#include "plib_spi1_master.h"

// *****************************************************************************
// *****************************************************************************
// Section: SPI1 Implementation
// *****************************************************************************
// *****************************************************************************


#define SPI1_CON_MSTEN                      (1 << _SPI1CON_MSTEN_POSITION)
#define SPI1_CON_CKP                        (0 << _SPI1CON_CKP_POSITION)
#define SPI1_CON_CKE                        (1 << _SPI1CON_CKE_POSITION)
#define SPI1_CON_MODE_32_MODE_16            (0 << _SPI1CON_MODE16_POSITION)
#define SPI1_CON_ENHBUF                     (1 << _SPI1CON_ENHBUF_POSITION)
#define SPI1_CON_MCLKSEL                    (0 << _SPI1CON_MCLKSEL_POSITION)
#define SPI1_CON_MSSEN                      (0 << _SPI1CON_MSSEN_POSITION)
#define SPI1_CON_SMP                        (0 << _SPI1CON_SMP_POSITION)

void SPI1_Initialize ( void )
{
    uint32_t rdata;

    /* Disable SPI1 Interrupts */
    IEC3CLR = 0x2000;
    IEC3CLR = 0x4000;
    IEC3CLR = 0x8000;

    /* STOP and Reset the SPI */
    SPI1CON = 0;

    /* Clear the Receiver buffer */
    rdata = SPI1BUF;
    rdata = rdata;

    /* Clear SPI1 Interrupt flags */
    IFS3CLR = 0x2000;
    IFS3CLR = 0x4000;
    IFS3CLR = 0x8000;

    /* BAUD Rate register Setup */
    SPI1BRG = 4;

    /* CLear the Overflow */
    SPI1STATCLR = _SPI1STAT_SPIROV_MASK;

    /*
    MSTEN = 1
    CKP = 0
    CKE = 1
    MODE<32,16> = 0
    ENHBUF = 1
    MSSEN = 0
    MCLKSEL = 0
    */
    SPI1CONSET = (SPI1_CON_MSSEN | SPI1_CON_MCLKSEL | SPI1_CON_ENHBUF | SPI1_CON_MODE_32_MODE_16 | SPI1_CON_CKE | SPI1_CON_CKP | SPI1_CON_MSTEN | SPI1_CON_SMP);

    /* Enable transmit interrupt when transmit buffer is completely empty (STXISEL = '01') */
    /* Enable receive interrupt when the receive buffer is not empty (SRXISEL = '01') */
    SPI1CONSET = 0x00000005;


    /* Enable SPI1 */
    SPI1CONSET = _SPI1CON_ON_MASK;
}

bool SPI1_TransferSetup (SPI_TRANSFER_SETUP* setup, uint32_t spiSourceClock )
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

    if(t_brg > 8191)
    {
        return false;
    }

    SPI1BRG = t_brg;
    SPI1CON = (SPI1CON & (~(_SPI1CON_MODE16_MASK | _SPI1CON_MODE32_MASK | _SPI1CON_CKP_MASK | _SPI1CON_CKE_MASK))) |
                            (setup->clockPolarity | setup->clockPhase | setup->dataBits);

    return true;
}

bool SPI1_Write(void* pTransmitData, size_t txSize)
{
    return(SPI1_WriteRead(pTransmitData, txSize, NULL, 0));
}

bool SPI1_Read(void* pReceiveData, size_t rxSize)
{
    return(SPI1_WriteRead(NULL, 0, pReceiveData, rxSize));
}

bool SPI1_WriteRead(void* pTransmitData, size_t txSize, void* pReceiveData, size_t rxSize)
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
        SPI1STATCLR = _SPI1STAT_SPIROV_MASK;

        /* Flush out any unread data in SPI read buffer from the previous transfer */
        while ((bool)(SPI1STAT & _SPI1STAT_SPIRBE_MASK) == false)
        {
            receivedData = SPI1BUF;
        }

        if (rxSize > txSize)
        {
            dummySize = rxSize - txSize;
        }

        /* If dataBit size is 32 bits */
        if (_SPI1CON_MODE32_MASK == (SPI1CON & _SPI1CON_MODE32_MASK))
        {
            rxSize >>= 2;
            txSize >>= 2;
            dummySize >>= 2;
        }
        /* If dataBit size is 16 bits */
        else if (_SPI1CON_MODE16_MASK == (SPI1CON & _SPI1CON_MODE16_MASK))
        {
            rxSize >>= 1;
            txSize >>= 1;
            dummySize >>= 1;
        }

        /* Make sure transmit buffer is empty */
        while((bool)(SPI1STAT & _SPI1STAT_SPITBE_MASK) == false);

        while ((txCount != txSize) || (dummySize != 0))
        {
            if (txCount != txSize)
            {
                if((_SPI1CON_MODE32_MASK) == (SPI1CON & (_SPI1CON_MODE32_MASK)))
                {
                    SPI1BUF = ((uint32_t*)pTransmitData)[txCount++];
                }
                else if((_SPI1CON_MODE16_MASK) == (SPI1CON & (_SPI1CON_MODE16_MASK)))
                {
                    SPI1BUF = ((uint16_t*)pTransmitData)[txCount++];
                }
                else
                {
                    SPI1BUF = ((uint8_t*)pTransmitData)[txCount++];
                }
            }
            else if (dummySize > 0)
            {
                SPI1BUF = 0xff;
                dummySize--;
            }

            if (rxCount == rxSize)
            {
                /* If inside this if condition, then it means that txSize > rxSize and all RX bytes are received */

                /* For transmit only request, wait for buffer to become empty */
                while((bool)(SPI1STAT & _SPI1STAT_SPITBE_MASK) == false);

                /* Read until the receive buffer is not empty */
                while ((bool)(SPI1STAT & _SPI1STAT_SPIRBE_MASK) == false)
                {
                    receivedData = SPI1BUF;
                    dummyRxCntr++;
                }
            }
            else
            {
                /* If data is read, wait for the Receiver Data the data to become available */
                while((SPI1STAT & _SPI1STAT_SPIRBE_MASK) == _SPI1STAT_SPIRBE_MASK);

                /* We have data waiting in the SPI buffer */
                receivedData = SPI1BUF;

                if (rxCount < rxSize)
                {
                    if((_SPI1CON_MODE32_MASK) == (SPI1CON & (_SPI1CON_MODE32_MASK)))
                    {
                        ((uint32_t*)pReceiveData)[rxCount++]  = receivedData;
                    }
                    else if((_SPI1CON_MODE16_MASK) == (SPI1CON & (_SPI1CON_MODE16_MASK)))
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
        while ((bool)((SPI1STAT & _SPI1STAT_SRMT_MASK) == false));

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
                while ((bool)(SPI1STAT & _SPI1STAT_SPIRBE_MASK) == false)
                {
                    receivedData = SPI1BUF;
                    dummyRxCntr++;
                }
            }
        }

        isSuccess = true;
    }

    return isSuccess;
}
