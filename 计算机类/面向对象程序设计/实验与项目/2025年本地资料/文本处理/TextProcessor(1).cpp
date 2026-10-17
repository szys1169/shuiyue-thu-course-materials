#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <cassert>
#include "TextProcessor.h"

void TextProcessor::setText(const std::string& text){
    text_ = text;
}
    
    
    

std::string TextProcessor::getText() const{
    return text_;
}

std::string TextProcessor::removeSpaces(){
    std::string result;
    for (char c : text_) {
        if (c != ' ') {
            result += c;
        }
    }
    return result;
}    

                // �Ƴ����пո�
std::string TextProcessor::toLowerCase(){
    std::string result;
    for (char c : text_) {
        if (c >= 'A' && c <= 'Z') {
            result += c + 32; // ת��ΪСд
        } else {
            result += c;
        }
    };   
    return result;
    };  
    
                    // ת��ΪСд
std::string TextProcessor::toUpperCase()
    {std::string result;
    for (char c : text_) {
        if (c >= 'a' && c <= 'z') {
            result += c - 32; // ת��Ϊ��д
        } else {
            result += c;
        }
    }; 
    return result;
    };   
    
                    // ת��Ϊ��д
std::string TextProcessor::reverse(){
    std::string result = text_;
    std::reverse(result.begin(), result.end());
    return result;
    };  

int TextProcessor::countOccurrences(const std::string& substr){
     if (substr.empty()) return 0; 
    int count = 0;
    size_t pos = text_.find(substr);
    while (pos != std::string::npos) {
        ++count;
        pos = text_.find(substr, pos + substr.length());
    }
    return count;
}


       // ͳ���Ӵ����ִ���
 std::vector<int> TextProcessor::findPositions(const std::string& substr){
    std::vector<int> positions;
    size_t pos=text_.find(substr);
    while (pos != std::string::npos) {
        positions.push_back(pos);
        pos = text_.find(substr, pos + substr.length());
    }; 
    return positions;}
    // ��������λ��
std::string  TextProcessor::replaceAll(const std::string& from, const std::string& to){
      std::vector<int> positions = findPositions(from);  // 只计算一次
    for(auto it = positions.rbegin(); it != positions.rend(); ++it) {  // 反向迭代避免位置变化
        text_.replace(*it, from.length(), to);
    }
    return text_;
} // ȫ���滻    

std::vector<std::string> TextProcessor::split(char delimiter){
     std::vector<std::string> result;
    int cc=0;
    for(int i=0;i<=text_.size()-1;i++)
    {
        if(text_[i]==delimiter)
        {
            if(i>cc)
            {
                std::string tidai;
                for(int j=cc;j<i;j++)
                {
                    tidai+=text_[j];
                }
                result.push_back(tidai);
            }
            cc=i+1;
        }
    }    
    std::string tidai;
    for(int j=cc;j<text_.size();j++)
    {
        tidai+=text_[j];
    }
    result.push_back(tidai);
    return result;
}

int TextProcessor::getCharCount(){
    return text_.size();
}                         
int TextProcessor::getCharCountNoSpaces(){
    TextProcessor a(text_);
    a.removeSpaces();
    return a.getCharCount();
 }                   // �ַ����������ո�
int TextProcessor:: getLineCount(){
    int i=1;
    for(auto a:text_){
        if(a=='\n')i++;
    }
    return i;
}    
bool TextProcessor::isPalindrome(){
  std::string reversed=text_;
  std::reverse(reversed.begin(),reversed.end());
  if(text_==reversed){return true;}
  return false;
};                          // �Ƿ�Ϊ����
bool TextProcessor::isNumeric(){
    if(text_.empty()){return false;}
    int coun=-1;
    int hasdot=false;
    for(auto it:text_){
        coun++;
        if((!isDigit(it))&&(it!='+')&&(it!='-')&&(it!='.'))return false;
        if(it=='+'||it=='-'){
            if(coun==0){continue;}
            else return false;}
        if(it=='.'){
            if(coun==0||coun==text_.size()-1)return false;
            if(hasdot)return false;
            hasdot=1;}
    }
    return true;
}                             // �Ƿ�Ϊ����
bool TextProcessor::containsOnly(const std::string& charset){
    return text_.find_first_not_of(charset) == std::string::npos;
}

std::string TextProcessor::centerAlign(int width, char fillChar){
    if(text_.size()>width)return text_;
    int totalPadding = width - text_.size();
    int leftPadding = totalPadding / 2;
    int rightPadding = totalPadding - leftPadding;
    return std::string(leftPadding, fillChar) + text_ + std::string(rightPadding, fillChar);
}

 // ���ж���
std::string TextProcessor::leftAlign(int width, char fillChar){
    if(text_.size()>width)return text_;
    int totalPadding = width - text_.size();
    return text_+std::string(totalPadding,fillChar);
}  // �����
std::string TextProcessor::rightAlign(int width, char fillChar){
    if(text_.size()>width)return text_;
    int totalPadding = width - text_.size();
    return std::string(totalPadding,fillChar)+text_;
}  // �Ҷ���

