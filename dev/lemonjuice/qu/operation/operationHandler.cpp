#include <string>
#include "operationHandler.h"

using namespace std;

/**
 * The custom ADD function for the queue
 * 
 * @param program_queue The queue for the program itself.
 * @param line_number The current line index in the program.
 * @param error_handler The interpreter's error handler.
 */
void OperationHandler::quAdd(std::queue<node>& program_queue, int line_number, errorHandler error_handler) {
    if (program_queue.size() < 2) {
        // Ensure that there are at least two elements in the queue
        error_handler.notEnoughArguments(line_number);
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
 * The custom ADDK function for the queue
 * 
 * @param program_queue The queue for the program itself.
 * @param line_number The current line index in the program.
 * @param error_handler The interpreter's error handler.
 */
void OperationHandler::quAddK(std::queue<node>& program_queue, int line_number, errorHandler error_handler) {
    if (program_queue.size() < 2) {
        // Ensure that there are at least two elements in the queue
        error_handler.notEnoughArguments(line_number);
    }

    node first_operand = program_queue.front();
    program_queue.pop();
    node second_operand = program_queue.front();

    if (first_operand.containsInt() && second_operand.containsInt()) {
        // Both operands are integers, perform integer addition
        int result = first_operand.getInt() + second_operand.getInt();
        program_queue.push(node(result));
    } else {
        // At least one operand is not an integer, concatenate string representations
        string result_str = first_operand.getString() + second_operand.getString();
        program_queue.push(node(result_str));
    }

    // Create a new queue and add the first operand to it
    std::queue<node> new_queue;
    new_queue.push(first_operand);

    // Add the rest of the original queue to the new queue
    while (!program_queue.empty()) {
        new_queue.push(program_queue.front());
        program_queue.pop();
    }

    // Replace the original queue with the new queue
    program_queue = new_queue;
}

/**
 * The custom SUB function for the queue
 * 
 * @param program_queue The queue for the program itself.
 * @param line_number The current line index in the program.
 * @param error_handler The interpreter's error handler.
 */
void OperationHandler::quSub(std::queue<node>& program_queue, int line_number, errorHandler error_handler) {
    if (program_queue.size() < 2) {
        // Ensure that there are at least two elements in the queue
        error_handler.notEnoughArguments(line_number);
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
        error_handler.operationMismatch(line_number);
    }
}

/**
 * The custom SUBK function for the queue
 * 
 * @param program_queue The queue for the program itself.
 * @param line_number The current line index in the program.
 * @param error_handler The interpreter's error handler.
 */
void OperationHandler::quSubK(std::queue<node>& program_queue, int line_number, errorHandler error_handler) {
    if (program_queue.size() < 2) {
        // Ensure that there are at least two elements in the queue
        error_handler.notEnoughArguments(line_number);
    }

    node first_operand = program_queue.front();
    program_queue.pop();
    node second_operand = program_queue.front();

    if (first_operand.containsInt() && second_operand.containsInt()) {
        // Both operands are integers, perform integer subtraction
        int result = first_operand.getInt() - second_operand.getInt();
        program_queue.push(node(result));
    } else {
        // Error: SUB operation is only defined for integer operands
        error_handler.operationMismatch(line_number);
    }

    // Create a new queue and add the first operand to it
    std::queue<node> new_queue;
    new_queue.push(first_operand);

    // Add the rest of the original queue to the new queue
    while (!program_queue.empty()) {
        new_queue.push(program_queue.front());
        program_queue.pop();
    }

    // Replace the original queue with the new queue
    program_queue = new_queue;
}

/**
 * The custom MUL function for the queue
 * 
 * @param program_queue The queue for the program itself.
 * @param line_number The current line index in the program.
 * @param error_handler The interpreter's error handler.
 */
void OperationHandler::quMul(std::queue<node>& program_queue, int line_number, errorHandler error_handler) {
    if (program_queue.size() < 2) {
        // Ensure that there are at least two elements in the queue
        error_handler.notEnoughArguments(line_number);
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
        error_handler.operationMismatch(line_number);
    }
}

/**
 * The custom MULK function for the queue
 * 
 * @param program_queue The queue for the program itself.
 * @param line_number The current line index in the program.
 * @param error_handler The interpreter's error handler.
 */
void OperationHandler::quMulK(std::queue<node>& program_queue, int line_number, errorHandler error_handler) {
    if (program_queue.size() < 2) {
        // Ensure that there are at least two elements in the queue
        error_handler.notEnoughArguments(line_number);
    }

    node first_operand = program_queue.front();
    program_queue.pop();
    node second_operand = program_queue.front();

    if (first_operand.containsInt() && second_operand.containsInt()) {
        // Both operands are integers, perform integer multiplication
        int result = first_operand.getInt() * second_operand.getInt();
        program_queue.push(node(result));
    } else {
        // Error: MUL operation is only defined for integer operands
        error_handler.operationMismatch(line_number);
    }

    // Create a new queue and add the first operand to it
    std::queue<node> new_queue;
    new_queue.push(first_operand);

    // Add the rest of the original queue to the new queue
    while (!program_queue.empty()) {
        new_queue.push(program_queue.front());
        program_queue.pop();
    }

    // Replace the original queue with the new queue
    program_queue = new_queue;
}

/**
 * The custom DIV function for the queue
 * 
 * @param program_queue The queue for the program itself.
 * @param line_number The current line index in the program.
 * @param error_handler The interpreter's error handler.
 */
void OperationHandler::quDiv(std::queue<node>& program_queue, int line_number, errorHandler error_handler) {
    if (program_queue.size() < 2) {
        // Ensure that there are at least two elements in the queue
        error_handler.notEnoughArguments(line_number);
    }

    node first_operand = program_queue.front();
    program_queue.pop();
    node second_operand = program_queue.front();
    program_queue.pop();

    if (first_operand.containsInt() && second_operand.containsInt()) {
        // Check for division by zero
        if (second_operand.getInt() == 0) {
            error_handler.divisionByZero(line_number);
        }

        // Both operands are integers, perform integer division
        int result = first_operand.getInt() / second_operand.getInt();
        program_queue.push(node(result));
    } else {
        // Error: DIV operation is only defined for integer operands
        error_handler.operationMismatch(line_number);
    }
}

/**
 * The custom DIVK function for the queue
 * 
 * @param program_queue The queue for the program itself.
 * @param line_number The current line index in the program.
 * @param error_handler The interpreter's error handler.
 */
void OperationHandler::quDivK(std::queue<node>& program_queue, int line_number, errorHandler error_handler) {
    if (program_queue.size() < 2) {
        // Ensure that there are at least two elements in the queue
        error_handler.notEnoughArguments(line_number);
    }

    node first_operand = program_queue.front();
    program_queue.pop();
    node second_operand = program_queue.front();

    if (first_operand.containsInt() && second_operand.containsInt()) {
        // Check for division by zero
        if (second_operand.getInt() == 0) {
            error_handler.divisionByZero(line_number);
        }

        // Both operands are integers, perform integer division
        int result = first_operand.getInt() / second_operand.getInt();
        program_queue.push(node(result));
    } else {
        // Error: DIV operation is only defined for integer operands
        error_handler.operationMismatch(line_number);
    }

    // Create a new queue and add the first operand to it
    std::queue<node> new_queue;
    new_queue.push(first_operand);

    // Add the rest of the original queue to the new queue
    while (!program_queue.empty()) {
        new_queue.push(program_queue.front());
        program_queue.pop();
    }

    // Replace the original queue with the new queue
    program_queue = new_queue;
}

/**
 * The custom MOD function for the queue
 * 
 * @param program_queue The queue for the program itself.
 * @param line_number The current line index in the program.
 * @param error_handler The interpreter's error handler.
 */
void OperationHandler::quMod(std::queue<node>& program_queue, int line_number, errorHandler error_handler) {
    if (program_queue.size() < 2) {
        // Ensure that there are at least two elements in the queue
        error_handler.notEnoughArguments(line_number);
    }

    node first_operand = program_queue.front();
    program_queue.pop();
    node second_operand = program_queue.front();
    program_queue.pop();

    if (first_operand.containsInt() && second_operand.containsInt()) {
        // Check for division by zero
        if (second_operand.getInt() == 0) {
            error_handler.divisionByZero(line_number);
        }

        // Both operands are integers, perform integer modulus
        int result = first_operand.getInt() % second_operand.getInt();
        program_queue.push(node(result));
    } else {
        // Error: MOD operation is only defined for integer operands
        error_handler.operationMismatch(line_number);
    }
}

/**
 * The custom MODK function for the queue
 * 
 * @param program_queue The queue for the program itself.
 * @param line_number The current line index in the program.
 * @param error_handler The interpreter's error handler.
 */
void OperationHandler::quModK(std::queue<node>& program_queue, int line_number, errorHandler error_handler) {
    if (program_queue.size() < 2) {
        // Ensure that there are at least two elements in the queue
        error_handler.notEnoughArguments(line_number);
    }

    node first_operand = program_queue.front();
    program_queue.pop();
    node second_operand = program_queue.front();

    if (first_operand.containsInt() && second_operand.containsInt()) {
        // Check for division by zero
        if (second_operand.getInt() == 0) {
            error_handler.divisionByZero(line_number);
        }

        // Both operands are integers, perform integer modulus
        int result = first_operand.getInt() % second_operand.getInt();
        program_queue.push(node(result));
    } else {
        // Error: MOD operation is only defined for integer operands
        error_handler.operationMismatch(line_number);
    }

    // Create a new queue and add the first operand to it
    std::queue<node> new_queue;
    new_queue.push(first_operand);

    // Add the rest of the original queue to the new queue
    while (!program_queue.empty()) {
        new_queue.push(program_queue.front());
        program_queue.pop();
    }

    // Replace the original queue with the new queue
    program_queue = new_queue;
}