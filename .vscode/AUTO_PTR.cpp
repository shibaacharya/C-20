#include <iostream>
#include <string.h>
using namespace std;
template<class T>
class AUTO_PTR {
public:
    explicit AUTO_PTR(T *p = 0): m_AutoPtr(p) {}
    template<class U>
    AUTO_PTR(AUTO_PTR<U>& rhs): m_AutoPtr(rhs.release()) {}
    ~AUTO_PTR() { delete m_AutoPtr; }
    template<class U>
    AUTO_PTR<T>& operator=(AUTO_PTR<U>& rhs)
    {
        if (this != &rhs) reset(rhs.release());
        return *this;
    }
    T& operator*() const { return *m_AutoPtr; }
    T* operator->() const { return m_AutoPtr; }
    T* get() const { return m_AutoPtr; }
    T* release()
    {
        T *oldPointee = m_AutoPtr;
        m_AutoPtr = 0;
        return oldPointee;
    }
    void reset(T *p = 0)
    {
        if (m_AutoPtr != p) {
            delete m_AutoPtr;
            m_AutoPtr = p;
        }
    }
    private:
        T *m_AutoPtr;
};
class MyClass
{
public:
    MyClass() //ctor
    {
        str = new char[255];
        cout << "Memory Allocated" << endl;
    }
    ~MyClass()
    {
        delete[] str;
        cout << "Memory deallocated" << endl;
    }
    void display()
    {
        strcpy(str, "This is test");
        cout << str << endl;
    }
private:
    char *str;
   
};
int main()
{
    cout << "inside main" << endl;
    AUTO_PTR<MyClass> b = AUTO_PTR<MyClass> (new MyClass);
    b.get()->display();
    AUTO_PTR<MyClass> c = b;
    if(b.get())
        cout << "valid" << endl;
    // Print the compiler version using predefined macros
    std::cout << "Compiler Version: ";

    // __GNUC__ is defined for GCC (GNU Compiler Collection)
    #ifdef __GNUC__
        std::cout << "GCC " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__;
    #endif

    // _MSC_VER is defined for Microsoft Visual C++
    #ifdef _MSC_VER
        std::cout << "MSVC " << _MSC_VER;
    #endif

    // Add more preprocessor checks for other compilers as needed
    // Print the C++ standard version using predefined macro
    std::cout << "C++ Standard Version: ";

    // Check the value of __cplusplus to determine the standard version
    #if __cplusplus == 201103L
        std::cout << "C++11";
    #elif __cplusplus == 201402L
        std::cout << "C++14";
    #elif __cplusplus == 201703L
        std::cout << "C++17";
    #elif __cplusplus == 202002L
        std::cout << "C++20";
    #else
        std::cout << "Unknown or Unsupported";
    #endif
    std::cout << std::endl;   
    return 0;
}