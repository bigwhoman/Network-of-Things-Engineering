#define LED D13

int out;
void setup(){
    out = 0;
    pinMode(LED, OUTPUT);
}

void loop(){
    out = ~out;
    digitalWrite(LED,out);
    delay(1000);
}
