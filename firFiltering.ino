#include "MAFilter.h"
// #include "FIRFilter.h"

MAFilter barFilterMovingAverage;
MAFilter secondMA;
MAFilter thirdMA;

// FIRFilter lpfAcc;

const int pin = A0;
int val = 0;
const int outpin = A1;

void setup()
{
  MAFilter_Init(&barFilterMovingAverage);
  MAFilter_Init(&secondMA);
  MAFilter_Init(&thirdMA);

  // FIRFilter_Init(&lpfAcc);

  Serial.begin(115200);
}

void loop()
{
  // GET DATA
  int data = analogRead(pin);

  /* Filter data */
  MAFilter_Update(&barFilterMovingAverage, data);
  MAFilter_Update(&secondMA, barFilterMovingAverage.out);
  MAFilter_Update(&thirdMA, secondMA.out);

  /* Log raw and filtered data via Serial */
  Serial.print(data);
  Serial.print(",");
  Serial.print(barFilterMovingAverage.out);
  Serial.print(",");
  Serial.print(secondMA.out);
  Serial.print(",");
  Serial.println(thirdMA.out);

  val = thirdMA.out;

  analogWrite(outpin, val);
}
