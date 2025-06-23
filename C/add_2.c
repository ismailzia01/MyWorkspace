#include<stdio.h>
int n;
int add()
{
    scanf("%d",&n);
    if(n==0)
    return;
    else
    return n + add();
}

int main()
{
    printf("%d",add());
    return 0;
}