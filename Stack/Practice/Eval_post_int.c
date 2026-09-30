#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100
typedef int ElemType;

// 栈
typedef struct
{
    ElemType* data;
    int top;
} Stack;

// 动态初始化
Stack* init_stack()
{
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->data = (ElemType*)malloc(sizeof(ElemType) * MAX_SIZE);
    s->top = -1;
    return s;
}

// 压栈
int push(Stack* s, ElemType e)
{
    if (s->top >= MAX_SIZE - 1)
    {
        printf("Stack full!\n");
        return -1;
    }

    s->data[++s->top] = e;
    return 0;
}

// 出栈
int pop(Stack* s, ElemType *e)
{
    if (s->top == -1)
        return -1;

    *e = s->data[s->top--];
    return 0;
}

// 符号枚举
typedef enum
{
    L_PARE, R_PARE, ADD, SUB, MUL, DIV, MOD, EOS, NUM
} ContentType;

// 输入表达式
int get_expr(char* expr)
{
    int mode;
    printf("Input mode (1 post, 2 mid): ");
    scanf("%d", &mode);

    if (mode == 2)
        printf("Input a int mid expr: ");
    else if (mode == 1)
        printf("Input a int post expr: ");
    else
        return 0;

    scanf("%s", expr);
    return mode;
}

// 判断表达式元素
ContentType get_token(char* symbol, char* expr, int* index)
{
    *symbol = expr[*index];
    *index += 1;

    switch (*symbol)
    {
        // case '(':
        //     return L_PARE;
        // case ')':
        //     return R_PARE;
        case '+':
            return ADD;
        case '-':
            return SUB;
        case '*':
            return MUL;
        case '/':
            return DIV;
        case '%':
            return MOD;
        case '\0':
            return EOS;
        default:
            if (*symbol >= '0' && *symbol <= '9')
                return NUM;
            else
                return -1;
    }
}

// 转换输出
char token_to_char(ContentType token)
{
    switch (token)
    {
        case L_PARE:
            return '(';
        case R_PARE:
            return ')';
        case ADD:
            return '+';
        case SUB:
            return '-';
        case MUL:
            return '*';
        case DIV:
            return '/';
        case MOD:
            return '%';
        default:
            return 0;
    }
}

// 中缀转后缀
int middle_to_post(char* mid, char* post)
{
    // 优先级定义（枚举顺序）
    static int in_pr[] = {0, 19, 12, 12, 13, 13, 13, 0, 0};
    static int out_pr[] = {20, 19, 12, 12, 13, 13, 13, 0, 0};

    Stack* symbol_s = init_stack();
    char symbol;
    int index = 0;
    ElemType e;
    ContentType token;

    symbol_s->data[0] = EOS;
    symbol_s->top++;
    token = get_token(&symbol, mid, &index);

    while (token != EOS)
    {
        if (token == NUM)
        {
            char tmp[2] = {symbol, 0};
            strcat(post, tmp);
        }
        else if (token == R_PARE)
        {
            while (symbol_s->data[symbol_s->top] != L_PARE)
            {
                pop(symbol_s, &e);
                char tmp[2] = {token_to_char(e), 0};
                strcat(post, tmp);
            }
            pop(symbol_s, &e);
        }
        else
        {
            while (in_pr[symbol_s->data[symbol_s->top]] >= out_pr[token])
            {
                pop(symbol_s, &e);
                char tmp[2] = {token_to_char(e), 0};
                strcat(post, tmp);
            }  
            push(symbol_s, token);
        }

        token = get_token(&symbol, mid, &index);
    }

    while (symbol_s->data[symbol_s->top] != EOS)
    {
        pop(symbol_s, &e);
        char tmp[2] = {token_to_char(e), 0};
        strcat(post, tmp);
    }
}

// 计算表达式
int eval(Stack* s, char* expr)
{
    char symbol;
    int op1, op2, result;
    int index = 0;
    ContentType token = get_token(&symbol, expr, &index);

    while (token != EOS)
    {
        if (token == -1)
        {
            printf("Wrong expression!\n");
            return -1;
        }
        else if (token == NUM)
            push(s, symbol - '0');
        else
        {
            int r1 = pop(s, &op2);
            int r2 = pop(s, &op1);

            if (r1 || r2)
            {
                printf("Pop Error!\n");
                return -1;
            }
        }

        switch (token)
        {
            // case L_PARE:
            //     break;
            // case R_PARE:
            //     break;
            case ADD:
                push(s, op1 + op2);
                break;
            case SUB:
                push(s, op1 - op2);
                break;
            case MUL:
                push(s, op1 * op2);
                break;
            case DIV:
                push(s, op1 / op2);
                break;
            case MOD:
                push(s, op1 % op2);
                break;
            default:
                break;
        }
        token = get_token(&symbol, expr, &index);
    }
    
    pop(s, &result);
    printf("res:%d\n", result);

    return 0;
}

int main()
{
    Stack* s = init_stack();
    char expr[MAX_SIZE];
    int mode;
    
    mode = get_expr(expr);

    if (mode == 2)
    {
        char tmp[MAX_SIZE];
        middle_to_post(expr, tmp);
        strcpy(expr, tmp);
        printf("Post expr: %s\n", expr);
    }

    eval(s, expr);

    return 0;
}