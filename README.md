# MPC6050
capturing accelerometer raw values from a MPC6050 (gy-521 breakout board) (I2C) 

This project is written in c using Atmel Studio to read the accelerometer raw values(x,y,z) of MPC6050 sensor on the gy-521 breakout board.
This reads the accelerometer values and then writes them into the serial monitor through UART. The UART code is in the main.c file.

#ATMEGA2560 microchip is used here and the Two Wire Interface(I2C) is used to communicate with the gy-521 board.
The I2C code is inside the i2c_master.c file. 
