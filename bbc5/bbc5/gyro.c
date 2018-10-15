/*
* Project Name: eYRC_BB_2403_Task1_Sensing
* File Name: gyro.c
*
* Created: 04-Dec-16 7:56:40 PM
* Author : Heethesh Vhavle
*
* Team: eYRC-BB#2403
* Theme: Balance Bot
*
* Library for L3G4200D Gyroscope
*
* Functions: gyro_init(), convert_gyro(), read_gyro(), get_gyro_angle(), calibrate_gyro()
* Global Variables: txf, last_time, x_offset, y_offset, z_offset
*/
#define F_CPU 14745600
#include "i2c_lib.h"
//#include "SCILAB.h"
//#include "../Support/support_lib.h"
#include "gyro.h"

//struct txFrame txf;
unsigned long last_time=0;

// Gyroscope Offsets
float x_offset = -0.04372;
float y_offset = 0.93170;
float z_offset = 0.28436;

/**********************************
Function name	:	gyro_init
Functionality	:	Initialize the gyroscope
Arguments		:	none
Return Value	:	void
Example Call	:	gyro_init()
***********************************/
void gyro_init()
{
	//check_device_ID(L3G4200D_ADDRESS, L3G4200D_WHO_AM_I, L3G4200D_KNOWN_ID);	// Verify Device ID
	check_status(i2c_sendbyte(L3G4200D_ADDRESS, L3G4200D_CTRL_REG1, 0x1F));		// 100Hz, 25Hz, Normal Mode
	check_status(i2c_sendbyte(L3G4200D_ADDRESS, L3G4200D_CTRL_REG4, 0xB0));		// 2000dps
}

/**********************************
Function name	:	calibrate_gyro
Functionality	:	Reads values of Gyroscope when static, computes average offset
Arguments		:	None
Return Value	:	void
Example Call	:	calibrate_gyro()
***********************************/
/*void calibrate_gyro()
{	
	int n=0;
	float xsum=0, ysum=0, zsum=0;
	while(n<1000)
	{
		read_gyro();
		xsum += xg_rate;
		ysum += yg_rate;
		zsum += zg_rate;
		txf.num = n;
		send_data_frame(&txf);
		n++;
	}	
	
	txf.XB = (float)(xsum)*0.001;
	txf.YB = (float)(ysum)*0.001;
	txf.ZB = (float)(zsum)*0.001;
	send_data_frame(&txf);	
}*/

/**********************************
Function name	:	convert_gyro
Functionality	:	Converts raw 2's compliment gyroscope readings to DPS, removes offset error
Arguments		:	Raw gyroscope reading, offset error value
Return Value	:	Angular velocity in DPS
Example Call	:	convert_gyro(X_DATA, X_OFFSET)
***********************************/
float convert_gyro(unsigned int value, float offset)
{
	float angle_rate;
	
	// Convert 2's compliment to float value
	if (value>32767) angle_rate = (float)(value-65536);
	else angle_rate = (float)value;
	
	// Convert RPS to DPS and remove offsets
	angle_rate = 0.07*angle_rate - offset;
	return angle_rate;
}

/**********************************
Function name	:	read_gyro
Functionality	:	To read Y-axis angular velocity from Gyroscope
Arguments		:	none
Return Value	:	Raw angular velocity
Example Call	:	read_gyro()
***********************************/
float read_gyro()
{	
	float yg_rate=0;
	UINT8 gyro_data[2] = {0, 0};
	
	// Read gyroscope data
	check_status(i2c_read_multi_byte(L3G4200D_ADDRESS, L3G4200D_OUT_Y_L, 2, gyro_data));
	
	// Combine low and high bytes
	yg_rate = convert_gyro((gyro_data[0] | gyro_data[1]<<8), y_offset);
	
	return yg_rate;
}

/**********************************
Function name	:	get_gyro_angle
Functionality	:	Computes the angular position by integrating angular velocity
Arguments		:	Current program time, current combined pitch angle
Return Value	:	Gyroscope pitch angle
Example Call	:	get_gyro_angle(epoch(), tilt_angle)
***********************************/
float get_gyro_pitch_angle(unsigned long current_time, float pitch_angle)
{
	float gyro_pitch_angle=0, delta=0, rate=0;
	
	rate = read_gyro();									// Read from gyroscope
	delta = (float)(current_time - last_time); //*0.001;	// Time elapsed in seconds
	gyro_pitch_angle = (rate*delta) + pitch_angle;			// Integrating angular velocity
	last_time = current_time;							// Save current time for next iteration

	return gyro_pitch_angle;
}

/**********************************
Function name	:	get_gyro_angle
Functionality	:	Computes the angular position by integrating angular velocity
Arguments		:	Current program time, current combined pitch angle
Return Value	:	Gyroscope pitch angle
Example Call	:	get_gyro_angle(epoch(), tilt_angle)
***********************************/
float get_gyro_roll_angle(unsigned long current_time, float roll_angle)
{
	float gyro_roll_angle=0, delta=0, rate=0;
	
	rate = read_gyro();									// Read from gyroscope
	delta = (float)(current_time - last_time)*0.001;	// Time elapsed in seconds
	gyro_roll_angle = (rate*delta) + roll_angle;			// Integrating angular velocity
	last_time = current_time;							// Save current time for next iteration

	return gyro_roll_angle;
}