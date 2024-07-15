#include "movingMaximum.h"

void MMFilter_Init(MMFilter *MM) {

  /* Clear filter buffer */
  for (uint8_t n = 0; n < movingMaximum_LENGTH; n++) {
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

  if (MM->bufIndex == movingMaximum_LENGTH) {
    MM->bufIndex = 0;
  }

  /* Compute new output sample */
  MM->out = 0.0f;

  for (int m = 0 ; m < movingMaximum_LENGTH ; m++)
  {
    if (MM->buf[m] > MM->out)
    {
      MM->out = MM->buf[m];
    }
  }

  /* Return Filtered Output */

  return MM->out;
}