//Vladislav Zolotukhin - Practice for Smart Pointers
#include <iostream>
#include <string>
#include <memory>
#include "SmartPointers.h"

int main() {

	example1();
	example2();
	example3();

}



void example1() {

	std::cout << "First Example\n\n";

	//Smart Pointers Example 

	//a block scope
	{
		std::unique_ptr<Entity> entity(new Entity()); //Default way of doing it
		//std::unique_ptr<Entity> entity = new Entity(); <--This doesn't work!
		//The constructor is explicit, there is no way to call it implicitly by doing a conversion
		entity->display(); //OK! Can call the class member functions

		//Preferred (safer way) of constructing a smart pointer, used to avoid any exceptions
		std::unique_ptr<Entity> entity2 = std::make_unique<Entity>(); //exception safety
		//if the constructor throws an exception, it won't result in a dangling pointer causing a memory leak

		//once this block closes, both of the above unique pointers will go out of scope and call the destructors of their objects
	}

	//*Remember: You cannot make copies of unique pointers! Each takes ownership of its resource and their lifetimes are tied.
	//If a unique pointer dies, it will clean up its resource, which would leave any other pointers that point toward the same resource dangling


	//Shared Pointers Example

	//a shared pointer, can create multiple of these or copy them. 
	std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>(); //Always do it this way
	//std::shared_ptr<Entity> sharedEntity(new Entity()); //This is an inefficient way of doing it
	
	//making a copy of the shared entity
	std::shared_ptr<Entity> e2 = sharedEntity;
	
	//shared pointers keep reference counters, keeping track of how many references there are to the pointer
	//once the reference counter reaches 0 (the last shared pointer is deleted) the memory is freed
	{
		std::shared_ptr<Entity> e3 = sharedEntity;
		//this pointer will go out of scope after this block finishes, but it will not destroy the entity!


	}
	std::shared_ptr<Entity> e4; //will assign this later
	{
		e4 = sharedEntity; 
		e4->display();
	}
	//If you place a breakpoint here, you'll see that no entity destructors have been called yet 
	//even though e3 and e4 have both already gone out of scope and been deleted


	//Weak Pointer
	std::weak_ptr<Entity> e5 = sharedEntity; 

	//Weak pointers do not take ownership of their resources, after this function returns control
	//the shared entity pointers will be deallocated, leaving e5 dangling
	//Can check to see if weak pointers are still active or not before calling them
	//This also does not increase the reference count of the shared pointer! 

	//sharedEntity destroyed message will occur here
}


void example2() {

	std::cout << "\n\nSecond Example\n" << std::endl;

	std::unique_ptr<int>u1 = std::make_unique<int>(25); //make a unique smart pointer of int type, assign value of 25

	//Must dereference the pointer to access its value
	std::cout << "Without dereferencing: " << u1 << std::endl; //prints in address instead of the value
	std::cout << "Dereferencing: " << *u1 << std::endl;

	//std::unique_ptr<int>u2 = u1; //Cannot share!

	std::unique_ptr<int>u2 = std::move(u1); //moving OK!

	std::cout << "Moved unique pointer!" << std::endl;
	std::cout << "Without dereferencing: " << u2 << "(same resource!)" << std::endl;
	std::cout << "Dereferencing: " << *u2 << "(same value!)\n" << std::endl;
	//CAUTION: u1 now becomes a null pointer. Do not attempt to dereference it
	//std::cout << "Dereferencing: " << *u1 << std::endl; <-BAD1

	/*   You can't catch null pointer exceptions even in a try...catch block. Don't do it!
	try {
		std::cout << "Dereferencing: " << *u1 << std::endl;
	}
	catch (...) {
		std::cout << "Don't try to dereference a null pointer. 'u1' has been moved!" << std::endl;
	}
	*/
	
	int a[]{ 7,14,21,28,35 };

	std::cout << "Array of unique pointers" << std::endl;
	for (int i = 0; i < 5; i++) {
		std::unique_ptr<int>aPtr = std::make_unique<int>(a[i]);
		std::cout << "A pointer: " << *aPtr << std::endl;
	} //no need to deallocate

	std::cout << "Accessing shared pointer reference counts" << std::endl;
	std::shared_ptr<Entity>sharedEntity = std::make_shared<Entity>();
	std::cout << "Shared Entity created! Entering block scope\n";
	{ 
		std::shared_ptr<Entity>s1  = sharedEntity;
		std::cout << "Shared Entity copied!\n";
		std::shared_ptr<Entity>s2 = sharedEntity;
		std::cout << "Shared Entity copied!\n";
		std::shared_ptr<Entity>s3 = sharedEntity;
		std::cout << "Shared Entity copied!\n";
		std::shared_ptr<Entity>s4 = sharedEntity;
		std::cout << "Shared Entity copied!\n";
		std::weak_ptr<Entity>w1 = sharedEntity; //These following 2 wont increase the reference count
		std::cout << "Shared Entity copied into a weak pointer!\n";
		std::weak_ptr<Entity>w2 = sharedEntity;
		std::cout << "Shared Entity copied into a weak pointer!\n";
		std::cout << "Shared Pointer Reference Count: " << sharedEntity.use_count() << std::endl;
	}
	std::cout << "Exited shared pointer copy block" << std::endl;
	std::cout << "Shared Pointer Reference Count: " << sharedEntity.use_count() << std::endl;

	//once this function returns control to main, sharedEntity will be destroyed
	//the weak pointers won't be able to keep it alive even if hypothetically they outlived this function scope
}

