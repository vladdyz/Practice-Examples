//Vlad Zolotukhin OOP345 Review
#include <iostream>

class Base {
public:
    Base() { std::cout << "Base constructor\n"; }
    ~Base() { std::cout << "Base destructor\n"; }
};

class Derived1 : public Base {
public:
    Derived1() { std::cout << "Derived1 constructor\n"; }
    ~Derived1() { std::cout << "Derived1 destructor\n"; }
};

class Derived2 : public Base {
public:
    Derived2() { std::cout << "Derived2 constructor\n"; }
    ~Derived2() { std::cout << "Derived2 destructor\n"; }
};

class Final : public Derived1, public Derived2 {
public:
    Final() { std::cout << "Final constructor\n"; }
    ~Final() { std::cout << "Final destructor\n"; }
};

int main() {
    Final f;
    return 0;
}

/* 
Output:
Base constructor
Derived1 constructor
Base constructor
Derived2 constructor
Final constructor
Final destructor
Derived2 destructor
Base destructor
Derived1 destructor
Base destructor

*/