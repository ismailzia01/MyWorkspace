#include<stdio.h>
// given an array printing it in reverse order ;

int main()
{
    int arr[9]={34,56,54,32,67,85,90,32,21};
    int i;
    for(i=8; i>=0; i--)
    {
        printf("%d ,",arr[i]);
    }
    return 0;
}