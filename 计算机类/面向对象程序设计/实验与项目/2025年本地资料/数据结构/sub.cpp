#include <cstdio>
int main(void)
{
    double a, b, result;
    char op;
    scanf("%lf %c %lf",&a, &op, &b);
    switch(op)
    {
    case '+':
        result =a+ b;
        break;
    case '-':
        result =a-b;
        break;
    default:
        result =a* b;
    }
    printf("%.0lf\n",result);return 0;
}