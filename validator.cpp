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
};

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
};

class NotEmptyValidator: public BaseValidator {
public:
    NotEmptyValidator() {};

    std::string validate(std::string testString) {
        puts("Checking if empty...");
        if (testString.empty()) {
            return "Please enter a value";
        }
        return BaseValidator::validate(testString);
    }
};

class LengthValidator: public BaseValidator {
    int minLength;

public:
    LengthValidator(int minLength) : minLength(minLength) {};

    std::string validate(std::string testString) override {
        std::cout << "Checking if length equals" << minLength << "...\n";
        
        if (testString.length() < minLength) {
            return "Please enter a value longer than " + std::to_string(minLength);
        }
        
        return BaseValidator::validate(testString);
    }
};

class RegexValidator: public BaseValidator {
    std::string patternName;
    std::string regexString;

public:
    RegexValidator(std::string patternName, std::string regexString): 
        patternName(patternName), regexString(regexString) {};
    
    std::string validate(std::string testString) override {
        std::cout << "Checking if string is a valid " << patternName << "...\n";

        if (!std::regex_match(testString, std::regex(regexString))) {
            return "The valud entered is not a valid " + patternName;
        }

        return BaseValidator::validate(testString);
    }
};

bool in_vector(const std::string &value, const std::vector<std::string> &v) {
    return std::find(v.begin(), v.end(), value) != v.end();
}

class HistoryValidator: public BaseValidator {
    std::vector<std::string> historyItems;

public:
    HistoryValidator(std::vector<std::string> historyItems): historyItems(historyItems) {};

    std::string validate(std::string testString) override {
        std::cout << "Checking if string is in history...\n";

        if (in_vector(testString, historyItems)) {
            return "Please enter a value that you have not used before";
        }

        return BaseValidator::validate(testString);
    }
};

int main(int argc, const char * argv[]) {
    std::vector<std::string> oldPasswords = { "abc123", "123456", "hello" };

    BaseValidator *emailValidator = new BaseValidator;
    
    emailValidator
        ->setNext(new NotEmptyValidator)
        ->setNext(new RegexValidator("email address", "^\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$"));
    
        std::cout << "Checking Emails ---------------\n";
        std::cout << "Input: \n" << emailValidator->validate("") << "\n\n";
        std::cout << "Input: shaun\n" << emailValidator->validate("shaun") << "\n\n";
        std::cout << "Input: shaun@test.com\n" << emailValidator->validate("shaun@test.com") << "\n\n";
    
    delete emailValidator;

    BaseValidator *passwdValidator = new BaseValidator;
    
    passwdValidator
        ->setNext(new NotEmptyValidator)
        ->setNext(new HistoryValidator(oldPasswords));
    
        std::cout << "Checking Password ---------------\n";
        std::cout << "Input: \n" << passwdValidator->validate("") << "\n\n";
        std::cout << "Input: abc123\n" << passwdValidator->validate("abc123") << "\n\n";
        std::cout << "Input: Abc123\n" << passwdValidator->validate("Abc123") << "\n\n";
    
    delete passwdValidator;
    
    return 0;
}