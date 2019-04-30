#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "buttonalt.h"

//*****************************************************************************
//
//! \addtogroup buttons_api
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// Holds the current, debounced state of each button.  A 0 in a bit indicates
// that that button is currently pressed, otherwise it is released.
// We assume that we start with all the buttons released (though if one is
// pressed when the application starts, this will be detected).
//
//*****************************************************************************
//static uint8_t g_ui8ButtonStates = ALL_BUTTONS;

//*****************************************************************************
//
//! Polls the current state of the buttons and determines which have changed.
//!
//! \param pui8Delta points to a character that will be written to indicate
//! which button states changed since the last time this function was called.
//! This value is derived from the debounced state of the buttons.
//! \param pui8RawState points to a location where the raw button state will
//! be stored.
//!
//! This function should be called periodically by the application to poll the
//! pushbuttons.  It determines both the current debounced state of the buttons
//! and also which buttons have changed state since the last time the function
//! was called.
//!
//! In order for button debouncing to work properly, this function should be
//! caled at a regular interval, even if the state of the buttons is not needed
//! that often.
//!
//! If button debouncing is not required, the the caller can pass a pointer
//! for the \e pui8RawState parameter in order to get the raw state of the
//! buttons.  The value returned in \e pui8RawState will be a bit mask where
//! a 1 indicates the buttons is pressed.
//!
//! \return Returns the current debounced state of the buttons where a 1 in the
//! button ID's position indicates that the button is pressed and a 0
//! indicates that it is released.
//
//*****************************************************************************
void
ButtonsPoll(uint32_t *pui32Data_Left, uint32_t *pui32Data_Right)
{
    //uint32_t ui32Delta;
    //uint32_t ui32Data_Left;
    //uint32_t ui32Data_Right;
    //static uint8_t ui8SwitchClockA = 0;
    //static uint8_t ui8SwitchClockB = 0;

    //
    // Read the raw state of the push buttons.  Save the raw state
    // (inverting the bit sense) if the caller supplied storage for the
    // raw value.
    //


    *pui32Data_Left = ((ROM_GPIOPinRead(GPIO_PORTB_BASE, LEFT_BUTTON_B)) | (ROM_GPIOPinRead(GPIO_PORTA_BASE, LEFT_BUTTON_A))) ;

    *pui32Data_Right = ((ROM_GPIOPinRead(GPIO_PORTB_BASE, RIGHT_BUTTON_B)) | (ROM_GPIOPinRead(GPIO_PORTA_BASE, RIGHT_BUTTON_A))) ;


   /* if(pui8RawState)
    {
        *pui8RawState = (uint8_t)~ui32Data;
    }

    //
    // Determine the switches that are at a different state than the debounced
    // state.
    //
    ui32Delta = ui32Data ^ g_ui8ButtonStates;

    //
    // Increment the clocks by one.
    //
    ui8SwitchClockA ^= ui8SwitchClockB;
    ui8SwitchClockB = ~ui8SwitchClockB; 

    //
    // Reset the clocks corresponding to switches that have not changed state.
    //
    ui8SwitchClockA &= ui32Delta;
    ui8SwitchClockB &= ui32Delta;

    //
    // Get the new debounced switch state.
    //
    g_ui8ButtonStates &= ui8SwitchClockA | ui8SwitchClockB;
    g_ui8ButtonStates |= (~(ui8SwitchClockA | ui8SwitchClockB)) & ui32Data;

    //
    // Determine the switches that just changed debounced state.
    //
    ui32Delta ^= (ui8SwitchClockA | ui8SwitchClockB);

    //
    // Store the bit mask for the buttons that have changed for return to
    // caller.
    //
    if(pui8Delta)
    {
        *pui8Delta = (uint8_t)ui32Delta;
    }

    //
    // Return the debounced buttons states to the caller.  Invert the bit
    // sense so that a '1' indicates the button is pressed, which is a
    // sensible way to interpret the return value.
    */
    return;
}

//*****************************************************************************
//
//! Initializes the GPIO pins used by the board pushbuttons.
//!
//! This function must be called during application initialization to
//! configure the GPIO pins to which the pushbuttons are attached.  It enables
//! the port used by the buttons and configures each button GPIO as an input
//! with a weak pull-down.
//!
//! \return None.
//
//*****************************************************************************
void
ButtonsInit(void)
{
    //
    // Enable the GPIO port to which the pushbuttons are connected.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);



    //
    // Unlock PF0 so we can change it to a GPIO input
    // Once we have enabled (unlocked) the commit register then re-lock it
    // to prevent further changes.  PF0 is muxed with NMI thus a special case.
    //
    /*HWREG(BUTTONS_GPIO_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(BUTTONS_GPIO_BASE + GPIO_O_CR) |= 0x01;
    HWREG(BUTTONS_GPIO_BASE + GPIO_O_LOCK) = 0;*/

    //
    // Set each of the button GPIO pins as an input with a pull-up.
    //
    ROM_GPIODirModeSet(GPIO_PORTA_BASE, LEFT_BUTTON_A | RIGHT_BUTTON_A, GPIO_DIR_MODE_IN);
    MAP_GPIOPadConfigSet(GPIO_PORTA_BASE, LEFT_BUTTON_A | RIGHT_BUTTON_A,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);

    ROM_GPIODirModeSet(GPIO_PORTB_BASE, LEFT_BUTTON_B | RIGHT_BUTTON_B, GPIO_DIR_MODE_IN);
    MAP_GPIOPadConfigSet(GPIO_PORTB_BASE, LEFT_BUTTON_B | RIGHT_BUTTON_B,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);


    //
    // Initialize the debounced button state with the current state read from
    // the GPIO bank.
    //
  //  g_ui8ButtonStates = ROM_GPIOPinRead(BUTTONS_GPIO_BASE, ALL_BUTTONS);

  return;
}

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
