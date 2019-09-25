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


//Global variable definitions
uint8_t mode = 0;
// Declare a semaphore handle.
SemaphoreHandle_t sem;
TaskHandle_t redHandle, greenHandle, blueHandle, stateHandle;
QueueHandle_t inputQueue;
uint8_t red_done, blue_done, green_done;

static void readInput(void* arg){
  while(1) {
    while (SerialUSB.available()) {
      
      char c = SerialUSB.read();
      SerialUSB.print(c);
      xQueueSend(inputQueue, (void *) &c, (TickType_t) 0);
    }
    vTaskDelay(50L * configTICK_RATE_HZ/1000);
  }
}

uint8_t selectMode(char in) {
  
  switch(in) {
    case 'R': 
      return 1;
    case 'G': 
      return 2;
    case 'B':
      return 3;
    case 'Y':
      return 4;
    case 'P':
      return 5;
    case 'T':
      return 6;
    case 'W': 
      return 7;
    default:
      return 0;    
  }
}

static void  updateMode(void* arg) {
  while(1){
//    SerialUSB.println(mode);
    if (eTaskGetState(redHandle) == eSuspended &&
        eTaskGetState(greenHandle) == eSuspended && 
        eTaskGetState(blueHandle) == eSuspended ) 
    {
      char c;
      if (xQueueReceive(inputQueue, &c, (TickType_t) 2)) {
        SerialUSB.print("Received character from queue: ");
        SerialUSB.println(c);
        mode = selectMode(c);
        SerialUSB.print("Update mode to ");
        SerialUSB.println(mode);
      }
      else mode = 0;
        
      digitalWrite(LED_R, LOW);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, LOW);
  
      vTaskResume(redHandle);
      vTaskSuspend(stateHandle);
    }
  }
}


static void ThreadRed(void* arg) {

  while(1) {
  xSemaphoreTake(sem, portMAX_DELAY);

  //turn on LED, but only if in the right mode
    if (mode == 1 || mode == 4 || mode == 5 || mode == 7) {
      digitalWrite(LED_R, HIGH);
      //wait 500 ms
      SerialUSB.println("Red on");

      //If this is the last LED to turn on for intended color, delay
      if (mode == 1) 
        vTaskDelay(1000L * configTICK_RATE_HZ / 1000);  
    }
    else {
      digitalWrite(LED_R, LOW);
    }

  //set done flag, give back semaphore, (possibly) update state, then delay to transfer control
  red_done = 1; 
  xSemaphoreGive(sem);
  vTaskResume(greenHandle);
  vTaskSuspend(redHandle);

  }
}

static void ThreadGreen(void* arg) {

  while(1) {
    xSemaphoreTake(sem, portMAX_DELAY);

   //turn on LED, but only if in the right mode
    if (mode == 2 || mode == 4 || mode == 6 || mode == 7) {
      digitalWrite(LED_G, HIGH);
      //wait 500 ms
      SerialUSB.println("Green on");

      //If this is the last LED to turn on for the intended color, delay
      if (mode == 2 || mode == 4)
        vTaskDelay(1000L * configTICK_RATE_HZ / 1000);
    }
    else {
      digitalWrite(LED_G, LOW);
    }
    
    green_done = 1;
    xSemaphoreGive(sem);
    vTaskResume(blueHandle);
    vTaskSuspend(greenHandle);

  }  
}

static void ThreadBlue(void* arg) {

  while(1) {
    xSemaphoreTake(sem, portMAX_DELAY);
    
    //turn on LED, but only if in the right mode
    if (mode == 3 || mode == 5 || mode == 6 || mode == 7) {
      digitalWrite(LED_B, HIGH);

      
      //If this is the last LED to turn on for intended color, delay
      vTaskDelay(1000L * configTICK_RATE_HZ / 1000);
    }
    else {
      digitalWrite(LED_B, LOW);
    }

    //set done flag, give back semaphore, (possibly) update state, then delay to transfer control
    blue_done = 1;
    xSemaphoreGive(sem);
    vTaskResume(stateHandle);
    vTaskSuspend(blueHandle);

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
  mode = 0;

  SerialUSB.println(configMINIMAL_STACK_SIZE); //130
  SerialUSB.println(configTICK_RATE_HZ); //1000
  SerialUSB.println(portMAX_DELAY); // max for 32-bit unsigned int

  sem = xSemaphoreCreateCounting(1, 1);
  if (sem==NULL) {
    SerialUSB.println("semaphore failed creation");
    while(1);
  }

  SerialUSB.println("1");
    

  portBASE_TYPE taskRed, taskGreen, taskBlue, taskUpdate, taskRead;
  taskRed = xTaskCreate(ThreadRed, NULL, configMINIMAL_STACK_SIZE, NULL, 2, &redHandle);
  if (taskRed != pdPASS) {
    SerialUSB.println("Creation of task red failed!");
    while(1);
  }
  taskGreen = xTaskCreate(ThreadGreen, NULL, configMINIMAL_STACK_SIZE, NULL, 2, &greenHandle);
  if (taskGreen != pdPASS) {
    SerialUSB.println("Creation of task green failed!");
    while(1);
  }
  taskBlue = xTaskCreate(ThreadBlue, NULL, configMINIMAL_STACK_SIZE, NULL, 2, &blueHandle);
  if (taskBlue != pdPASS) {
    SerialUSB.println("Creation of task blue failed!");
    while(1);
  }

  SerialUSB.println("1.5");

  taskUpdate = xTaskCreate( updateMode, NULL, configMINIMAL_STACK_SIZE, NULL, 2, &stateHandle);
  if (taskUpdate != pdPASS) {
    SerialUSB.println("Creation update task failed!");
    while(1);
  }

  
  taskRead = xTaskCreate( readInput, NULL, configMINIMAL_STACK_SIZE, NULL, 3, NULL);
  if (taskRead != pdPASS) {
    SerialUSB.println("Creation read task failed!");
    while(1);
  }

  SerialUSB.println("2");
  inputQueue = xQueueCreate((UBaseType_t) 128, (UBaseType_t) sizeof(char));
  if (inputQueue == NULL) {
    SerialUSB.println("Queue not created...");
    while(1);
  }
  
  SerialUSB.println("Starting Scheduler");
  vTaskStartScheduler();
  
  vTaskSuspend(redHandle);
  vTaskSuspend(greenHandle);
  vTaskSuspend(blueHandle);
}

// the loop function runs over and over again forever
void loop() {

}
