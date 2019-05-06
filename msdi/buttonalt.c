/*Texas A&M University
**Electronic Systems Engineering Technology
**ESET 420 Capstone II
**Author: Jonathan Noland
**File: buttonalt.c
**------------------------------------------------------------------------------
**This file contains the functions to use gpio to read buttons 
*/

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

/*Function Name: ButtonsPoll
**Description: Read GPIO status of buttons
**Parameters: pointer to variables for left and right side of board
**            
**Returns: Void
*/
void
ButtonsPoll(uint32_t *pui32Data_Left, uint32_t *pui32Data_Right)
{


    *pui32Data_Left = ((ROM_GPIOPinRead(GPIO_PORTB_BASE, LEFT_BUTTON_B)) | (ROM_GPIOPinRead(GPIO_PORTA_BASE, LEFT_BUTTON_A))) ;

    *pui32Data_Right = ((ROM_GPIOPinRead(GPIO_PORTB_BASE, RIGHT_BUTTON_B)) | (ROM_GPIOPinRead(GPIO_PORTA_BASE, RIGHT_BUTTON_A))) ;



    return;
}

/*Function Name: ButtonsInit
**Description: Prepare gpio for use as inputs
**Parameters: void
**            
**Returns: Void
*/
void
ButtonsInit(void)
{
    //
    // Enable the GPIO port to which the pushbuttons are connected.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);




    //
    // Set each of the button GPIO pins as an input with a pull-up.
    //
    ROM_GPIODirModeSet(GPIO_PORTA_BASE, LEFT_BUTTON_A | RIGHT_BUTTON_A, GPIO_DIR_MODE_IN);
    MAP_GPIOPadConfigSet(GPIO_PORTA_BASE, LEFT_BUTTON_A | RIGHT_BUTTON_A,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);

    ROM_GPIODirModeSet(GPIO_PORTB_BASE, LEFT_BUTTON_B | RIGHT_BUTTON_B, GPIO_DIR_MODE_IN);
    MAP_GPIOPadConfigSet(GPIO_PORTB_BASE, LEFT_BUTTON_B | RIGHT_BUTTON_B,
                         GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);




  return;
}
