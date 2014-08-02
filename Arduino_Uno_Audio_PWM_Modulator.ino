/* Arduino Uno Audio PWM Modulator
 by Matt "Sigurthr" Giordano. 1/9/2014.
 Audio Input on Analog 0, PWM output on Digital 6.
 I/O circuitry as follows:
 Input: capacitor couple iPod audio through 4.7uF.
 Bias Input pin to 2.5V with one 10k resistor to 5v,
 and another 10k resistor to ground to form a voltage divider.
 Output goes to a RC filter made of a series 560 ohm resistor
 and a parallel 0.1uF capacitor.
 Capacitor couple this node to amplifier of choice.
 
 07/20/2014 - modified by Benjamin "Nefarius" Höglinger
 
 */

int duty;
int raw;
float volt;

void setup(){
  TCCR0B &= B11111000;
  TCCR0B |= B00000001;
  // PWM Boost pins 5 & 6 to 64KHz

  // ADC Boost Start - sets ADC clock to 1MHz
  // defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

  // set ADC prescaler to 16
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
  // ADC Boost End
}
void loop(){
  raw = analogRead (0);
  volt = (5.0 * raw) / 1023;
  duty = 255 * (volt / 5);
  analogWrite(6, duty);
}




