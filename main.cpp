//Author - Ibrahim Shah
//Date Written - 07/07/26
//hey yooo

#include <iostream>
#include<string>

using namespace std;

int main(){

    string command;

    while(true){

        cout << "my shell> ";//test print

        getline(cin, command); //get user input from shell

        if(command == "exit"){
            break; //exit shell with exit as command
        }

        cout << "You typed: "<<command << endl; //put user input to shell

        if(command.substr(0,4)=="echo"){
            cout << command.substr(5) <<endl; //echo command to shell
        }

    }

}