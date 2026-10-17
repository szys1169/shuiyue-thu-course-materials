#ifndef Editor_H
#define Editor_H

#include <vector>
#include<iostream>
#include<utility>
#include<list>
#include<regex>
using namespace std;

// 你可以根据需要修改此文件

class TextEditor
{
private:
    using Position = std::pair<int, int>;
    Position pt;
    std::vector<std::string> data;
    int maxrow=0;
    int maxcol=0;
    int version=0;
    list<vector<string>> li;
public:
    TextEditor():data({""}),pt({0,0})
    { 
    li.push_back(data);
    };
    void move(Position dest);
    void write(const std::string &str);
    void newline();
    void del();
    void screenshot();
    void undo();
    void apply(const std::string &opt){
    if(opt=="SCREEN"){screenshot();}
    if(opt[0]=='W'){
    string a="";
    for(int i=0;i<opt.length();i++){
        if(opt[i]==' '){
            for(int j=i;j<opt.length();j++)a+=opt[j];
        }
    }
    write(a);
    }
    if(opt[0]=='M'){
        int a;int b;
        std::regex num_regex(R"([-+]?\d+)"); // 匹配正/负整数的正则表达式

        std::vector<int> numbers; // 存储提取的数字
        auto begin = std::sregex_iterator(opt.begin(), opt.end(), num_regex);
        auto end = std::sregex_iterator();

    // 提取所有匹配的数字
    for (auto it = begin; it != end && numbers.size() < 2; ++it) {
        numbers.push_back(std::stoi(it->str()));
    }
        a=numbers[0];b=numbers[1];
        Position c=make_pair(a,b);
        move(c);
    }
    if(opt=="DELETE"){del();}
    if(opt=="NEWLINE"){newline();}
    if(opt=="UNDO"){undo();}
    };
};
#endif // Editor_H