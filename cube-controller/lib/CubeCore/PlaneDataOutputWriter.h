/* 
* PlaneOutputWriter.h
*
* Created: 07.07.2021 20:36:46
* Author: vhopf
*/


#ifndef __PLANEDATAOUTPUTWRITER_H__
#define __PLANEDATAOUTPUTWRITER_H__

#include "FrameBuffer.h"

#define BUFFER_COUNT 3

//Number of LED per Shift-Register Stack
#define SHIFT_REGISTER_WIDTH 32
#define SHIFT_REGISTER_BYTES (SHIFT_REGISTER_WIDTH / 8)
#define SHIFT_REGISTER_ROW_COUNT (BUFFER_SHORT_SIZE / SHIFT_REGISTER_WIDTH)

class PlaneDataOutputWriter
{
//variables
public:
protected:
    plane_t *plane;

    uint8_t nRowIndex;

    const uint8_t *PORT_DATA_OUT;
    const uint8_t *PORT_CONTROL_OUT;
    const uint8_t CONTROL_CLOCK_PIN;
    const uint8_t CONTROL_OE_PIN;
    const uint8_t CONTROL_STO_PIN;

    uint8_t nState;
private:

//functions
public:
	PlaneDataOutputWriter(const uint8_t *PORT_DATA_OUT, const uint8_t *PORT_CONTROL_OUT, 
        const uint8_t CONTROL_CLOCK_PIN, const uint8_t CONTROL_OE_PIN, const uint8_t CONTROL_STO_PIN);
	~PlaneDataOutputWriter();

    void setPlaneNumber(uint8_t nRowIndex);
    void latchData();

    void cyclicWritePlaneData();
protected:
private:
};

#endif //__PLANEDATAOUTPUTWRITER_H__