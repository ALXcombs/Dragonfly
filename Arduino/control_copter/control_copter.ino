// control_copter

/*
This repeatedly sends commands to the helicopter.
The commands must be sent repeatedly or the copter will shut down.

It also monitors the serial port, to update the commands it should send.
The commands are 4 values in sequence: yaw, pitch, throttle, trim
- 127 is max
- Yaw 0 is turn right
- Pitch 0 is forward
- Throttle 90 is ascend, 63-ish is hover
- Trim is added to Yaw...kind of (more study needed)
*/

const int IRLED = 8; // The pin the IR LED is connected to
const int IRLED2 = 9; //Second LED
const int STATUS = 13; // The pin the status LED is on
byte cmds[] = {63, 63, 0, 63}; // Default flight commands

byte sendPacket(byte cmds[]){
  // Blinks IR LED in code to control copter
  
  // Works for Symya S107G
  static byte markL, countP, countR, one, zero;
  static bool data;
  static const byte maskB[] = {1,2,4,8,16,32,64,128};

  //digitalWrite(STATUS,HIGH);

  countP = 4;
  countR = 8;
  
  one = 0;
  zero = 0;

  data = true;

  // transmit start of packet
  markL = 77;
  while(markL--){
    digitalWrite(IRLED, LOW);
    digitalWrite(IRLED2, LOW);
    delayMicroseconds(10);
    digitalWrite(IRLED, HIGH);
    digitalWrite(IRLED2, HIGH);
    delayMicroseconds(10);
  }

  delayMicroseconds(1998);

  markL = 12;
  while(data){

    // transmit a binary 0 or 1
    while(markL--){
      digitalWrite(IRLED, LOW);
      digitalWrite(IRLED2, LOW);
      delayMicroseconds(10);
      digitalWrite(IRLED, HIGH);
       digitalWrite(IRLED2, HIGH);
      delayMicroseconds(10);
    }
    markL = 12;
    if(cmds[4-countP] & maskB[--countR]){
      one++;
      delayMicroseconds(688);
    }else{
      zero++;
      delayMicroseconds(288);
    }

    if(!countR){
      countR = 8;
      countP--;
    }

    if(!countP){
      data = false;
    }
  }

  while(markL--){
    digitalWrite(IRLED, LOW);
    digitalWrite(IRLED2, LOW);
    delayMicroseconds(10);
    digitalWrite(IRLED, HIGH);
    digitalWrite(IRLED2, HIGH);
    delayMicroseconds(10);
  }

  //digitalWrite(STATUS,LOW);

  return((.1-.014296-one*.000688-zero*.000288)*1000); // in ms.
}


void setup(){
    Serial.begin(9600);
    pinMode(STATUS, OUTPUT);
    digitalWrite(STATUS, LOW);
    pinMode(IRLED,  OUTPUT);
    digitalWrite(IRLED,  HIGH);
    pinMode(IRLED2,  OUTPUT);
    digitalWrite(IRLED2,  HIGH);
    pinMode(IRLED2,  OUTPUT);
}


void serialEvent(){
  int c;
  int cv;
  // Gets bytes from serial port, updates the command params
  digitalWrite(STATUS, HIGH);
  if(Serial.available() != 4){
    return;
  }
  for(int i=0; i < 4; ++i){
    c = Serial.read();
    cv = (c - 48) * 10;
    cmds[i] = c;
  }
  digitalWrite(STATUS, LOW);  
}

void loop(){
    delay(sendPacket(cmds));
}
