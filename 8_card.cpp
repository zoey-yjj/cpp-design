#include <iostream>

/*
 * Template Method pattern
 *
 * 1. Multistep process where the implementation of individual steps can vary
 * 2. Break into series of steps, represent each step as a method, different 
 *    process implement its own step with particular variations.
 * 
 * Abstract Class
 * ---------------------
 * + methods()
 * 
 * Client
 * ---------------------
 * - currentStrategy
 * ---------------------
 * + setStrategy(...)
 */

class GreetingCardTemplate {
protected:
    virtual std::string intro(const std::string & to) {
        return "Dear " + to + ",\n";
    }
    virtual std::string occasion() {
        return "Just writing to say hi! Hope all is well with you.\n";
    }
    virtual std::string closing(const std::string & from) {
        return "Sincerely,\n" + from + "\n";
    }
public:
    std::string generate(const std::string & to, const std::string & from) {
        return intro(to) + occasion() + closing(from);
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
