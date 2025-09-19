int pirPino = 2;   

void setup() {
  pinMode(pirPino, INPUT);  
  Serial.begin(9600);     
}

void loop() {
  int motionDetected = digitalRead(pirPino);

  if (motionDetected == HIGH) { 
    Serial.println("Movimento detectado");
  } else {
    Serial.println("Sem movimento");
  }

  delay(100);
}
