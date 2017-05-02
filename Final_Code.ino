#include <Wire.h> // Used to establied serial communication on the I2C bus
#include "SparkFunTMP102.h" // Used to send and recieve specific information from our sensor

const int buttonPinA = 22; // Board location of button
int stateA = 0;    // button is initially off
int buttonStateA = 0; //Variable which will read physical state of button (pressed or not)

const int buttonPinB = 23;
int stateB = 0;
int buttonStateB = 0;

int fetPinA = 4;   // location of MOFSET
int fetPinB = 3;
const int pinDown = 0;  // heat pad at 0% function

// Locations for interface led's
int led1A = 9;
int led2A = 10;
int led3A = 11;
int led4A = 12; 
int led1B = 5;
int led2B = 6; 
int led3B = 7; 
int led4B = 8;

// LED states (lit or not) for each LED
int state1A = 0;
int state2A = 0;
int state3A = 0;
int state4A = 0;
int state1B = 0;
int state2B = 0;
int state3B = 0;
int state4B = 0;

// Initialization of potentiometers
int potValueA;    // save analog value
const int potPinA = A1;  // location for potentiometer
int potValueB;
const int potPinB = A2;

// Connections
// VCC = 3.3V
// GND = GND
// SDA = A4
// SCL = A5
const int ALERT_PIN = A4;

TMP102 sensor0(0x49); // Initialize sensor at I2C address 0x48
// Sensor address can be changed with an external jumper to:
// ADD0 - Address
//  VCC - 0x49
//  SDA - 0x4A
//  SCL - 0x4B

