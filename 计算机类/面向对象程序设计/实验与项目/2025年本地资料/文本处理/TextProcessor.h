#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <cassert>

class TextProcessor {
public:
    // 构造函数
    TextProcessor():text_(""){};
    TextProcessor(const std::string& text):text_(text){};
    
    // 设置和获取文本
    void setText(const std::string& text);
    std::string getText() const;
    
    // 基础字符串操作
    std::string removeSpaces();                    // 移除文本里所有的空格，并返回移除空格后的字符串
    std::string toLowerCase();                     // 将字符串里所有字符均转为小写，并返回转换后的字符串
    std::string toUpperCase();                     // 将字符串里所有字符均转为大写，并返回转换后的字符串
    std::string reverse();                         // 将字符串反转，并返回反转后的字符串
    
    // 字符串查找和替换
    int countOccurrences(const std::string& substr);        // 返回子串substr在字符串中出现的次数，如果从未出现则返回0
    std::vector<int> findPositions(const std::string& substr); // 返回子串`substr`的首字母在字符串中的所有位置，如果不含该子串则返回空数组
    std::string replaceAll(const std::string& from, const std::string& to); // 将字符串中的from字符串全部替换为to字符串
    
    // 字符串分割
    std::vector<std::string> split(char delimiter);        // 按字符delimiter分割
    
    // 字符和单词统计
    int getCharCount();                           // 统计字符数（包含空格）
    int getCharCountNoSpaces();                   // 统计字符数（不含空格）
    int getLineCount();                           // 统计行数（最少有一行）
    
    // 字符串验证
    bool isPalindrome();                          // 是否为回文字符串
    bool isNumeric();                             // 是否为数字（允许开头有正负号，允许是小数）
    bool containsOnly(const std::string& charset); // 是否只包含指定字符charset
    
    // 格式化功能
    std::string centerAlign(int width, char fillChar = ' '); // 使用fillChar进行填充（默认为空格），将字符串以居中对齐的方式扩充为宽度为width的新字符串，如果本身字符串就比width宽，则返回原本的字符串
    std::string leftAlign(int width, char fillChar = ' ');   // 使用fillChar进行填充（默认为空格），将字符串以左对齐的方式扩充为宽度为width的新字符串，如果本身字符串就比width宽，则返回原本的字符串
    std::string rightAlign(int width, char fillChar = ' ');  // 使用fillChar进行填充（默认为空格），将字符串以右对齐的方式扩充为宽度为width的新字符串，如果本身字符串就比width宽，则返回原本的字符串

private:
    std::string text_;
    bool isDigit(char c) const {
        //辅助函数，判断c是否是数字
        return c >= '0' && c <= '9';
    }
    bool isAlpha(char c) const {
        //辅助函数，判断c是否是字母
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }
};