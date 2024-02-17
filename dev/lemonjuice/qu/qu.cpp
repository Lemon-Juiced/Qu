#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include "error\errorHandler.h"
#include "node\node.h"

using namespace std;

// Globals
errorHandler error_handler; // error_handler to handle errors.
queue<node> program_queue; // Queue, that represents the queue, that is the memory of the program.
map<string, int> saved_positions; // Map that stores the positions the programmer dictated for GOTOs.

// Prototypes
bool fileArgChecker(int argc);
int run(vector<string> program_text);
bool isInteger(string str);

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
        if(file_extension != "qu") error_handler.fileInvalidExtensionError(file_name); // Error sequence for invalid file extensions.
    }
    else error_handler.fileInvalidExtensionError(file_name); // Error sequence for invalid file extensions.

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
        if (argc < expected_args) error_handler.fileMissingError(argc);
        else error_handler.fileExtraError(argc, expected_args);
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
        if(current_line.find("ADD") != string::npos){
            node old_front = program_queue.front();
            program_queue.pop();

            node new_front = program_queue.front();
            if(new_front.containsInt()){
                if(old_front.containsInt()) new_front.setInt(old_front.getInt() + new_front.getInt()); // int + int == int
                else error_handler.operationMismatchError(i); // int + string != int 
            } else {
                if(old_front.containsString()) new_front.setString(old_front.getString() + new_front.getString()); // string + string == string
                else new_front.setString(old_front.getIntAsString() + new_front.getString()); // string + int == string
            }
        }

        // EMPTY 
        if (current_line.find("EMPTY") != string::npos) {
            (void) program_queue.empty(); // Ignoring the return value intentionally
        }

        // PEEK & PEEKLN
        if(current_line.find("PEEK") != string::npos){
            node current_node = program_queue.front();

            if(current_line.find("LN") != string::npos) {
                if(current_line.find("PEEKLN") != string::npos) current_node.peek_println(); // PEEKLN
                else error_handler.unknownInstruction(i);
            }
            else current_node.peek_print(); // PEEK
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

        // POPALL
        if (current_line.find("POPALL") != string::npos) {
            bool print_newline = current_line.find("LN") != string::npos; // Check if "LN" is present
            while (!program_queue.empty()) {
                node current_node = program_queue.front();
                program_queue.pop();
        
                if (print_newline) {
                    current_node.pop_println(); // Print each popped element on a new line
                } else {
                    current_node.pop_print(); // Print each popped element
                }
            }
        }

        // POP & POPLN
        if(current_line.find("POP") != string::npos){
            node current_node = program_queue.front();
            
            if(current_line.find("LN") != string::npos) {
                if(current_line.find("POPLN") != string::npos) current_node.pop_println(); // POPLN
                else error_handler.unknownInstruction(i);
            } 
            else current_node.pop_print(); // POP

            program_queue.pop(); // This has to be done separately because ".pop()" doesn't return anything... why? Because who could ever want to see what the first element in a FIFO data structure was.
        }

        // PUSH
        if (current_line.find("PUSH") != string::npos) {
            size_t quote_pos1 = current_line.find('\"'); // The first occurrence of '\"'
            size_t quote_pos2 = current_line.rfind('\"'); // The last occurrence of '\"'

            if (quote_pos1 != string::npos && quote_pos2 != string::npos) {
                // If quotes are found, it's a string
                if (quote_pos1 != quote_pos2) {
                    string push_string = current_line.substr(quote_pos1 + 1, quote_pos2 - quote_pos1 - 1); // Extract substring between quotes
                    node new_node = node(push_string);
                    program_queue.push(new_node);
                } else {
                    error_handler.invalidPushError(i);
                }
            } else {
                // If quotes are not found, treat it as an integer
                string second_half = current_line.substr(current_line.find("PUSH") + 5); // +5 to skip "PUSH "
                if (isInteger(second_half)) {
                    int push_int = stoi(second_half);
                    node new_node = node(push_int);
                    program_queue.push(new_node);
                } else {
                    error_handler.invalidPushError(i);
                }
            }
        }

        // SUB
        if(current_line.find("SUB") != string::npos){
            node old_front = program_queue.front();
            program_queue.pop();

            node new_front = program_queue.front();
            if(new_front.containsInt()){
                if(old_front.containsInt()) new_front.setInt(old_front.getInt() - new_front.getInt()); // int - int == int
            } else error_handler.operationMismatchError(i); //Anything else is error.
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