/*
 * NativeEntropyMock.h
 *
 * Created: 24.10.2021 10:15:54
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#ifdef PLATFORM_NATIVE

#include <stdint.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

const uint32_t WDT_RETURN_BYTE=256;
const uint32_t WDT_RETURN_WORD=65536;

union ENTROPY_LONG_WORD 
{
  uint32_t int32;
  uint16_t int16[2];
  uint8_t int8[4];
};

class EntropyClass
{
public:
  void Initialize(void){
    srand (static_cast <unsigned> (time(0)));
  }

  uint32_t random(void){
      return rand();
  }
  uint32_t random(uint32_t max){
      return rand() % max;
  }
  uint32_t random(uint32_t min, uint32_t max){
      return (rand() % (max-min))+min;
  }
  uint8_t randomByte(void){
      return (uint8_t)(rand() % 0xFF);
  }
  uint16_t randomWord(void){
      return (uint16_t)(rand() % 0xFFFF);
  }
  float randomf(void){ 
      //TODO
      return 0.0;
  }
  float randomf(float max){
      //TODO
      return 0.0;
  }
  float randomf(float min, float max){
      //TODO
      return 0.0;
  }
  float rnorm(float mean, float stdDev){
      //TODO
      return 0.0;
  }
  uint8_t available(void){
      //TODO
      return 0;
  }
 private:
};
extern EntropyClass Entropy;

#endif

#endif // __NATIVEENTROPYMOCK_H__