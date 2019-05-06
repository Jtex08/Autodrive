/*Texas A&M University
**Electronic Systems Engineering Technology
**ESET 420 Capstone II
**Author: Jonathan Noland
**File: buttonalt.
**------------------------------------------------------------------------------
**Header file for functions and defines to use gpio to read buttons 
*/

#ifndef BUTTONALT_H
#define BUTTONALT_H


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
// Defines for the hardware resources used by the pushbuttons.
//
// The switches are on the following ports/pins:
//
//  PB0  BTN1       PB7 BTN6
//  PB1  BTN2       PB6 BTN7
//  PA5  BTN3       PA4 BTN8
//  PA6  BTN4       PA3 BTN9
//  PA7  BTN5       PA2 BTN10
//
// Switch to BAT, Resistor divider w/ 3V3 to GPIO pins. Pull down resistor
//
//*****************************************************************************


#define NUM_BUTTONS             10
#define BTN_ONE                 GPIO_PIN_0
#define BTN_TWO                 GPIO_PIN_1
#define BTN_THREE               GPIO_PIN_5
#define BTN_FOUR                GPIO_PIN_6
#define BTN_FIVE                GPIO_PIN_7
#define BTN_SIX                 GPIO_PIN_7
#define BTN_SEVEN               GPIO_PIN_6
#define BTN_EIGHT               GPIO_PIN_4
#define BTN_NINE                GPIO_PIN_3
#define BTN_TEN                 GPIO_PIN_2

#define RIGHT_BUTTON            GPIO_PIN_0

#define LEFT_BUTTON_B           (BTN_ONE | BTN_TWO)
#define LEFT_BUTTON_A           (BTN_THREE | BTN_FOUR | BTN_FIVE)
#define RIGHT_BUTTON_B          (BTN_SIX | BTN_SEVEN)
#define RIGHT_BUTTON_A          (BTN_EIGHT | BTN_NINE | BTN_TEN)


#define ALL_BUTTONS             (LEFT_BUTTON | RIGHT_BUTTON)



//*****************************************************************************
//
// Functions exported from buttonalt.c
//
//*****************************************************************************
extern void ButtonsInit(void);
extern void ButtonsPoll(uint32_t *pui32Data_Left,
                             uint32_t *pui32Data_Right);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

//*****************************************************************************
//
// Prototypes for the globals exported by this driver.
//
//*****************************************************************************

#endif  // ROSSERIAL_TIVAC_TUTORIALS_BUTTONS_BUTTONS_H
