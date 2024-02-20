#pragma once 
#include <string>

class errorHandler{
private:
    void printError(const std::string& message);
public:
    errorHandler();

    void divideByZeroError(int);

    void exitProgram(int);

    void invalidPushError(int);

    void fileExtraError(int, int);
    void fileInvalidExtensionError(std::string);
    void fileMissingError(int);

    void goToInvalidLineError(int);

    void nonIntegerReturnValueError(int);

    void notEnoughArgumentsError(int);

    void operationMismatchError(int);

    void unspecifiedComparisonOperationError(int);

    void printError(int);

    void readError(int);

    void retEmptyQueueError(int); 

    void singleBarError(int, int);
    void singleQuoteError(int, int);

    void unknownInstruction(int);

};