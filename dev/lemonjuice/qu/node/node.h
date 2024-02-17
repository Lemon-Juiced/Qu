#pragma once 
#include <string>

class node{
private:
    int intVal;
    std::string stringVal;
    bool isInt;
public:
    node();
    node(int);
    node(std::string);
    node(int, std::string, bool);

    bool containsInt() const;        
    bool containsString() const;     
    int getInt() const;              
    std::string getIntAsString() const;  
    std::string getString() const;   
    void setInt(int);
    void setString(std::string);
    void peek_print() const;         
    void peek_println() const;       
    void pop_print() const;          
    void pop_println() const;        
};