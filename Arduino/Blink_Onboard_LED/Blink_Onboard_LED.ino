 // Example 01 : Blinking LED
 
 const int LED = 13; //LED connected to
                     //digital pin 13
 
 void setup()
 {
   pinMode(LED, OUTPUT);  //sets the digital 
                         //pin as output
 }
 
 void loop()
 {
   digitalWrite(LED, HIGH);  //turns the LED on
   delay(250);              //waits for a quarter of a second
   digitalWrite(LED, LOW);  //turns the LED off
   delay(10);             //waits for a really short time
   digitalWrite(LED, HIGH);  //turns the LED on
   delay(250);              //waits for a quarter of a second
   digitalWrite(LED, LOW);  //turns the LED off
   delay(10);             //waits for a really short time
   digitalWrite(LED, HIGH);  //turns the LED on
   delay(250);              //waits for a quarter of a second
   digitalWrite(LED, LOW);  //turns the LED off
   delay(10);             //waits for a really short time
   digitalWrite(LED, HIGH);  //turns the LED on
   delay(250);              //waits for a quarter of a second
   digitalWrite(LED, LOW);  //turns the LED off
   delay(500);             //waits for half a second
 }
