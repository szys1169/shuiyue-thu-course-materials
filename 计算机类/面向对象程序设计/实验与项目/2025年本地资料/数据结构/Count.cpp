#include <cstdio>
#include <cstring>
#include <cctype>

#define STR_LEN 4096

int main(void)
{
    char text[STR_LEN + 1];
    gets(text);

    int cnt[26];
    for (int i = 0; i < 26; i++)
    {
        cnt[i] = 0;
    }

    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        char c = text[i];
        if (isalpha(c))
        {
            cnt[toupper(c) - 'A']++;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        if (cnt[i] != 0)
        {
            printf("%c: %d\n", i + 'A', cnt[i]);
        }
    }

    return 0;
}