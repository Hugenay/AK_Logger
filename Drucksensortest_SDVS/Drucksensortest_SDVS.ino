




#include <SdFat.h>

#include <i2c_t3.h>
#define PRESSURE_SENSOR_ADRESS 0x78   // = 0b1111000
#define OUTMIN 0x0666
#define OUTMAX 0x6CCC
#define PMAX 25
#define SENSIVITY 1045.56    //25mb unidirekt
#define AIRDENSITY 1.2041

//Mux control pins
int s0 = 5;
int s1 = 6;
int s2 = 7;
int s3 = 8;

uint16_t rawPressure;
const int chipSelect = 10; //Adafruit SD-Board

String dataString;
IntervalTimer SensorTimer;
IntervalTimer LogTimer;

SdFat sd;
SdFile file;

volatile bool SensorFlag, SensorFlagCpy, LogFlag, LogFlagCpy;


void setup()
{
	// Open serial communications

	Serial.begin(115200);
	while (!Serial);
	Serial.println("Serial open");

	//Mux pinout setup
	pinMode(s0, OUTPUT);
	pinMode(s1, OUTPUT);
	pinMode(s2, OUTPUT);
	pinMode(s3, OUTPUT);

	digitalWrite(s0, LOW);
	digitalWrite(s1, LOW);
	digitalWrite(s2, LOW);
	digitalWrite(s3, LOW);




	pinMode(10, OUTPUT);

	if (!sd.begin(chipSelect, SPI_FULL_SPEED)) {			// initalisiert SPI und die SD-Karte)
		Serial.println("Card failed, or not present");
	}
	else{
		Serial.println("Card available");
	}





	Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);
	Serial.println("Wire online");
	LogTimer.begin(log2SD, 10000);
	Serial.println("LogTimer online");
	delay(1);
	SensorTimer.begin(getSensorData, 10000);
	Serial.println("SensorTimer online");
}


void loop()
{
	long time3 = 0;
	noInterrupts();
	SensorFlagCpy = SensorFlag;
	LogFlagCpy = LogFlag;
	SensorFlag = false;
	LogFlag = false;
	interrupts();
	double time1 = micros();

	if (SensorFlagCpy)
	{
		time3 = micros();

		dataString = "";
		dataString += String(time3) + "\t";
		for (int i = 0; i <= 16; i++) {

			uint8_t msb = 0, lsb = 0;
			SelectChannel(i);

			Wire.requestFrom(PRESSURE_SENSOR_ADRESS, 2, I2C_STOP);

			while (Wire.available())
			{
				msb = Wire.read();
				lsb = Wire.read();
			}

			rawPressure = (int)(msb << 8) | lsb;
			//Pressure = (rawPressure - OUTMIN) / SENSIVITY;
			dataString += String(rawPressure) + "\t";



		}
		dataString += "\n";
		Serial.println(dataString);


		SensorFlagCpy = false;


	}

	if (LogFlagCpy)
	{

		// File dataFile = SD.open("data.txt", O_CREAT | O_APPEND | O_WRITE);
		file.open(sd.vwd(), "data3.txt", O_CREAT | O_APPEND | O_WRITE);
		if (file.isOpen()) {
			file.print(dataString);
			file.close();
		}
		else {
			Serial.println("Save fail");
		}

		LogFlagCpy = false;

	}

	double time2 = micros();
	//Serial.println(time2 - time1); 
	//Serial.println(time3);
}




void getSensorData(){

	SensorFlag = true;

}


void log2SD(){

	LogFlag = true;

}

void SelectChannel(int channel){
	int controlPin[] = { s0, s1, s2, s3 };

	int muxChannel[16][4] = {
		{ 0, 0, 0, 0 }, //channel 0
		{ 1, 0, 0, 0 }, //channel 1
		{ 0, 1, 0, 0 }, //channel 2
		{ 1, 1, 0, 0 }, //channel 3
		{ 0, 0, 1, 0 }, //channel 4
		{ 1, 0, 1, 0 }, //channel 5
		{ 0, 1, 1, 0 }, //channel 6
		{ 1, 1, 1, 0 }, //channel 7
		{ 0, 0, 0, 1 }, //channel 8
		{ 1, 0, 0, 1 }, //channel 9
		{ 0, 1, 0, 1 }, //channel 10
		{ 1, 1, 0, 1 }, //channel 11
		{ 0, 0, 1, 1 }, //channel 12
		{ 1, 0, 1, 1 }, //channel 13
		{ 0, 1, 1, 1 }, //channel 14
		{ 1, 1, 1, 1 }  //channel 15
	};

	//loop through the 4 sig
	for (int i = 0; i < 4; i++){
		digitalWrite(controlPin[i], muxChannel[channel][i]);
	}
}


