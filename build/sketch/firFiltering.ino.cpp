#include <Arduino.h>
#line 1 "C:\\Users\\robbi\\repos\\firFiltering\\firFiltering.ino"
#include "MAFilter.h"
// #include "FIRFilter.h"

MAFilter barFilterMovingAverage;
MAFilter secondMA;
MAFilter thirdMA;

// FIRFilter lpfAcc;

const int pin = A0;
int val = 0;
const int outpin = A1;

#line 14 "C:\\Users\\robbi\\repos\\firFiltering\\firFiltering.ino"
void setup();
#line 25 "C:\\Users\\robbi\\repos\\firFiltering\\firFiltering.ino"
void loop();
#line 5 "C:\\Users\\robbi\\repos\\firFiltering\\MAFilter.ino"
void MAFilter_Init(MAFilter *MA);
#line 19 "C:\\Users\\robbi\\repos\\firFiltering\\MAFilter.ino"
float MAFilter_Update(MAFilter *MA, float inp);
#line 14 "C:\\Users\\robbi\\repos\\firFiltering\\firFiltering.ino"
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

#line 1 "C:\\Users\\robbi\\repos\\firFiltering\\MAFilter.ino"
#include "MAFilter.h"

static float MA_IMPULSE_RESPONSE[MA_FILTER_LENGTH] = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f};

void MAFilter_Init(MAFilter *MA) {

  /* Clear filter buffer */
  for (uint8_t n = 0; n < MA_FILTER_LENGTH; n++) {
    MA->buf[n] = 0.0f;
  }

  /* Reset buffer index */
  MA->bufIndex = 0;

  /* Clear filter output */
  MA->out = 0.0f;
}

float MAFilter_Update(MAFilter *MA, float inp) {

  /* Store latest sample in buffer */
  MA->buf[MA->bufIndex] = inp;

  /* Increment buffer index and wrap around if necessary */
  MA->bufIndex++;

  if (MA->bufIndex == MA_FILTER_LENGTH) {
    MA->bufIndex = 0;
  }

  /* Compute new output sampe (via convolution) */
  MA->out = 0.0f;

  uint8_t sumIndex = MA->bufIndex;

  for (uint8_t n = 0; n < MA_FILTER_LENGTH; n++) {

    /* Decrease index and wrap if necessary */
    if (sumIndex > 0) {
      sumIndex--;
    } else {
      sumIndex = MA_FILTER_LENGTH - 1;
    }

    /* Multiply impulse response with shifted input sample and add to output */
    MA->out += MA_IMPULSE_RESPONSE[n] * MA->buf[sumIndex];

  }

  /* Return Filtered Output */

  return MA->out;
}
