void setup() {
pinMode(BUILTIN_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output
}
 
// the loop function runs over and over again forever
void loop() {
int i;
for(i = 0; i<3; i++){
  digitalWrite(BUILTIN_LED, LOW); // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(300); // Wait for a second
  digitalWrite(BUILTIN_LED, HIGH); // Turn the LED off by making the voltage HIGH
  delay(300);
}
for(i = 0; i<3; i++){
  digitalWrite(BUILTIN_LED, LOW); // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(1000); // Wait for a second
  digitalWrite(BUILTIN_LED, HIGH); // Turn the LED off by making the voltage HIGH
  delay(1000);
}
for(i = 0; i<3; i++){
  digitalWrite(BUILTIN_LED, LOW); // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(300); // Wait for a second
  digitalWrite(BUILTIN_LED, HIGH); // Turn the LED off by making the voltage HIGH
  delay(300);
}


delay(2000); // Wait for two seconds (to demonstrate the active low LED)
}