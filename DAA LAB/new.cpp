#include<iostream>
using namespace std;

void rev(int arr[], int n) {
    int temp;
    for(int i =0; i < n/2; i++) {
        temp = arr[n - i - 1];
        arr[n - i - 1] = arr[i];
        arr[i] = temp;
    }
}


int main() {
    int n = 5;
    int arr[n] = { 10, 20, 30 , 40 , 50};
    rev(arr, n);
    for(int i = 0; i < n; i++)
        cout << arr[i] <<" ";
    return 0;
}