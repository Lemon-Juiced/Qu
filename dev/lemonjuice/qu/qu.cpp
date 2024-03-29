#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include "error\errorHandler.h"
#include "node\node.h"
#include "operation\operationHandler.h"

using namespace std;

// Globals
errorHandler error_handler; // error_handler to handle errors.
queue<node> program_queue; // Queue, that represents the queue, that is the memory of the program.
map<string, int> saved_positions; // Map that stores the positions the programmer dictated for GOTOs.

// Prototypes
bool fileArgChecker(int argc);
int run(vector<string> program_text);
bool isInteger(string str);
bool compareFirstTwo(const std::queue<node>& program_queue, string comparisonType, int line);

/**
 * This is the main entryway into the interpreter.
 */
int main(int argc, char *argv[]){
    // Handle all file stuff before interpretation.
    fileArgChecker(argc); // Check for the correct number of arguments.
    fstream program_file; // File passed as an argument.
    program_file.open(argv[1], ios::in); // Sets the file as a read-only file.
    string file_name = argv[1]; // Get the file's name.

    // This section doesn't seem to work 100% correctly. 
    size_t last_dot_pos = file_name.find_last_of('.'); // Find the last dot in the file's name.
    if (last_dot_pos != string::npos) { // Checking if the '.' is found in the file's name.
        string file_extension = file_name.substr(last_dot_pos + 1); // Get the file's extension.
        if(file_extension != "qu") error_handler.invalidFileExtension(file_name); // Error sequence for invalid file extensions.
    }
    else error_handler.invalidFileExtension(file_name); // Error sequence for invalid file extensions.

    // Moves the file contents into the program.
    vector<string> program_text; // The text of the program in string vector form.
    if(program_file.is_open()){
        string line;
        while (getline(program_file, line)) program_text.push_back(line);
    }
    program_file.close();

    // This is a test to just print output.
    cout << "Program Start: " << endl;
    for (const auto& line : program_text) std::cout << "\t" << line << std::endl;
    cout << "Program End" << endl;

    return run(program_text);
}

/**
 * Checks to make sure the correct number of arguments was passed to the interpreter.
 * For now only 2 arguments should be seen, this method can be modified going forward if more arguments are required.
 * 
 * @param argc The number of arguments passed to the interpreter.
 * @return true if argc is correct, the program will error and end otherwise.
 */
bool fileArgChecker(int argc){
    int expected_args = 2;
    if(argc != expected_args){ 
        if (argc < expected_args) error_handler.missingFileArgument(argc);
        else error_handler.extraFileArguments(argc, expected_args);
    }
    return true;
}

/**
 * The actual run section of the program for the interpreter.
 * 
 * @param program_text The actual text that is the program.
 * @return true if argc is correct, the program will error and end otherwise.
 */
