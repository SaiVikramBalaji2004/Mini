#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <OV7670.h>

// Define pin connections
#define CS_PIN 10

OV7670 camera;
File imageFile;

void setup() {
  Serial.begin(9600);
  // Initialize camera
  if (!camera.begin()) {
    Serial.println("Camera initialization failed");
    while (1);
  }
  Serial.println("Camera initialized");

  // Initialize SD card
  if (!SD.begin(CS_PIN)) {
    Serial.println("SD card initialization failed");
    while (1);
  }
  Serial.println("SD card initialized");
}

void loop() {
  // Capture image from camera
  uint8_t imageBuffer[640 * 480];
  camera.capture(imageBuffer);

  // Save captured image to SD card
  imageFile = SD.open("captured.bmp", FILE_WRITE);
  if (imageFile) {
    imageFile.write(imageBuffer, sizeof(imageBuffer));
    imageFile.close();
    Serial.println("Image saved to SD card");
  } else {
    Serial.println("Failed to save image");
  }

  // Compare with pre-stored image
  File storedImageFile = SD.open("stored.bmp");
  if (storedImageFile) {
    uint8_t storedImageBuffer[640 * 480];
    storedImageFile.read(storedImageBuffer, sizeof(storedImageBuffer));
    storedImageFile.close();

    bool imagesMatch = true;
    for (int i = 0; i < sizeof(imageBuffer); i++) {
      if (imageBuffer[i] != storedImageBuffer[i]) {
        imagesMatch = false;
        break;
      }
    }

    if (imagesMatch) {
      Serial.println("Images match!");
    } else {
      Serial.println("Images do not match.");
    }
  } else {
    Serial.println("Failed to open stored image");
  }

  delay(5000); // Wait for 5 seconds before capturing the next image
}
