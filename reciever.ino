#include <VirtualWire.h>

const int led_pin = 6;
const int receive_pin = 11;

void setup()
{
  delay(1000);                       // Give time for setup
  Serial.begin(9600);                // Initialize serial for debugging
  Serial.println("setup");

  vw_set_rx_pin(receive_pin);        // Set the receive pin
  vw_setup(2000);                    // Bits per second, 2000bps
  vw_rx_start();                     // Start the receiver
  pinMode(led_pin, OUTPUT);          // Set the LED pin as output
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];   // Buffer for incoming message
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen))  // If a message is received
  {
    digitalWrite(led_pin, HIGH);     // Turn on LED to indicate a good message
    Serial.print("Got: ");
    
    for (int i = 0; i < buflen; i++) // Print the message in HEX format
    {
      Serial.print(buf[i], HEX);
      Serial.print(' ');
    }
    Serial.println();
    digitalWrite(led_pin, LOW);      // Turn off the LED
  }
}
