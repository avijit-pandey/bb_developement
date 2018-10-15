/*
* Project Name: eYRC_BB_2403_Task1_Sensing
* File Name: gyro.h
*
* Created: 04-Dec-16 7:56:40 PM
* Author : Heethesh Vhavle
*
* Team: eYRC-BB#2403
* Theme: Balance Bot
*
* Library for L3G4200D Gyroscope
*/

#ifndef GYRO_H_
#define GYRO_H_

// Register Map
#define L3G4200D_ADDRESS		0x69 << 1	
#define L3G4200D_WHO_AM_I		0x0F
#define L3G4200D_KNOWN_ID		0xD3
#define L3G4200D_CTRL_REG1		0x20
#define L3G4200D_CTRL_REG4		0x23
#define L3G4200D_OUT_X_L		0x28
#define L3G4200D_OUT_Y_L		0x2A

// Function Declarations
void gyro_init();
float convert_gyro(unsigned int value, float offset);
float read_gyro();
float get_gyro_pitch_angle(unsigned long current_time, float pitch_angle);
//void calibrate_gyro();

#endif