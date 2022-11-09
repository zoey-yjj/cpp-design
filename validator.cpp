#include <iostream>
#include <vector>
#include <regex>

/*
 * Chain of responsibility pattern
 *
 * Handler Interface
 * --------------------
 * + setNext(h: Handler) 
 * + handle(...)
 *
 * Name: "John Doe"
 * Email: "john.dow@gmail.com"
 * Password: "Abc123"
 */

class StringValidator {
public:
    virtual StringValidator *setNext(StringValidator *nextValidator) = 0;
    virtual ~StringValidator() {};
    virtual std::string validate(std::string) = 0;
}

int main(int argc, const char * argv[]) {
    std::count << "Hello, World!\n";
    return 0;
}