int run(vector<string> program_text){
    // This is just for debug
    cout << "Output Start: " << endl;

    // On the first run through of the program we should find all the saved positions and save to the saved_positions map<string, int>.
    for(int i = 0; i < program_text.size(); i++){
        string current_line = program_text[i];
        if (current_line.find('|') != std::string::npos) {
            size_t bar_pos1 = current_line.find('|'); //The first occurrence of '|'
            size_t bar_pos2 = current_line.rfind('|'); //The last occurrence of '|'
            if(bar_pos1 == bar_pos2) error_handler.singleBarError(bar_pos1, i);
            else {
                string save = current_line.substr(bar_pos1+1, bar_pos2-1);
                saved_positions.insert({save, i});
            }
        }
    }

    // This will be used for map stuff later
    //if(saved_positions.at("HELP") == 2) cout << "True" << endl;

    // Run the code for real this time.
    for(int i = 0; i < program_text.size(); i++){
        string current_line = program_text[i];

        // Skip empty lines and lines starting with '|'
        if(current_line.empty() || current_line.find_first_not_of(" \t") == string::npos || current_line[0] == '|') {
            continue;
        }

        // ADD
        if (current_line.find("ADD") != string::npos) {
            OperationHandler::quAdd(program_queue, i, error_handler);
        }

        // ADDK
        if (current_line.find("ADDK") != string::npos) {
            OperationHandler::quAddK(program_queue, i, error_handler);
        }

        // DIV
        if(current_line.find("DIV") != string::npos){
            OperationHandler::quSub(program_queue, i, error_handler);
        }

        // DIVK
        if(current_line.find("DIVK") != string::npos){
            OperationHandler::quSubK(program_queue, i, error_handler);
        }

        // EMPTY 
        if (current_line.find("EMPTY") != string::npos) {
            (void) program_queue.empty(); // Ignoring the return value intentionally
        }

        // GOTO 
        size_t goto_pos = current_line.find("GOTO");
        if (goto_pos != std::string::npos && (goto_pos == 0 || current_line[goto_pos - 1] == ' ')) {
            // Extract the argument of the GOTO instruction
            std::string arg = current_line.substr(goto_pos + 5); // +5 to skip "GOTO "

            // Check if the argument is a line number or a saved position
            int line_number;
            if (isInteger(arg)) {
                // Argument is a line number
                line_number = std::stoi(arg);
            } else {
                // Argument is a saved position
                if (saved_positions.find(arg) != saved_positions.end()) {
                    // Jump to the saved position
                    i = saved_positions[arg];
                    continue; // Skip the rest of the loop to avoid processing the new line again
                } else {
                    // Error: Invalid saved position
                    error_handler.invalidGoto(i);
                }
            }

            // Check if the line number is valid
            if (line_number >= 0 && line_number < program_text.size()) {
                // Jump to the specified line
                i = line_number;
                continue; // Skip the rest of the loop to avoid processing the new line again
            } else {
                // Error: Invalid line number
                error_handler.invalidGoto(i);
            }
        }   

        // IFEQ
        size_t ifeq_pos = current_line.find("IFEQ");
        if (ifeq_pos != std::string::npos && (ifeq_pos == 0 || current_line[ifeq_pos - 1] == ' ')) {
            // Extract the argument of the IFEQ instruction
            std::string arg = current_line.substr(ifeq_pos + 5); // +5 to skip "IFEQ "

            // Parse the argument to extract the line number or saved position
            int jump_line;
            if (isInteger(arg)) {
                jump_line = std::stoi(arg);
            } else {
                if (saved_positions.find(arg) != saved_positions.end()) {
                    jump_line = saved_positions[arg];
                } else {
                    error_handler.unknownInstruction(i);
                    continue;
                }
            }

            // Check if the condition is met using compareFirstTwo function
            if (compareFirstTwo(program_queue, "==", i)) {
                // Jump to the specified line
                i = jump_line;
                continue;
            }
        }

        // IFGT
        size_t ifgt_pos = current_line.find("IFGT");
        if (ifgt_pos != std::string::npos && (ifgt_pos == 0 || current_line[ifgt_pos - 1] == ' ')) {
            std::string arg = current_line.substr(ifgt_pos + 5); // +5 to skip "IFGT "

            // Parse the argument to extract the line number or saved position
            int jump_line;
            if (isInteger(arg)) {
                jump_line = std::stoi(arg);
            } else {
                if (saved_positions.find(arg) != saved_positions.end()) {
                    jump_line = saved_positions[arg];
                } else {
                    error_handler.unknownInstruction(i);
                    continue;
                }
            }

            // Check if the condition is met using compareFirstTwo function
            if (compareFirstTwo(program_queue, ">", i)) {
                // Jump to the specified line
                i = jump_line;
                continue;
            }
        }

        // IFLT
        size_t iflt_pos = current_line.find("IFLT");
        if (iflt_pos != std::string::npos && (iflt_pos == 0 || current_line[iflt_pos - 1] == ' ')) {
            std::string arg = current_line.substr(iflt_pos + 5); // +5 to skip "IFLT "

            // Parse the argument to extract the line number or saved position
            int jump_line;
            if (isInteger(arg)) {
                jump_line = std::stoi(arg);
            } else {
                if (saved_positions.find(arg) != saved_positions.end()) {
                    jump_line = saved_positions[arg];
                } else {
                    error_handler.unknownInstruction(i);
                    continue;
                }
            }

            // Check if the condition is met using compareFirstTwo function
            if (compareFirstTwo(program_queue, "<", i)) {
                // Jump to the specified line
                i = jump_line;
                continue;
            }
        }

        // IFNQ
        size_t ifnq_pos = current_line.find("IFNQ");
        if (ifnq_pos != std::string::npos && (ifnq_pos == 0 || current_line[ifnq_pos - 1] == ' ')) {
            std::string arg = current_line.substr(ifnq_pos + 5); // +5 to skip "IFNQ "

            // Parse the argument to extract the line number or saved position
            int jump_line;
            if (isInteger(arg)) {
                jump_line = std::stoi(arg);
            } else {
                if (saved_positions.find(arg) != saved_positions.end()) {
                    jump_line = saved_positions[arg];
                } else {
                    error_handler.unknownInstruction(i);
                    continue;
                }
            }

            // Check if the condition is met using compareFirstTwo function
            if (compareFirstTwo(program_queue, "!=", i)) {
                // Jump to the specified line
                i = jump_line;
                continue;
            }
        }

        // MOD
        if(current_line.find("MOD") != string::npos){
            OperationHandler::quMod(program_queue, i, error_handler);
        }

        // MODK
        if(current_line.find("MODK") != string::npos){
            OperationHandler::quModK(program_queue, i, error_handler);
        }

        // MUL
        if(current_line.find("MUL") != string::npos){
            OperationHandler::quMul(program_queue, i, error_handler);
        }

        // MULK
        if(current_line.find("MULK") != string::npos){
            OperationHandler::quMulK(program_queue, i, error_handler);
        }

        // PEEK & PEEKLN
        if(current_line.find("PEEK") != string::npos){
            node current_node = program_queue.front();

            if(current_line.find("LN") != string::npos) {
                if(current_line.find("PEEKLN") != string::npos) current_node.p_println(); // PEEKLN
                else error_handler.unknownInstruction(i);
            }
            else current_node.p_print(); // PEEK
        }

        // POKE
        if (current_line.find("POKE") != string::npos) {
            // Convert the queue to a temporary vector
            vector<node> temp_vector;
            while (!program_queue.empty()) {
                temp_vector.push_back(program_queue.front());
                program_queue.pop();
            }

            // Shuffle the elements of the temporary vector
            std::srand(std::time(0)); // Seed the random number generator
            for (size_t i = temp_vector.size() - 1; i > 0; --i) {
                size_t j = std::rand() % (i + 1); // Generate a random index between 0 and i
                std::swap(temp_vector[i], temp_vector[j]); // Swap elements at indices i and j
            }

            // Push the shuffled elements back into the queue
            for (const auto& elem : temp_vector) {
                program_queue.push(elem);
            }
        }

        // POP, POPLN, POPALL & POPALLLN
        if (current_line.find("POP") != string::npos) {
            bool pop_all = current_line.find("ALL") != string::npos; // Check if "ALL" is present
            bool print_newline = current_line.find("LN") != string::npos; // Check if "LN" is present
    
            if (pop_all) {
                while (!program_queue.empty()) {
                    node current_node = program_queue.front();
                    program_queue.pop();
                    if (print_newline) current_node.p_println(); // Print each popped element on a new line
                    else current_node.p_print(); // Print each popped element
                }
            } else {
                node current_node = program_queue.front();
                if (print_newline) current_node.p_println(); // POPLN
                else current_node.p_print(); // POP
                program_queue.pop(); // This has to be done separately because ".pop()" doesn't return anything... why? Because who could ever want to see what the first element in a FIFO data structure was.
            }
        }

        // PRINT
        size_t print_pos = current_line.find("PRINT");
        if (print_pos != std::string::npos && (print_pos == 0 || current_line[print_pos - 1] == ' ')) {
            // Extract the argument of the PRINT instruction
            std::string arg = current_line.substr(print_pos + 6); // +6 to skip "PRINT "

            // Remove leading and trailing double quotes if they exist
            if (!arg.empty() && arg.front() == '"' && arg.back() == '"') {
                arg = arg.substr(1, arg.length() - 2);
            }

            // Print the argument
            std::cout << arg << std::endl;
        }

        // PUSH
        if (current_line.find("PUSH") != string::npos) {
            size_t quote_pos1 = current_line.find('\"'); // The first occurrence of '\"'
            size_t quote_pos2 = current_line.rfind('\"'); // The last occurrence of '\"'

            if (quote_pos1 != std::string::npos && quote_pos2 != std::string::npos) {
                // If quotes are found, it's a string
                if (quote_pos1 != quote_pos2) {
                    string push_string = current_line.substr(quote_pos1 + 1, quote_pos2 - quote_pos1 - 1); // Extract substring between quotes

                    // Replace escape sequences with their corresponding characters
                    for (size_t pos = push_string.find('\\'); pos != std::string::npos; pos = push_string.find('\\', pos + 1)) {
                        if (push_string[pos + 1] == 'n') { // Check for newline escape sequence
                            push_string.replace(pos, 2, "\n"); // Replace "\n" with newline character
                        }
                    }

                    node new_node = node(push_string);
                    program_queue.push(new_node);
                } else {
                    error_handler.invalidPush(i);
                }
            } else {
                // If quotes are not found, treat it as an integer
                string second_half = current_line.substr(current_line.find("PUSH") + 5); // +5 to skip "PUSH "
                if (isInteger(second_half)) {
                    int push_int = stoi(second_half);
                    cout << "Pushing integer: " << push_int << endl; // Debugging output
                    node new_node = node(push_int);
                    program_queue.push(new_node);
                } else {
                    error_handler.invalidPush(i);
                }
            }
        }

        // QDISPLAY
        if (current_line.find("QDISPLAY") != string::npos) {queue<node> temp_queue = program_queue; // Create a copy of the original queue
            while (!temp_queue.empty()) {
                node current_node = temp_queue.front();
                temp_queue.pop();
                current_node.p_print(); // Print each popped element
                if (!temp_queue.empty()) cout << ", "; // Print comma to separate elements if there are more elements in the queue
            }
            cout << endl;
        }

        // READ
        size_t read_pos = current_line.find("READ");
        if (read_pos != std::string::npos && (read_pos == 0 || current_line[read_pos - 1] == ' ')) {
            // Extract the argument of the READ instruction
            std::string arg = current_line.substr(read_pos + 5); // +5 to skip "READ "

            // Remove leading and trailing double quotes if they exist
            if (!arg.empty() && arg.front() == '"' && arg.back() == '"') {
                arg = arg.substr(1, arg.length() - 2);
            }

            // Print the argument
            std::cout << arg;

            // Read a line from the user
            std::string line;
            std::getline(std::cin, line);

            // Attempt to convert the line into an integer
            bool is_integer = true;
            try {
                int value = std::stoi(line);
                // If successful, push the integer to the queue
                program_queue.push(node(value));
            } catch (std::invalid_argument&) {
                // If conversion fails, push the line as a string to the queue
                is_integer = false;
                program_queue.push(node(line));
            }
        }

        // RET
        if (current_line.find("RET") != std::string::npos) {
            // Check if the queue is empty
            if (program_queue.empty()) {
                error_handler.returnFromEmptyQueue(i);
                return -1; // End the program with an error code
            } else {
                // Get the front of the queue
                node front_node = program_queue.front();
                program_queue.pop();
                // Return the value of the front of the queue
                if (front_node.containsInt()) {
                    return front_node.getInt();
                } else {
                    error_handler.nonIntegerReturnValue(i);
                }
            }
        }

        // SUB
        if(current_line.find("SUB") != string::npos){
            OperationHandler::quSub(program_queue, i, error_handler);
        }

        // SUBK
        if(current_line.find("SUBK") != string::npos){
            OperationHandler::quSubK(program_queue, i, error_handler);
        }

        // SORTUP
        if (current_line.find("SORTUP") != string::npos) {
            // Copy elements of the queue to a temporary vector
            vector<node> temp_vector;
            while (!program_queue.empty()) {
                temp_vector.push_back(program_queue.front());
                program_queue.pop();
            }

            // Sort the temporary vector
            sort(temp_vector.begin(), temp_vector.end(), [](const node &a, const node &b) {
                if (a.containsInt() && b.containsInt()) {
                    return a.getInt() < b.getInt(); // Sort integers in ascending order
                } else if (!a.containsInt() && !b.containsInt()) {
                    return a.getString() < b.getString(); // Sort strings in ascending order
                } else {
                    // If types are different, prioritize integers over strings
                    return a.containsInt();
                }
            });

            // Push sorted elements back to the queue
            for (const auto &elem : temp_vector) {
                program_queue.push(elem);
            }
        }

        // SORTDOWN
        if (current_line.find("SORTDOWN") != string::npos) {
            // Copy elements of the queue to a temporary vector
            vector<node> temp_vector;
            while (!program_queue.empty()) {
                temp_vector.push_back(program_queue.front());
                program_queue.pop();
            }

            // Sort the temporary vector
            sort(temp_vector.begin(), temp_vector.end(), [](const node &a, const node &b) {
                if (a.containsInt() && b.containsInt()) {
                    return a.getInt() > b.getInt(); // Sort integers in descending order
                } else if (!a.containsInt() && !b.containsInt()) {
                    return a.getString() > b.getString(); // Sort strings in descending order
                } else {
                    // If types are different, prioritize integers over strings
                    return a.containsInt();
                }
            });

            // Push sorted elements back to the queue
            for (const auto &elem : temp_vector) {
                program_queue.push(elem);
            }
        }

    }


    return 0;
}

