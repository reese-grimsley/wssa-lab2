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

  /** Blink blue twice per second **/
//  digitalWrite(LED_B, HIGH);   
//  delay(250);                  
//  digitalWrite(LED_B, LOW);   
//  delay(250);                 

  /** Toggle LED white  **/
  digitalWrite(LED_R, HIGH);  
  digitalWrite(LED_G, HIGH);  
  digitalWrite(LED_B, HIGH);  // Turning on all LEDs will produce a white light
  delay(500);                 
  digitalWrite(LED_R, LOW); 
  digitalWrite(LED_G, LOW); 
  digitalWrite(LED_B, LOW);   
  delay(500);                 
}
