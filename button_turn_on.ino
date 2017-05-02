
// Const int - value never changes (ideal for defining a location)
const int buttonPin = 7;     // Location of button on Arduino
const int led1 = 48;         // Location of LEDs on Arduino
const int led2 = 49;
const int led3 = 47;
const int led4 = 43;

// Int - variable that will change:
int buttonState = 0;         // variable for reading the button's status (pressed or not)
int state = 0;               // variable that will indicate whether system is on or off

void setup() {
  // initialize the pushbutton pin as an input:
  Serial.begin(9600);         // Allows user to open Serial monitor
  pinMode(buttonPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  // read the state of the button value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    if (state == 0) {                 // If the system was off when the button was pressed, turn it on
      state = 1;
       for (int i; i < 3; i++) {       // Initiatie blinking sequence of LEDs
        digitalWrite(led1, HIGH);
        delay(50);
        digitalWrite(led2, HIGH);
        delay(50);
        digitalWrite(led3, HIGH);
        delay(50);
        digitalWrite(led4, HIGH);
        delay(50);
        digitalWrite(led4, LOW);
        delay(50);
        digitalWrite(led3, LOW);
        delay(50);
        digitalWrite(led2, LOW);
        delay(50);
        digitalWrite(led1, LOW);
      }
    }
    else if (state == 1) {          // Otherwise, turn it off
      state = 0;
      digitalWrite(led1, LOW);       // Ensure that the LEDs turn off as well
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
    }
  }

  Serial.print("Button State: ");   // Print values onto Serial monitor
  Serial.println(state);

  //delay(500);                 // Delay purely for printing purposes
                                // Comment it out to see the print outs more clearly

}
