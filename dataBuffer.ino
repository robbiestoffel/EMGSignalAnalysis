#include "dataBuffer.h"

void Buffer_Init(Buffer *B) {
   /* Initialize the Buffer */

   /* Clear filter buffer */
   for (uint8_t n = 0; n < bufferLength; n++) {
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

  if (B->bufIndex == bufferLength) {
    B->bufIndex = 0;
  }
}