void example3() {
	std::cout << "\n\nExample 3\n\n";

	std::weak_ptr<Entity>ent;
	std::cout << "Weak pointer created outside of block scope, not assigned\n";
	{
		std::cout << "Entering block scope...\n\n";
		std::shared_ptr<Entity>ent2 = std::make_shared<Entity>();
		std::cout << "Shared pointer created for a new entity object in block scope\n";
		ent = ent2;
		std::cout << "Weak pointer assigned to the shared pointer in block scope\n";
		std::cout << "Calling shared pointer display: ";
		ent2->display();
		std::cout << std::endl;
		//cannot call class function from weak_ptr using -> or ->*, must convert it to a shared ptr
		//ent->display(); //BAD
		std::cout << "Converting weak pointer to shared pointer using .lock() to access display: ";
		std::shared_ptr<Entity>temp = ent.lock();
		temp->display(); //OK!
		std::cout << std::endl;
		std::cout << "Exiting block scope, shared pointer will be destroyed!\n" << std::endl;
	}
	std::cout << "Trying to access the weak pointer resource again outside of the block through a temp shared pointer\n";
	std::shared_ptr<Entity>temp = ent.lock();
	std::cout << "Assigned a new shared pointer of entity type (temp) to the weak pointer" << std::endl;
	std::cout << "Calling the entity display function through temp :";
	temp->display();
	std::cout << "Ok because we convert it to a smart pointer, entity display still accessible\n" << std::endl;
	//However, we would lose any member variables in the object if they existed

	std::cout << "We cannot dereference weak pointers directly, we always have to lock them!" << std::endl;

	std::weak_ptr<int>myInt;
	std::cout << "Case 2: Weak pointer of int type declared but not assigned, entering block scope...\n";
	{
		std::cout << "Creating a new shared pointer inside the block with a value of 42" << std::endl;
		std::shared_ptr<int>mySharedInt = std::make_shared<int>(42);
		std::cout << "Assigning weak pointer to shared pointer\n";
		myInt = mySharedInt;
		std::cout << "Shared pointer address: " << mySharedInt << std::endl;
		std::cout << "Shared pointer value: " << *mySharedInt << std::endl;
		std::cout << "Exiting block scope" << std::endl;
	}
	std::cout << "Trying to access the weak pointer resource (42) by converting it to a new shared pointer and assigning using the .lock method again\n";
	std::shared_ptr<int>temp2 = myInt.lock();
	std::cout << "Assigned a new shared pointer (temp) of int type to the weak pointer of int type\n";

	std::cout << "If we try to cout the new shared pointer temp, it will result in a compiler error!\n\n";
	//std::cout << *temp2 << std::endl;  //BAD
	//The memory address of the value 42 was deallocated within the previous block scope, the weak pointer did not keep it alive
	//even though it was assigned to it. There is nothing to output.

}