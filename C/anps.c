#include<stdio.h>
#include<stdlib.h>
int main()
{
    int x,A,P;
    printf("Enter side of square :");
    scanf("%d",&x);
    A=x*x;
    P=4*x;
    printf("Area =%d\nPerimeter =%d\n",A,P);
    return 0;
}