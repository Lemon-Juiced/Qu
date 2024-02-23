#pragma once 
#include <string>

class errorHandler{
private:
    void printError(const std::string& message);
public:
    errorHandler();

    void divisionByZero(int);

    void exitProgram(int);

    void invalidPush(int);

    void extraFileArguments(int, int);
    void invalidFileExtension(std::string);
    void missingFileArgument(int);

    void invalidGoto(int);

    void nonIntegerReturnValue(int);

    void notEnoughArguments(int);

    void operationMismatch(int);

    void unspecifiedComparisonOperation(int);

    void invalidPrintOperation(int);

    void invalidReadOperation(int);

    void returnFromEmptyQueue(int); 

    void singleBarError(int, int);
    void singleQuoteError(int, int);

    void unknownInstruction(int);

};