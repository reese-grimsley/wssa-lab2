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


static void ThreadRed(void* arg) {

  //turn on LED
  digitalWrite(LED_R, HIGH);
  //wait 500 ms
  SerialUSB.println("Red on");
  vTaskDelay(500L * configTICK_RATE_HZ / 1000);
  //turn off
  digitalWrite(LED_R, LOW);

  //wait 500 ms
  vTaskDelay(500L * configTICK_RATE_HZ / 1000);

  SerialUSB.println("Red Done");
  while(1);
  
}

static void ThreadGreen(void* arg) {

  //turn on LED
  digitalWrite(LED_G, HIGH);
  //wait 500 ms
  SerialUSB.println("Green on");
  vTaskDelay(500L * configTICK_RATE_HZ / 1000);
  //turn off
  digitalWrite(LED_G, LOW);

  //wait 500 ms
  vTaskDelay(500L * configTICK_RATE_HZ / 1000);

  SerialUSB.println("Green Done");
  while(1);        
  
}

static void ThreadBlue(void* arg) {

  //turn on LED
  digitalWrite(LED_B, HIGH);
  //wait 500 ms
  SerialUSB.println("Blue on");
  vTaskDelay(500L * configTICK_RATE_HZ / 1000);
  //turn off
  digitalWrite(LED_B, LOW);

  //wait 500 ms
  vTaskDelay(500L * configTICK_RATE_HZ / 1000);

  SerialUSB.println("Blue Done");
  while(1);        
  
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

  portBASE_TYPE taskRed, taskGreen, taskBlue;
  taskRed = xTaskCreate(ThreadRed, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
  if (taskRed != pdPASS) {
    SerialUSB.println("Creation of task 1 failed!");
    while(1);
  }
  taskGreen = xTaskCreate(ThreadGreen, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
  if (taskGreen != pdPASS) {
    SerialUSB.println("Creation of task 1 failed!");
    while(1);
  }
  taskBlue = xTaskCreate(ThreadBlue, NULL, configMINIMAL_STACK_SIZE, NULL, 2, NULL);
  if (taskBlue != pdPASS) {
    SerialUSB.println("Creation of task 1 failed!");
    while(1);
  }

      
  vTaskStartScheduler();
}

// the loop function runs over and over again forever
void loop() {

}
