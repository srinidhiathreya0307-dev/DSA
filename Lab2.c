#include <stdio.h>
#include <stdlib.h>
#define MAX 100
struct stack
{
    int data[MAX];
    int top;
};
typedef struct stack STACK;
void push(STACK *s, int value)
{
    s->data[++s->top] = value;
}
int pop(STACK *s)
{
    return s->data[s->top--];
}
void convert(STACK *s, int num)
{
    int rem;
    if (num == 0)
    {
        printf("Binary equivalent = 0");
        return;
    }
    while (num > 0)
    {
        rem = num % 2;
        push(s, rem);
        num = num / 2;
    }
    printf("Binary equivalent = ");
    while (s->top != -1)
    {
        printf("%d", pop(s));
    }
}
void main()
{
    STACK s;
    int decimal;
    s.top = -1;
    printf("Enter a decimal number: ");
    scanf("%d", &decimal);
    convert(&s, decimal);
}