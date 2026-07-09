#include<iostream>
#include<string>
#include <unistd.h>

#include "command.h"

using namespace std;

void executeEcho(string command){
    cout << command.substr(5) << endl; //print the string after echo command
}

void executePwd(){
    char buffer[100];
    char *result = getcwd(buffer, 100); //get current working directory
    cout << result << endl;
}