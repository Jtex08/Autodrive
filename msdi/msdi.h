//Defines and Macros for MSDI


#ifndef __MSDI_H__
#define __MSDI_H__

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
#define MSDI_REG_RW_R               0x00000000  // Read register mask MSB set to 0
#define MSDI_REG_RW_W               0x80000000  // Write register mask MSB set to 1



//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************





//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __MSDI_H__