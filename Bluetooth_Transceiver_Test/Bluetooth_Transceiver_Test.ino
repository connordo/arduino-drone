#include <SoftwareSerial.h>

// Define the data transmit/receive pins in Arduino

#define TxD 2

#define RxD 3

SoftwareSerial mySerial(RxD, TxD); // RX, TX for Bluetooth

void setup() {
  mySerial.begin(9600); // For Bluetooth
  Serial.begin(9600); // For the IDE monitor Tools -> Serial Monitor
  // Any code that you want to run once....
  pinMode(13, OUTPUT);
}

void loop() {

  // put your main code here, to run repeatedly:
  boolean isValidInput;

  do {
    byte c; // get the next character from the bluetooth serial port
    while ( !mySerial.available() ) ; // LOOP...
    c = mySerial.read(); // Execute the option based on the character recieved
    Serial.print(c); // Print the character received to the IDE serial monitor
    switch ( c ) {

      case 'a': // You've entered a
        // Do the code you need when 'a' is received.....
        digitalWrite(13, HIGH);
        mySerial.println( "You've entered an 'a'" );
        isValidInput = true;
        break;

      case 'b': // You've entered b
        // Do the code you need when 'a' is received.....
        digitalWrite(13, LOW);
        mySerial.println( "You've entered an 'b'" );
        isValidInput = true;
        break;

      default:
        // Do the code you need when any other character is received.....
        mySerial.println( "Please enter 'a' or 'b'" );
        isValidInput = false;
        break;

    }
  } while ( isValidInput == true ); // Repeat the loop
}
