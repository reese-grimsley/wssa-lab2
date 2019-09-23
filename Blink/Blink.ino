/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/

#define LED_R 6
#define LED_G 7
#define LED_B 8

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize pins for LEDs as output
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);

  Serial.begin(9600)
}

// the loop function runs over and over again forever
void loop() {

  /** Blink red twice per second **/
//  digitalWrite(LED_R, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(250);                       // wait for a second
//  digitalWrite(LED_R, LOW);    // turn the LED off by making the voltage LOW
//  delay(250);                       // wait for a second


  /** Blink Green twice per second; can do the same with Blue **/
//  digitalWrite(LED_G, HIGH);  
//  delay(250);                 
//  digitalWrite(LED_G, LOW);  
//  delay(250);            

  /** Blink red twice per second **/
//  digitalWrite(LED_R, HIGH);   
//  delay(250);                  
//  digitalWrite(LED_R, LOW);   
//  delay(250);                 

  /** Toggle LED white  **/
  digitalWrite(LED_R, HIGH);  
  digitalWrite(LED_G, HIGH);  
  digitalWrite(LED_B, HIGH);  // Turning on all LEDs will lead to a white light
  delay(500);                 
  digitalWrite(LED_R, LOW); 
  digitalWrite(LED_G, LOW); 
  digitalWrite(LED_B, LOW);   
  delay(500);                 
}
