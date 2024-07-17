#include <Arduino.h>
#line 1 "C:\\Users\\robbi\\repos\\emgAnalysis\\emgAnalysis.ino"
#include "dataBuffer.h"
#include "movingCalculations.h"
#include "snr.h"

Buffer dataBuffer;
Buffer maxBuffer;
// Buffer snrAverage;
// Buffer snrMaximum;

const uint8_t pin = A0;
int data = 0;

float ma;
float mm;
// float ma_snr;
// float mm_snr;

#line 18 "C:\\Users\\robbi\\repos\\emgAnalysis\\emgAnalysis.ino"
void setup();
#line 28 "C:\\Users\\robbi\\repos\\emgAnalysis\\emgAnalysis.ino"
void loop();
#line 3 "C:\\Users\\robbi\\repos\\emgAnalysis\\dataBuffer.ino"
void Buffer_Init(Buffer *B);
#line 15 "C:\\Users\\robbi\\repos\\emgAnalysis\\dataBuffer.ino"
void Buffer_Update(Buffer *B, float data);
#line 3 "C:\\Users\\robbi\\repos\\emgAnalysis\\movingCalculations.ino"
float movingAverage(Buffer *B);
#line 26 "C:\\Users\\robbi\\repos\\emgAnalysis\\movingCalculations.ino"
float movingMaximum(Buffer *B);
#line 6 "C:\\Users\\robbi\\repos\\emgAnalysis\\snr.ino"
float SNR_Calculate(Buffer *B);
#line 18 "C:\\Users\\robbi\\repos\\emgAnalysis\\emgAnalysis.ino"
void setup() {
  Serial.begin(115200);

  /* Reset Buffer */
  Buffer_Init(&dataBuffer);
  Buffer_Init(&maxBuffer);
  // Buffer_Init(&snrAverage);
  // Buffer_Init(&snrMaximum);
}

void loop() {
  /* Keep buffer filled with the latest data */
  data = analogRead(pin);

  Buffer_Update(&dataBuffer, data);
  mm = movingMaximum(&dataBuffer);
  
  Buffer_Update(&maxBuffer, mm);
  ma = movingAverage(&maxBuffer);

  // Buffer_Update(&snrAverage, ma);
  // Buffer_Update(&snrMaximum, mm);
  
  // ma_snr = SNR_Calculate(&snrAverage);
  // mm_snr = SNR_Calculate(&snrMaximum);

  Serial.print(data);
  Serial.print(",");
  Serial.println(ma);
}
#line 1 "C:\\Users\\robbi\\repos\\emgAnalysis\\dataBuffer.ino"
#include "dataBuffer.h"

void Buffer_Init(Buffer *B) {
   /* Initialize the Buffer */

   /* Clear filter buffer */
   for (uint8_t n = 0; n < bufferLength; n++) {
    B->buf[n] = 0.0f;
   }

   /* Reset Buffer Index */
   B->bufIndex = 0;
}

void Buffer_Update(Buffer *B, float data) {

  /* Store latest sample in buffer */
  B->buf[B->bufIndex] = data;

  /* Increment buffer index */
  B->bufIndex++;

  if (B->bufIndex == bufferLength) {
    B->bufIndex = 0;
  }
}


#line 1 "C:\\Users\\robbi\\repos\\emgAnalysis\\movingCalculations.ino"
#include "movingCalculations.h"

float movingAverage(Buffer *B) {
  MAout = 0.0f;

  uint8_t sumIndex = B->bufIndex;

  for (uint8_t n = 0; n < bufferLength; n++) {

    /* Decrease index and wrap if necessary */
    if (sumIndex > 0) {
      sumIndex--;
    } else {
      sumIndex = bufferLength - 1;
    }

    /* Convolution in parts */
    MAout += 0.0625 * B->buf[sumIndex];

  }

  /* Return Filtered Output */
  return MAout;
}

float movingMaximum(Buffer *B) {
  MMout = 0.0f;
  

  /* Calculate Maximum */
  for (uint8_t n = 0; n < bufferLength; n++) {
    if (B->buf[n] > MMout) {
      MMout = B->buf[n];
    }
  }

  /* Return Filtered Output */
  return MMout;
}
#line 1 "C:\\Users\\robbi\\repos\\emgAnalysis\\snr.ino"
#include "snr.h"

float signalPower;
float snr;

float SNR_Calculate(Buffer *B) {

  // Calculate Signal Power
  
  signalPower = 0;

  for (uint8_t n = 0; n < bufferLength; n++) {
    signalPower += ( B->buf[n] * B->buf[n] );
  }

  signalPower = signalPower / bufferLength;

  // Calculate Signal-to-noise ratio

  snr = 10 * log( signalPower / noisePower );

  return snr;
}
