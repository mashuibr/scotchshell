//Author - Ibrahim Shah
//Date Written - 07/07/26
//hey yooo

#include <iostream>
#include<string>
#include "command.h" //include command.h to use executeEcho function

using namespace std;

void commandRedirect(string command, string argument){
    if(command == "exit"){
        exit(0); //exit shell with exit as command
    }
 

    if(command=="echo"){
        executeEcho(argument); //call function executeEcho
    }

    if(command=="pwd"){
        executePwd(); //call function executePwd
    }
    if(command=="ls"){
        executels(); //call function executels
    }
}

int main(){

    string instruction, command, argument;

    while(true){

        cout <<"\033[36m"<< "mashu@scotch: "<< "\033[0m";//test print

        getline(cin, instruction); //get user input from shell

        // Extract command and argument
        size_t index = instruction.find(' ');
        if(index == string::npos){
            command = instruction;
            argument = "";
        }
        else{
            command = instruction.substr(0, index);
            argument = instruction.substr(index + 1);
        }
       // cout << "You typed: "<<command << endl; //put user input to shell
        commandRedirect(command, argument); //call function commandRedirect to execute command

    }

}
