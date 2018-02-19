#include "../std_lib_facilities.h"

vector<char> letter_to_digit(vector<char> sev){
    vector<char> translated;  //this is the vector that is returned
    for(int i = 0; i < sev.size(); i++){ //iterates through the word part of the phonenumber
        //if/else statements determine the number the letter translates to
        if (sev[i] == 'a' || sev[i] == 'b' || sev[i] == 'c'){
            translated.push_back('2');
        }
        else if (sev[i] == 'd' || sev[i] == 'e' || sev[i] == 'f'){
            translated.push_back('3');
        }
        else if (sev[i] == 'g' || sev[i] == 'h' || sev[i] == 'i'){
            translated.push_back('4');
        }
        else if (sev[i] == 'j' || sev[i] == 'k' || sev[i] == 'l'){
            translated.push_back('5');
        }
        else if (sev[i] == 'm' || sev[i] == 'n' || sev[i] == 'o'){
            translated.push_back('6');
        }
        else if (sev[i] == 'p' || sev[i] == 'q' || sev[i] == 'r' || sev[i] == 's'){
            translated.push_back('7');
        }
        else if (sev[i] == 't' || sev[i] == 'u' || sev[i] == 'v'){
            translated.push_back('8');
        }
        else if (sev[i] == 'w' || sev[i] == 'x' || sev[i] == 'y' || sev[i] == 'z'){
            translated.push_back('9');
        }
        
    }
    return translated; //returns the translated phone number
}

void printnum(vector<char> original, vector<char> vec){
    for(int j = 0; j < 5; ++j){ //prints out the first 4 digits of the given phonenumber
        cout << original[j];
    }
    cout << "-";
    //prints out the translated part of the phonenumber
    for(int i = 0; i < 3; ++i){
        cout << vec[i];
    }
    cout << "-";
    for(int i = 3; i < vec.size(); ++i){
        cout << vec[i];
    }
    cout << "\n";
}

int main(){
vector<char> whole(13);
vector<char> seven(7);
string num;

cout << "Please enter an 11 digit phone number with letters in the format 1-709-flowers.\n";
cin >> num;
    for (int j = 0; j < 13; ++j){
        whole[j] = num[j];
    }
    for (int i = 6; i < 13; ++i){
        seven[i-6] = whole[i];
    }

printnum(whole, letter_to_digit(seven));
}

        
