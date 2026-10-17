#include "operator.h"
#include "switch.h"

template <class T>
void runForIt();

int main(int argc, char const *argv[])
{
    string master_type;
    cin >> master_type;
    if (master_type == "int")
        runForIt<int>();
    else if (master_type == "char")
        runForIt<char>();
    return 0;
}

template <class T>
void runForIt(){
    MySwitch<T> mySwitch;
    int target, m, n;
    cin >> target >> m;

    void (*operators[6])(int&) = {guard, increment, decrement, doublew, neg, halve};

    fori0n(i, m) {
        T flag; int op; bool shouldBreak;
        cin >> flag >> op >> shouldBreak;
        mySwitch.addCase(flag, operators[op], &target, shouldBreak);
    }

    cin >> n;
    fori0n(i, n) {
        T value;
        cin >> value;
        mySwitch.execute(value);
        cout << target << endl;
    }
}

