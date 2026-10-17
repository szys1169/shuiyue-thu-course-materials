#ifndef Editor_H
#define Editor_H

#include <iostream>
#include <vector>
#include <string>
// 你可以根据需要修改此文件

class TextEditor
{
private:
    using Position = std::pair<int, int>;
    Position position;
    std::vector<std::string> data;
    std::vector<std::pair<Position,std::vector<std::string>>> situation;
    int operation = 0;
public:
    TextEditor(){
        position = std::make_pair(0,0);
        data.push_back("");
    };
    void move(Position dest){
        if(dest.first < 0)position.first = 0;
        else if(dest.first<data.size())position.first = dest.first;
        else position.first = data.size() - 1;
        if(dest.second < 0)position.second = 0;
        else if(dest.second<=data[position.first].size())position.second = dest.second;
        else position.second = data[position.first].size();
    };
    void write(const std::string &str){
        int length = str.size();
        for(int j=0;j<length;j++){
            auto iter = data[position.first].begin();
            for(int i=0;i<position.second;i++)iter++;
            data[position.first].insert(iter,str[j]);
            position.second++;
        };
        situation.push_back(std::make_pair(position,data));
        operation++;
    };
    void newline(){
        std::string a;
        for(int i=data[position.first].size()-1;i>=position.second;i--){
            a.push_back(data[position.first][i]);
            data[position.first].pop_back();
        }
        std::string b;
        for(int i=a.size()-1;i>=0;i--){
            b.push_back(a[i]);
        }
        auto iter = data.begin();
        for(int i=0;i<position.first;i++)iter++;
        iter++;
        data.insert(iter,b);
        position.first++;
        position.second=0;
        situation.push_back(std::make_pair(position,data));
        operation++;
    };
    void del(){
        if(position.second==0){
            if(position.first==0);
            else{
                position.second = data[position.first-1].size();
                for(int i=0;i<data[position.first].size();i++){
                data[position.first-1].push_back(data[position.first][i]);
                }
                auto iter = data.begin();
                for(int i=0;i<position.first;i++)iter++;
                data.erase(iter);
                position.first--;
            }
        }
        else{
        auto iter = data[position.first].begin();
        for(int i=1;i<position.second;i++)iter++;
        data[position.first].erase(iter);
        position.second--;
        };
        situation.push_back(std::make_pair(position,data));
        operation++;
    };
    void screenShot(){
        std::cout << "### SCREENSHOT BEGIN ###" << std::endl;
        for(int i=0;i<position.first;i++)std::cout<< data[i]<<std::endl;
        for(int i=0;i<position.second;i++)std::cout<< data[position.first][i];
        std::cout << '*';
        for(int i=position.second;i<data[position.first].size();i++)std::cout<< data[position.first][i];
        std::cout << std::endl;
        for(int i=position.first+1;i<data.size();i++)std::cout<< data[i]<<std::endl;
        std::cout << "### SCREENSHOT END ###" << std::endl;
    };
    void undo(){
        if(situation.size()<=1)return ;
        situation.pop_back();
        int length = situation.size() - 1;
        position = situation[length].first;
        data = situation[length].second;
    };
    void apply(const std::string &opt){
    std::vector<std::string> result;
    std::string delimiter;
    for(int i=0;i<opt.length();i++){
        if(opt[i]==' '){
            result.push_back(delimiter);
            delimiter = "";
        }
        else delimiter = delimiter + opt[i];
    };
    if(opt[opt.length()-1]!=' ')result.push_back(delimiter);
        if(result[0]=="MOVE"){
            Position middle;
            int i = 0;
            middle.first = std::atoi(result[1].c_str());
            middle.second = std::atoi(result[2].c_str());
            move(middle);
        }
        else if(result[0]=="WRITE"){
            write(result[1]);
        }
        else if(result[0]=="NEWLINE"){newline();}
        else if(result[0]=="DELETE"){del();}
        else if(result[0]=="SCREEN"){screenShot();}
        else if(result[0]=="UNDO"){undo();}
    };
};

#endif // Editor_H

#ifndef Editor_H
#define Editor_H

#include <vector>
#include <memory>
using namespace std;
// 你可以根据需要修改此文件

class TextEditor
{
private:
    using Position = std::pair<int, int>;
    Position position;
    std::vector<std::string> data;
    struct shuju
    {
        std::vector<std::string> data;
        Position position;
    };
    std::vector<shuju> history;
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