TMP102 sensor1(0x48);     // Initialization of second TMP102 sensor
const int ALERT_PIN1 = A3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  sensor0.begin();  // Join I2C bus
  sensor0.setFault(0);
  sensor0.setAlertPolarity(1);
  sensor0.setAlertMode(0);
  sensor0.setConversionRate(2);
  sensor0.setExtendedMode(0);
  sensor0.setHighTempF(85.0);
  sensor0.setLowTempF(84.0);
  sensor1.begin();  // Join I2C bus
  sensor1.setFault(0);
  sensor1.setAlertPolarity(1);
  sensor1.setAlertMode(0);
  sensor1.setConversionRate(2);
  sensor1.setExtendedMode(0);
  sensor1.setHighTempF(85.0);
  sensor1.setLowTempF(84.0);
  pinMode(ALERT_PIN, INPUT);
  pinMode(ALERT_PIN1, INPUT);
  pinMode(buttonPinA, INPUT);
  pinMode(buttonPinB, INPUT);
  pinMode(potPinA, INPUT);
  pinMode(led1A, OUTPUT);
  pinMode(led2A, OUTPUT);
  pinMode(led3A, OUTPUT);
  pinMode(led4A, OUTPUT);
  pinMode(fetPinA, OUTPUT);
  pinMode(potPinB, INPUT);
  pinMode(led1B, OUTPUT);
  pinMode(led2B, OUTPUT);
  pinMode(led3B, OUTPUT);
  pinMode(led4B, OUTPUT);
  pinMode(fetPinB, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  float temperature, temp1;
  boolean alertPinState, alertRegisterState, aps1, ars1;

  // Turn sensors on to start temperature measurement.
  // Current consumtion typically ~10uA.
  sensor0.wakeup();
  sensor1.wakeup();

  // Read temperature data
  temperature = sensor0.readTempF();
  //temperature = sensor0.readTempC();
  temp1 = sensor1.readTempF();

  // Check for Alert
  alertPinState = digitalRead(ALERT_PIN); // read the Alert from pin
  alertRegisterState = sensor0.alert();   // read the Alert from register
  aps1 = digitalRead(ALERT_PIN1);
  ars1 = sensor1.alert();

  // Place sensor in sleep mode to save power.
  // Current consumtion typically <0.5uA.
  sensor0.sleep();
  sensor1.sleep();

  // Print temperature and alarm state of each TMP102
  Serial.print("Temperature 0: ");
  Serial.print(temperature);

  Serial.print("\t                 Temperature 1: ");
  Serial.println(temp1);

  Serial.print("Alert Pin 0: ");
  Serial.print(alertPinState);

  Serial.print(" Alert Register 0: ");
  Serial.print(alertRegisterState);

  Serial.print("\t Alert Pin 1: ");
  Serial.print(aps1);

  Serial.print("\t Alert Register 1: ");
  Serial.println(ars1);

  buttonStateA = digitalRead(buttonPinA);        // Read buttonState (pressed or not)
  buttonStateB = digitalRead(buttonPinB);
  potValueA = analogRead(potPinA);                 // Read analog (potentiometer)
  potValueA = map(potValueA, 0, 1023, 0, 260);        // Map potValue to 0-255 range
  potValueB = analogRead(potPinB);
  potValueB = map(potValueB, 0, 1023, 0, 260);
  Serial.print("pot valueA: ");
  Serial.print(potValueA);
  Serial.print("\t                         pot valueB: ");
  Serial.println(potValueB);

  buttonStateA = digitalRead(buttonPinA);
  if (buttonStateA == HIGH) {
    if (stateA == 0) {
      stateA = 1;
      for (int i; i < 3; i++) {       // Initiatie blinking sequence of LEDs
        digitalWrite(led1A, HIGH);
        delay(50);
        digitalWrite(led2A, HIGH);
        delay(50);
        digitalWrite(led3A, HIGH);
        delay(50);
        digitalWrite(led4A, HIGH);
        delay(50);
        digitalWrite(led4A, LOW);
        delay(50);
        digitalWrite(led3A, LOW);
        delay(50);
        digitalWrite(led2A, LOW);
        delay(50);
        digitalWrite(led1A, LOW);
      }
    }
    else if (stateA == 1) {
      stateA = 0;
      digitalWrite(led1A, LOW);
      digitalWrite(led2A, LOW);
      digitalWrite(led3A, LOW);
      digitalWrite(led4A, LOW);
      state1A = 0;
      state2A = 0;
      state3A = 0;
      state4A = 0;
    }
  }

  if (stateA == 1) {
    analogWrite(fetPinA, potValueA);                 // Write value onto MOSFET

    if (potValueA <= 260) {                         // 100% power, all LEDs are on
      digitalWrite(led1A, HIGH);
      digitalWrite(led2A, HIGH);
      digitalWrite(led3A, HIGH);
      digitalWrite(led4A, HIGH);
      state1A = 1;
      state2A = 1;
      state3A = 1;
      state4A = 1;

      if (potValueA < 191) {                    // Turn off LEDs one by one as potValueA decreases
        digitalWrite(led4A, LOW);
        state4A = 0;

        if (potValueA < 127) {
          digitalWrite(led3A, LOW);
          state3A = 0;

          if (potValueA < 63) {
            digitalWrite(led2A, LOW);
            state2A = 0;

            if (potValueA < 1) {
              digitalWrite(led1A, LOW);
              state1A = 0;

            }
          }
        }
      }
    }
  

  else if (stateA == 0 ) {
    analogWrite(fetPinA, pinDown);      // Turn off MOSFET and lights
    digitalWrite(led1A, LOW);
    digitalWrite(led2A, LOW);
    digitalWrite(led3A, LOW);
    digitalWrite(led4A, LOW);
  }
  }

// Now repeat all of the above for the second heating pad  
buttonStateB = digitalRead(buttonPinB);  
if (buttonStateB == HIGH) {
    if (stateB == 0) {
      stateB = 1;
      for (int i; i < 3; i++) {
        digitalWrite(led1B, HIGH);
        delay(50);
        digitalWrite(led2B, HIGH);
        delay(50);
        digitalWrite(led3B, HIGH);
        delay(50);
        digitalWrite(led4B, HIGH);
        delay(50);
        digitalWrite(led4B, LOW);
        delay(50);
        digitalWrite(led3B, LOW);
        delay(50);
        digitalWrite(led2B, LOW);
        delay(50);
        digitalWrite(led1B, LOW);
        //delay(50);
      }
    }
    else if (stateB == 1) {
      stateB = 0;
      digitalWrite(led1B, LOW);
      digitalWrite(led2B, LOW);
      digitalWrite(led3B, LOW);
      digitalWrite(led4B, LOW);
      state1B = 0;
      state2B = 0;
      state3B = 0;
      state4B = 0;
    }
  }

  Serial.print("Button StateA: ");
  Serial.print(stateA);

  Serial.print("\t                 Button StateB: ");
  Serial.println(stateB);

  if (stateB == 1) {
    analogWrite(fetPinB, 255);                 // Write value onto MOSFET

    if (potValueB <= 260) {
      digitalWrite(led1B, HIGH);
      digitalWrite(led2B, HIGH);
      digitalWrite(led3B, HIGH);
      digitalWrite(led4B, HIGH);
      state1B = 1;
      state2B = 1;
      state3B = 1;
      state4B = 1;

      if (potValueB < 191) {
        digitalWrite(led4B, LOW);
        state4B = 0;

        if (potValueB < 127) {
          digitalWrite(led3B, LOW);
          state3B = 0;

          if (potValueB < 63) {
            digitalWrite(led2B, LOW);
            state2B = 0;

            if (potValueB < 1) {
              digitalWrite(led1B, LOW);
              state1B = 0;

            }
          }
        }
      }
    }

  else if (stateB == 0) {
    analogWrite(fetPinB, 255);
    digitalWrite(led1B, LOW);
    digitalWrite(led2B, LOW);
    digitalWrite(led3B, LOW);
    digitalWrite(led4B, LOW);
    state1B = 0;
    state2B = 0;
    state3B = 0;
    state4B = 0;
  }
  }

// Print out results
  Serial.print("led1A: ");
  Serial.print(state1A);
  Serial.print("\t                         led1B: ");
  Serial.println(state1B);
  Serial.print("led2A: ");
  Serial.print(state2A);
  Serial.print("\t                         led2B: ");
  Serial.println(state2B);  
  Serial.print("led3A: ");
  Serial.print(state3A);
  Serial.print("\t                         led3B: ");
  Serial.println(state3B);
  Serial.print("led4A: ");
  Serial.print(state4A);
  Serial.print("\t                         led4B: ");
  Serial.println(state4B);

  Serial.print("Heat Pad A: ");
  Serial.print((potValueA/260)*100);
  Serial.print("%");
  Serial.print("\t                         Heat Pad B: ");
  Serial.println((potValueB/260)*100);
  Serial.print("%");
  Serial.println(" ");
}