/**
 * Checks if a given string is an integer
 * 
 * @param str The given string
 * @return true if the string is an integer, false otherwise
 */
bool isInteger(string str){
    try{
        stoi(str);
        return true;
    } catch (...) {
        return false;
    }
}

/**
 * Compares the first two elements of a queue
 * 
 * @param program_queue The queue of the program itself
 * @param comparisonType The type of comparison to check for
 * @param line The line the comparsion happens at, for error handling.
 * @return the result of the comparison
 */
bool compareFirstTwo(const std::queue<node>& program_queue, string comparisonType, int line) {
    // Make a copy of the queue
    std::queue<node> temp_queue = program_queue;

    // Check if there are at least two elements in the queue
    if (temp_queue.size() < 2) {
        error_handler.notEnoughArguments(line);
    }

    // Access the first element
    node first_element = temp_queue.front();

    // Dequeue the first element
    temp_queue.pop();

    // Access the second element
    node second_element = temp_queue.front();

    // Check the comparison type and compare
    if(comparisonType == ">"){
        if(first_element.getInt() > second_element.getInt()) return true;
        else return false;
    } else if(comparisonType == "<"){
        if(first_element.getInt() < second_element.getInt()) return true;
        else return false;
    } else if(comparisonType == "=="){
        if(first_element.getInt() == second_element.getInt()) return true;
        else return false;
    } else if(comparisonType == "!="){
        if(first_element.getInt() != second_element.getInt()) return true;
        else return false;
    } else {
        error_handler.unspecifiedComparisonOperation(line);
    }

    return false; // Something went wrong with the comparison
}