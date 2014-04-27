// Receive values from the computer
// and blink the light that many times
// Make sure you click on serial monitor
// after you upload

const int IRLED = 8; // IR LED connected to pin 8
const int STATUS = 13; // LED connected to pin 13

int val = 0;
int i;
int count;

void setup() {  
  pinMode(IRLED, OUTPUT);  //sets the digital 
                         //pin as output
  pinMode(STATUS, OUTPUT);
  
  Serial.begin(9600);  // open the serial port to send
                       // data back to the computer at
                       // 9600 bits per second
}

void loop() {
  
  val = Serial.read();  // read the value from
                        // the sensor
                        
  if (val != -1) {
    
    count = val - 48;    //48 is the ascii code for 0
    
    for (i = 0; i < count; i++) {
    
      digitalWrite(IRLED, HIGH);  //turn IRLED ON
      delay(250);              //waits for a quarter of a second
      digitalWrite(IRLED, LOW);   //turn IRLED OFF
      delay(250);              //waits for a quarter of a second
    }
  
  }
}
