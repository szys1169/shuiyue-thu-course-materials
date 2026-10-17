#include "pvector.h"
using namespace std;

int main(){

    #ifdef SUBTASK1
    // Subtask 1
    cout << "Subtask 1" << endl;
    PVector<int> a1;                  // Create an empty PVector, a1 = []
    cout << a1 << endl;               // Output: []
    auto a2 = a1.push_back(1);      // a2 = [1]
    cout << a2 << endl;               // Output: [1]
    int index = 0, value = 2;
    auto a3 = a2.set(index, value);   // modify an element, a3 = [2]
    cout << a3 << endl;               // Output: [2]
    auto a4 = a2.push_back(3);        // a4 = [1, 3]
    cout << a4 << endl;               // Output: [1, 3]
    cout << a4[1] << endl;           // Output: 3
    auto a5 = a4.push_back(5);        // a5 = [1, 3, 5]
    cout << a5 << endl;               // Output: [1, 3, 5]
    #endif

    #ifdef SUBTASK2
    // Subtask 2
    cout << "Subtask 2" << endl;
    auto b4 = a5.undo();             // b4 = [1, 3]
    cout << b4 << endl;
    auto b2 = b4.undo();             // b3 = [1]
    cout << b2 << endl;
    auto b1 = b2.undo();             // b1 = []
    cout << b1 << endl;
    b1.undo();                       // Output: cannot undo
    auto b6 = b2.push_back(0);       // b6 = [1, 0]
    cout << b6 << endl;
    #endif

    #ifdef SUBTASK3
    // Subtask 3
    cout << "Subtask 3" << endl;
    auto c7 = a3.update(a5);        // c7 = [2, 3, 5]
    cout << c7 << endl;
    auto c3 = c7.undo();            // c3 = [2]
    cout << c3 << endl;
    auto c8 = a5.update(a3);        // c8 = [2, 3, 5]
    cout << c8 << endl;
    auto c5 = c8.undo();            // c5 = [1, 3, 5]
    cout << c5 << endl;
    auto c9 = a1.update(c8);        // c9 = [2, 3, 5]
    cout << c9 << endl;
    auto c10 = c8.update(a1);       // c10 = [2, 3, 5]
    cout << c10 << endl;
    auto c11 = c10.undo();          // c11 = [2, 3, 5]
    cout << c11 << endl;

    PVector<int> other;
    a3.update(other);                 // Output: cannot update: no origin found
    a4.update(b6);                    // Output: cannot update: conflicts found
    c10.update(b6);                   // Output: cannot update: conflicts found
    auto c12=a2.update(c9);           // Output: cannot update: conflicts found
    #endif

    PVector<int> base;                // base = []
    cout << base << endl;
    auto v1 = base.push_back(1);      // v1 = [1]
    cout << v1 << endl;
    auto v2 = v1.push_back(2);        // v2 = [1, 2]
    cout << v2 << endl;
    auto v3 = v1.push_back(3);        // v3 = [1, 3] (并行分支)
    cout << v3 << endl;
    auto v4 = v2.set(1, 4);           // v4 = [1, 4]
    cout << v4 << endl;
    auto v5 = v3.set(1, 5);           // v5 = [1, 5]
    cout << v5 << endl;
    auto v6 = v4.update(v5);          // 冲突: 都修改了索引1
    PVector<int> origin;              // origin = []
    cout << origin << endl;
    auto x1 = origin.push_back(1);    // x1 = [1]
    cout << x1 << endl;
    auto x2 = x1.push_back(2);        // x2 = [1, 2]
    cout << x2 << endl;
    auto x3 = x2.set(0, 10);          // x3 = [10, 2]
    cout << x3 << endl;
    auto x4 = x3.update(x2);          // x4 = [10, 2, 2]
    cout << x4 << endl;
    auto x5 = x4.undo();              // x5 = [10, 2]
    cout << x5 << endl;
    auto x6 = x5.undo();              // x6 = [1, 2]
    cout << x6 << endl;
    auto x7 = x6.push_back(1);          // x7 = [1, 2, 1]
    cout << x7 << endl;
    auto x8 = x7.update(x3);          // x7 = [1, 2]
    cout << x8 << endl;
    auto x9 = x3.update(x7);          // x7 = [1, 2]
    cout << x9 << endl;
    PVector<int> start;               // start = []
auto s1 = start.push_back(1);     // s1 = [1]
    cout << s1 << endl;
auto s2 = s1.push_back(2);        // s2 = [1, 2]
cout << s2 << endl;
auto s3 = s1.push_back(3);        // s3 = [1, 3] (并行分支)
cout << s3 << endl;
auto s4 = s2.set(0, 10);          // s4 = [10, 2]
cout << s4 << endl;
auto s5 = s3.set(0, 10);          // s5 = [10, 3]
cout << s5 << endl;
auto s6 = s4.update(s5);          // 冲突: 都修改了索引0
    return 0;
}
