#include "snr.h"

// add necessary variables for calculation

void SNR_Init(SNRCalculator *SNR) {

  /* Clear filter buffer */
  for (uint8_t n = 0; n < SNR_Time_Interval; n++) {
    SNR->buf[n] = 0.0f;
  }

  /* Reset buffer index */
  SNR->bufIndex = 0;

  /* Clear filter output */
  SNR->out = 0.0f;
}

float SNR_Calculate(SNRCalculator *SNR, float data) {

  // temp buffer the data
  SNR->buf[SNR->bufIndex] = data;

  // Increase buffer index if necessary
  SNR->bufIndex++;

  if (SNR->bufIndex == SNR_Time_Interval) {
    SNR->bufIndex = 0;
  }

  // used the currently buffered data to calculate P_signal
  SNR->out = 0.0f;

  uint8_t sumIndex = SNR->bufIndex;

  for (uint8_t n = 0; n < SNR_Time_Interval; n++) {

    if (sumIndex > 0) {
      sumIndex--;
    } else {
      sumIndex = SNR_Time_Interval - 1;
    }

    // now actually do the calculation
  }

  // import in P_noise and use both values to calculate SNR

  // log SNR values, and buffer snr elsewhere to be averaged later?

}