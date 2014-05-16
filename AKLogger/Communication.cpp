#include "Communication.h"


Communication::Communication(void)
{
}


Communication::~Communication(void)
{
}




/*! \brief read from a I2C device
	
	 \param error Error code:
-10 = could not open connection
-11 = buffer size is diffrent than expected


*/
int Communication::i2cread(int Sensor_Adress, int Register_Adress, uint8_t *buffer, int size)
{
	while (Wire.available()) {
		int i, n, error;

		Wire.beginTransmission(Sensor_Adress);
		n = Wire.write(Register_Adress);
		if (n != 1)
			return (-10);

		n = Wire.endTransmission(false);    // hold the I2C-bus
		if (n != 0)
			return (n);

		// Third parameter is true: relase I2C-bus after data is read.
		Wire.requestFrom(Sensor_Adress, size, true);
		i = 0;
		while(Wire.available() && i<size)
		{
			buffer[i++]=Wire.read();
		}
		if ( i != size)
			return (-11);

		return (0);  // return : no error
	}
}




/*! \brief write to an I2C device

	\param error Error Code:
-20 = could not open connection
-21 = could not write to to device

*/
int Communication::i2cwrite(int Sensor_Adress, int Register_Adress, uint8_t *pData){

	int n, error;

	Wire.beginTransmission(Sensor_Adress);
	n = Wire.write(Register_Adress);        // write the start address
	if (n != 1)
		return (-20);

	n = Wire.write(pData, 1);  // write data bytes
	if (n != 1)
		return (-21);

	error = Wire.endTransmission(true); // release the I2C-bus
	if (error != 0)
		return (error);

	return (0);         // return : no error
}
