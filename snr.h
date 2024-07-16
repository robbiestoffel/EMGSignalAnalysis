/* Header Code + Definitions (I think??) */

#ifndef SNR_H
#define SNR_H

#include <stdint.h>
#include "dataBuffer.h"

// Predetermined Noise Power
// Calculating this will need to be automated in the future
// Currently and Arbitary value (10)
#define noisePower 10

float SNR_Calculate(Buffer *B);

#endif