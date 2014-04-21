const int LED = 8; // This is the IR LED
const int STATUS = 13; // This LED will blink for each command sequence sent


byte sendPacket(byte cmds[]){
  // Blink the IR LED to send four commands
  
  // We convert each command to 8 bit binary
  static byte markL, countP, countR, one, zero;
  static bool data;
  static const byte maskB[] = {1,2,4,8,16,32,64,128};

  digitalWrite(STATUS,HIGH);

  countP = 4;
  countR = 8;
  
  one = 0;
  zero = 0;

  data = true;

  // Signal the beginning of a command; get copter's attention
  markL = 77;
  while(markL--){
    digitalWrite(LED,LOW);
    delayMicroseconds(10);
    digitalWrite(LED,HIGH);
    delayMicroseconds(10);
  }
  delayMicroseconds(1998);

  // Loop through the 4 commands
  while(data){

    // Signal the start of a byte
    markL = 12;
    while(markL--){
      digitalWrite(LED,LOW);
      delayMicroseconds(10);
      digitalWrite(LED,HIGH);
      delayMicroseconds(10);
    }

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
    digitalWrite(LED,LOW);
    delayMicroseconds(10);
    digitalWrite(LED,HIGH);
    delayMicroseconds(10);
  }

  digitalWrite(STATUS,LOW);

  return((.1-.014296-one*.000688-zero*.000288)*1000); // in ms.
}


byte cmds[] = {63, 63, 0, 63};
//yaw, pitch, throttle, trim

void setup(){
    Serial.begin(9600);
    pinMode(STATUS, OUTPUT);
    digitalWrite(STATUS, LOW);
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);
}


void serialEvent1(){
   if(Serial.available() != 4){
        return;
    }
    for(int i=0; i < 4; ++i){
        cmds[i] = Serial.read();
    }
}

void loop(){
    cmds[0] = 0; // yaw
    cmds[1] = 0; // pitch
    cmds[2] = 0; // throttle
    cmds[3] = 0; // trim
    delay(sendPacket(cmds));
}
