#line 1 "C:\\Users\\robbi\\repos\\emgAnalysis\\movingAverage.h"
/* Header Code + Definitions */

#ifndef movingAverage_H
#define movingAverage_H

#include <stdint.h>

#define movingAverage_LENGTH 10

typedef struct {
  float buf[movingAverage_LENGTH];
  uint8_t bufIndex;

  float out;
} MAFilter;

void MAFilter_Init(MAFilter *MA);
float MAFilter_Update(MAFilter *MA, float inp);

#endif