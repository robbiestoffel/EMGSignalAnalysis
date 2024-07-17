# 1 "C:\\Users\\robbi\\repos\\emgAnalysis\\emgAnalysis.ino"
# 2 "C:\\Users\\robbi\\repos\\emgAnalysis\\emgAnalysis.ino" 2
# 3 "C:\\Users\\robbi\\repos\\emgAnalysis\\emgAnalysis.ino" 2
# 4 "C:\\Users\\robbi\\repos\\emgAnalysis\\emgAnalysis.ino" 2

Buffer dataBuffer;
Buffer maxBuffer;
// Buffer snrAverage;
// Buffer snrMaximum;

const uint8_t pin = A0;
int data = 0;

float ma;
float mm;
// float ma_snr;
// float mm_snr;

void setup() {
  Serial.begin(115200);

  /* Reset Buffer */
  Buffer_Init(&dataBuffer);
  Buffer_Init(&maxBuffer);
  // Buffer_Init(&snrAverage);
  // Buffer_Init(&snrMaximum);
}

void loop() {
  /* Keep buffer filled with the latest data */
  data = analogRead(pin);

  Buffer_Update(&dataBuffer, data);
  mm = movingMaximum(&dataBuffer);

  Buffer_Update(&maxBuffer, mm);
  ma = movingAverage(&maxBuffer);

  // Buffer_Update(&snrAverage, ma);
  // Buffer_Update(&snrMaximum, mm);

  // ma_snr = SNR_Calculate(&snrAverage);
  // mm_snr = SNR_Calculate(&snrMaximum);

  Serial.print(data);
  Serial.print(",");
  Serial.println(ma);
}
# 1 "C:\\Users\\robbi\\repos\\emgAnalysis\\dataBuffer.ino"
# 2 "C:\\Users\\robbi\\repos\\emgAnalysis\\dataBuffer.ino" 2

void Buffer_Init(Buffer *B) {
   /* Initialize the Buffer */

   /* Clear filter buffer */
   for (uint8_t n = 0; n < 16; n++) {
    B->buf[n] = 0.0f;
   }

   /* Reset Buffer Index */
   B->bufIndex = 0;
}

void Buffer_Update(Buffer *B, float data) {

  /* Store latest sample in buffer */
  B->buf[B->bufIndex] = data;

  /* Increment buffer index */
  B->bufIndex++;

  if (B->bufIndex == 16) {
    B->bufIndex = 0;
  }
}
# 1 "C:\\Users\\robbi\\repos\\emgAnalysis\\movingCalculations.ino"
# 2 "C:\\Users\\robbi\\repos\\emgAnalysis\\movingCalculations.ino" 2

float movingAverage(Buffer *B) {
  MAout = 0.0f;

  uint8_t sumIndex = B->bufIndex;

  for (uint8_t n = 0; n < 16; n++) {

    /* Decrease index and wrap if necessary */
    if (sumIndex > 0) {
      sumIndex--;
    } else {
      sumIndex = 16 - 1;
    }

    /* Convolution in parts */
    MAout += 0.0625 * B->buf[sumIndex];

  }

  /* Return Filtered Output */
  return MAout;
}

float movingMaximum(Buffer *B) {
  MMout = 0.0f;


  /* Calculate Maximum */
  for (uint8_t n = 0; n < 16; n++) {
    if (B->buf[n] > MMout) {
      MMout = B->buf[n];
    }
  }

  /* Return Filtered Output */
  return MMout;
}
# 1 "C:\\Users\\robbi\\repos\\emgAnalysis\\snr.ino"
# 2 "C:\\Users\\robbi\\repos\\emgAnalysis\\snr.ino" 2

float signalPower;
float snr;

float SNR_Calculate(Buffer *B) {

  // Calculate Signal Power

  signalPower = 0;

  for (uint8_t n = 0; n < 16; n++) {
    signalPower += ( B->buf[n] * B->buf[n] );
  }

  signalPower = signalPower / 16;

  // Calculate Signal-to-noise ratio

  snr = 10 * log( signalPower / 10 );

  return snr;
}
