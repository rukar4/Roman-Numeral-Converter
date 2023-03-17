#include <iostream>
#include <stack>

using namespace std;

//Define Roman numerals to their decimal values.
int const I = 1;
int const V = 5;
int const X = 10;
int const L = 50;
int const C = 100;
int const D = 500;
int const M = 1000;

//Print function I used mainly to debug my code
template <typename T>
void PrintNumeral(stack<T> numeral){
    while(!numeral.empty()){
        cout << numeral.top() << " ";
        numeral.pop();
    }
    cout << endl;
};

//Function definitions
int ConvertRomanToDecimal(const string& romanNumeral, stack<char>& numeralStack);
void StackRomanNumeral(const string& romanNumeral, stack<char>& numeralStack);
stack<int> RawNumeralsToValues(stack<char> numeralStack);
string ConvertDecimalToRoman(int decimal);

int main() {
    stack<char> numeral;
    int userDecision = 0;
    int userDecimal;
    string userNumeral;

    do {
        cout << "Which converter would you like? (Enter an integer) \n"
                "1  Roman Numeral to Decimal\n"
                "2  Decimal to Roman Numeral\n"
                "0  Exit (Any other input)" << endl;

        cin >> userDecision;
        cin.ignore();

        if (userDecision == 1) {
            cout << endl << "Enter Roman Numeral:" << endl;
            cin >> userNumeral;
            cout << endl << ConvertRomanToDecimal(userNumeral, numeral) << endl << endl;
            continue;
        } else if (userDecision == 2) {
            cout << endl << "Enter Integer:" << endl;
            cin >> userDecimal;
            cout << endl << ConvertDecimalToRoman(userDecimal) << endl << endl;
            continue;
        }
    } while(userDecision == 1 || userDecision == 2);
}

string ConvertDecimalToRoman(int decimal){
    string romanNumeral;
    /* Check the size of decimal and as long as it is not zero, we keep iterating over it checking to see what the next
     * largest Roman Numeral is for the integer we input. */
    while(decimal != 0) {
        if (decimal >= M) {
            romanNumeral += "M";
            decimal -= M;
        } else if (decimal >= M - C) {
            romanNumeral += "CM";
            decimal -= M - C;
        } else if (decimal >= D) {
            romanNumeral += "D";
            decimal -= D;
        } else if (decimal >= D - C) {
            romanNumeral += "CD";
            decimal -= D - C;
        } else if (decimal >= C) {
            romanNumeral += "C";
            decimal -= C;
        } else if (decimal >= C - X) {
            romanNumeral += "XC";
            decimal -= C - X;
        } else if (decimal >= L) {
            romanNumeral += "L";
            decimal -= L;
        } else if (decimal >= L - X) {
            romanNumeral += "XL";
            decimal -= L - X;
        } else if (decimal >= X) {
            romanNumeral += "X";
            decimal -= X;
        } else if (decimal >= X - I) {
            romanNumeral += "IX";
            decimal -= X - I;
        } else if (decimal >= V) {
            romanNumeral += "V";
            decimal -= V;
        } else if (decimal >= V - I) {
            romanNumeral += "IV";
            decimal -= V - I;
        } else {
            while(decimal != 0){
                romanNumeral += "I";
                decimal -= I;
            }
        }
    }
    return romanNumeral;
}

int ConvertRomanToDecimal(const string& romanNumeral, stack<char>& numeralStack){
    int total = 0;
    //Convert the roman numeral into a stack of characters.
    StackRomanNumeral(romanNumeral, numeralStack);

    //Get the raw values of the numerals
    stack<int> values = RawNumeralsToValues(numeralStack);

//    PrintNumeral(values);

    //Loop through values and add them to the total.
    while(!values.empty()){
        //Check if we are on the last character in the numeral. If we are, we simply add it without comparing it.
        if(values.size() == 1){
            total += values.top();
            values.pop();
            continue;
        }

        /* Now we check to see if we need to subtract the pairs from each other. We add the difference to the total
         * if so and add both if not. */
        int next = values.top();
        values.pop();

        if (next < values.top()){
            next = values.top() - next;
            total += next;
            values.pop();
        } else {
            total += next;
        }
    }
    return total;
}

void StackRomanNumeral(const string& romanNumeral, stack<char>& numeralStack){
    while(!numeralStack.empty()){
        numeralStack.pop();
    }

    for (char i : romanNumeral){
        numeralStack.push(toupper(i));
    }
}

stack<int> RawNumeralsToValues(stack<char> numeralStack){
    //Create a stack of the raw values of each individual letter.
    stack<int> rawValues;
    while (!numeralStack.empty()){
        if(numeralStack.top() == 'I'){
            rawValues.push(I);
            numeralStack.pop();
        } else if(numeralStack.top() == 'V'){
            rawValues.push(V);
            numeralStack.pop();
        } else if(numeralStack.top() == 'X'){
            rawValues.push(X);
            numeralStack.pop();
        } else if(numeralStack.top() == 'L'){
            rawValues.push(L);
            numeralStack.pop();
        } else if(numeralStack.top() == 'C'){
            rawValues.push(C);
            numeralStack.pop();
        } else if(numeralStack.top() == 'D'){
            rawValues.push(D);
            numeralStack.pop();
        } else if(numeralStack.top() == 'M'){
            rawValues.push(M);
            numeralStack.pop();
        } else {
            throw out_of_range("Error: Invalid input for selection.");
        }
    }
    return rawValues;
}
