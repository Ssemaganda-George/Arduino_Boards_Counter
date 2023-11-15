// Define variables
volatile int connectedBoards = 0;  // Counter variable for connected boards
const int numBoards = 5;  // Adjust this based on the number of external boards
int boardPins[] = {2, 3, 4, 5, 6};  // Digital input pins for each external board
const int myBoardID = 1;  // Unique ID for each external board (change for each board)

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(9600);

  // Set the board pins as INPUT_PULLUP
  for (int i = 0; i < numBoards; i++) {
    pinMode(boardPins[i], INPUT_PULLUP);
  }

  // Set the signal pin as OUTPUT for the master board
  #ifdef IS_MASTER
    pinMode(13, OUTPUT);  // Use the built-in LED pin for signaling
  #endif

  // Attach interrupt to the rising edge of any board pin
  for (int i = 0; i < numBoards; i++) {
    attachInterrupt(digitalPinToInterrupt(boardPins[i]), boardConnected, RISING);
  }
}

void loop() {
  // Display the number of connected boards
  Serial.print("Connected Boards: ");
  Serial.println(connectedBoards);

  // Master board functionality
  #ifdef IS_MASTER
    // You can add additional logic or tasks here if needed
  #endif

  // Slave board functionality
  #ifndef IS_MASTER
    // Signal the main board
    digitalWrite(13, HIGH);  // Use the built-in LED pin for signaling

    // Calculate the blink rate based on the position of the board
    int blinkRate = connectedBoards - myBoardID + 1;

    // Blink the LED based on the calculated rate
    blinkLED(13, blinkRate);  // Use the built-in LED pin for signaling

    // You can add additional logic or tasks here if needed
  #endif
}

// Interrupt Service Routine (ISR) to increment the connected boards count
void boardConnected() {
  connectedBoards++;
}

// Function to blink the LED based on the blink rate
void blinkLED(int ledPin, int blinkRate) {
  int blinkDelay = 1000 / blinkRate;  // Calculate delay for blinking
  for (int i = 0; i < blinkRate; i++) {
    digitalWrite(ledPin, HIGH);
    delay(blinkDelay / 2);
    digitalWrite(ledPin, LOW);
    delay(blinkDelay / 2);
  }
}

