#ifndef Editor_H
#define Editor_H

#include <vector>

// 你可以根据需要修改此文件

class TextEditor
{
private:
    using Position = std::pair<int, int>;
    std::vector<std::string> data;

public:
    TextEditor();
    void move(Position dest);
    void write(const std::string &str);
    void newline();
    void del();
    void screenShot();
    void undo();
    void apply(const std::string &opt);
};

#endif // Editor_H