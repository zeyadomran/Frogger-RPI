#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "initGPIO.h"
#include "SNES_Driver.h"
#include <time.h>

/**
    INP_GPIO sets a Pin to be an Input.
    @param pin, pin is an integer which stores the location of the pin you want to be an input.
    @param *gpioptr, *gpioptr stores the GPIO base.
*/
void INP_GPIO(int pin, unsigned int *gpioptr) { *(gpioptr + (pin / 10)) &= ~(7 << (pin % 10) * 3); }

/**  
    OUT_GPIO sets a Pin to be an output.
    @param pin, pin is an integer which stores the location of the pin you want to be an output.
    @param *gpioptr, *gpioptr stores the GPIO base.
*/
void OUT_GPIO(int pin, unsigned int *gpioptr) { *(gpioptr + (pin / 10)) |= (1 << (pin % 10) * 3); }

/**  
    Init_GPIO initializes all three pins that are used by the SNES Controller to Input or Output.
    @param *gpioptr, *gpioptr stores the GPIO base.
*/
void Init_GPIO(unsigned int *gpioptr) {
    // Initializing Clock
    INP_GPIO(CLK, gpioptr);
    OUT_GPIO(CLK, gpioptr);
    // Initializing Latch
    INP_GPIO(LAT, gpioptr);
    OUT_GPIO(LAT, gpioptr);
    // Initializing Data
    INP_GPIO(DAT, gpioptr);
}

/**  
    Write_Latch writes to the Latch pin a 0 or a 1.
    @param write, write is used to store whether you wish to write a 1 or 0.
    @param *gpioptr, *gpioptr stores the GPIO base.
*/
void Write_Latch(int write, unsigned int *gpioptr) { 
    if(write == 1) {
        gpioptr[GPSET0] = 1 << LAT;
    } else {
        gpioptr[GPCLR0] = 1 << LAT;
    }
}

/**  
    Write_Clock writes to the Clock pin a 0 or a 1.
    @param write, write is used to store whether you wish to write a 1 or 0.
    @param *gpioptr, *gpioptr stores the GPIO base.
*/
void Write_Clock(int write, unsigned int *gpioptr) {
    if(write == 1) {
        gpioptr[GPSET0] = 1 << CLK;
    } else {
        gpioptr[GPCLR0] = 1 << CLK;
    }
}

/**  
    Read_Data reads from the Data to see whether it stored a 0 or a 1 at its current location.
    @param *gpioptr, *gpioptr stores the GPIO base.
    @return Read_Data returns the value stored in the current location of the Data pin.
*/
int Read_Data(unsigned int *gpioptr) { return (gpioptr[GPLEV0] >> DAT) & 1; }

/**  
    Read_SNES reads whether any buttons are pressed and updates the buttonArray.
    @param *gpioptr, *gpioptr stores the GPIO base.
    @param buttonArray[16], buttonArray is used to store the state of each button, it could be a 1 or 0.
*/
void Read_SNES(unsigned int *gpioptr, int buttonArray[16]) {
    Write_Clock(1, gpioptr);
    Write_Latch(1, gpioptr);
    delayMicroseconds(12);
    Write_Latch(0, gpioptr);
    int i = 1;
    while(i <= 16) {
        delayMicroseconds(6);
        Write_Clock(0, gpioptr);
        delayMicroseconds(6);
        buttonArray[i - 1] = Read_Data(gpioptr);
        Write_Clock(1, gpioptr);
        i++;
    }
}

/**  
    resetButtonArray resets the values buttonArray.
    @param buttonArray[16], buttonArray is the array we wish to reset.
*/
void resetButtonArray(int buttonArray[16]) { for(int i = 0; i < 16; i++) buttonArray[i] = 1; }

/**  
    buttonPressed checks which button was pressed.
    @param buttonArray[16], buttonArray is the array we wish to check.
    @return the button pressed : -1 if no buttons were pressed.
*/
int buttonPressed(int buttonArray[16]) {
    for(int i = 0; i < 16; i++) {
        if(buttonArray[i] == 0) {
            return i + 1;
        }
    }
    return -1;
}

/**  
    Gets the latest button pressed.
    @return the button pressed : -1 if no button was pressed.
*/
int getButtonPressed(unsigned int *gpioPtr) {
    int buttonArray[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; 
    int button = -1;
    Read_SNES(gpioPtr, buttonArray);
    button = buttonPressed(buttonArray);
    resetButtonArray(buttonArray);
    delay(175);
    return button;
}
