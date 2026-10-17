#pragma once
#include <bits/stdc++.h>

class PalString
{
private:
    char *text;

public:
    PalString(const char *input)
    {
        int len = strlen(input);
        if (len == 0)
        {
            text[0] = '\0';
        }
        text = new char[len * 2 + 1];
        for (int i = 0; i < len; i++)
        {
            text[i] = input[i];
        }
        for (int i = 0; i < len; i++)
        {
            text[i + len] = input[len - i - 1];
        }
        text[len * 2] = '\0';
    }
    PalString(const PalString &other)
    {
        int len = strlen(other.text);
        text = new char[len + 1];
        for (int i = 0; i < len; i++)
        {
            text[i] = other.text[i];
        }
        text[len] = '\0';
    }
    char *getString()
    {
        return text;
    }

    void changeString(const char *c)
    {
        int len = strlen(c);
        if (len == 0)
        {
            text[0] = '\0';
            return;
        }
        char *tmp = new char[len * 2 + 1];
        for (int i = 0; i < len; i++)
        {
            tmp[i] = c[i];
        }
        for (int i = 0; i < len; i++)
        {
            tmp[i + len] = c[len - i - 1];
        }
        tmp[len * 2] = '\0';
        delete[] text;
        text = tmp;
        return;
    }
    friend std::ostream &operator<<(std::ostream &out, const PalString &t);
    ~PalString()
    {
        delete[] text;
    }
};

std::ostream &operator<<(std::ostream &out, const PalString &t)
{
    // std::cout << "hello?" << '\n';
    out << t.text;
    return out;
}