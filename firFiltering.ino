#include "movingAverage.h"
#include "movingMaximum.h"
// #include "snr.h"
// #include "FIRFilter.h"

MAFilter barFilterMovingAverage;
MAFilter secondMA;
MAFilter thirdMA;

MMFilter filterMovingMax;

// FIRFilter lpfAcc;

const int pin = A0;

void setup()
{
  MAFilter_Init(&barFilterMovingAverage);
  MAFilter_Init(&secondMA);
  MAFilter_Init(&thirdMA);

  MMFilter_Init(&filterMovingMax);

  // FIRFilter_Init(&lpfAcc);

  Serial.begin(115200);
}

void loop()
{
  /* Get Data */
  int data = analogRead(pin);

  /* Filter data */
  // MAFilter_Update(&barFilterMovingAverage, data);
  // MAFilter_Update(&secondMA, barFilterMovingAverage.out);
  // MAFilter_Update(&thirdMA, secondMA.out);

  MMFilter_Update(&filterMovingMax, data);

  /* Log raw and filtered data via Serial */
  Serial.print(data);
  // Serial.print(",");
  // Serial.print(barFilterMovingAverage.out);
  // Serial.print(",");
  // Serial.print(secondMA.out);
  Serial.print(",");
  Serial.println(filterMovingMax.out);
}
