/*******************************************************************************
* File Name     : r_stdint.h
* Version       : 1.07
* Device(s)     : -
* Tool-Chain    : -
* H/W Platform  : -
* Description   : Integer type definition header file.
******************************************************************************/
/******************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 11.08.2011 1.00  First Release
*               : 12.12.2011 1.01  Add CX compiler
*               : 15.03.2012 1.02  Add GHS(Green Hills) __ghs__
*               : 17.01.2013 1.03  Fixed H8 compiler option "C89/C99"
*               : 13.05.2013 1.04  Add IAR(RL78) compiler. Add Define "far" and "near".
*               : 09.07.2014 1.05  Clean up.
*               : 18.09.2014 1.06  Add armcc compiler.
*               : 07.08.2015 1.07  Add ccrl compiler.
******************************************************************************/
#ifndef __r_stdint_h__
#define __r_stdint_h__

#include <limits.h>

#if defined(__RX) \
|| defined(__GNUC__)\
|| (defined(__H8__) && (__RENESAS_VERSION__ >= 0x0700) && (__STDC_VERSION__ == 199901L))\
|| (defined(_WIN32) && defined(_MSC_VER) && (_MSC_VER >= 1600))\
|| defined(__ICCRL78__)\
|| defined(__arm__)\
|| defined(__CCRL__)
#include <stdint.h>

#elif defined(_SH)\
|| defined(__K0R__)\
|| defined(__CA850__)\
|| defined(__ghs__)\
|| defined(__CX__)\
|| defined(__CA78K0__)\
|| defined(NC30)\
|| defined(NC308)\
|| defined(NC100)\
|| defined(__M32R__)\
|| (defined(__H8__) && (__RENESAS_VERSION__ < 0x0700))\
|| (defined(__H8__) && (__RENESAS_VERSION__ >= 0x0700) && (__STDC_VERSION__ != 199901L))\
|| defined(_WIN32) && defined(_MSC_VER) && (_MSC_VER < 1600)

typedef signed char         int8_t;
typedef unsigned char       uint8_t;
typedef signed short        int16_t;
typedef unsigned short      uint16_t;
typedef signed long         int32_t;
typedef unsigned long       uint32_t;

#if defined(_SH)\
|| defined(__CX__)\
|| defined(NC30)\
|| defined(NC308)\
|| defined(NC100)\
|| defined(__ghs__)\
|| defined(_WIN32) && defined(_MSC_VER) && (_MSC_VER < 1600)
typedef signed long long    int64_t;
typedef unsigned long long  uint64_t;
#endif

#endif

#if UINT_MAX == 0xffffU
typedef uint16_t natural_uint_t;
typedef int16_t  natural_int_t;
#else
typedef uint32_t natural_uint_t;
typedef int32_t  natural_int_t;
#endif

#endif


/* Defined FAR, NEAR */
#if !defined(near) || !defined(far)
#if defined(R8C) || defined(M16C) || defined(M32C)
/* R8C, M16C, M32C */
#define near near
#define far  far
#elif defined(__RL78__) || defined(__ICCRL78__)
/* RL78 */
#define near __near
#define far  __far
#else
/* Other (Needlessness) */
#define near
#define far
#endif
#endif

