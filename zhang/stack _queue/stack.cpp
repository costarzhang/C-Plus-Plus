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
    if (s->top - s->base == s->stacksize) //栈满，扩容
    {
        s->base = (ElemType *)realloc(s->base, (s->stacksize + 10) * sizeof(ElemType));
        if (!s->base)
        {
            return;
        }
        s->top = s->base + s->stacksize; //重新设置栈顶指针
        s->stacksize += 10;
    }
    *(s->top) = e;
    s->top++;
}
// 出栈
void pop(stack *s, ElemType &e)
{
    if (s->top == s->base) //栈空
    {
        return;
    }
    e = *--(s->top);
}
//销毁栈
void destroystack(stack *s)
{
    ElemType *e;
    for (int i = 0; i < s->stacksize; i++)
    {
        e = s->base;
        free(e);
        s->base++;
    }
    s->top = s->base = nullptr;
    s->stacksize = 0;
}
int getlength(stack *s)
{
    return s->top - s->base;
}
void printstack(stack *s)
{
    ElemType *e = s->base;
    while (e != s->top)
    {
        printf("%c ", *e);
        e++;
    }
}

//中缀转后缀
void intopos(string p)
{
    string result[50] = {""}; // 保存结果
    stack s;
    initstack(&s, 10);
    int c = 0;
    int count = 0;
    while (count < p.length())
    {
        int flag = 0;
        while (isdigit(p[count]) || p[count] == '.') //处理数字
        {

            flag = 1;
            result[c] += p[count];
            count++;
        }
        if (flag)
        {
            c++;
        }
        if (')' == p[count]) //遇到右括号，依次出栈栈中元素，直到遇到一个左括号与之配对，左括号也弹出
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
                    if (e == '(') //栈中'('必须和')'匹配
                    {
                        push(&s, e);
                    }
                    else //栈顶元素优先级比'+','-'高，出栈并加入表达式
                    {
                        result[c++] = e;
                    }
                } while (getlength(&s) && e != '('); //栈非空且栈顶不是')',继续检查栈顶元素
                push(&s, p[count]);                  //栈顶元素优先级比当前元素优先级低，入栈
            }
        }
        else if (p[count] == '*' || p[count] == '/' || p[count] == '(') //高优先级，直接入栈
        {
            push(&s, p[count]);
        }
        if (p[count] == '#')
            break;
        count++; //处理下一字符
    }
    while (getlength(&s)) //栈中剩余元素依次出栈输出
    {
        char e;
        pop(&s, e);
        result[c++] = e;
    }
    int i = 0;
    while (i < c)
    {
        cout << result[i++] << ' ';
    }
}
//中缀转前缀
void intopre(string p)
{
    string result[50] = {""}; // 保存结果
    stack s;
    initstack(&s, 20);
    int c = 0;
    int count = p.length();
    while (count >= 0)
    {
        int flag = 0;
        while (isdigit(p[count]) || p[count] == '.') //处理数字
        {

            flag = 1;
            result[c] += p[count];
            count--;
        }
        if (flag)
        {
            c++;
        }
        if ('(' == p[count])
        {
            char e;
            pop(&s, e);
            while (e != ')')
            {
                result[c++] = e;
                pop(&s, e);
            }
        }
        else if (p[count] == '+' || p[count] == '-')
        {
            if (!getlength(&s))
            {
                push(&s, p[count]);
            }
            else
            {
                char e;
                do
                {
                    pop(&s, e);
                    if (e == ')')
                    {
                        push(&s, e);
                    }
                    else
                    {
                        result[c++] = e;
                    }
                } while (getlength(&s) && e != ')');
                push(&s, p[count]);
            }
        }
        else if (p[count] == '*' || p[count] == '/' || p[count] == ')')
        {
            push(&s, p[count]);
        }
        if (p[count] == '#')
            break;
        count--;
    }
    while (getlength(&s)) //栈中剩余元素依次出栈输出
    {
        char e;
        pop(&s, e);
        result[c++] = e;
    }
    --c;
    while (c >= 0)
    {
        cout << result[c--] << ' ';
    }
}

int main()
{
    string s = "(3+5)*7";
    intopos(s);
    printf("\n");
    intopre(s);
    return 0;
}