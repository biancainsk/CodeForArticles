#include <iostream>
using namespace std;

class MyClass
{
public:
    MyClass() { cout << "Default constructor\n"; }
    MyClass(const MyClass& other) { cout << "Copy constructor\n"; }
    MyClass(MyClass&&) { std::cout << "Move constructor\n"; }
    ~MyClass() { cout << "Destructor\n"; }
};


void takeByValue(MyClass obj)
{
    cout << "Inside function\n";
}

MyClass retNRVO()
{
    MyClass obj;
    return obj;
}

MyClass retURVO()
{
    return MyClass();
}

void throwFunc()
{
    MyClass exception;
    std::cout << "About to throw..." << std::endl;
    throw exception;
}

void throwFuncTemp()
{
    std::cout << "About to throw..." << std::endl;
    throw MyClass();
}

int main()
{
    ///// INITIALIZATION /////
    std::cout << "----------INITIALIZATION-----------\n";

    // 1.1: 
    MyClass obj1C;
    MyClass obj2C = obj1C; // == MyClass obj2C(obj1C); == MyClass obj2C{obj1C};
    std::cout << "---\n";
    // OUT C++ 11, copy elision disabled:            // OUT C++ 11, copy elision not disabled:
    // Default constructor                           // Default constructor
    // Copy constructor                              // Copy constructor

    // OUT C++ 17, copy elision disabled:            // OUT C++ 17, copy elision not disabled:
    // Default constructor                           // Default constructor
    // Copy constructor                              // Copy constructor

    // 1.2:
    MyClass obj1M;
    MyClass obj2M = std::move(obj1M); // == MyClass obj2M(std::move(obj1M)); == MyClass obj2M{std::move(obj1M)};
    std::cout << "---\n";
    // OUT C++ 11, copy elision disabled:            // OUT C++ 11, copy elision not disabled:
    // Default constructor                           // Default constructor
    // Move constructor                              // Move constructor

    // OUT C++ 17, copy elision disabled:            // OUT C++ 17, copy elision not disabled:
    // Default constructor                           // Default constructor
    // Move constructor                              // Move constructor

    // 1.3:
    MyClass obj3M = MyClass();
    // OUT C++ 11, copy elision disabled:            // OUT C++ 11, copy elision not disabled:
    // Default constructor                           // Default constructor
    // Move constructor
    // Destructor

    // OUT C++ 17, copy elision disabled:            // OUT C++ 17, copy elision not disabled:
    // Default constructor                           // Default constructor


    std::cout << "---------END INITIALIZATION------------\n";
    //////////////////////////////////////////////////////////

    ///// FUNC ARG PASSING /////
    std::cout << "----------FUNC ARG PASSING-----------\n";

    // 2.1:
    MyClass obj3C;
    takeByValue(obj3C);
    std::cout << "---\n";
    // OUT C++ 11, copy elision disabled:            // OUT C++ 11, copy elision not disabled:
    // Default constructor                           // Default constructor
    // Copy constructor                              // Copy constructor
    // Inside function                               // Inside function
    // Destructor                                    // Destructor

    // OUT C++ 17, copy elision disabled:            // OUT C++ 17, copy elision not disabled:
    // Default constructor                           // Default constructor
    // Copy constructor                              // Copy constructor
    // Inside function                               // Inside function
    // Destructor                                    // Destructor

    // 2.2:
    MyClass obj4M;
    takeByValue(std::move(obj4M));
    std::cout << "---\n";
    // OUT C++ 11, copy elision disabled:            // OUT C++ 11, copy elision not disabled:
    // Default constructor                           // Default constructor
    // Move constructor                              // Move constructor
    // Inside function                               // Inside function
    // Destructor                                    // Destructor

    // OUT C++ 17, copy elision disabled:            // OUT C++ 17, copy elision not disabled:
    // Default constructor                           // Default constructor
    // Move constructor                              // Move constructor
    // Inside function                               // Inside function
    // Destructor                                    // Destructor

    // 2.3:
    takeByValue(MyClass());
    std::cout << "---\n";
    // OUT C++ 11, copy elision disabled:            // OUT C++ 11, copy elision not disabled:
    // Default constructor                           // Default constructor
    // Move constructor                              // Inside function
    // Inside function                               // Destructor
    // Destructor
    // Destructor

    // OUT C++ 17, copy elision disabled:            // OUT C++ 17, copy elision not disabled:
    // Default constructor                           // Default constructor
    // Inside function                               // Inside function  
    // Destructor                                    // Destructor
   

    std::cout << "----------END FUNC ARG PASSING-----------\n";
    //////////////////////////////////////////////////////////

    ///// FUNC RETURN NRVO /////
    std::cout << "----------FUNC RETURN NRVO-----------\n";

    // 3.1:
    MyClass obj5M = retNRVO();
    std::cout << "---\n";
    // OUT C++ 11, copy elision disabled:            // OUT C++ 11, copy elision not disabled:
    // Default constructor                           // Default constructor
    // Move constructor
    // Destructor
    // Move constructor
    // Destructor

    // OUT C++ 17, copy elision disabled:            // OUT C++ 17, copy elision not disabled:
    // Default constructor                           // Default constructor
    // Move constructor
    // Destructor

    // 3.2:
    auto lambdaFunc2 = []()
    {
        MyClass obj;
        return obj;
    };
    MyClass obj2L = lambdaFunc2();
    std::cout << "---\n";
    // OUT C++ 11, copy elision disabled:            // OUT C++ 11, copy elision not disabled:
    // Default constructor                           // Default constructor
    // Move constructor
    // Destructor
    // Move constructor
    // Destructor

    // OUT C++ 17, copy elision disabled:            // OUT C++ 17, copy elision not disabled:
    // Default constructor                           // Default constructor
    // Move constructor
    // Destructor


    std::cout << "----------END FUNC RETURN NRVO-----------\n";
    //////////////////////////////////////////////////////////

    ///// FUNC RETURN URVO /////
    std::cout << "----------FUNC RETURN URVO-----------\n";
    
    // 4.1:
    MyClass obj7M = retURVO();
    std::cout << "---\n";
    // OUT C++ 11, copy elision disabled:            // OUT C++ 11, copy elision not disabled:
    // Default constructor                           // Default constructor
    // Move constructor
    // Destructor
    // Move constructor
    // Destructor

    // OUT C++ 17, copy elision disabled:            // OUT C++ 17, copy elision not disabled:
    // Default constructor                           // Default constructor

    // 4.2:
    auto lambdaFunc3 = []()
    {
        return MyClass();
    };
    MyClass obj3L = lambdaFunc3();
    // OUT C++ 11, copy elision disabled:            // OUT C++ 11, copy elision not disabled:
    // Default constructor                           // Default constructor
    // Move constructor
    // Destructor
    // Move constructor
    // Destructor

    // OUT C++ 17, copy elision disabled:            // OUT C++ 17, copy elision not disabled:
    // Default constructor                           // Default constructor


    std::cout << "----------END FUNC RETURN URVO-----------\n";
    //////////////////////////////////////////////////////////

    ///// THROW AND HANDLER /////
    std::cout << "----------THROW AND HANDLER-----------\n";

    // 5.1:
    try
    {
        throwFunc();
    }
    catch(MyClass e)
    {
        std::cout << "Caught exception\n";
    }
    std::cout << "---\n";
    // OUT C++ 11, copy elision disabled:            // OUT C++ 11, copy elision not disabled:
    // Default constructor                           // Default constructor
    // About to throw...                             // About to throw...
    // Move constructor                              // Move constructor
    // Destructor                                    // Destructor
    // Copy constructor                              // Copy constructor
    // Caught exception                              // Caught exception
    // Destructor                                    // Destructor
    // Destructor                                    // Destructor

    // OUT C++ 17, copy elision disabled:            // OUT C++ 17, copy elision not disabled:
    // Default constructor                           // Default constructor
    // About to throw...                             // About to throw...
    // Move constructor                              // Move constructor
    // Destructor                                    // Destructor
    // Copy constructor                              // Copy constructor
    // Caught exception                              // Caught exception
    // Destructor                                    // Destructor
    // Destructor                                    // Destructor

    // 5.2:
    try
    {
        throwFuncTemp();
    }
    catch(const MyClass& e)
    {
        std::cout << "Caught exception\n";
    }
    // OUT C++ 11, copy elision disabled:            // OUT C++ 11, copy elision not disabled:
    // About to throw...                             // About to throw...
    // Default constructor                           // Default constructor
    // Move constructor                              // Caught exception
    // Destructor                                    // Destructor
    // Caught exception                              
    // Destructor                                        

    // OUT C++ 17, copy elision disabled:            // OUT C++ 17, copy elision not disabled:
    // About to throw...                             // About to throw...
    // Default constructor                           // Default constructor
    // Caught exception                              // Caught exception
    // Destructor                                    // Destructor                              

    std::cout << "----------END THROW AND HANDLER-----------\n";
    //////////////////////////////////////////////////////////
}
