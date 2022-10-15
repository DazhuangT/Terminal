#include "command.h"

//Dazhuang Teng 251052285
//10/5/2021
//This class will connect the mainwindow and linuxsystem, then also capture and transfer the output result
command::command(std::string commandInput)
{
    commandTxt = commandInput;
    result = "";
    nextLine = "\n";//a singal change to a new line for result
    returnCode = 0;
}

//fuction: execute
//An execute method to execute the command, storing the output and return code appropriately.
//parameter
//return: void return nothing
void command::execute(){
    try {
        boost::process::ipstream pipe_stream;
        boost::process::child c(commandTxt, (boost::process::std_err & boost::process::std_out) > pipe_stream);

        std::string line;

        //complie linux command and then save result in a string
        while (pipe_stream && std::getline(pipe_stream, line) && !line.empty()){
            //std::cerr << line << std::endl;
            result.append(line);
            result.append(nextLine);
        }
        c.wait();
        returnCode = c.exit_code();//get the right exitcode

    }  catch (const boost::process::process_error& e) {
        result.append(e.what());//if there is no result, just save the error info
        returnCode = -1;//if error showed up, the exit code is always -1
    }
}

//function:getCommandText
//getter method for the input text
//parameter
//return commandTxt
std::string command::getCommandtext(){
    return commandTxt;
}

//setter for the command text
void command::setCommandtext(std::string newCommandtxt){
    commandTxt = newCommandtxt;
}

//function:getResult
//getter method for the final result of execute
//parameter
//return result
std::string command::getResult(){
    return result;
}

//function:getReturncode
//getter method for the exit code of execute child
//parameter
//return returnCode
int command::getReturncode(){
    return returnCode;
}

//function getCodestring
//this method transfer returncode into string
//parameter
//return codeString
std:: string command::getCodestring(){
    std:: string codeString = std::to_string(getReturncode());
    return codeString;
}

//destructor
command::~command()
{
}
