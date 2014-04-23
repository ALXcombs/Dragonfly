// Receive values from the computer
// and blink the light that many times
// Make sure you click on serial monitor
// after you upload

const int LED = 13; //LED connected to
                     //digital pin 13
int val = 0;

int i;

int count;

void setup() {
  
  pinMode(LED, OUTPUT);  //sets the digital 
                         //pin as output
  
  Serial.begin(9600);  // open the serial port to send
                       // data back to the computer at
                       // 9600 bits per second
}

void loop() {
  
  val = Serial.read();  // read the value from
                        // the sensor
                        
  if (val != -1) {
    
    count = val - 48;
    
    for (i = 0; i < count; i++) {
    
      digitalWrite(LED, HIGH);  //turn LED ON
      delay(250);              //waits for a quarter of a second
      digitalWrite(LED, LOW);   //turn LED OFF
      delay(250);              //waits for a quarter of a second
    }
  
  }
}
