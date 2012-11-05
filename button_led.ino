const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

int remoteIndicator = false; // keeps track of the desired remote on/off state
int lastRemoteIndicator = false; // record of prior remote state
unsigned long lastSent = 0; // records last time the remote was re-set to keep it in sync

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
  
  Serial.begin(9600);
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  remoteIndicator = buttonState;

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if( remoteIndicator != lastRemoteIndicator ) {
    if (buttonState == HIGH) {     
      // turn LED on:    
      digitalWrite(ledPin, HIGH);    
      setRemoteState(0x5);    
    } 
    else {
      // turn LED off:
      digitalWrite(ledPin, LOW); 
      setRemoteState(0x4);
    }
    lastRemoteIndicator = remoteIndicator;
  }
}

void setRemoteState(int value) {  // pass either a 0x4 or and 0x5 to turn the pin on or off
  Serial.write((byte)0x7E); // start byte
  Serial.write((byte)0x0); // high part of length (always zero)
  Serial.write((byte)0x10); // low part of length (the number of bytes that follow, not including checksum)
  Serial.write((byte)0x17); // 0x17 is a remote AT command
  Serial.write((byte)0x0); // frame id set to zero for no reply
  // ID of recipient, or use 0xFFFF for broadcast
  Serial.write((byte)00);
  Serial.write((byte)00);
  Serial.write((byte)00);
  Serial.write((byte)00);
  Serial.write((byte)00);
  Serial.write((byte)00);
  Serial.write((byte)0xFF); // 0xFF for broadcast
  Serial.write((byte)0xFF); // 0xFF for broadcast
  // 16 bit of recipient or 0xFFFE if unknown
  Serial.write((byte)0xFF);
  Serial.write((byte)0xFE);
  Serial.write((byte)0x02); // 0x02 to apply changes immediately on remote
  // command name in ASCII characters
  Serial.write((byte)'D');
  Serial.write((byte)'1');
  // command data in as many bytes as needed
  Serial.write((byte)value);
  // checksum is all bytes after length bytes
  long sum = 0x17 + 0xFF + 0xFF + 0xFF + 0xFE + 0x02 + 'D' + '1' + value;
  Serial.write((byte)( 0xFF - ( sum & 0xFF)) ); // calculate the proper checksum
  //delay(10); // safety pause to avoid overwhelming the serial port (if this function is not implemented properly)
}


