#include <VirtualWire.h>

const int led_pin = 11;
const int transmit_pin = 12;
const int transmit_en_pin = 3;

void setup()
{
  // Initialize the IO and ISR
  vw_set_tx_pin(transmit_pin);       // Set the transmit pin
  vw_set_ptt_pin(transmit_en_pin);   // Set the transmit enable pin
  vw_set_ptt_inverted(true);         // For DR3100 or similar modules
  vw_setup(2000);                    // Bits per second, 2000bps
  pinMode(led_pin, OUTPUT);          // Set the LED pin as output
}

byte count = 1;

void loop()
{
  char msg[7] = {'h','e','l','l','o',' ','#'};
  msg[6] = count;                    // Update message count
  digitalWrite(led_pin, HIGH);       // Turn on LED to indicate transmission
  vw_send((uint8_t *)msg, 7);        // Send the message
  vw_wait_tx();                      // Wait until message is fully sent
  digitalWrite(led_pin, LOW);        // Turn off LED
  delay(1000);                       // Wait for a second before sending again
  count++;                           // Increment the message count
}
