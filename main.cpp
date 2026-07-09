//Author - Ibrahim Shah
//Date Written - 07/07/26
//hey yooo

#include <iostream>
#include<string>
#include "command.h" //include command.h to use executeEcho function

using namespace std;

int main(){

    string command;

    while(true){

        cout << "mashu@scotch:  ";//test print

        getline(cin, command); //get user input from shell

        if(command == "exit"){
            break; //exit shell with exit as command
        }

        cout << "You typed: "<<command << endl; //put user input to shell

        if(command.substr(0,4)=="echo"){
            executeEcho(command); //call function executeEcho
        }

    }

}
