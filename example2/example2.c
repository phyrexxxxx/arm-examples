#include <stdio.h>

int multiply(int a, int b);
int multiplyadd(int a, int b, int c);
int multiplysub(int a, int b, int c);

int main(void)
{
    int a, b, c, d;

    a = 10;
    b = 14;
    c = 3;
    d = multiply(a, b);

    printf("a * b is %d\n", d);
    d = multiplyadd(a, b, c);

    printf("a * b + c is %d\n", d);
    d = multiplysub(a, b, c);

    printf("c - a * b is %d\n", d);

    return 0;
}

int multiply(int a, int b)
{
    return (a * b);
}

int multiplyadd(int a, int b, int c)
{
    return ((a * b) + c);
}

int multiplysub(int a, int b, int c)
{
    return (c - (a * b));
}