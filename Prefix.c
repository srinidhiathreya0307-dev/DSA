#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 20

struct stack
{
    int top;
    char data[SIZE];
};

typedef struct stack STACK;

void push(STACK *s, char item)
{
    s->data[++(s->top)] = item;
}

char pop(STACK *s)
{
    return s->data[(s->top)--];
}

int preced(char symbol)
{
    switch(symbol)
    {
        case '^': return 5;
        case '*':
        case '/':
        case '%': return 3;
        case '+':
        case '-': return 1;
    }
    return 0;
}

void infixtoprefix(STACK *s, char infix[SIZE])
{
    int i, j = 0;
    char prefix[SIZE], temp, symbol;
    char reverse[SIZE];

    for(i = 0; infix[i] != '\0'; i++)
        reverse[i] = infix[i];

    reverse[i] = '\0';

    for(i = 0; reverse[i] != '\0'; i++)
    {
        if(reverse[i] == '(')
            reverse[i] = ')';
        else if(reverse[i] == ')')
            reverse[i] = '(';
    }

    for(i = 0; reverse[i] != '\0'; i++)
    {
        symbol = reverse[i];

        if(isalnum(symbol))
            prefix[j++] = symbol;
        else
        {
            switch(symbol)
            {
                case '(':
                    push(s, symbol);
                    break;

                case ')':
                    temp = pop(s);
                    while(temp != '(')
                    {
                        prefix[j++] = temp;
                        temp = pop(s);
                    }
                    break;

                case '+':
                case '-':
                case '*':
                case '/':
                case '%':
                case '^':
                    if(s->top == -1 || s->data[s->top] == '(')
                        push(s, symbol);
                    else
                    {
                        while(s->top != -1 &&
                              s->data[s->top] != '(' &&
                              preced(s->data[s->top]) > preced(symbol))
                            prefix[j++] = pop(s);

                        push(s, symbol);
                    }
                    break;

                default:
                    printf("\nInvalid!!!!!");
                    exit(0);
            }
        }
    }

    while(s->top != -1)
        prefix[j++] = pop(s);

    prefix[j] = '\0';

    for(i = 0, j = j - 1; i < j; i++, j--)
    {
        temp = prefix[i];
        prefix[i] = prefix[j];
        prefix[j] = temp;
    }

    printf("\nThe prefix expression is %s\n", prefix);
}

int main()
{
    STACK s;
    s.top = -1;

    char infix[SIZE];

    printf("\nRead Infix expression\n");
    scanf("%s", infix);

    infixtoprefix(&s, infix);

    return 0;
}