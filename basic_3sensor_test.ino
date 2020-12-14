#include <SPI.h>
#include <SD.h>

// constants won't change. They're used here to set pin numbers:
const int sensorPowerPin = 2;     // the number of the pin for powering sensors
const int sdPowerPin = 3;         //the number for the pin VCC to SD card (+5V)
const int sensorPin4 = A0;    // select the input pin for the soil moisture sensor
const int sensorPin8 = A1;    // select the input pin for the soil moisture sensor
const int sensorPin12 = A2;    // select the input pin for the soil moisture sensor
const int chipSelect = 4;

// initialize variables
float sensorValue = 0;  // variable to store the value coming from the sensor
float meas = 0;        //variable for storing measured values
float sensorReading = 0;  //variable for the averaged sensor Reading

String data;
String fname = "20201212.txt";


void setup() {
  // put your setup code here, to run once:

  // declare OUTPUT pins:
  pinMode(sensorPowerPin, OUTPUT);
  pinMode(sdPowerPin, OUTPUT);

  // initialize INPUT pins:
//  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
//  while (!Serial) {
//    ; // wait for serial port to connect. Needed for native USB port only
//  }

  Serial.println();
  Serial.println("*************************************************");
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
   // while (1);
  }
  Serial.println("card initialized.");

  //setup data file header
  data = "millis; meas0; meas1; meas2; meas3; meas4; meas5; sensorReading; meas0; meas1; meas2; meas3; meas4; meas5; sensorReading; meas0; meas1; meas2; meas3; meas4; meas5; sensorReading;";
  write2SD(data);
  data = "";

}

void loop() {
  // put your main code here, to run repeatedly:



  digitalWrite(sensorPowerPin, HIGH);  //turn on power to sensors
  delay(500);
  
    //write CPU clock time
    data += millis();
    
    //read sensor

    //read sensor 1 8************
    for (int meas_i = 0; meas_i < 5; meas_i++){
       sensorValue = analogRead(sensorPin4) * 5.0 / 1023.0;  //read value from sensor and convert to voltage

       meas = meas + sensorValue;

       data += sensorValue;
       data += ";";

       Serial.print("sensorValue");
       Serial.print(meas_i);
       Serial.print(": ");
       Serial.print(sensorValue);
       Serial.print("     ");
       Serial.print("meas: ");
       Serial.println(meas);
       
       delay(200);
    }

    sensorReading = meas / 5;   //average measurements for a reading
    meas = 0;  //reset meas variable after computation
    
    data += sensorReading;
    data += ";";
    Serial.print("sensorReading: ");
    Serial.println(sensorReading);


//read sensor pin8 A1 *********
    for (int meas_i = 0; meas_i < 5; meas_i++){
       sensorValue = analogRead(sensorPin8) * 5.0 / 1023.0;  //read value from sensor and convert to voltage

       meas = meas + sensorValue;

       data += sensorValue;
       data += ";";

       Serial.print("sensorValue");
       Serial.print(meas_i);
       Serial.print(": ");
       Serial.print(sensorValue);
       Serial.print("     ");
       Serial.print("meas: ");
       Serial.println(meas);

       delay(200);
    }

    sensorReading = meas / 5;   //average measurements for a reading
    meas = 0;  //reset meas variable after computation
    
    data += sensorReading;
    data += ";";
    Serial.print("sensorReading: ");
    Serial.println(sensorReading);


// read sensor pin12 A2 *****************
    for (int meas_i = 0; meas_i < 5; meas_i++){
       sensorValue = analogRead(sensorPin12) * 5.0 / 1023.0;  //read value from sensor and convert to voltage

       meas = meas + sensorValue;

       data += sensorValue;
       data += ";";
       
       Serial.print("sensorValue");
       Serial.print(meas_i);
       Serial.print(": ");
       Serial.print(sensorValue);
       Serial.print("     ");
       Serial.print("meas: ");
       Serial.println(meas);

       delay(200);
    }

    sensorReading = meas / 5;   //average measurements for a reading
    meas = 0;  //reset meas variable after computation
    
    data += sensorReading;
    data += ";";
    Serial.print("sensorReading: ");
    Serial.println(sensorReading);


    //write to SD
    digitalWrite(sdPowerPin, HIGH);  //turn on SD power
    delay(500);
    write2SD(data);  //write block of data to SD
    data = "";  //reset data file
    delay(500);

    digitalWrite(sdPowerPin, LOW);
    digitalWrite(sensorPowerPin, LOW);
    
    delay(30*60*1000);  //wait 30 minutes before next reading
//delay(3000);
}


void write2SD (String s)
{
    // print to the serial port too:
    Serial.println("data write to SD");
    Serial.println(s);
    
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open(fname, FILE_WRITE);

    // if the file is available, write to it:
    if (dataFile) {
       dataFile.println(s);
       dataFile.close();

    }
    // if the file isn't open, pop up an error:
    else {
       Serial.print("error opening ");
       Serial.print(fname);
       Serial.println(".txt");
    } 
} 
