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

class StringValidator {  // main interface for all handlers
public:
    virtual ~StringValidator() {};
    virtual StringValidator *setNext(StringValidator *nextValidator) = 0;  // input pointer to next validator, return string validitor
    virtual std::string validate(std::string) = 0;  // return string error or success
}


class BaseValidator: public StringValidator {  // all validators has in common
protected:
    StringValidator *next = nullptr;  // point to the next validator in the chain

public:
    virtual ~BaseValidator() { delete next; };  // virtual distructor

    StringValidator *setNext(StringValidator *nextValidator) override {
        next = nextValidator;
        return nextValidator;
    }

    virtual std::string validate(std::string testString) override {
        if (this->next) {  // check if there is a next validator in the chain
            return this->next->validate(testString);
        }
        return "Success";  // this is the last in chain
    }
}


class NotEmptyValidator: public BaseValidator {
public:
    NotEmptyValidator() {};

    std::string validate(std::string testString) {
        puts("Checking if empty...")

        if (testString.empty()) {
            return "Please enter a value";
        }

        return BaseValidator::validate(testString):
    }
}


int main(int argc, const char * argv[]) {
    std::count << "Hello, World!\n";
    return 0;
}