#pragma once 

#include "../error/errorHandler.h"
#include "../node/node.h"
#include <queue>

class OperationHandler {
public:
    static void quAdd(std::queue<node>& program_queue, int line_number, errorHandler error_handler);
    static void quAddK(std::queue<node>& program_queue, int line_number, errorHandler error_handler);
    static void quSub(std::queue<node>& program_queue, int line_number, errorHandler error_handler);
    static void quSubK(std::queue<node>& program_queue, int line_number, errorHandler error_handler);
    static void quMul(std::queue<node>& program_queue, int line_number, errorHandler error_handler);
    static void quMulK(std::queue<node>& program_queue, int line_number, errorHandler error_handler);
    static void quDiv(std::queue<node>& program_queue, int line_number, errorHandler error_handler);
    static void quDivK(std::queue<node>& program_queue, int line_number, errorHandler error_handler);
    static void quMod(std::queue<node>& program_queue, int line_number, errorHandler error_handler);
    static void quModK(std::queue<node>& program_queue, int line_number, errorHandler error_handler);
};