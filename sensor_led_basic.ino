#include <LiquidCrystal_I2C.h>

#include <LiquidCrystal.h>

/********************************
   name:I2C LCD1602
   function:You should now see your I2C LCD1602 display the flowing characters: "SunFounder" and "hello, world".
 ********************************/
//Email:support@sunfounder.com
//Website:www.sunfounder.com

/********************************/
// include the library code
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
/**********************************************************/
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
/*********************************************************/
void setup()
{
  pinMode(3, INPUT_PULLUP);// define pin two as input for push button
  pinMode(10, OUTPUT);// defind pin 10 as output
  pinMode(2,OUTPUT);
  digitalWrite(2, HIGH);
  Serial.begin(9600);
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight
}
/*********************************************************/
void loop()
{
  int value = analogRead(A0);
  Serial.println(value);

  int pusshed = digitalRead(3);// read pin 2 and put the result in the "pusshed" variable
  if(pusshed == LOW){
    digitalWrite(10, HIGH);// if pusheed is equal LOW, turn the pin 10 HIGH (give it 5v)
  }else{
    digitalWrite(10, LOW);// else set pin 10 to low or zero volt
  }
  lcd.setCursor(1, 0); // set the cursor to column 3, line 0
  lcd.print("Light: ");  // Print a message to the LCD
  
  lcd.setCursor(8, 0); // set the cursor to column 2, line 1
  lcd.print(value);  // Print a message to the LCD.
  lcd.setCursor(1, 1); // set the cursor to column 2, line 1
  lcd.print("Pushed: ");  // Print a message to the LCD.
  lcd.setCursor(9, 1); // set the cursor to column 2, line 1
  lcd.print(pusshed);  // Print a message to the LCD.
  
  delay(1000);
}
/***********/
