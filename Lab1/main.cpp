#include <iostream>
#include "include/euclid.h" 
using namespace std;

int main() {
    int num1, num2;
    cout << "Введите первое число: ";
    cin >> num1;
    cout << "Введите второе число: ";
    cin >> num2;
    int divider = euclid(num1, num2); 

    cout << divider << endl;
    return 0;
}