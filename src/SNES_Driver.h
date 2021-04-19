#ifndef SNES_Driver
#define SNES_Driver

// Global Definitions for the GPIO Registers.
#define GPLEV0 13
#define GPSET0 7
#define GPCLR0 10

// Global Definitions for the CLOCK, LATCH, & DATA line Pin Number.
#define CLK 11
#define LAT 9
#define DAT 10

/* Prototypes */

void INP_GPIO(int pin, unsigned int *gpioptr);
void OUT_GPIO(int pin, unsigned int *gpioptr);
void Init_GPIO(unsigned int *gpioptr);
void Write_Latch(int write, unsigned int *gpioptr);
void Write_Clock(int write, unsigned int *gpioptr);
int Read_Data(unsigned int *gpioptr);
void Read_SNES(unsigned int *gpioptr, int buttonArray[16]);
void resetButtonArray(int buttonArray[16]);
int buttonPressed(int buttonArray[16]);
int getButtonPressed(unsigned int *gpioptr);

#endif