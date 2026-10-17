#include <functional>
using namespace std;

class Click {
private:
    // TODO
public:
    // TODO
    Click();
    // TODO
    void setClickCommand(std::function<void()> f);
    // TODO
    virtual void click();
};
class DoubleClick {
private:
    // TODO
public:
    // TODO
    DoubleClick();
    // TODO
    void setDoubleClickCommand(std::function<void()> f);
    // TODO
    virtual void doubleClick();
};