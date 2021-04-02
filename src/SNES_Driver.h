#ifndef SNES_Driver
#define SNES_Driver

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
int getButtonPressed(void);

#endif