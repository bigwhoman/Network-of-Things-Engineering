# Assignment 1
## (a)

Based on Ohm's Law : $R=\frac{V}{I}$
<br>
According to the ESP8266 datasheet, when GPIO13 pin is configured as an output, it can provide <b>3.3V</b> on Logic high(1) and 0 on Logic low(0).
<br>
Based of our sources, the typical voltage range for a 5mm Red Led is between 1.8 and 2.2V and the typical forward current is 20mA.
<br>
Also the maximum current per GPIO pin is 12mA so we could do a back-of-envelope calculation to see that :
<br> 
3.3 - 1.8 = 1.5V( Voltage across the resistor ) ==>
$\frac{1.5}{12*10^{-3}}=125\Omega$ of resistance it needs at minimum to ensure that we are in the safe range of the GPIO current output. This means that 330ohm is an adequate resistance for our red LED.

## (b)

If we use a resistance higher than calculated, the current flowing through the LED would be lower and thus we would have less brightness. 
<br>
On the other hand, if we use less resistance, then the current flowing through the GPIO pin would be beyond its safe limits and it would probably damage it and also if the current flowing through the LED is more than 20mA, it would damage the LED too.

# Assignment 2

```cpp
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
```

# Assignment 3

## (a)

I2C is a aynchronous serial communications protocol for short-distance communications between circuits on the same board.
<br>

The way it works is as below : 
<li> SDA or the Serial Data Line for data transfer
<li> SCL or the Serial Clock Line for synchronization

Both of these lines are bidirectional and multiple devices can use the same bus.
<br>
The communication protocol is as below : 
1. Start: SDA = 0 and SCL = 1 <br>
2. Address Transmission: Master sends device address <br>
3. R/W bit: Indicates our operation <br>
4. ACK: Receiving device pulls SDA LOW <br>
5. Data Transmission: 8-bit data packets with ACK <br>
6. Stop Condition: SDA goes HIGH while SCL is HIGH <br>

The advantages of this protocol are :
<li> Simple Hardware (only 2 wires are needed)
<li> Supports multiple masters and slaves
<li> Reliable 

## (b)

An I2C LCD display is essentially a traditional LCD with an added I2C adapter board (usually based on the PCF8574 IC) that converts I2C signals to the parallel interface the LCD needs. While a traditional LCD requires 6-8 data pins plus 3 control pins (totaling 9-11 GPIO pins), an I2C LCD only needs 2 pins (SDA and SCL) to achieve the same functionality. You can convert any traditional LCD to I2C by adding a PCF8574 module - just connect the LCD's data pins (D4-D7) to P4-P7 on the PCF8574, control pins (RS, RW, E) to P0-P2, and backlight to P3, then wire up SDA, SCL, VCC, and GND to your microcontroller.

# Assignment 4
## (a)

We would use ```lcd.setCursor(9,0)``` to start printing in the tenth column of the first row (indices start from 0)

## (b)

We could see that the string "hello w" would be shown and the rest of our string would be truncated.

# Assignment 5

## (a)
Relative Humidity is the ratio of actual water vapor present in the air compared to the maximum amount of water vapor the air can hold at that specific temperature, expressed as a percentage.

## (b)
No, because its range is from 20% to 90%

## (c)
Range: 0°C to 50°C
<br>
Accuracy: ±2°C
<br>
Sampling Rate: maximum of 1 sample persecond with the recommendation of no more than one reading every 2 seconds

# Assignment 6


# Assignment 7
## (a)

Sound travels at almost 343 m/s in room tempreture. 
<br>
$2 * Distance = time * 343 => Distance(m) = time(s) * 171.5$

## (b)

According to the datasheet, the distance range is 2cm at minimum and 400cm at maximum. The Resolution is almost 0.3cm and +-3mm in ideal conditions with measuring angle of 15 degrees. However according to some forums, this sensor is less reliable at less than 2cm and more than 300cm, angled surfaces and extreme temperatures.

# Assignment 8

```cpp
#include "distance.h"
#define LED D13
const int trigPin = D15;
const int echoPin = D14;

HCSR04 hcsr04(trigPin, echoPin);

void setup(){
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
}

void loop(){
    float distance = hcsr04.calculate_distance();
    if(distance < 10){
        digitalWrite(LED, HIGH);
    } else { 
        digitalWrite(LED, LOW);
    }
}
```

# Assignment 9
## (a)

This sensor is designed to detect infrared radiation in the wavelength range of approximately 8-14 micrometers 

## (b)

The base sensensivity : 
<li> Temperature difference: Around 4°C between the moving object and background
<li> Angle: ~110° horizontal and ~70° vertical detection range
<li> Distance: Generally effective from 3-7 meters (adjustable via potentiometer)
<il> Movement speed: Can detect motion between 0.3 to 3 m/s

This sensivity could be adjusted by changing the jumper setting on the board.


# Assignment 10

```cpp
#include "PIR.h"
#define LED D13
const int pirSensor = D15;

PIR pir(pirSensor);

void setup(){
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
}

void loop(){
    bool is_motion = pir.detect_motion();
    if(is_motion){
        digitalWrite(LED, HIGH);
    } else { 
        digitalWrite(LED, LOW);
    }
    delay(1000);
}

```