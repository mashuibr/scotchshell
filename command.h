#ifndef COMMANDS_H
#define COMMANDS_H

#include<string>

void executeEcho(std::string statement);
void executePwd();
void executels();
void executeCd(std::string path);
std::string getPrompt();

#endif