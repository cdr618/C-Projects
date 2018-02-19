#include "std_lib_facilities.h"

struct controlvector{  //control vector object for each machine instruction
    string name;
    vector<int> control; // array of 0s and 1s

    //constructor
    controlvector(string n, vector<int> c) : name(n), control(c) {};
};

vector<controlvector> master;

int main(){
    cout << "Enter each control instruction of your Instruction Processing Cycle. Do not include \"C0, C1, etc.\" When you are entering steps specific to an instruction, preface the step with \"stepcode: \" as in \"add: \" or \"lw: \". Make sure every step that is specific to an instruction contains the stepcode. If two instructions have a step in common, the step must be input twice, once for each stepcode. Press CTRL + d to stop entering the IPC.\n";

    string ipc;
    vector<string> orders;
    vector<string> firstwords;
    
    //get the inputted machine instruction
    while (getline(cin,ipc)){ 
        bool alreadylisted = false;
        bool empty = true;

        //access the first word of the instruction
        string firstorder;
        char lastchar;
        stringstream ss{ipc};
        ss >> firstorder;
        lastchar = firstorder[firstorder.length() - 1];

        //if the fist word is followed by a colon
        if (lastchar == ':'){
            //record the code
            firstwords.push_back(firstorder);
            //if this is the first control vector
            if(orders.size() == 0){
                //add a new conrol vector to the array of control vectors
                vector<int> one;
                controlvector x(firstorder, one);
                master.push_back(x); 
                orders.push_back(firstorder);
               
                empty = false;
                alreadylisted = true;
            } 
            //if this is not the first
            else{
                //check to see if this code had already been used
                for(int i = 0; i < orders.size(); i++){
                    if(firstorder == orders[i]){
                        alreadylisted = true;
                        empty = false;
                    }
                }
            }
            //if it hasn't already been used, add a new control vector to the array
            if(!alreadylisted && empty){
                vector<int> one;
                controlvector x(firstorder, one);
                master.push_back(x); 
                orders.push_back(firstorder);
            }
        }
        //if this isn't a code, indicate that
        else{
            firstwords.push_back("not key word"); 
        }
    }
    //fill up the arrays with 1s for steps used by all instructions and 0s or 1s for the rest depending on the instruction
    for(int i = 0; i < master.size(); i++){
        for(string s : firstwords){
            if(s == master[i].name){
                master[i].control.push_back(1);
            }
            else if(s == "not key word"){
                master[i].control.push_back(1);
            }
            else{
                master[i].control.push_back(0);
           }
        }
    }
    //output the results
    cout << "\nControl Vectors:\n";
    for(int i = 0; i < master.size(); i++){
        cout << master[i].name << " ";
        for(int b : master[i].control){
            cout << b;
        }
        cout << "\n\n";
    } 

    cout << "Microprogram:\n";
    for(int i = 0; i < master[0].control.size(); i++){
        cout << "C" << i << " ";
    }
    cout << "\n";
    for(int i = 0; i < master.size(); i++){

        for(int b : master[i].control){
            cout << " " << b << " ";
        }
        cout << "\n";
    } 

}

