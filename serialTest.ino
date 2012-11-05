
int led = 12;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT); 
  
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  
}

void loop() {
  if(Serial.available() > 0) {
    digitalWrite(led, HIGH);
    delay(1000); 
    digitalWrite(led, LOW);
    Serial.println("Hello from Arduino");
  }
}
    
