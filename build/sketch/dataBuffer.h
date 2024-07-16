#line 1 "C:\\Users\\robbi\\repos\\emgAnalysis\\dataBuffer.h"
#ifndef dataBuffer_H
#define dataBuffer_H

#include <stdint.h>

#define bufferLength 16

typedef struct {
  float buf[bufferLength];
  uint8_t bufIndex;
} Buffer;

void Buffer_Init(Buffer *B);
void Buffer_Update(Buffer *B, float data);

#endif