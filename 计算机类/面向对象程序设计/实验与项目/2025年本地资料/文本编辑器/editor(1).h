#ifndef Editor_H
#define Editor_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
// 你可以根据需要修改此文件

class TextEditor
{
private:
    using Position = std::pair<int, int>;
    Position position;
    std::vector<std::string> data;
    std::vector<std::pair<Position,std::vector<std::string>>> situation;
public:
    TextEditor(){
        position = {0,0};
        data.push_back("");
    };
    void move(Position dest){
        position.first=std::max(0,dest.first);
    if(position.first>data.size()-1)position.first=data.size()-1;
    position.second=std::max(0,dest.second);
    if(position.second>data[position.first].size())position.second=data[position.first].size();
    };
    void write(const std::string &str){
        data[position.first].insert(position.second,str);
        position.second+=str.size();
        situation.push_back({position,data});
    };
    void newline(){
        int row = position.first;
    int col = position.second;
    std::string& currentLine = data[row];
    std::string newLine = currentLine.substr(col);
    currentLine.erase(col);
    data.insert(data.begin() + row + 1, newLine);
    position = {row + 1, 0};
        situation.push_back({position,data});
    };
    void del(){
        int row = position.first;
    int col = position.second;
    if (row == 0 && col == 0) return;    
    if (col == 0) {
        if (row > 0) 
        {
            int prevRow = row - 1;
            int prevRowlength=data[prevRow].size();
            data[prevRow] += data[row];
            data.erase(data.begin() + row);
            position = {prevRow, prevRowlength};
        }
    } 
    else 
    {
        data[row].erase(col - 1, 1);
        position.second--;
    }   
        situation.push_back({position,data});
    };
    void screenShot(){
        std::cout << "### SCREENSHOT BEGIN ###" << std::endl;      
    if (data.empty()) {
        std::cout << "*" << std::endl;
    } else {
        for (size_t i = 0; i < data.size(); ++i) {
            if (static_cast<int>(i) == position.first) 
            {
                std::cout << data[i].substr(0, position.second) << "*" ;
                if(position.second<data[i].size())
                    std::cout<< data[i].substr(position.second); 
                std::cout<< std::endl;
            } else {
                std::cout << data[i] << std::endl;
            }
        }
    }       
    std::cout << "### SCREENSHOT END ###" << std::endl;
    };
    void undo(){
        if(!data.empty()){
        int version=situation.size();
    data=situation[version-1].second;
    position=situation[version-1].first;
    situation.pop_back();
    };
}
    void apply(const std::string &opt){
        std::istringstream iss(opt);
    std::string cmd;
    iss >> cmd;
    if (cmd == "MOVE")
    {
        int row, col;
        iss >> row >> col;
        move({row, col});
    } 
    else if (cmd == "WRITE")
    {
        std::string text;
        std::getline(iss >> std::ws, text);
        write(text);
    } 
    else if (cmd == "NEWLINE") 
    {
        newline();
    } 
    else if (cmd == "DELETE") 
    {
        del();
    } 
    else if (cmd == "UNDO")
    {
        undo();
    }
    else if (cmd == "SCREEN")
    {
        screenShot();
    }
    };
};
#endif // Editor_H