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
//  PB0         PB7
//  PB1         PB6
//  PA5         PA4
//  PA6         PA3
//  PA7         PA2
//
// Switch to BAT, Resistor divider w/ 3V3 to GPIO pins. Pull down resistor
//
//*****************************************************************************
#define BUTTONS_GPIO_PERIPH     SYSCTL_PERIPH_GPIOF
#define BUTTONS_GPIO_BASE       GPIO_PORTF_BASE

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

#define ALL_BUTTONS             (LEFT_BUTTON | RIGHT_BUTTON)

//*****************************************************************************
//
// Useful macros for detecting button events.
//
//*****************************************************************************
#define BUTTON_PRESSED(button, buttons, changed)                              \
        (((button) & (changed)) && ((button) & (buttons)))

#define BUTTON_RELEASED(button, buttons, changed)                             \
        (((button) & (changed)) && !((button) & (buttons)))


//*****************************************************************************
//
// Functions exported from buttons.c
//
//*****************************************************************************
extern void ButtonsInit(void);
extern uint8_t ButtonsPoll(uint8_t *pui8Delta,
                             uint8_t *pui8Raw);

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
