#include <i2c_t3.h>


#define PRESSURE_SENSOR_ADRESS 0x78   // = 0b1111000
#define OUTMIN 0x0666
#define OUTMAX 0x6CCC
#define PMAX 25
#define SENSIVITY 1045.56    //25mb unidirekt
#define AIRDENSITY 1.2041

uint16_t rawPressure;
double newSpeed, Pressure, pressureh2o;

void setup()
{
	Wire.begin();
	Serial.begin(115200);
  /* add setup code here */

}

void loop()
{

	uint8_t msb, lsb;


	Wire.requestFrom(0x78, 2, I2C_STOP);
    while(Wire.available())   
    { 
		msb = Wire.read(); 
		lsb = Wire.read();
	}


	Serial.print(msb,HEX);
	Serial.print("\t");
	Serial.print(lsb,HEX);
	Serial.print("\t");

	


	rawPressure = (int)(msb << 8) | lsb;

	Serial.print(rawPressure,HEX);
	Serial.print("\t");


	Pressure = (rawPressure - OUTMIN) / SENSIVITY;

	pressureh2o = Pressure * 10.197;

	newSpeed = sqrt( 2 * Pressure / AIRDENSITY);

	Serial.print(Pressure);
	Serial.print(" mbar");
	Serial.print("\t");
	Serial.print(pressureh2o);
	Serial.print(" mmH2O");
	Serial.print("\t");
	Serial.print(newSpeed);
	Serial.println(" m/s");

	delay(100);

}



