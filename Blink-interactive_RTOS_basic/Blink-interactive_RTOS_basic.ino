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
#include <FreeRTOS_ARM.h>

#define LED_R 6
#define LED_G 7
#define LED_B 8

String in = "";
uint8_t mode = 7; //bits correspond to colors


static void Thread1(void* arg) {
  while (1) {


  if (SerialUSB.available()) {
    in = SerialUSB.readStringUntil('\n');
    SerialUSB.println(in);
  }

  if (in.equals("red") || in.equals("white") || in.equals("yellow") || in.equals("purple") )
    mode = mode | 0x1;
  else 
    mode = (mode & ~0x1);
  if (in.equals("green") || in.equals("white") || in.equals("yellow") || in.equals("periwinkle"))
    mode = mode | 0x2;
  else 
    mode = (mode & ~0x2);
  if (in.equals("blue") || in.equals("white") || in.equals("purple") || in.equals("periwinkle"))
    mode = mode | 0x4;
  else 
    mode = (mode & ~0x4);

  SerialUSB.println(mode);
  //write the bits depending on the active mode
  if (mode & 1)
    digitalWrite(LED_R, HIGH);
  if (mode & 2)
    digitalWrite(LED_G, HIGH);
  if (mode & 4)
    digitalWrite(LED_B, HIGH);

//  delay(500);
  vTaskDelay(500);

  if (mode & 1)
    digitalWrite(LED_R, LOW);
  if (mode & 2)
    digitalWrite(LED_G, LOW);
  if (mode & 4)
    digitalWrite(LED_B, LOW);

//  delay(500);
  vTaskDelay(500);
             
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize pins for LEDs as output
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);


  
  SerialUSB.begin(9600);
  while (!SerialUSB);
  SerialUSB.println("ready to go\n");
  SerialUSB.flush();
  mode = 7;

  SerialUSB.println(configMINIMAL_STACK_SIZE);
  SerialUSB.println(configTICK_RATE_HZ);

    portBASE_TYPE s1;
      s1 = xTaskCreate(Thread1, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
      if (s1 != pdPASS) {
        SerialUSB.println("Creation of task 1 failed!");
        while(1);
      }
  vTaskStartScheduler();
}

// the loop function runs over and over again forever
void loop() {

}
