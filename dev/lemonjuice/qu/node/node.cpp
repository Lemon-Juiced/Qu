#include "node.h"

#include <iostream>

using namespace std;

node::node() : node (0, "", true) {}

node::node(int intValue) : node (intValue, "", true) {}

node::node(string stringValue) : node (0, stringValue, false) {}

node::node(int intValue, std::string stringValue, bool isInteger) : intVal(intValue), stringVal(stringValue), isInt(isInteger) {}

bool node::containsInt() const {
    return isInt;
}

bool node::containsString() const {
    return !isInt;
}

int node::getInt() const {
    return intVal;
}

std::string node::getIntAsString() const {
    return std::to_string(intVal);
}

std::string node::getString() const {
    return stringVal;
}

void node::setInt(int intValue) {
    intVal = intValue;
}

void node::setString(std::string stringValue) {
    stringVal = stringValue;
}

void node::peek_print() const {
    if (containsInt()) {
        std::cout << getInt();
    } else {
        std::cout << getString();
    }
}

void node::peek_println() const {
    peek_print();
    std::cout << std::endl;
}

void node::pop_print() const {
    if (containsInt()) {
        std::cout << getInt();
    } else {
        std::cout << getString();
    }
}

void node::pop_println() const {
    pop_print();
    std::cout << std::endl;
}