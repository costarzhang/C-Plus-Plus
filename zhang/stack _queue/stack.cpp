#include <iostream>
#include <string>
using namespace std;

typedef char ElemType;
typedef struct
{
    ElemType *top = nullptr;  // 栈顶
    ElemType *base = nullptr; // 栈底
    int stacksize;            // 栈的大小
} stack;

// 栈初始化
void initstack(stack *s, int size)
{
    if (s->base == nullptr)
    {
        s->base = (ElemType *)malloc(size * sizeof(ElemType));
    }
    if (!s->base)
    {
        return;
    }
    s->top = s->base;
    s->stacksize = size;
}
// 入栈
void push(stack *s, ElemType e)
{
    if (s->top - s->base == s->stacksize)
    {
        s->base = (ElemType *)realloc(s->base, (s->stacksize + 10) * sizeof(ElemType));
        if (!s->base)
        {
            return;
        }
        s->top = s->base + s->stacksize;
        s->stacksize += 10;
    }
    *(s->top) = e;
    s->top++;
}
// 出栈
void pop(stack *s, ElemType &e)
{
    if (s->top == s->base)
    {
        return;
    }
    e = *--(s->top);
}
void destroystack(stack *s)
{
    for (int i = 0; i < s->stacksize; i++)
    {
        free(s->base);
        s->base++;
    }
    s->top = s->base = nullptr;
    s->stacksize = 0;
}
int getlength(stack *s)
{
    return s->top - s->base;
}
/*
中缀表达式转换为后缀表达式
表达式树：
    将中缀表达式转换为表达式树。后序遍历表达式树
辅助栈
    从左到右遍历中缀表达式的每个操作数和操作符。
    当读到操作数时，立即把它输出，即成为后缀表达式的一部分；
    若读到操作符，判断该符号与栈顶符号的优先级，
        若该符号优先级高于栈顶元素，则将该操作符入栈，
        否则就依次把栈中运算符弹出并加到后缀表达式尾端，
        直到遇到优先级低于该操作符的栈元素或者左括号，然后把该操作符压入栈中。
        如果遇到”(”，直接压入栈中，如果遇到一个”)”，那么就将栈元素弹出（直到遇到左括号，将左括号弹出）并加到后缀表达式尾端，但左右括号并不输出。
        最后，如果读到中缀表达式的尾端，将栈元素依次完全弹出并加到后缀表达式尾端。
*/
/*
(1) 初始化两个栈：运算符栈S1和储存中间结果的栈S2；
(2) 从右至左扫描中缀表达式；
(3) 遇到操作数时，将其压入S2；
(4) 遇到运算符时，比较其与S1栈顶运算符的优先级：
(4-1) 如果S1为空，或栈顶运算符为右括号“)”，则直接将此运算符入栈；
(4-2) 否则，若优先级比栈顶运算符的较高或相等，也将运算符压入S1；
(4-3) 否则，将S1栈顶的运算符弹出并压入到S2中，再次转到(4-1)与S1中新的栈顶运算符相比较；


(5) 遇到括号时：
(5-1) 如果是右括号“)”，则直接压入S1；
(5-2) 如果是左括号“(”，则依次弹出S1栈顶的运算符，并压入S2，直到遇到右括号为止，此时将这一对括号丢弃；


(6) 重复步骤(2)至(5)，直到表达式的最左边；


(7) 将S1中剩余的运算符依次弹出并压入S2；
(8) 依次弹出S2中的元素并输出，结果即为中缀表达式对应的前缀表达式。
*/
void trans(string p)
{
    string result[50] = {""}; // 保存结果
    stack s;
    initstack(&s, 10);
    int c = 0;
    int count = 0;
    while (p[count] != '#')
    {
        int flag = 0;
        while (isdigit(p[count]) || p[count] == '.')
        {

            flag = 1;
            result[c] += p[count];
            count++;
        }
        if (flag)
        {
            c++;
        }
        if (')' == p[count]) //遇到右括号，依次出栈栈中元素，直到遇到一个左括号与之配对
        {
            char e;
            pop(&s, e);
            while (e != '(')
            {
                result[c++] = e;
                pop(&s, e);
            }
        }
        else if (p[count] == '+' || p[count] == '-')
        {
            if (!getlength(&s))
            { // 栈空，“+”和“-”的优先级最低，入栈
                push(&s, p[count]);
            }
            else
            { // 栈非空，检查栈顶元素
                char e;
                do
                {
                    pop(&s, e);
                    if (e == '(')
                    {
                        push(&s, e);
                    }
                    else
                    {
                        result[c++] = e;
                    }
                } while (getlength(&s) && e != '(');
                push(&s, p[count]);
            }
        }
        else if (p[count] == '*' || p[count] == '/' || p[count] == '(')
        {
            push(&s, p[count]);
        }
        if (p[count] == '#')
            break;
        count++;
    }
    while (getlength(&s)) //栈中剩余元素依次出栈输出
    {
        char e;
        pop(&s, e);
        result[c++] = e;
    }
    result[c] = '#';
    int i = 0;
    while (result[i] != "#")
    {
        cout << result[i] << ' ';
        i++;
    }
}
int main()
{
    string s = "1.2+2*2#";
    trans(s);
    return 0;
}