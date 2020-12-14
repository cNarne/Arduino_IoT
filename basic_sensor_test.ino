#include <SPI.h>
#include <SD.h>

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  8;      // the number of the LED pin
const int sensorPin = A0;    // select the input pin for the potentiometer
const int chipSelect = 4;

// initialize variables
float sensorValue = 0;  // variable to store the value coming from the sensor
int buttonState = 0;         // variable for reading the pushbutton status
float meas = 0;        //variable for storing measured values
float sensorReading = 0;  //variable for the averaged sensor Reading

String data;
String fname = "20201212.txt";


void setup() {
  // put your setup code here, to run once:

  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

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
  data = "millis; meas0; meas1; meas2; meas3; meas4; meas5; sensorReading";
  write2SD(data);
  data = "";



  
}

void loop() {
  // put your main code here, to run repeatedly:


  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
     delay(10);  //delay to ensure button is pressed
    
    // turn LED on:
    digitalWrite(ledPin, HIGH);

    //write CPU clock time
    data += millis();
    
    //read sensor
    for (int meas_i = 0; meas_i < 5; meas_i++){
       sensorValue = analogRead(sensorPin) * 5.0 / 1023.0;  //read value from sensor and convert to voltage

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

    sensorReading = meas / 5 * (5.0 / 1023.0);   //average measurements for a reading
    data += sensorReading;
    data += ";";
    Serial.print("sensorReading: ");
    Serial.println(sensorReading);

    //write to SD
    Serial.println("write2SD");
    write2SD(data);
    
    
    delay(2000);
    digitalWrite(ledPin, LOW);

    meas = 0;  //reset meas variable after computation
    data = "";  //reset data file
    
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
}


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
