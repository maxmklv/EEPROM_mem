#include <stdint.h> // integer types and widths
#include <stdbool.h> // Boolean types
#include "inc/hw_types.h" // common types
#include "inc/hw_memmap.h" // memory map for Tiva
#include "driverlib/sysctl.h" // system control driver
#include "driverlib/gpio.h" // GPIO API
#include "driverlib/pin_map.h"
#include "driverlib/debug.h"
#include "driverlib/eeprom.h"

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0);
    SysCtlDelay(20000000);

    uint32_t pui32Data[2];
    uint32_t pui32Read[2];

    pui32Data[0] = 0x12345678;
    pui32Data[1] = 0x56789abc;

    // Erase the block of code identified earlier
    FlashErase(0x10000);

    // Programs the data array we created, to the start of the block, of the length of the array
    FlashProgram(pui32Data, 0x10000, sizeof(pui32Data));

    // Lights the red LED to indicate success
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_1);

    // Delays about two seconds before the program traps in the while(1) loop.
    SysCtlDelay(26666666);

    // Turn on the EEPROM peripheral
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);

    // Perform a recovery if power failed during a previous write operation
    EEPROMInit();

    // Erase the entire EEPROM
    EEPROMMassErase();

    // Read the erased values into offset address
    EEPROMRead(pui32Read, 0x0, sizeof(pui32Read));

    // Program the data array, to the beginning of EEPROM, of the length of the array
    EEPROMProgram(pui32Data, 0x0, sizeof(pui32Data));

    // Read that data into array puiRead
    EEPROMRead(pui32Read, 0x0, sizeof(pui32Read));

    // Turn off the red LED
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x0);

    // Turn on the blue LED
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, GPIO_PIN_2);

    while(1)
    {

    }

}
