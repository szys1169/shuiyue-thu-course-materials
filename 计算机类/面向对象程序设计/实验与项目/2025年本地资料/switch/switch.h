#ifndef SWITCH_H
#define SWITCH_H

#include <vector>

template <class T>
class MySwitch {
private:
    struct Case {
        T flag;
        void (*op)(int&);
        int* target;
        bool shouldBreak;
    };
    std::vector<Case> cases;

public:
    void addCase(T flag, void (*op)(int&), int* target, bool shouldBreak) {
        cases.push_back({flag, op, target, shouldBreak});
    }

    void execute(T value) {
        for (const auto& c : cases) {
            if (c.flag == value) {
                c.op(*c.target);
                if (c.shouldBreak) {
                    break;
                }
            }
        }
    }
};

#endif    