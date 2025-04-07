#include <iostream>

template<typename T>
const T& min(const T& a, const T& b)
{
    std::cout << "const T& min(const T& a, const T& b)" << std::endl;
    return a < b ? a: b;
}

double min(double a, double b)
{
    std::cout << "double min(double a, double b)" << std::endl;
    return a < b ? a: b;
}

template<typename T>
const T& min(const T& a, const T& b, const T& c)
{
    std::cout << "const T& min(const T& a, const T& b, const T& c)" << std::endl;
    T val = min(min(a,b),c);

    std::cout << &val << "\n";
    return val;
}

void p(const double& a)
{
    std::cout << &a << "\n";
}

int main()
{
    double a = 1.0, b = 2.0, c = 3.0;
    double m = min(a,b,c);


    std::cout << "val m = " << m << "\n";
    std::cout << "ptr m = " << &m << "\n";

    std::cout << "Hello world\n"
    return 0;

}