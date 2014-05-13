
#include <i2c_t3.h>
#include <SD.h>

unsigned long time1, time2;

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
double newSpeed, Pressure, pressureh2o;
const int chipSelect = 10; //Adafruit SD-Board

//byte pinTable[] = {7,4,3,2};

void setup()
{
   // Open serial communications and wait for port to open:
  Serial.begin(115200);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
    //Mux pinout setup
  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);


  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  
  }
  Serial.println("card initialized.");
 Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);
// Serial.println("wire initialized.");
 
}


void loop()
{
	
	uint8_t msb, lsb;	
	String dataString = "";
	
	for (int i =1; i <= 3; i++) {
                
		SelectChannel(i);
                		
		/*erial.print("Drucksensor ");
		Serial.print(i);
		Serial.print(" ");
                */
		//Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);
		//Serial.println("wire initialized.");
                
		Wire.requestFrom(0x78, 2, I2C_STOP);
	  
		while(Wire.available())  
		{ 
			msb = Wire.read(); 
			lsb = Wire.read();
		}
               
	        
		/*Serial.print("MSB: ");
		Serial.println(msb);
		Serial.print("LSB: ");
		Serial.println(lsb);
		*/
		
		rawPressure = (int)(msb << 8) | lsb;
		Pressure = (rawPressure - OUTMIN) / SENSIVITY; 
		
	        time1 =micros();
		dataString = String(msb) + "\t" + String(lsb) + "\t" + String(rawPressure) +"\t" + String(Pressure) +"mbar\t";
		//Serial.print(dataString);
		//Serial.println();
	        
		File dataFile = SD.open("data.txt", FILE_WRITE);
		
		if (dataFile) {
			dataFile.println(dataString);
			dataFile.close();
			//Serial.println(dataString);
		}
		else {
			Serial.println("Sava fail");
		}
		 time2 = micros();
		
        
	
	} 
	//Serial.println("Time: ");
        
        
        Serial.println(time2-time1);

}

int SelectChannel (int channel){
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
	//Serial.print("Selected Channel ");
	//Serial.print(channel);
	//Serial.println();

}


