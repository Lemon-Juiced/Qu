#pragma once 
#include <string>

class errorHandler{
private:
public:
    errorHandler();

    void divideByZeroError(int);

    void exitProgram(int);

    void invalidPushError(int);

    void fileExtraError(int, int);
    void fileInvalidExtensionError(std::string);
    void fileMissingError(int);

    void notEnoughArgumentsError(int);

    void operationMismatchError(int);

    void singleBarError(int, int);
    void singleQuoteError(int, int);

    void unknownInstruction(int);

};