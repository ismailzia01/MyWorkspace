#include<stdio.h>
int main()
{
    float l,w,A,P;
    printf("enter the length of rectangle :");
    scanf("%f",&l);
    printf("enter width of rectangle :");
    scanf("%f",&w);
    A=l*w;
    P=2*(l+w);
    printf("Area of rectangle =%f\n",A);
    printf("Perimeter of rectangl=%f\n",P);
    return 0;
    
}