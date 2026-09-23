#include <stdio.h>
#include <stdlib.h>
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

// 符号定义
typedef enum
{
    L_PARE, R_PARE, ADD, SUB, MUL, DIV, MOD, EOS, NUM
} ContentType;

int get_expr(char* expr)
{
    printf("Input a int post expr: ");
    scanf("%s", expr);
    return 0;
}

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
    
    get_expr(expr);
    eval(s, expr);

    return 0;
}