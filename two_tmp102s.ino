#include <Wire.h>           // Used to establied serial communication on the I2C bus
#include "SparkFunTMP102.h" // Used to send and recieve specific information from our sensors

// Connections
// VCC = 3.3V
// GND = GND
// SDA = A4
// SCL = A5

TMP102 sensor0(0x48);     // Initialization of second TMP102 sensor
const int ALERT_PIN = A15;

TMP102 sensor1(0x49); // Initialize sensor at I2C address 0x48
// Sensor address can be changed with an external jumper to:
// ADD0 - Address
//  VCC - 0x49
//  SDA - 0x4A
//  SCL - 0x4B
const int ALERT_PIN1 = A1;

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
}

void loop() {
  // put your main code here, to run repeatedly:
  float temperature, temp1;                               //Initializes tmperature variables
  boolean alertPinState, alertRegisterState, aps1, ars1;  //Initializes alert states 

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

  // Print temperature and alarm state of each TMP102 sensor
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
}
