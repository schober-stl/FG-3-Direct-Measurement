/*  This project uses a Teeny 4.0 https://www.pjrc.com/ and 2 FG-3+ fluxgate magnetometers from https://www.fgsensors.com/
 *  Must cut trace that connects Vin to USB on Teensy 4.0 so powered by linear regulaor circuit https://www.pjrc.com/store/teensy40.html 
 *  The Teensy 4.0 and Fg-3+ sensors are powered by the linear regulator circuit in https://www.fgsensors.com/_files/ugd/7034a0_c59536c9022b4a5798fcc6045dcf6841.pdf
 *  Must use logic leveler to convert FG3+ signal from 5.0 V to 3.3 V before connecting to pins on Teensy (pins are not 5.0 V tolerant)
 *  Uses Interrupts to get pulse duration for both pins 6 and 9
 *  MainPeriod contols speed versus precision
*/

#define MainPeriod 2500 // adjust for tradeoff of precision vs speed
const byte interruptPin1 = 6;
const byte interruptPin2 = 9;

long previousMillis = 0; // will store last time of the cycle end

volatile unsigned long duration1 = 0; // accumulates pulse width for pin 6
volatile unsigned int pulsecount1 = 0;
volatile unsigned long previousMicros1 = 0;

volatile unsigned long duration2 = 0; // accumulates pulse width for pin 9
volatile unsigned int pulsecount2 = 0;
volatile unsigned long previousMicros2 = 0;

void setup()
{
  Serial.begin(9600); 
  attachInterrupt(digitalPinToInterrupt(interruptPin1), myinthandler1, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), myinthandler2, RISING);
}

void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= MainPeriod) 
  {
    noInterrupts();
    previousMillis = currentMillis;   
    unsigned long _duration1 = duration1;
    unsigned long _pulsecount1 = pulsecount1;
    duration1 = 0; // clear counters
    pulsecount1 = 0;

    unsigned long _duration2 = duration2;
    unsigned long _pulsecount2 = pulsecount2;
    duration2 = 0; // clear counters
    pulsecount2 = 0;

    float Freq1 = 1e6 / float(_duration1);    // Duration is in microseconds, so it is 1e6 / T
    float Freq2 = 1e6 / float(_duration2);

    Freq1 *= _pulsecount1; // calculate frequency for pin 6
    Freq2 *= _pulsecount2; // calculate frequency for pin 9

    Serial.print("Hz on pin 6: ");
    Serial.print(Freq1, 3);

    Serial.print("    pin 9: ");
    Serial.println(Freq2, 3);

    interrupts();
  }
}

void myinthandler1() // interrupt handler for pin 6
{
  unsigned long currentMicros = micros();
  duration1 += currentMicros - previousMicros1;
  previousMicros1 = currentMicros;
  pulsecount1++;
}

void myinthandler2() // interrupt handler for pin 9
{
  unsigned long currentMicros = micros();
  duration2 += currentMicros - previousMicros2;
  previousMicros2 = currentMicros;
  pulsecount2++;
}
