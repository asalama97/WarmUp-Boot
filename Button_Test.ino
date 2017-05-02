
// Const int - value never changes (ideal for defining a location)
const int buttonPin = 7;     // Location of button on Arduino

// Int - variable that will change:
int buttonState = 0;         // variable for reading the button's status (pressed or not)
int state = 0;               // variable that will indicate whether system is on or off

void setup() {
  // initialize the pushbutton pin as an input:
  Serial.begin(9600);         // Allows user to open Serial monitor
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the button value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    if (state == 0) {                 // If the system was off when the button was pressed, turn it on
      state = 1;
    }
    else if (state == 1) {          // Otherwise, turn it off
      state = 0;

    }
  }

  Serial.print("Button State: ");   // Print values onto Serial monitor
  Serial.println(state);

  //delay(500);                 // Delay purely for printing purposes
                                // Comment it out to see the print outs more clearly

}
