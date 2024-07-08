#line 1 "C:\\Users\\robbi\\repos\\firFiltering\\MAFilter.h"
/* Header Code + Definitions */

#ifndef MA_FILTER_H
#define MA_FILTER_H

#include <stdint.h>

#define MA_FILTER_LENGTH 10

typedef struct {
  float buf[MA_FILTER_LENGTH];
  uint8_t bufIndex;

  float out;
} MAFilter;

void MAFilter_Init(MAFilter *MA);
float MAFilter_Update(MAFilter *MA, float inp);

#endif