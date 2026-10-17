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
            c=c-32;
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
            c=c+32;
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
    for(int i=text_.size()-1;i>=0;i--)
    {
        if(text_[text_.size()-i-1]!=text_[i])
        {
            return false;
        }
    }
    return true;
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
    return true;
}                            
bool TextProcessor::containsOnly(const std::string& charset)
{
    vector<int> shu=findPositions(charset);
    int jj=charset.size();
    if(shu[0]!=0){return false;}
    shu.push_back(text_.size());
    for(int i=0;i<shu.size();i++)
    {
        if(shu[i]+jj<shu[i+1])
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
    string result;
    for(int i=0;i<=jj-1;i++)
    {
        result+=fillChar;
    }
    for(int i=0;i<=text_.size()-1;i++)
    {
        result+=text_[i];
    }
    for(int i=0;i<=jj-1;i++)
    {
        result+=fillChar;
    }
    return result;
}
std::string TextProcessor::leftAlign(int width, char fillChar)
{
    if(text_.size()>=width)
    {
        return text_;
    }
    int jj=width-text_.size();
    string result;
    for(int i=0;i<=jj-1;i++)
    {
        result+=fillChar;
    }
    for(int i=0;i<=text_.size()-1;i++)
    {
        result+=text_[i];
    }
    return result;
}   
std::string TextProcessor::rightAlign(int width, char fillChar)
{
    if(text_.size()>=width)
    {
        return text_;
    }
    int jj=width-text_.size();
    string result;
    for(int i=0;i<=text_.size()-1;i++)
    {
        result+=text_[i];
    }
    for(int i=0;i<=jj-1;i++)
    {
        result+=fillChar;
    }
    return result;
} 