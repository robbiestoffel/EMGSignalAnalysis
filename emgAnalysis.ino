#include "dataBuffer.h"
#include "movingCalculations.h"

Buffer dataBuffer;

const uint8_t pin = A0;
int data = 0;

float ma;
float mm;

void setup() {
  Serial.begin(115200);

  /* Reset Buffer */
  Buffer_Init(&dataBuffer);
}

void loop() {
  /* Keep buffer filled with the latest data */
  data = analogRead(pin);
  Buffer_Update(&dataBuffer, data);

  /* Run Calculations From Buffered Data */
  ma = movingAverage(&dataBuffer);
  mm = movingMaximum(&dataBuffer);

  Serial.print(ma);
  Serial.print(",");
  Serial.print(mm);
}