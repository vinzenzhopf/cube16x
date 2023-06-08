/*
 * StatisticArray.h
 *
 * Created: 08.06.2023 13:15:38
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

template <class T, int ARRAY_SIZE, unsigned long T_MAX_VALUE> 
class StatisticArray final {
    public:
    protected:
        T _data[ARRAY_SIZE];
        T _floatingSum;
        float _floatingMean;
        T _maxValue;
        T _minValue;
        int _index;
    private:
	public:
        StatisticArray() :
            _floatingSum(0),
            _maxValue(0),
            _minValue(0),
            _index(0){
            resetBuffer();
        }
        ~StatisticArray() = default;
        
        void push(T value){
            _index = (_index+1) % ARRAY_SIZE;
            _floatingSum -= _data[_index];
            _data[_index] = value;
            _floatingSum += value;

            _floatingMean = ((float)_floatingSum) / ARRAY_SIZE;
            if(value > _maxValue){
                _maxValue = value;
            }
            if(value < _minValue){
                _minValue = value;
            }
        }

        void resetBuffer(){
            for(int i = 0; i < ARRAY_SIZE; i++){
                _data[i] = 0;
            }
            _floatingSum = 0;
            _floatingMean = 0;
            _maxValue = 0;
            _minValue = T_MAX_VALUE;
            _index = ARRAY_SIZE - 1;
        }

        uint32_t Sum() const { return _floatingSum; }
        float Mean() const { return _floatingMean; }
        uint32_t Min() const { return _minValue; }
        uint32_t Max() const { return _maxValue; }
        uint32_t Last() const { return _data[_index]; }

    protected:        
    private:  
};

