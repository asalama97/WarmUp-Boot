int potValue;             // save analog value (potentiometer)
const int potPin = A1; // location for potentiometer
int led1 = 48;
int led2 = 49;
int led3 = 47;
int led4 = 43;

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(potPin, INPUT);                     // Declare the inputs and outputs
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
  
}
void loop() {
    // put your main code here, to run repeatedly:
    potValue = analogRead(potPin);                // Read the position of the potentiometer
    potValue = map(value, 0, 1023, 0, 255);       // Translate potValue into a PWM (0-255) scale
    Serial.print("pot value: ");                  // Print the potValue
    Serial.println(value);

  if (potValue <= 255) {              // If the potentiometer is turned on to the max, turn all the lights on
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    if (potValue < 191) {             // Turn the LEDs off one by one, in sequence, in equal increments of the potValue
      digitalWrite(led4, LOW);
      if (potValue < 127) {
        digitalWrite(led3, LOW);
        if (potValue < 64) {
          digitalWrite(led2, LOW);
          if (potValue < 1) {
           digitalWrite(led1, LOW);                              
          }                    
        }             
      }          
    }       
  }
}
