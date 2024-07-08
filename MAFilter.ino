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