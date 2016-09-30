/*     ---------------------------------------------------------
 *     |  i has temperature monitoring                         |
 *     ---------------------------------------------------------
 *
 *  sets LED color based on environmental temperature
 *  reports the temperature (F) in the serial console
 *  offers an on/off switch for the LED using a momentary button
 *
 */

/*
 * TMP36 Pin Variables
 * the analog pin the TMP36's Vout (sense) pin is connected to
 * the resolution is 10 mV / degree centigrade 
 * (500 mV offset) to make negative temperatures an option
 */
int temperaturePin = 0;

/*
 * RGB LED pins
 * the three digital pins of the digital LED
 * 9 = redPin, 10 = greenPin, 11 = bluePin
 */
int ledDigitalOne[] = {9, 10, 11}; 

// push button pin
int buttonPin = 13;
int buttonStatus = 1;
byte button;
byte oldbuttonStatus = 0;
byte state = 0;

/*
 * Define on as LOW (this is because we use a common 
 * Anode RGB LED (common pin is connected to +5 volts)
 * Define off as HIGH
 */
const boolean ON = LOW;
const boolean OFF = HIGH;

// predefined colors
const boolean RED[] = {ON, OFF, OFF};    
const boolean GREEN[] = {OFF, ON, OFF}; 
const boolean BLUE[] = {OFF, OFF, ON}; 
const boolean YELLOW[] = {ON, ON, OFF}; 
const boolean CYAN[] = {OFF, ON, ON}; 
const boolean MAGENTA[] = {ON, OFF, ON}; 
const boolean WHITE[] = {ON, ON, ON}; 
const boolean BLACK[] = {OFF, OFF, OFF}; 

// temperature range definitions
int hotTemp = 85;
int warmTemp = 77;
int normalTemp = 73;
int coldTemp = 71;
// int freezingTemp = ;

// an Array that stores the predefined colors
const boolean* COLORS[] = {RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, WHITE, BLACK};

/*
 * setup() - this function runs once when you turn your Arduino on
 * we initialize the serial connection with the computer and
 * setup input/output pins
 */
void setup()
{
  // start the serial connection with the copmuter
  Serial.begin(9600);

  // set the three LED pins as outputs
  for(int i = 0; i < 3; i++){
   pinMode(ledDigitalOne[i], OUTPUT);
  }

  // declare push button as input
  pinMode(buttonPin, INPUT);
}

// run over and over again
void loop()
{
  // getting the voltage reading from the temperature sensor
  float temperature = getVoltage(temperaturePin);

  /*
   * converting from 10 mv per degree wit 500 mV offset
   * to degrees ((volatge - 500mV) times 100)
   */
  temperature = (((temperature - .5) * 100) * 1.8) + 32;

  // printing the result
  Serial.println(temperature);
  //Serial.println(" degrees F");

  // check what the button is doing
  buttonStatus = digitalRead(buttonPin);

  // same as if(buttonStatus == high && oldbuttonStatus == low)
  // if(buttonStatus && !oldbuttonStatus) {
    // we have a new button press
    // if the state is off, turn it on
    // if(state == 0) {
      // do stuff
      // state = 1;
      // Serial.println("lights on");
      // set the LED color based on the temperature
      if(temperature >= 85) {
        // hot
        setColor(ledDigitalOne, RED);
      } else if((temperature < 85) && (temperature > 77)) {
        // warm
        setColor(ledDigitalOne, YELLOW);
      } else if((temperature <= 77) && (temperature > 74)) {
        // normal
        setColor(ledDigitalOne, GREEN);
      } else if((temperature <=74 ) && (temperature > 71)) {
        // cold
        setColor(ledDigitalOne, BLUE);
      } else if(temperature <=71) {
        // freezing
        setColor(ledDigitalOne, CYAN);
      } else {
        // wtf
        setColor(ledDigitalOne, WHITE);
      }
    // if the state is on, turn it off
    // } else {
      // state = 0;
      // Serial.println("lights off");
      // setColor(ledDigitalOne, BLACK);
    // }
    // oldbuttonStatus = 1;
  // same as if(buttonStatus == low && oldbuttonStatus == high)
  // } else if(!buttonStatus && oldbuttonStatus) {
    // the button was released
    // oldbuttonStatus = 0;
  // }

  // pause for 1/4 of a second
  delay(250);
}

/*
 * getVoltage() - returns the voltage on the analog input defined by
 * pin
 */
float getVoltage(int pin){
  /*
   * converting from a 0 to 1023 digital range
   * to 0 to 5 volts (each 1 reading equals ~ 5 millivolts
   */
  return (analogRead(pin) * .004882814);
}

/* 
 * sets an led to any color
 * led - a three element array defining the three color pins (led[0] = redPin, led[1] = greenPin, led[2] = bluePin)
 * color - a three element boolean array (color[0] = red value (LOW = on, HIGH = off), color[1] = green value, color[2] =blue value)
 */
void setColor(int* led, boolean* color){
  for(int i = 0; i < 3; i++){
    digitalWrite(led[i], color[i]);
  }
}

// a version of setColor that allows for using const boolean colors
void setColor(int* led, const boolean* color){
  boolean tempColor[] = {color[0], color[1], color[2]};
  setColor(led, tempColor);
}
