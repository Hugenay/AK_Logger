

#include <i2c_t3.h>
#include <SD.h>




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

volatile bool SensorFlag, SensorFlagCpy, LogFlag, LogFlagCpy;


void setup()
{
	// Open serial communications
	Serial.begin(115200);
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

	// make sure that the default chip select pin is set to
	// output, even if you don't use it:
	pinMode(10, OUTPUT);
	// see if the card is present and can be initialized:
	if (!SD.begin(chipSelect)) {
		Serial.println("Card failed, or not present");
		// don't do anything more:
		return;
	
	}

	Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);

	LogTimer.begin(log2SD,10000);
	delay(1);
	SensorTimer.begin(getSensorData,10000);
}


void loop()
{

	noInterrupts();
	SensorFlagCpy = SensorFlag;
	LogFlagCpy = LogFlag;
	SensorFlag = false;
	LogFlag = false;
	interrupts();


	if (SensorFlagCpy)
	{

		uint8_t msb, lsb;	
		dataString = "";

		for (int i = 1; i <= 3; i++) {

			SelectChannel(i);

			Wire.requestFrom(PRESSURE_SENSOR_ADRESS, 2, I2C_STOP);

			while(Wire.available())  
			{ 
				msb = Wire.read(); 
				lsb = Wire.read();
			}

			rawPressure = (int)(msb << 8) | lsb;
			//Pressure = (rawPressure - OUTMIN) / SENSIVITY; 

			dataString += String(rawPressure) + "\n" ;

		} 



		//dataString =  "\t" + dataString; // mircos() entfernt

		Serial.println(dataString);

		SensorFlagCpy = false;

	}

	if (LogFlagCpy && dataString.length()==512)
	{

		File dataFile = SD.open("data.txt", O_CREAT | O_APPEND | O_WRITE);

		if (dataFile) {
			dataFile.println(dataString);
			dataFile.close();
		}
		else {
			Serial.println("Save fail");
		}

		LogFlagCpy = false;

	}
	
}




void getSensorData(){

	SensorFlag = true;

}


void log2SD(){

	LogFlag = true;

}

void SelectChannel (int channel){
	int controlPin[] = {s0, s1, s2, s3};

	int muxChannel[16][4]={
		{0,0,0,0}, //channel 0
		{1,0,0,0}, //channel 1
		{0,1,0,0}, //channel 2
		{1,1,0,0}, //channel 3
		{0,0,1,0}, //channel 4
		{1,0,1,0}, //channel 5
		{0,1,1,0}, //channel 6
		{1,1,1,0}, //channel 7
		{0,0,0,1}, //channel 8
		{1,0,0,1}, //channel 9
		{0,1,0,1}, //channel 10
		{1,1,0,1}, //channel 11
		{0,0,1,1}, //channel 12
		{1,0,1,1}, //channel 13
		{0,1,1,1}, //channel 14
		{1,1,1,1}  //channel 15
	};

	//loop through the 4 sig
	for(int i = 0; i < 4; i ++){
		digitalWrite(controlPin[i], muxChannel[channel][i]);
	}
}

