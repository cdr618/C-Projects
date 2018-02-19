#include "../std_lib_facilities.h"
// Insert your print function definition here!
// Test your function by the following main program.

void print(string label, const vector<int>& vec){ //print function
    cout << label;    //outputs the label
    for(int i = 0; i < vec.size(); ++i){  //iterates through the vector and prints every element
        cout << vec[i] << " ";
    }
    cout << "\n";
}

void fibonacci(int x, int y, vector<int>& v, int n){
    int temp;  //initializes the int that will be added to the vector
    v.push_back(x);  //adds the first 2 numbers in the sequence
    v.push_back(y);
    for(int i = 2; i < n; ++i){  //adds numbers until the vector is of size n 
        temp = v[i-1] + v[i-2]; //calculates the next digit in the fibonacci sequence
        v.push_back(temp);  //adds the calculated number to the vector
    }
}

int main( )
{
vector<int> v1 = { 13, 21, 35, 47, 59 };
print("The elements of the first vector are: ", v1);
vector<int> v2 = { 23, 31, 45, 57, 69, 72};
print("The elements of the second vector are: ", v2);

vector<int> a, b;
fibonacci(1, 1, a, 12);
print("The fibonacci numbers from 1,1 are: ", a);
fibonacci(8,13, b, 10);
print("The fibonacci numbers from 8,13 are: ", b);
return 0;
}
