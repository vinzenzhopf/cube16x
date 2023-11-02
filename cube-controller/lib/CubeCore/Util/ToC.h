/*
 * Toc.h
 *
 * Trigger on change 
 *
 *
 * Created: 02.11.2023 19:38:43
 * Author: Vinzenz hopf (happyfreak.de)
 */

#pragma once

#include <LedCube16x.h>
#include <string.h>
#include <math.h>

template <typename T> 
class ToC{
    private:
        T lastValue;
    public:
        bool Q;
        bool call(T value){
            Q = (value != lastValue);
            lastValue = value;
            return Q;    
        }    
};
