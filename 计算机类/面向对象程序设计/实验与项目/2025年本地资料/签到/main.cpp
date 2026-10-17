#include<iostream>
class Test {
    public:
        int* buf;
    
        // 默认构造函数
        Test() : buf(new int(0)) {
            std::cout << "Test(): this->buf @ " << buf << std::endl;
        }
    
        // 拷贝构造函数
        Test(const Test& other) : buf(new int(*other.buf)) {
            std::cout << "Test(const Test&) called. this->buf @ " << buf << std::endl;
        }
    
        // 移动构造函数
        Test(Test&& other) noexcept : buf(other.buf) {
            other.buf = nullptr;
            std::cout << "Test(Test&&) called. this->buf @ " << buf << std::endl;
        }
    
        // 析构函数
        ~Test() {
            std::cout << "~Test(): this->buf @ " << buf << std::endl;
            delete buf;
        }
    };
    
    // 全局函数 f1
    Test f1(const Test& t) {
        return t;
    }
    
    // 全局函数 f2
    Test& f2(Test& t) {
        return t;
    }
    
    // 全局函数 f3
    Test f3(const Test& t1, const Test& t2) {
        Test temp(t1);
        return temp;
}
int main()
 {
    Test a, b;
    Test A = f1(a);
    Test& B = f2(b);
    Test C = f3(a, b);
    return 0;
}    