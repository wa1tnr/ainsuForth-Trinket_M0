// Sat Dec  2 20:50:31 UTC 2017
// 4735-b0d-00a-   the -00x- is new Dec 2, 2017 on the Trinket M0 branch

// previous timestampe (CPX branch):

// Sat Jul 29 18:14:02 UTC 2017
// 4735-b0b-01-

#include <Adafruit_DotStar.h>

#define NUMPIXELS 1 // Number of LEDs in strip

// On the Trinket M0 schematic, physical pins 1 and 2 of the SAMD21E18,
// giving perhaps PA00 and PA01.  Spoken for elsewhere:

// D1 D4 D3 D0 D2
// A0 A2 A3 A4 A1

// This leaves perhaps D5 D6 as likely.  Look for this.
#define DATAPIN    3 // Gemma M0
#define CLOCKPIN   4 // Gemma M0

Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

void setup_dotstar() {
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}

int      head  = 0, tail = -3;  // Index of first 'on' and 'off' pixels
uint32_t color = 0x010000;      // 'On' color (starts red)

void loop_dotstar() {
  strip.setPixelColor(head, color); // 'On' pixel at head
  strip.setPixelColor(tail, 0);     // 'Off' pixel at tail
  strip.show();                     // Refresh strip
  delay(20);                        // Pause 20 milliseconds (~50 FPS)

  if(++head >= NUMPIXELS) {         // Increment head index.  Off end of strip?
    head = 0;                       //  Yes, reset head index to start
    if((color >>= 8) == 0)          //  Next color (R->G->B) ... past blue now?
      color = 0x010000;             //   Yes, reset to red
  }
  if(++tail >= NUMPIXELS) tail = 0; // Increment, reset tail index

Serial.println("\r\nWent off tail.  Bye from dotstar.");

}

// END
