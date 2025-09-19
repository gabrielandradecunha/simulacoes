#include <IRremote.h>

// A ideia é ativar um led ao receber determinado valor através do sensor

int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); 
  Serial.println("Infravermelho ligado");
  pinMode(13,OUTPUT);
}


void loop() {
  if (irrecv.decode(&results)) {
    Serial.println("Valor recebido: ");
    Serial.println(results.value, DEC);
    if (results.value == 2077596311){
     digitalWrite(13,HIGH); 
    }
    irrecv.resume(); 
  }
  delay(100);
}
