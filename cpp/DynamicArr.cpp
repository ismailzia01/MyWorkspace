#include <iostream>
#include <vector>
#include <limits> // for numeric_limits
using namespace std;

int main() {
    vector<int> nums;
    int input;

    cout << "Enter integers (type any non-integer like 'q' to stop):" << endl;

    while (cin >> input) {
        nums.push_back(input);
    }

    // Clear the error flag from cin to allow further input/output
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nYou entered " << nums.size() << " numbers:" << endl;
    for (int num : nums) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}


