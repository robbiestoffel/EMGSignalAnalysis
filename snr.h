/* Header Code + Definitions (I think??) */

#ifndef SNR_H
#define SNR_H

#include <stdint.h>

// Time Interval
#define SNR_Time_Interval 10

// Predetermined Noise Power
// Calculating this will need to be automated in the future
// Currently and Arbitary value (10)
#define P_noise 10

typedef struct {
  // information needed to be kept track of to calc snr
  float buf[SNR_Time_Interval];
  uint8_t bufIndex;

  float out;
} SNR;

void SNR_Init(SNR)
void SNR_Calculate(SNR, float data)

#endef