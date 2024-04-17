//Vladislav Zolotukhin - Practice for Smart Pointers
#ifndef SMARTPOINTERS_H
#define SMARTPOINTERS_H
#include <iostream>

void example1();
void example2();
void example3();

class Entity {

public:
	Entity() {
		std::cout << "Entity Constructed" << std::endl;
	}
	~Entity() {
		std::cout << "Entity Destroyed" << std::endl;
	}
	void display() {
		std::cout << "Entity Display Function" << std::endl;
	}




};


#endif
