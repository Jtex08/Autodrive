/*Texas A&M University
**Electronic Systems Engineering Technology
**ESET 420 Capstone II
**Author: Jonathan Noland
**File: msdi.h
**------------------------------------------------------------------------------
**This file contains the definitions and includes neccessary to use the TIC-10024-Q1 
*/

#ifndef __MSDI_H__
#define __MSDI_H__

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

/*
* Error codes.
*/
typedef enum
{
    MSDI_STATUS_SUCCESS          = 0U,    /*!< No error. */
    MSDI_STATUS_SPI_INIT         = 1U,    /*!< SPI initialization failure. */
    MSDI_STATUS_COMM_ERROR       = 2U     /*!< Error in communication. */
} msdi_status_t;


/*
**Parity code
*/
typedef enum
{
    LEAVE_PARITY_BIT                  = 0U,
    SET_PARITY_BIT                    = 1U 
} msdi_parity_t;



//*****************************************************************************
//
// The following values define the registers for the MSDI
//
//*****************************************************************************
#define DEVICE_ID               0x01000000  // Device ID Register
#define INT_STAT                0x02000000  // Interrupt Status Register
#define CRC                     0x03000000  // CRC Result Register
#define IN_STAT_MISC            0x04000000  // Misc Status Register
#define IN_STAT_COMP            0x05000000  // Comparator Status Register
#define CONFIG                  0x1A000000  // Device Global Configuration Register
#define IN_EN                   0x1B000000  // Input Enable Register
#define CS_SELECT               0x1C000000  // Current Source/Sink Selection Register
#define WC_CFG0                 0x1D000000  // Wetting Current Configuration Register
#define WC_CFG1                 0x1E000000  // Wetting Current Configuration Register
#define CCP_CFG0                0x1F000000  // Clean Current Polling Register
#define CCP_CFG1                0x20000000  // Clean Current Polling Register
#define THRES_COMP              0x21000000  // Comparator Threshold Control Register
#define INT_EN_COMP1            0x22000000  // Comparator Input Interrupt Generation Control Register
#define INT_EN_COMP2            0x23000000  // Comparator Input Interrupt Generation Control Register
#define INT_EN_CFG0             0x24000000  // Global Interrupt Generation Control Register

//*****************************************************************************
//
// The following values define the Read/Write Masks
//
//*****************************************************************************
#define MSDI_REG_R_MASK             0x7E000000  // Read register mask MSB set to 0, 6 register ID Bits, rest 0 prior to Parity
#define MSDI_REG_RW_W               0x80000000  // Write register mask MSB set to 1

/*****************************************************************************
* Number of data iterations for complete 32 bit send and receive.
****************************************************************************/
#define NUM_SSI_DATA            2

/*******************************************************************************
 *Parity Bit Masks
 ******************************************************************************/
#define SET_PARITY_BIT_MASK        0x00000001 //Parity bit mask if raw value has even parity set bit to 1

/*******************************************************************************
 *Transfer Masks
 ******************************************************************************/
#define LOWER_TRANSFER_MASK        0x0000FFFF //Mask lower 16 bits for transfer

/*******************************************************************************
 *Fault status register
 ******************************************************************************/

#define MSDI_POR_STAT_MASK                    (0x00000080U)/*Power on reset mask*/
#define MSDI_SPI_FAIL_MASK                    (0x00000040U)/*SPI Comm fail*/
#define MSDI_PRTY_FAIL_MASK                   (0x00000020U)/*Parity fail mask*/
#define MSDI_SSC_MASK                         (0x00000010U)/*Switch state change*/
#define MSDI_RES_MASK                         (0x00000008U)/*Reserved and always at 0*/
#define MSDI_TEMP_MASK                        (0x00000004U)/*Temperature event mask*/
#define MSDI_OI_MASK                          (0x00000002U)/*Other interrupt*/


//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

/*Function Name: TEST_FUNC
**Description: Test function
**Parameters: ui32Register = register name
**            ui32DataRX = pointer to storing value
**Returns: Will change according to need
*/
uint32_t TEST_FUNC(uint32_t ui32Register,uint32_t pui32DataRx[NUM_SSI_DATA]);



//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif /* __MSDI_H__ */
