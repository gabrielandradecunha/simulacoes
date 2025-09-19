#include <IRremote.h>

int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  Serial.println("Ativando infravermelhpo....");
  irrecv.enableIRIn(); 
  Serial.println("Infravermelho ativado");
  pinMode(13,OUTPUT);
}


void loop() {
  if (irrecv.decode(&results)) {
    Serial.println("Valor recebido");
    if (results.value == 16580863){
     digitalWrite(13,HIGH); 
    }
    irrecv.resume(); 
  }
  delay(100);
}
