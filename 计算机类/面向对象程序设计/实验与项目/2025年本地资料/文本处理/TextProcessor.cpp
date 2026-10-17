#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <cassert>
#include"TextProcessor.h"
using namespace std;

//TextProcessor::TextProcessor():text_(""){};
//TextProcessor::TextProcessor(const std::string& text):text_(text){};

void TextProcessor::setText(const std::string& text)
{
    text_=text;
};
std::string TextProcessor::getText() const
{
    return text_;
}

std::string TextProcessor::removeSpaces()
{
    std::string result;
    for(char c:text_)
    {
        if(c!=' ')
        {
            result+=c;
        }
    }
    return result;
}               
std::string TextProcessor::toLowerCase()
{
    std::string result;
    for(char c:text_)
    {
        if(c >= 'A' && c <= 'Z')
        {
            c=c+32;
        }
        result+=c;
    }
    return result;
}                
std::string TextProcessor::toUpperCase()
{
    std::string result;
    for(char c:text_)
    {
        if(c >= 'a' && c <= 'z')
        {
            c=c-32;
        }
        result+=c;
    }
    return result;
}                   
std::string TextProcessor::reverse()
{
    std::string result;
    for(int i=text_.size()-1;i>=0;i--)
    {
        result+=text_[i];
    }
    return result;
}   

int TextProcessor::countOccurrences(const std::string& substr)
{
    int counnt=0;
    for(int i=0;i<=text_.size()-substr.size();i++)
    {
        int panduan=0;
        for(int j=0;j<substr.size();j++)
        {
            if(text_[i+j]!=substr[j])
            {
                panduan=1;
                break;
            }
        }
        if(panduan==0)counnt++;
    }
    return counnt;
}    
std::vector<int> TextProcessor::findPositions(const std::string& substr)
{
    std::vector<int> result;
    for(int i=0;i<=text_.size()-substr.size();i++)
    {
        int panduan=0;
        for(int j=0;j<substr.size();j++)
        {
            if(text_[i+j]!=substr[j])
            {
                panduan=1;
                break;
            }
        }
        if(panduan==0)result.push_back(i);
    }
    return result;
}
std::string TextProcessor::replaceAll(const std::string& from, const std::string& to)
{
    if (from.empty()) return text_;
    std::string result = text_;
    int pos = 0;
    while((pos = result.find(from, pos)) != std::string::npos)
    {
        result.replace(pos, from.length(), to);
        pos += to.length();
    }
    return result;
}
    
std::vector<std::string> TextProcessor::split(char delimiter)
{
    vector<string> result;
    int cc=0;
    for(int i=0;i<=text_.size()-1;i++)
    {
        if(text_[i]==delimiter)
        {
            if(i>cc)
            {
                string tidai;
                for(int j=cc;j<i;j++)
                {
                    tidai+=text_[j];
                }
                result.push_back(tidai);
            }
            cc=i+1;
        }
    }    
    string tidai;
    for(int j=cc;j<text_.size();j++)
    {
        tidai+=text_[j];
    }
    result.push_back(tidai);
    return result;
}
/*
std::vector<std::string> TextProcessor::split(char delimiter)
{
    vector<string> result;
    int cc=0;
    for(int i=0;i<=text_.size()-1;i++)
    {
        if(text_[i]==delimiter)
        {
            if(i>cc)
            {
                string tidai;
                for(int j=cc;j<i;j++)
                {
                    tidai+=text_[j];
                }
                result.push_back(tidai);
            }
            cc=i+1;
        }
    }    
    string tidai;
    for(int j=cc;j<text_.size();j++)
    {
        tidai+=text_[j];
    }
    result.push_back(tidai);
    return result;
}
*/
int TextProcessor::getCharCount()
{
    return text_.size();
}                     
int TextProcessor::getCharCountNoSpaces()
{
    int counnt=0;
    for(char c:text_)
    {
        if(c!=' ')
        {
            counnt++;
        }
    }
    return counnt;
}                 
int TextProcessor::getLineCount()
{
    int counnt=1;
    for(char c:text_)
    {
        if(c=='\n')
        {
            counnt++;
        }
    }
    return counnt;
}

bool TextProcessor::isPalindrome()
{
    string aa=removeSpaces();
    TextProcessor b(aa);
    string cc=b.toLowerCase(); 
    TextProcessor c(cc); 
    string a1=c.getText();
    string a2=c.reverse();
    return a1==a2;
}                       
bool TextProcessor::isNumeric()
{
    int i=0;
    int counnt=0;
    if(text_[0]=='+'||text_[0]=='-'){i=1;}
    for(;i<=text_.size()-1;i++)
    {
        if(text_[i]=='.')
        {
            counnt++;
        }
        else if(!isDigit(text_[i]))
        {
            return false;
        }
    }
    if(counnt>1){return false;}
    for(auto t:text_)
    {
        if(isDigit(t))
        {
            return true;
        }
    }
    return false;
}                            
bool TextProcessor::containsOnly(const std::string& charset)
{
    for(auto t:text_)
    {
        int panduan=0;
        for(auto k:charset)
        {
            if(t==k)
            {
                panduan=1;
            }
        }
        if(panduan==0)
        {
            return false;
        }
    }
    return true;
} 

std::string TextProcessor::centerAlign(int width, char fillChar)
{
    if(text_.size()>=width)
    {
        return text_;
    }
    int jj=(width-text_.size())/2;
    int kk=width-text_.size()-jj;
    return string(jj,fillChar)+text_+string(kk,fillChar);
}
std::string TextProcessor::leftAlign(int width, char fillChar)
{
    if(text_.size()>=width)
    {
        return text_;
    }
    int jj=width-text_.size();
    return text_+string(jj,fillChar);
}   
std::string TextProcessor::rightAlign(int width, char fillChar)
{
    if(text_.size()>=width)
    {
        return text_;
    }
    int jj=width-text_.size();
    return string(jj,fillChar)+text_;
} 