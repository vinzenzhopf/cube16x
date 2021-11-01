
#pragma once

#include "stdint.h"

struct Vector3D { 
    float x;
	float y;
	float z;
}; 

struct IntVector3D{
    int8_t x;
    int8_t y;
    int8_t z;

    IntVector3D() : 
            x(0), y(0), z(0){
    }
    IntVector3D(int8_t x, int8_t y, int8_t z) : 
            x(x), y(y), z(z){
    }
    IntVector3D(IntVector3D *v){
        x = v->x;
        y = v->y;
        z = v->z;
    }
    virtual ~IntVector3D() = default;

    void set(int8_t x, int8_t y, int8_t z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void reset(){
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    IntVector3D operator+(const IntVector3D &b) const {
        IntVector3D c;
        c.x = this->x + b.x;
        c.y = this->y + b.y;
        c.z = this->z + b.z;
        return c;
    }

    IntVector3D operator+(const int8_t &b) const {
        IntVector3D c;
        c.x = this->x + b;
        c.y = this->y + b;
        c.z = this->z + b;
        return c;
    }

    IntVector3D operator-(const IntVector3D &b) const {
        IntVector3D c;
        c.x = this->x - b.x;
        c.y = this->y - b.y;
        c.z = this->z - b.z;
        return c;
    }

    IntVector3D operator-(const int8_t &b) const {
        IntVector3D c;
        c.x = this->x - b;
        c.y = this->y - b;
        c.z = this->z - b;
        return c;
    }
};

struct IntVector2D {
    int8_t x;
    int8_t y;

    public:
    IntVector2D() : 
            x(0), y(0) {
    }
    IntVector2D(int8_t x, int8_t y) : 
            x(x), y(y){
    }
    IntVector2D(IntVector2D *v){
        x = v->x;
        y = v->y;
    }

    void set(int8_t x, int8_t y){
        this->x = x;
        this->y = y;
    }

    void reset(){
        this->x = 0;
        this->y = 0;
    }
    
    IntVector2D operator+(const IntVector2D &b) const {
        IntVector2D c;
        c.x = this->x + b.x;
        c.y = this->y + b.y;
        return c;
    }

    IntVector2D operator-(const IntVector2D &b) const {
        IntVector2D c;
        c.x = this->x - b.x;
        c.y = this->y - b.y;
        return c;
    }
};