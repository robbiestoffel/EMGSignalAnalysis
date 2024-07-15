# 1 "C:\\Users\\robbi\\repos\\firFiltering\\firFiltering.ino"
# 2 "C:\\Users\\robbi\\repos\\firFiltering\\firFiltering.ino" 2
# 3 "C:\\Users\\robbi\\repos\\firFiltering\\firFiltering.ino" 2
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
# 1 "C:\\Users\\robbi\\repos\\firFiltering\\movingAverage.ino"
# 2 "C:\\Users\\robbi\\repos\\firFiltering\\movingAverage.ino" 2

static float MA_IMPULSE_RESPONSE[10] = {0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f};

void MAFilter_Init(MAFilter *MA) {

  /* Clear filter buffer */
  for (uint8_t n = 0; n < 10; n++) {
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

  if (MA->bufIndex == 10) {
    MA->bufIndex = 0;
  }

  /* Compute new output sample (via convolution) */
  MA->out = 0.0f;

  uint8_t sumIndex = MA->bufIndex;

  for (uint8_t n = 0; n < 10; n++) {

    /* Decrease index and wrap if necessary */
    if (sumIndex > 0) {
      sumIndex--;
    } else {
      sumIndex = 10 - 1;
    }

    /* Multiply impulse response with shifted input sample and add to output */
    MA->out += MA_IMPULSE_RESPONSE[n] * MA->buf[sumIndex];

  }

  /* Return Filtered Output */

  return MA->out;
}
# 1 "C:\\Users\\robbi\\repos\\firFiltering\\movingMaximum.ino"
# 2 "C:\\Users\\robbi\\repos\\firFiltering\\movingMaximum.ino" 2

void MMFilter_Init(MMFilter *MM) {

  /* Clear filter buffer */
  for (uint8_t n = 0; n < 16; n++) {
    MM->buf[n] = 0.0f;
  }

  /* Reset buffer index */
  MM->bufIndex = 0;

  /* Clear filter output */
  MM->out = 0.0f;
}

float MMFilter_Update(MMFilter *MM, float inp) {

  /* Store latest sample in buffer */
  MM->buf[MM->bufIndex] = inp;

  /* Increment buffer index and wrap around if necessary */
  MM->bufIndex++;

  if (MM->bufIndex == 16) {
    MM->bufIndex = 0;
  }

  /* Compute new output sample */
  MM->out = 0.0f;

  for (int m = 0 ; m < 16 ; m++)
  {
    if (MM->buf[m] > MM->out)
    {
      MM->out = MM->buf[m];
    }
  }

  /* Return Filtered Output */

  return MM->out;
}
# 1 "C:\\Users\\robbi\\repos\\firFiltering\\snr.ino"
// #include "snr.h"

// // add necessary variables for calculation

// void SNR_Init(SNRCalculator *SNR) {

//   /* Clear filter buffer */
//   for (uint8_t n = 0; n < SNR_Time_Interval; n++) {
//     SNR->buf[n] = 0.0f;
//   }

//   /* Reset buffer index */
//   SNR->bufIndex = 0;

//   /* Clear filter output */
//   SNR->out = 0.0f;
// }

// float SNR_Calculate(SNRCalculator *SNR, float data) {

//   // temp buffer the data
//   SNR->buf[SNR->bufIndex] = data;

//   // Increase buffer index if necessary
//   SNR->bufIndex++;

//   if (SNR->bufIndex == SNR_Time_Interval) {
//     SNR->bufIndex = 0;
//   }

//   // used the currently buffered data to calculate P_signal
//   SNR->out = 0.0f;

//   uint8_t sumIndex = SNR->bufIndex;

//   for (uint8_t n = 0; n < SNR_Time_Interval; n++) {

//     if (sumIndex > 0) {
//       sumIndex--;
//     } else {
//       sumIndex = SNR_Time_Interval - 1;
//     }

//     // now actually do the calculation
//   }

//   // import in P_noise and use both values to calculate SNR

//   // log SNR values, and buffer snr elsewhere to be averaged later?

// }
