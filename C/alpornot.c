#include<stdio.h>
#include<stdlib.h>
int main()
{
    char ch;
    printf("Enter a value :");
    scanf("%c",&ch);
    if(ch>='a' && ch<='z' || ch>='A' && ch<='Z')
    printf("%c is a character",ch);
    else
    printf("it is not a character");
    return 0;
}