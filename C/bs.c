#include<stdio.h>
//#include<conio.h>

int binarySearch(int a[], int size, int val) {
	int low = 0;
	int high = size -1;
	while(low <= high) {
		int mid = (low + ( high - low))/2;
		if(val < a[mid])
			high = mid - 1;
		else if(val > a[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int main() {
 int a[10] ,i, size, val, bs;
 printf("Enter the size of the array : ");
 scanf("%d", &size);
 printf("Enter the %d element of the arrays: ", size);
 for(i = 0; i < size; i++) {
   scanf("%d", &a[i]);
   }
 printf("Enter the element to be searched : ");
 scanf("%d", &val);
 bs = binarySearch(a, size, val);
 if(bs != -1)
	printf("found at %d\n", bs);
 else
	printf("Not found" );
//getch();
return 0;

}
