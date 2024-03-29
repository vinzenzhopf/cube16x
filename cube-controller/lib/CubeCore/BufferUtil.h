/*
 * BufferUtil.h
 *
 * Defines the frame-buffer and methods for operating on it.
 *
 *
 * Created: 01.07.2017 12:13:51
 * Author: Vinzenz hopf (happyfreak.de)
 */

#pragma once

#include <LedCube16x.h>
#include <string.h>
#include <math.h>
#include "Util/IntVectors.h"
#include "Util/PlaneUtil.h"

class BufferUtil {
    public:
    protected:
        buffer_t *buffer;
    private:
	public:
        BufferUtil(){
            buffer = nullptr;
        }
        BufferUtil(buffer_t *buffer) :
            buffer(buffer){
        }
        ~BufferUtil() = default;

        /**
         * Updates the reference of the buffer.
         */
        virtual void updateBufferRef(buffer_t *newBuffer) {
            buffer = newBuffer;
        }

        /**
         * Returns the pointer to the current buffer.
         */
        virtual buffer_t* getBufferRef(){
            return buffer;
        }

		/**
         * Clears the buffer.
         */
		void clearBuffer(){
            memset(buffer, 0x00, sizeof(buffer_t));
        }

        /**
         * Sets the buffer to all 1.
         */
        void setBuffer(){
            memset(buffer, 0xFF, sizeof(buffer_t));
        }

        /**
         * Sets the Buffer to an alternating pattern, where each bit is alternating zu the prevoius.
         */
        void setBufferAlternating(){
            // for(uint8_t i = 0; i < PLANE_COUNT; i++){
            //     for(uint8_t j = 0; j < PLANE_SHORT_SIZE; j++){
            //         buffer.asPlanes[i].asShort[j] = (j%2==0)?0b1010101010101010:0b0101010101010101;
            //     }
            // }
        }

        /**
         * Tests the to the given Byte-Pattern
         */
        void setBufferToByte(uint8_t byte){
            for(uint16_t i = 0; i < BUFFER_BYTE_SIZE; i++){
                buffer->asBytes[i] = byte;
            }
        }

        /**
         * Tests the to the given Row-Pattern
         */
        void setBufferToRow(row_t row){
            for(uint8_t i = 0; i < BUFFER_ROW_SIZE; i++){
                buffer->asRows[i] = row;
            }
        }

        /**
         * Copys the given buffer to this buffer.
         */
        void copyFromBuffer(buffer_t *pBuffer){
            // for(uint16_t i = 0; i < BUFFER_ROW_SIZE; i++){
            //     buffer->asRows[i] = pBuffer->asRows[i];
            // }
            //memcpy(dest, src, len)
            memcpy(&buffer->asBytes, pBuffer->asBytes, BUFFER_BYTE_SIZE);
        }

        /**
         * Copys the this buffer to the given buffer.
         */
        void copyToBuffer(buffer_t *pBuffer){
            // for(uint16_t i = 0; i < BUFFER_ROW_SIZE; i++){
            //     pBuffer->asRows[i] = buffer->asRows[i];
            // }
            //memcpy(dest, src, len)
            memcpy(pBuffer->asBytes, &buffer->asBytes, BUFFER_BYTE_SIZE);
        }

        /**
         * Returns the value of the LED on the given corrdinates. Uses the default cube orientation (y is front).
         */
        bool getLed(uint8_t x, uint8_t y, uint8_t z){
            uint16_t index = (uint16_t)z * PLANE_LED_COUNT + (uint16_t)y * CUBE_EDGE_SIZE;
            return (buffer->asRows[index] >> x) & 1;
        }

        /**
         * Returns the value of the LED on the given corrdinates. Uses the default cube orientation (y is front).
         */
        bool getLed(uint16_t x){
            return (buffer->asWords[ x / LEDS_PER_WORD] >> (x % LEDS_PER_WORD)) & 1;
        }

        /**
         * Sets the led with the given index to a given value.
         */
        void setLed(uint16_t index, bool value){
            row_t i = index/LEDS_PER_ROW;
            row_t newbit = !!value; // Also booleanize to force 0 or 1
            buffer->asRows[i] ^= (-newbit ^ buffer->asRows[i]) & (1 << (index%LEDS_PER_ROW));
        }

        /**
         * Sets the LED with the given corrdinates to the given value.
         */
        void setLed(uint8_t x, uint8_t y, uint8_t z, bool value) {
            row_t i = ((row_t)z * PLANE_LED_COUNT + (row_t)y * LEDS_PER_ROW) / LEDS_PER_ROW;
            row_t newbit = !!value; // Also booleanize to force 0 or 1
            buffer->asRows[i] ^= (-newbit ^ buffer->asRows[i]) & (1 << (row_t)x);
        }

        void setLed(ECubeDirection dir, uint8_t x, uint8_t y, uint8_t z, bool value){
            
        }

        void setRow(ECubeDirection dir, uint8_t x, uint8_t y, row_t *data){
            
        }

        void setPlane(ECubeDirection dir, uint8_t x, uint8_t data){
            uint8_t d = !!data;
            plane_t plane;
            memset(&plane, d, sizeof(plane_t));
            setPlane(dir, x, &plane);
        }

        void setPlane(uint8_t x, plane_t *data){
            memcpy(&(buffer->asPlanes[x]), data, sizeof(plane_t));
        }

        void setPlane(ECubeDirection dir, uint8_t x, plane_t *data){
            if(dir == ECubeDirection::Z){
                setPlane(x, data);
            }else{
                for(uint8_t i = 0; i < LEDS_PER_ROW; i++){
                    for(uint8_t j = 0; j < LEDS_PER_ROW; j++){
                        bool value = PlaneUtil.getLed(data, i, j);
                        if(dir == ECubeDirection::X){
                            setLed(x, j, i, value);
                        }else if(dir == ECubeDirection::Y){
                            setLed(j, x, i, value);
                        }
                    }
                }
            }
        }

        // /**
        //  * Rotate the current buffer by the given angle on the given axis.
        //  */
        // void rotateBuffer(ECubeDirection direction, float angle){
        //     float s = sin(angle);
        //     float c = cos(angle);
        // }

        // void rotateBufferX(float angle){

        // }

        
    protected:
        Vector3D rotatePointX(Vector3D point, float cos, float sin){
            return {
                point.x,
                point.y * cos - point.z * sin,
                point.y * sin + point.z * cos
            };
        }
        Vector3D rotatePointY(Vector3D point, float cos, float sin){
            return {
                point.x * cos + point.z * sin,
                point.y,
                point.x * (-sin) + point.z * cos
            };
        }
        Vector3D rotatePointZ(Vector3D point, float cos, float sin){
            return {
                point.x * cos - point.y * sin,
                point.x * sin + point.y * cos,
                point.z
            };
        }

    private:
};

