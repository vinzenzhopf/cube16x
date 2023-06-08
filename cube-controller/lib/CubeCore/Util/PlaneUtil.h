/*
 * PlaneUtil.h
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

class PlaneUtilClass {
public:
        /**
     * Clears the plane
     */
    void constexpr clearPlane(plane_t *plane){
        memset(plane, 0x00, sizeof(plane_t));
    }

    /**
     * Sets the plane to all 1.
     */
    void constexpr setPlane(plane_t *plane){
        memset(plane, 0xFF, sizeof(plane_t));
    }

    /**
     * Sets every byte of the plane to the given byte.
     */
    void constexpr setPlaneToByte(plane_t *plane, uint8_t value){
        memset(plane, value, sizeof(plane_t));
    }

    /**
     * Sets every row of the plane to the given row.
     */
    void constexpr setPlaneToRow(plane_t *plane, row_t row){
        for(int i = 0; i < PLANE_ROW_SIZE; i++){
            plane->asRows[i] = row;
        }
    }

    /**
     * Copys the plane data from "src" to "dst".
     */
    void constexpr copyPlane(plane_t *dst, plane_t *src){
        memcpy(dst, src, sizeof(plane_t));
    }

    /**
     * Gets the value of the led on the given coordinates.
     */
    bool constexpr getLed(plane_t *plane, uint8_t x, uint8_t y){
        uint16_t rowIndex = (uint16_t)y * CUBE_EDGE_SIZE;
        return (plane->asRows[rowIndex] >> x) & 1;
    }

    /**
     * Gets the value of the led on the given index.
     */
    bool constexpr getLed(plane_t *plane, uint16_t x){
        return (plane->asWords[ (word_t)x / LEDS_PER_ROW ] >> (x % LEDS_PER_ROW)) & 1;
    }

    /**
     * Sets the led with the given index to a given value.
     */
    void constexpr setLed(plane_t *plane, uint16_t index, bool value){
        row_t i = index / LEDS_PER_ROW;
        row_t newbit = !!value; // Also booleanize to force 0 or 1
        plane->asRows[i] ^= (-newbit ^ plane->asRows[i]) & (1 << (index % LEDS_PER_ROW));
    }

    /**
     * Sets the LED with the given corrdinates to the given value.
     */
    void constexpr setLed(plane_t *plane, uint8_t x, uint8_t y, bool value) {
        uint16_t index = ((uint16_t)y) * LEDS_PER_ROW;
        row_t newbit = !!value; // Also booleanize to force 0 or 1
        plane->asRows[index] ^= (-newbit ^ plane->asRows[index]) & ((row_t)1 << x);
    }

    void setLed(ECubeDirection dir, uint8_t x, uint8_t y, uint8_t z, bool value);

    void setRow(ECubeDirection dir, uint8_t x, uint8_t y, row_t *data);

};
extern PlaneUtilClass PlaneUtil;

