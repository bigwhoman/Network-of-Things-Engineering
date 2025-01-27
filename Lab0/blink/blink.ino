void setup()
{
    pinMode(BUILTIN_LED, OUTPUT); // Initialize the BUILTIN_LED pin as an output
}

// the loop function runs over and over again forever
void loop()
{
    int i;
    int count;
    count = 2;
    for (size_t i = 0; i < count; i++)
    {
        digitalWrite(BUILTIN_LED, LOW); // Turn the LED on (Note that LOW is the voltage level
        delay(500);                      // Wait
        digitalWrite(BUILTIN_LED, HIGH); // Turn the LED off by making the voltage HIGH
        delay(500);
    }

    delay(2000); // Wait for two seconds (to demonstrate the active low LED)
}