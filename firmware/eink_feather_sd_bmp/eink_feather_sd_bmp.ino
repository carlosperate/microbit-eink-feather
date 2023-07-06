// Adafruit_ImageReader test for Adafruit E-Ink Breakouts.
// Demonstrates loading images from SD card or flash memory to the screen,
// to RAM, and how to query image file dimensions.
// Requires BMP file in root directory of QSPI Flash:
// hello.bmp.

#include <Adafruit_GFX.h>         // Core graphics library
#include "Adafruit_ThinkInk.h"
#include <SdFat.h>                // SD card & FAT filesystem library
#include <Adafruit_SPIFlash.h>    // SPI / QSPI flash library
#include <Adafruit_ImageReader_EPD.h> // Image-reading functions

// Comment out the next line to load from SPI/QSPI flash instead of SD card:
#define USE_SD_CARD 1

#define EPD_DC      12 // can be any pin, but required!
#define EPD_CS      9  // can be any pin, but required!
#define SRAM_CS     -1  // can set to -1 to not use a pin (uses a lot of RAM!)
#define EPD_BUSY    -1  // can set to -1 to not use a pin (will wait a fixed delay)
#define EPD_RESET   -1  // can set to -1 and share with chip Reset (can't deep sleep)
#define SD_CS       16  // SD card chip select

// Mono Displays
ThinkInk_290_Grayscale4_T5 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

// Filesystem
SdFat                    SD;         // SD card filesystem
Adafruit_ImageReader_EPD reader(SD); // Image-reader object, pass in SD filesys

// Image
Adafruit_Image_EPD   img;        // An image loaded into RAM

void setup(void) {

  ImageReturnCode stat; // Status from image-reading functions

  Serial.begin(9600);
  //while(!Serial);           // Wait for Serial Monitor before continuing

  display.begin();

  // The Adafruit_ImageReader constructor call (above, before setup())
  // accepts an uninitialized SdFat or FatVolume object. This MUST
  // BE INITIALIZED before using any of the image reader functions!
  Serial.print(F("Initializing filesystem..."));
  // SPI or QSPI flash requires two steps, one to access the bare flash
  // memory itself, then the second to access the filesystem within...

  // SD card is pretty straightforward, a single call...
  if(!SD.begin(SD_CS, SD_SCK_MHZ(10))) { // Breakouts require 10 MHz limit due to longer wires
    Serial.println(F("SD begin() failed"));
    for(;;); // Fatal error, do not continue
  }

  Serial.println(F("OK!"));

  // Load full-screen BMP file 'hello.bmp' at position (0,0) (top left).
  // Notice the 'reader' object performs this, with 'epd' as an argument.
  Serial.print(F("Loading hello.bmp to canvas..."));
  stat = reader.drawBMP((char *)"/hello.bmp", display, 0, 0);
  reader.printStatus(stat); // How'd we do?
  display.display();

  // Query the dimensions of image 'hello.bmp' WITHOUT loading to screen:
  int32_t width  = 0;
  int32_t height = 0;
  Serial.print(F("Querying hello.bmp image size..."));
  stat = reader.bmpDimensions("hello.bmp", &width, &height);
  reader.printStatus(stat);   // How'd we do?
  if(stat == IMAGE_SUCCESS) { // If it worked, print image size...
    Serial.print(F("Image dimensions: "));
    Serial.print(width);
    Serial.write('x');
    Serial.println(height);
  }

  delay(30 * 1000); // Pause 30 seconds before continuing because it's eInk

  Serial.print(F("Drawing canvas to EPD..."));
  display.clearBuffer();

  // Load small BMP 'hello.bmp' into a GFX canvas in RAM. This should fail
  // gracefully on Arduino Uno and other small devices, meaning the image
  // will not load, but this won't make the program stop or crash, it just
  // continues on without it. Should work on larger ram boards like M4, etc.
  stat = reader.loadBMP("/hello.bmp", img);
  reader.printStatus(stat); // How'd we do?
}

void loop() {
  for(int r=0; r<4; r++) {     // For each of 4 rotations...
    display.setRotation(r);    // Set rotation
    display.fillScreen(0);     // and clear screen
    display.clearBuffer();
    img.draw(display, 0, 0);
    display.display();
    delay(30 * 1000); // Pause 30 sec.
  }
}
