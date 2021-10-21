

//CheckDiv8 is aktive
#define F_CPU_CLK 9600000UL
#define F_CPU ( F_CPU_CLK / 8 )

#include <avr/io.h>
#include <util/delay.h>

#define SBI(port,bit)	(port) |= (1 << (bit))
#define CBI(port,bit)	(port) &= ~(1<<(bit))

/* DDR Register Configuration (1=Output Pin, 0=Input Pin) */
#define DIR_B		0b00011001		// Input Data Port

#define PIN_DAT 3
#define PIN_CLK 4
#define PIN_INF 0

uint8_t volatile nDrawingState = 0;
uint8_t volatile nDrawingIndex = 0;
uint16_t volatile nData = 0b1010101010101010;

void setBit(volatile uint8_t *pPort, uint8_t nPin, bool bValue){
  if(bValue){
		*pPort |= (1<<nPin);
	}else{
		*pPort &= ~(1<<nPin);
	}
}

void writeData(uint16_t nData, uint8_t nIndex){
  bool bOn = ((nData & ((uint16_t)1 << nIndex)) != 0);
  if(bOn){
    SBI(PORTB, PIN_DAT);
  }else{
    CBI(PORTB, PIN_DAT);
  }
}

void drawingLoop()
{
  switch(nDrawingState){
    case 0:
      writeData(nData, nDrawingIndex);
      SBI(PORTB, PIN_DAT);
      nDrawingState = 10;
      break;
    case 10:
      SBI(PORTB, PIN_CLK);
      nDrawingState = 20;
      break;
    case 20:
      CBI(PORTB, PIN_CLK);
      nDrawingIndex++;
      nDrawingIndex %= 32;
      nDrawingState = 0;
      break;
    default:
      nDrawingState = 0;
      break;
  }
}

int main(void)
{
  //Initialize Port
	PORTB = 0b00000001;
  DDRB = DIR_B;

  uint32_t nCounter = 0;
  bool bValue = false;

  while(true){
    drawingLoop();
    if(nCounter == 0){
      nCounter = 50000;
      bValue = !bValue;
      setBit(&PORTB, PIN_INF, bValue);
    }else{
      nCounter--;
    }
  }
}


