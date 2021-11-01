
#pragma once

#include "stdint.h"
#include "IntVectors.h"
#include "BufferUtil.h"

#define MIN(A, B) (( (A) < (B) ) ? (A) : (B))
#define MAX(A, B) (( (A) > (B) ) ? (A) : (B))

struct IntCube {
    IntVector3D pos;
    IntVector3D size;

    IntCube() : pos(), size() {
    }
    virtual ~IntCube() = default;

    void set(int8_t x, int8_t y, int8_t z, int8_t depth, int8_t width, int8_t height){
        pos.x = x;
        pos.y = y;
        pos.z = z;
        size.x = depth;
        size.y = width;
        size.z = height;
    }

    void set(int8_t x, int8_t y, int8_t z, int8_t size){
        pos.x = x;
        pos.y = y;
        pos.z = z;
        this->size.x = size;
        this->size.y = size;
        this->size.z = size;
    }

    void set(IntVector3D &v1, IntVector3D &v2){
        pos.x = MIN(v1.x, v2.x);
        pos.y = MIN(v1.y, v2.y);
        pos.z = MIN(v1.z, v2.z);
        size.x = abs(v2.x-v1.x)+1;
        size.y = abs(v2.y-v1.y)+1;
        size.z = abs(v2.z-v1.z)+1;
    }

    void drawCube(BufferUtil *buffer){
        uint16_t index;
        for(int8_t x = pos.x; x < pos.x+size.x; x++){
            for(int8_t y = pos.y; y < pos.y+size.y; y++){
                for(int8_t z = pos.z; z < pos.z+size.z; z++){
                    index = (uint16_t)z * LEDS_PER_PLANE + (uint16_t)y * LEDS_PER_ROW + (uint16_t)x;
                    buffer->setLed(index, true);
                }
            }  
        }
    }

    void drawCubeWireframe(BufferUtil *buffer){
        IntVector3D topEdge = pos + size - 1;
        for(uint8_t x = pos.x; x < topEdge.x+1; x++){
            //buffer->setLed((uint8_t)1, (uint8_t)x, (uint8_t)0, true);
            buffer->setLed(x, pos.y, topEdge.z, true);
            buffer->setLed(x, topEdge.y, topEdge.z, true);
            buffer->setLed(x, pos.y, pos.z, true);
            buffer->setLed(x, topEdge.y, pos.z, true);
        }
        for(int8_t y = pos.y; y < topEdge.y; y++){
            buffer->setLed(pos.x, y, topEdge.z, true);
            buffer->setLed(topEdge.x, y, topEdge.z, true);
            buffer->setLed(pos.x, y, pos.z, true);
            buffer->setLed(topEdge.x, y, pos.z, true);
        } 
        for(int8_t z = pos.z+1; z < topEdge.z; z++){
            buffer->setLed(pos.x, pos.y, z, true);
            buffer->setLed(topEdge.x, pos.y, z, true);
            buffer->setLed(pos.x, topEdge.y, z, true);
            buffer->setLed(topEdge.x, topEdge.y, z, true);
        }  
    }
};

