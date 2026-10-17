/*#include <vector>
#include <memory>
#include <algorithm>
#include<iostream>
#include <sstream>
#include"editor.h"
using namespace std;

TextEditor::TextEditor():data({""}),position({0,0}),history(){};

void TextEditor::move(Position dest)
{
    position.first=max(0,dest.first);
    if(position.first>data.size()-1)position.first=data.size()-1;
    position.second=max(0,dest.second);
    if(position.second>data[position.first].size())position.second=data[position.first].size();
    shuju newstate;
}

void TextEditor::write(const std::string &str)
{
    history.push_back({data,position});
    data[position.first].insert(position.second,str);
    position.second+=str.size();
}

void TextEditor::newline()
{
    history.push_back({data,position});
    int row = position.first;
    int col = position.second;
    std::string& currentLine = data[row];
    std::string newLine = currentLine.substr(col);
    currentLine.erase(col);
    data.insert(data.begin() + row + 1, newLine);
    position = {row + 1, 0};
}

void TextEditor::del()
{
    history.push_back({data,position});
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
}

void TextEditor::screenShot()
{
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
}

void TextEditor::undo()
{
    if(history.empty())return ;
    int version=history.size();
    data=history[version-1].data;
    position=history[version-1].position;
    history.pop_back();
}

void TextEditor::apply(const std::string &opt)
{
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
}*/