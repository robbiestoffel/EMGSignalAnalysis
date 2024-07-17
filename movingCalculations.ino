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