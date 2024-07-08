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

float SNR_Calculate

float SNR