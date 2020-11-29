#include <iostream>
using namespace std;
#define maxsize 8
/*
问题由模式串决定
对于失配字符前的串，模式串和文本串已经完全匹配，
模式串存在公共前后缀，则前缀一定可以和后缀对应的文本串匹配。
*/

// 计算模式串指针位置，即next数组
/*
对于模式串【a1, a2, ... , ai-1, ai, ..., an】，
next[i]的值是当在第i个字符处产生不匹配时，模式串指针需要调整的位置。
其在值上等于其前面子串（不妨称为模式串字串）【a1, a2, ...,ai-1】
中的最长公共前后缀长度+，在执行匹配时便是已匹配的字符串。
指针iPrefix指示【a1, a2, ... ai-1】中的最长公共前缀的最后一个字符，
iPostfix指示最长公共后缀的最后一个字符，即第i个字符的前一个字符，
其不发生回溯。
*/
void getnext(string pattern, int next[])
{
    int iPostfix = 1;
    int iPrefix = 0;
    next[1] = 0;
    while (iPostfix < pattern.length())
    {
        // 最长公共前缀为0，则next[iPostfix++] = 0 + 1
        // 最长公共前缀最后一个字符和最长公共后缀最后一个字符匹配
        // next[iPostfix++] = iPrefix,因为iPrefix是最长公共前缀的最后一个字符
        // 也就代表最长公共前缀长度
        if (iPrefix == 0 || pattern[iPrefix] == pattern[iPostfix])
        {
            iPostfix++;
            iPrefix++;
            next[iPostfix] = iPrefix;
        }
        else // 字符不匹配，回溯前缀指针至上一次匹配成功的字符后一个位置
        {
            iPrefix = next[iPrefix];
        }
        /*
        理解：【a1, a2, a3, ... aiPrefix, ..., aiPostfix, ai】
        在aiPrefix和aiPostfix处失配，则a1到aiPrefix-1的串一定和aiPostfix
        之前的一个串匹配。
        */
    }
}
// 优化next数组
void getnextval(int nextval[], int next[], string pattern)
{
    nextval[1] = 0;
    for (int j = 2; j < pattern.length(); j++)
    {
        if (pattern[next[j]] == pattern[j])
        {
            nextval[j] = nextval[next[j]];
        }
        else
        {
            nextval[j] = next[j];
        }
    }
}
int kmp(string text, string pattern, int next[], int pos)
{
    int iText = pos; // 文本串指针，开始匹配位置
    int iPattern = 1;
    while (iText < text.length() && iPattern < pattern.length())
    {
        if (iPattern == 0 || text[iText] == pattern[iPattern])
        {
            iText++;
            iPattern++;
        }
        else
        {
            iPattern = next[iPattern];
        }
    }
    if (iPattern >= pattern.length())
    {
        return iText - pattern.length();
    }
    else
    {
        return 0;
    }
}
int main()
{
    //string text = "#ababcabcacbab";
    string pattern = "#abcac";
    int next[6] = {0};
    getnext(pattern, next);
    int i = kmp(text, pattern, next, 1);
    cout << "\n"
         << i << endl;
    return 0;
}