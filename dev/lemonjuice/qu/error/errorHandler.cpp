#include "errorHandler.h"

#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

errorHandler::errorHandler(){}

/**
 * Handles errors when an error occurs when a division by zero happens.
 * 
 * @param line The line of the error.
 */
void errorHandler::divideByZeroError(int line){
    cout << "Error: Division by zero at line: " << line << "." << endl;
    exitProgram(-1);
}

/**
 * Handles exiting a program when an error is encounted.
 * 
 * @param exitCode The exit code to use.
 */
void errorHandler::exitProgram(int exitCode){
    exit(exitCode);
}

/**
 * Handles errors when an error occurs where PUSH can't read what's being put onto the queue.
 * 
 * @param line The line of the error.
 */
void errorHandler::invalidPushError(int line){
    cout << "Error: Invalid PUSH on: " << line << "." << endl;
    exitProgram(-1);
}

/**
 * Handles errors when extra files are specified at interpretation.
 * 
 * @param max_arg The index of the final arg.
 * @param expected_args The expected number of args that should have been specified.
 */
void errorHandler::fileExtraError(int max_arg, int expected_args){
    cout << "Error: Extra file argument at index (indices): ";
    for (size_t i = expected_args; i <= max_arg; i++){
        cout << max_arg;
        if(i+1 != max_arg) cout << ", ";
        cout << "." << endl;
    }
    exitProgram(-1);
}

/**
 * Handles errors when the file extension is invalid.
 * 
 * @param file_name The file's name.
 */
void errorHandler::fileInvalidExtensionError(std::string file_name){
    cout << "Error: The file: " << file_name << " is invalid." << endl;
    cout << "File name must end in \".qu\"." << endl;
    exitProgram(-1);
}

/**
 * Handles errors when files are missing at interpretation.
 * 
 * @param arg The index of the missing arg.
 */
void errorHandler::fileMissingError(int arg){
    cout << "Error: Missing file argument at index: " << arg << "." << endl;
    exitProgram(-1);
}

/**
 * Handles errors when there aren't enough arguments to successfully complete an operation.
 * 
 * @param line The line of the error.
 */
void errorHandler::notEnoughArgumentsError(int line){
    cout << "Error: Missing arguments at line : " << line << "." << endl;
    exitProgram(-1);
}

/**
 * Handles errors when a string an integer node have an incompatible operations on eachother.
 * 
 * @param line The line of the error.
 */
void errorHandler::operationMismatchError(int line){
    cout << "Error: Mismatched int and string operaton on : " << line << "." << endl;
    exitProgram(-1);
}

/**
 * Handles errors when there is a single lone '|' character.
 * 
 * @param index The index of the  single lone '|'.
 * @param line The line of the error.
 */
void errorHandler::singleBarError(int index, int line){
    cout << "Error: Single '|' on line: " << line << " at index: " << index << "." << endl;
    exitProgram(-1);
}

/**
 * Handles errors when there is a single lone '\"' character.
 * 
 * @param index The index of the  single lone '\"'.
 * @param line The line of the error.
 */
void errorHandler::singleQuoteError(int index, int line){
    cout << "Error: Single '\"' on line: " << line << " at index: " << index << "." << endl;
    exitProgram(-1);
}

/**
 * Handles errors when there is an unknown instruction is used.
 * 
 * @param line The line of the error.
 */
void errorHandler::unknownInstruction(int line){
    cout << "Error: Unknown instruction on line: " << line << "." << endl;
    exitProgram(-1);
}
