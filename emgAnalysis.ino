#include "dataBuffer.h"
#include "movingCalculations.h"
#include "snr.h"

Buffer dataBuffer;
Buffer snrAverage;
Buffer snrMaximum;

const uint8_t pin = A0;
int data = 0;

float ma;
float mm;
float ma_snr;
float mm_snr;

void setup() {
  Serial.begin(115200);

  /* Reset Buffer */
  Buffer_Init(&dataBuffer);
  Buffer_Init(&snrAverage);
  Buffer_Init(&snrMaximum);
}

void loop() {
  /* Keep buffer filled with the latest data */
  data = analogRead(pin);
  Buffer_Update(&dataBuffer, data);

  /* Run Calculations From Buffered Data */
  ma = movingAverage(&dataBuffer);
  mm = movingMaximum(&dataBuffer);

  Buffer_Update(&snrAverage, ma);
  Buffer_Update(&snrMaximum, mm);
  
  ma_snr = SNR_Calculate(&snrAverage);
  mm_snr = SNR_Calculate(&snrMaximum);

  Serial.print(ma);
  Serial.print(",");
  Serial.print(mm);
}