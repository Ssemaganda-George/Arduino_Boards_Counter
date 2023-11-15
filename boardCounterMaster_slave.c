// Code for master board

// Define variables
volatile int connectedBoards = 0;  // Counter variable for connected boards
const int numBoards = 5;  // Adjust this based on the number of external boards
int boardPins[] = {2, 3, 4, 5, 6};  // Digital input pins for each external board

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(9600);

  // Set the board pins as INPUT_PULLUP
  for (int i = 0; i < numBoards; i++) {
    pinMode(boardPins[i], INPUT_PULLUP);
  }

  // Attach interrupt to the rising edge of any board pin
  for (int i = 0; i < numBoards; i++) {
    attachInterrupt(digitalPinToInterrupt(boardPins[i]), boardConnected, RISING);
  }
}

void loop() {
  // Display the number of connected boards
  Serial.print("Connected Boards: ");
  Serial.println(connectedBoards);

  // You can add additional logic or tasks here if needed
}

// Interrupt Service Routine (ISR) to increment the connected boards count
void boardConnected() {
  connectedBoards++;
}


// Code for slave boards

// Define variables
const int myBoardID = 1;  // Unique ID for each external board (change for each board)
const int signalPin = 2;  // Digital output pin to signal the main board
const int ledPin = 13;    // Built-in LED pin for signaling

void setup() {
  // Set the signal pin as OUTPUT
  pinMode(signalPin, OUTPUT);

  // Set the LED pin as OUTPUT
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Signal the main board
  digitalWrite(signalPin, HIGH);

  // Calculate the blink rate based on the position of the board
  int blinkRate = connectedBoards - myBoardID + 1;

  // Blink the LED based on the calculated rate
  blinkLED(blinkRate);

  // You can add additional logic or tasks here if needed
}

// Function to blink the LED based on the blink rate
void blinkLED(int blinkRate) {
  int blinkDelay = 1000 / blinkRate;  // Calculate delay for blinking
  for (int i = 0; i < blinkRate; i++) {
    digitalWrite(ledPin, HIGH);
    delay(blinkDelay / 2);
    digitalWrite(ledPin, LOW);
    delay(blinkDelay / 2);
  }
}
