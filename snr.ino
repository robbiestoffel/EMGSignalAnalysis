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