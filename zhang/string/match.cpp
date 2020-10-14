#include <iostream>
using namespace std;

// 简单模式匹配
int index(string text, string pattern) {
    int iText = 0; // 文本字符指针
    int iPattern = 0; //模式串字符指针
    int k = iText; // 记录每趟开始匹配时文本指针的位置

    while (iText <= text.length() && iPattern <= pattern.length()) {
        for (int i = k; i < text.length(); i++) {
            cout << text[i];
        }
        cout << endl;
        for (int j = 0; j < pattern.length(); j++) {
            cout << pattern[j];
        }
        cout << endl;
        if (text[iText] == pattern[iPattern]) { // 字符匹配，指针后移
            ++iText;
            ++iPattern;
        } else { // 字符不匹配，文本指针后移一位
                iText = ++k;
                iPattern = 0; // 模式串指针回到模式串初始位置
        }
    }
    if (iPattern > pattern.length() - 1) {
        return k;
    } else {
        return pattern.length();
    }
}


int main() {
    string text = "ABABCABCACBAB";
    string pattern = "ABCAC";
    cout << index(text, pattern);
}