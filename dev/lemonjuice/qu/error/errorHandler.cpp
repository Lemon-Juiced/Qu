#include "errorHandler.h"

#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

// ANSI Escape Codes
const std::string RED_COLOR = "\033[1;31m";
const std::string RESET_COLOR = "\033[0m";

errorHandler::errorHandler(){}

/**
 * Helper function to print error messages with red color
 * 
 * @param error_message The error message included.
 */
void errorHandler::printError(const string& error_message) {
    cerr << RED_COLOR << "Error: " << error_message << RESET_COLOR << endl;
}

/**
 * Handles errors when an error occurs when a division by zero happens.
 * 
 * @param line The line of the error.
 */
void errorHandler::divideByZeroError(int line){
    printError("Division by zero at line: " + to_string(line));
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
    printError("Invalid PUSH on line: " + to_string(line));
    exitProgram(-1);
}

/**
 * Handles errors when extra files are specified at interpretation.
 * 
 * @param max_arg The index of the final arg.
 * @param expected_args The expected number of args that should have been specified.
 */
void errorHandler::fileExtraError(int max_arg, int expected_args){
    cerr << RED_COLOR << "Error: Extra file argument(s) at index (indices): ";
    for (size_t i = expected_args; i <= max_arg; i++) {
        cerr << i;
        if (i + 1 <= max_arg) {
            cerr << ", ";
        }
    }
    cerr << "." << RESET_COLOR << endl;
    exitProgram(-1);
}

/**
 * Handles errors when the file extension is invalid.
 * 
 * @param file_name The file's name.
 */
void errorHandler::fileInvalidExtensionError(std::string file_name){
    printError("The file: " + file_name + " is invalid.\nFile name must end in \".qu\".");
    exitProgram(-1);
}

/**
 * Handles errors when files are missing at interpretation.
 * 
 * @param arg The index of the missing arg.
 */
void errorHandler::fileMissingError(int arg){
    printError("Missing file argument at index: " + to_string(arg));
    exitProgram(-1);
}

/**
 * Handles errors when a GOTO instruction sends the program to an unexpected area.
 * 
 * @param line The line of the error.
 */
void errorHandler::goToInvalidLineError(int line){
    printError("GOTO tried to send program to unexpected area at line: " + to_string(line));
    exitProgram(-1);
}

/**
 * Handles errors when a RET instruction tries to pass a value other than an integer to the return value.
 * 
 * @param line The line of the error.
 */
void errorHandler::nonIntegerReturnValueError(int line){
    printError("Tried to return value other than an integer at line: " + to_string(line));
    exitProgram(-1);
}

/**
 * Handles errors when there aren't enough arguments to successfully complete an operation.
 * 
 * @param line The line of the error.
 */
void errorHandler::notEnoughArgumentsError(int line){
    printError("Missing arguments at line: " + to_string(line));
    exitProgram(-1);
}

/**
 * Handles errors when there an unspecified comparsion operation is used
 * 
 * @param line The line of the error.
 */
void errorHandler::unspecifiedComparisonOperationError(int line){
    printError("An unspecified comparsion operation was used at line: " + to_string(line));
    exitProgram(-1);
}

/**
 * Handles errors when a RET instruction tries to return from an empty queue.
 * 
 * @param line The line of the error.
 */
void errorHandler::retEmptyQueueError(int line){
    printError("Tried to return value from an empty queue at line: " + to_string(line));
    exitProgram(-1);
}

/**
 * Handles errors when a string and integer node have an incompatible operations on eachother.
 * 
 * @param line The line of the error.
 */
void errorHandler::operationMismatchError(int line){
    printError("Mismatched int and string operation on line: " + to_string(line));
    exitProgram(-1);
}

/**
 * Handles errors when something is passed to PRINT that cannot be printed.
 * 
 * @param line The line of the error.
 */
void errorHandler::printError(int line){
    printError("Something was attempted to be printed via PRINT that cannot be printed on line: " + to_string(line));
    exitProgram(-1);
}

/**
 * Handles errors when something is passed to READ that cannot be read.
 * 
 * @param line The line of the error.
 */
void errorHandler::readError(int line){
    printError("Something was attempted to be read via READ that cannot be read on line: " + to_string(line));
    exitProgram(-1);
}

/**
 * Handles errors when there is a single lone '|' character.
 * 
 * @param index The index of the  single lone '|'.
 * @param line The line of the error.
 */
void errorHandler::singleBarError(int index, int line){
    printError("Single '|' on line: " + to_string(line) + " at index: " + to_string(index));
    exitProgram(-1);
}

/**
 * Handles errors when there is a single lone '\"' character.
 * 
 * @param index The index of the  single lone '\"'.
 * @param line The line of the error.
 */
void errorHandler::singleQuoteError(int index, int line){
    printError("Single '\"' on line: " + to_string(line) + " at index: " + to_string(index));
    exitProgram(-1);
}

/**
 * Handles errors when there is an unknown instruction is used.
 * 
 * @param line The line of the error.
 */
void errorHandler::unknownInstruction(int line){
    printError("Unknown instruction on line: " + to_string(line));
    exitProgram(-1);
}
