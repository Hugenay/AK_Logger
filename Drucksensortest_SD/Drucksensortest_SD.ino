#include <VM_Boards.h>
#include <i2c_t3.h>
#include <SD.h>

Sd2Card card;
SdVolume volume;
SdFile root;

#define PRESSURE_SENSOR_ADRESS 0x78   // = 0b1111000
#define OUTMIN 0x0666
#define OUTMAX 0x6CCC
#define PMAX 25
#define SENSIVITY 1045.56    //25mb unidirekt
#define AIRDENSITY 1.2041

uint16_t rawPressure;
double newSpeed, Pressure, pressureh2o;
const int chipSelect = 10; //Adafruit SD-Board

void setup()
{
  Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);
  Serial.begin(9600);

  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);

  // see if the card is present and can be initialized:
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

}

void loop()
{

  uint8_t msb, lsb;
  String dataString = "";

  Wire.requestFrom(0x78, 2, I2C_STOP);
  while(Wire.available())   
  { 
    msb = Wire.read(); 
    lsb = Wire.read();
  }


  //Serial.print(msb,HEX);
  //Serial.print("\t");
  //Serial.print(lsb,HEX);
  //Serial.print("\t");




  rawPressure = (int)(msb << 8) | lsb;

  //Serial.print(rawPressure,HEX);
  //Serial.print("\t");


  Pressure = (rawPressure - OUTMIN) / SENSIVITY;

  pressureh2o = Pressure * 10.197;

  newSpeed = sqrt( 2 * Pressure / AIRDENSITY);

  //Serial.print(Pressure);
  //Serial.print(" mbar");
  //Serial.print("\t");
  //Serial.print(pressureh2o);
  //Serial.print(" mmH2O");
  //Serial.print("\t");
  //Serial.print(newSpeed);
  //Serial.println(" m/s");



  dataString = String(msb) + "\t" + String(lsb) + "\t" + String(rawPressure) +"\t" + String(Pressure) +"mbar\t" + String(pressureh2o) + "mmH20\t" + String(newSpeed)+ "m/s";
Serial.println(dataString);
  File dataFile = SD.open("Messdaten.txt", FILE_WRITE);

  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }
  else {
    Serial.println("Sava fail");
  }
  delay(1000);

}




