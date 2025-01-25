#include <iostream>

struct Base
{
    Base() { print(); }

    void print() { std::cout << "Base" << std::endl; }

    virtual ~Base() { print(); }
};

struct Derived: Base
{
    Derived() { print(); throw "error";}
    virtual void print() { std::cout << "Derived" << std::endl; }
    virtual ~Derived() { print(); }
};
int main()
{
    try
    {
        Base* base = new Derived();
        base->print();
        delete base;
    } 
    catch(...)
    {
        std::cout << "error";
    }

    return 0;
}