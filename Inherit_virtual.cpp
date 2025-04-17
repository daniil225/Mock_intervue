#include <iostream>

template <typename T>
class cpp_class
{
    T a_, b_;

public:
    cpp_class(T a, T b) : a_(a), b_(b) {}

    void get() const
    {
        std::cout << a_ << " " << b_ << "\n";
    }

    void set_a(int val) { a_ = val; }
    void set_b(int val) { b_ = val; }
};


extern "C" void func()
{
    cpp_class<int> d1(10, 20);
    cpp_class<double> d2(2.45, 2.22);

    d1.get();
    d2.get();
}

extern "C" void func_rep(std::size_t sz)
{
    for(int i = 0; i < sz; i++)
        func();
}


int main()
{

    func_rep(4);
 
  

    return 0;
}
