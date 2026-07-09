#include<iostream>
#include<string>
#include <unistd.h>
#include <dirent.h>

#include "command.h"

using namespace std;

void executeEcho(string statement){
    cout << statement << endl; //print the string after echo command
}

void executePwd(){
    char buffer[100];
    char *result = getcwd(buffer, 100); //get current working directory
    cout << result << endl;
}

void executels(){
    DIR* dir= opendir(".");
    struct dirent *head;
    while((head=readdir(dir))!=NULL){
        if (head->d_name[0] == '.')
            continue;
        cout<< head->d_name <<endl;
    }
}