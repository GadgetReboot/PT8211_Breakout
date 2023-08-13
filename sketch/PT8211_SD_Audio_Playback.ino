/*
  ESP32 I2S MP3/WAV SD Card Playback Test
 
  Hardware:  Uses external I2S DAC or ESP32 built in DAC

  Uses ESP32-audioI2S Library https://github.com/schreibfaul1/ESP32-audioI2S

  Gadget Reboot
*/

#include "Arduino.h"
#include "Audio.h"
#include "SD.h"
#include "FS.h"

// SD Card SPI pins
#define CS             5
#define SPI_MOSI      23
#define SPI_MISO      19
#define SPI_SCK       18

// I2S external DAC pins
#define I2S_DOUT      25   // data in to I2S module
#define I2S_LRC       26   // WS (word select)
#define I2S_BCLK      27   // bit clock


// uncomment one of these to set up audio interface for internal/external DAC
Audio audio;  // use external I2S DAC
//Audio audio(true, I2S_DAC_CHANNEL_BOTH_EN);  // use esp32 internal DAC

void setup() {
  Serial.begin(115200);

  // configure SPI for SD card access
  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);

  // init SD card
  if (!SD.begin(CS)) {
    Serial.println("SD card error");
    while (true);
  }

  // configure external I2S DAC - comment out these lines if using internal DAC
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setI2SCommFMT_LSB(true); // data format for PT8211 is different from some other DACs. Comment out if using other formats

  audio.setVolume(12);

  // play specific mp3 or wav file on SD card
  audio.connecttoFS(SD,"/testfile.mp3");
  //audio.connecttoFS(SD, "/testfile.wav");
}

void loop() {
  audio.loop();
}
