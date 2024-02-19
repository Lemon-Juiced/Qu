#include <string>
#include "operationHandler.h"

using namespace std;

// Globals
errorHandler error_handler; // error_handler to handle errors.

/**
 * The custom ADD function for the queue
 * 
 * @param program_queue The queue for the program itself.
 * @param line_number The current line index in the program.
 */
void OperationHandler::quAdd(std::queue<node>& program_queue, int line_number) {
    if (program_queue.size() < 2) {
        // Ensure that there are at least two elements in the queue
        error_handler.notEnoughArgumentsError(line_number);
    }

    node first_operand = program_queue.front();
    program_queue.pop();
    node second_operand = program_queue.front();
    program_queue.pop();

    if (first_operand.containsInt() && second_operand.containsInt()) {
        // Both operands are integers, perform integer addition
        int result = first_operand.getInt() + second_operand.getInt();
        program_queue.push(node(result));
    } else {
        // At least one operand is not an integer, concatenate string representations
        string result_str = first_operand.getString() + second_operand.getString();
        program_queue.push(node(result_str));
    }
}

/**
 * The custom SUB function for the queue
 * 
 * @param program_queue The queue for the program itself.
 * @param line_number The current line index in the program.
 */
void OperationHandler::quSub(std::queue<node>& program_queue, int line_number) {
    if (program_queue.size() < 2) {
        // Ensure that there are at least two elements in the queue
        error_handler.notEnoughArgumentsError(line_number);
    }

    node first_operand = program_queue.front();
    program_queue.pop();
    node second_operand = program_queue.front();
    program_queue.pop();

    if (first_operand.containsInt() && second_operand.containsInt()) {
        // Both operands are integers, perform integer subtraction
        int result = first_operand.getInt() - second_operand.getInt();
        program_queue.push(node(result));
    } else {
        // Error: SUB operation is only defined for integer operands
        error_handler.operationMismatchError(line_number);
    }
}

/**
 * The custom MUL function for the queue
 * 
 * @param program_queue The queue for the program itself.
 * @param line_number The current line index in the program.
 */
void OperationHandler::quMul(std::queue<node>& program_queue, int line_number) {
    if (program_queue.size() < 2) {
        // Ensure that there are at least two elements in the queue
        error_handler.notEnoughArgumentsError(line_number);
    }

    node first_operand = program_queue.front();
    program_queue.pop();
    node second_operand = program_queue.front();
    program_queue.pop();

    if (first_operand.containsInt() && second_operand.containsInt()) {
        // Both operands are integers, perform integer multiplication
        int result = first_operand.getInt() * second_operand.getInt();
        program_queue.push(node(result));
    } else {
        // Error: MUL operation is only defined for integer operands
        error_handler.operationMismatchError(line_number);
    }
}

/**
 * The custom DIV function for the queue
 * 
 * @param program_queue The queue for the program itself.
 * @param line_number The current line index in the program.
 */
void OperationHandler::quDiv(std::queue<node>& program_queue, int line_number) {
    if (program_queue.size() < 2) {
        // Ensure that there are at least two elements in the queue
        error_handler.notEnoughArgumentsError(line_number);
    }

    node first_operand = program_queue.front();
    program_queue.pop();
    node second_operand = program_queue.front();
    program_queue.pop();

    if (first_operand.containsInt() && second_operand.containsInt()) {
        // Check for division by zero
        if (second_operand.getInt() == 0) {
            error_handler.divideByZeroError(line_number);
        }

        // Both operands are integers, perform integer division
        int result = first_operand.getInt() / second_operand.getInt();
        program_queue.push(node(result));
    } else {
        // Error: DIV operation is only defined for integer operands
        error_handler.operationMismatchError(line_number);
    }
}

/**
 * The custom MOD function for the queue
 * 
 * @param program_queue The queue for the program itself.
 * @param line_number The current line index in the program.
 */
void OperationHandler::quMod(std::queue<node>& program_queue, int line_number) {
    if (program_queue.size() < 2) {
        // Ensure that there are at least two elements in the queue
        error_handler.notEnoughArgumentsError(line_number);
    }

    node first_operand = program_queue.front();
    program_queue.pop();
    node second_operand = program_queue.front();
    program_queue.pop();

    if (first_operand.containsInt() && second_operand.containsInt()) {
        // Check for division by zero
        if (second_operand.getInt() == 0) {
            error_handler.divideByZeroError(line_number);
        }

        // Both operands are integers, perform integer modulus
        int result = first_operand.getInt() % second_operand.getInt();
        program_queue.push(node(result));
    } else {
        // Error: MOD operation is only defined for integer operands
        error_handler.operationMismatchError(line_number);
    }
}