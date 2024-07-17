#line 1 "C:\\Users\\robbi\\repos\\emgAnalysis\\movingCalculations.h"
#ifndef movingCalculations_H
#define movingCalculations_H

#include "dataBuffer.h"

float MAout;
float MMout;

float movingAverage(Buffer *B);
float movingMaximum(Buffer *B);

#endif