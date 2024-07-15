/* Header Code + Definitions */

#ifndef movingMaximum_H
#define movingMaximum_H

#include <stdint.h>

#define movingMaximum_LENGTH 16

typedef struct {
  float buf[movingMaximum_LENGTH];
  uint8_t bufIndex;

  float out;
} MMFilter;

void MMFilter_Init(MMFilter *MM);
float MMFilter_Update(MMFilter *MM, float inp);

#endif