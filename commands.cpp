#include<iostream>
#include <stdio.h>
#include<cstring>
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

string getPrompt(){
    const char* home = getenv("HOME"); //get home directory path
    char buffer[100];
    char *path= getcwd(buffer, 100); //get current working directory
    string path_string=string(path);

    if (path_string.rfind(home, 0) == 0){
        path_string = "~" + path_string.substr(strlen(home)); //replace home directory path with ~
    }
    
    return path_string;
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

void executeCd(string path){
    if(chdir(path.c_str()) != 0){
        perror("chdir failed");
    }
    else{
        cout << "Changed directory to: " << path << endl;
    } //change directory to the specified path
}