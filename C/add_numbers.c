#include<stdio.h>

int main()
{
    int n;
    int sum=0;
    printf("Enter numbers you want add up (Enter 0 to stop !):\n");
    do
    {
        scanf("%d",&n);
        sum += n;

    }while(n != 0);
    printf("Result = %d",sum);
    return 0;
}