#include "snr.h"

void SNR_Init(SNR) {

  /* Clear filter buffer */
  for (uint8_t n = 0; n < SNR_Time_Interval; n++) {
    SNR->buf[n] = 0.0f;
  }

  /* Reset buffer index */
  SNR->bufIndex = 0;

  /* Clear filter output */
  SNR->out = 0.0f;
}

float SNR_Calculate(SNR, float data) {

  // temp buffer the data

  // used the currently buffered data to calculate P_signal

  // import in P_noise and use both values to calculate SNR

  // log SNR values, and buffer snr elsewhere to be averaged later?

}

float SNR