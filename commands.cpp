#include<iostream>
#include<string>

#include "command.h"

using namespace std;

void executeEcho(string command){
    cout << command.substr(5) << endl; //print the string after echo command
}

