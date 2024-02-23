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

void node::p_print() const {
    if (containsInt()) {
        std::cout << getInt();
    } else {
        std::cout << getString();
    }
}

void node::p_println() const {
    p_print();
    std::cout << std::endl;
}

/**
 * Creates the display of a node in a human-readable form.
 * This creates a psuedo-json form of the node.
 * 
 * @return The human-readable display of a node.
 */
std::string node::createNodeDisplay() const {
    std::string node = "";
    node += "{\n";
    node += "\t\"nodeType\": ";

    if(containsInt()) {
        node += "\"int\",\n";
        node += "\t\"nodeValue\": " + std::to_string(getInt()) + "\n";
    }
    else {
        node += "\"string\",\n";
        node += "\t\"nodeValue\": \"" + getString() + "\"\n";
    }

    node += "}";
    return node;
}

/**
 * Prints the contents of a node to the standard output.
 */
void node::printNode() const {
    cout << createNodeDisplay() << endl;
}