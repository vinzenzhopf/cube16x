/*
 * TestClass.h
 *
 * Created: 06.07.2021 21:28:51
 *  Author: vhopf
 */ 


#ifndef TESTCLASS_H_
#define TESTCLASS_H_

class TestClass {
	int width, height;
	public:
	void set_values (int,int);
	int area() {return width*height;}
};

#endif /* TESTCLASS_H_ */