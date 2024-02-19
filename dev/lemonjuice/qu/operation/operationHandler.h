#pragma once 

#ifndef OPERATION_HANDLER_H
#define OPERATION_HANDLER_H

#include "../error/errorHandler.h"
#include "../node/node.h"
#include <queue>

class OperationHandler {
public:
    static void quAdd(std::queue<node>& program_queue, int line_number, errorHandler error_handler);
    static void quSub(std::queue<node>& program_queue, int line_number, errorHandler error_handler);
    static void quMul(std::queue<node>& program_queue, int line_number, errorHandler error_handler);
    static void quDiv(std::queue<node>& program_queue, int line_number, errorHandler error_handler);
    static void quMod(std::queue<node>& program_queue, int line_number, errorHandler error_handler);
};

#endif // OPERATION_HANDLER_H