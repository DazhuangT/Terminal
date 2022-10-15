#ifndef COMMAND_H
#define COMMAND_H

#include <boost/process.hpp>
#include <iostream>
#include <exception>

//Dazhuang Teng 251052285
//10/5/2021
//This class will connect the mainwindow and linuxsystem, then also capture and transfer the output result
class command
{
public:
    command(std::string);//A constructor to initialize the attributes of objects of the class when created, taking the command to execute as a parameter.
    ~command();//A destructor to tear things down when objects are destroyed.
    void execute();//An execute method to execute the command, storing the output and return code appropriately.
    //getters and setter
    void setCommandtext(std::string);
    std:: string getCommandtext();
    std:: string getResult();
    int getReturncode();
    std:: string getCodestring();//this class simply transfer return code to a string

private:
    std::string commandTxt, result, nextLine;
    int returnCode;//exitcode
};

#endif // COMMAND_H
