#include <iostream>
#include <vector>

/*
 * Memento pattern
 *
 * 1. Freeze or save objects so that cannot be modified
 *    by any other part of program until unfrozen.
 * 2. Allow certain objects save themselves cannot be modified.
 * 
 * Memento Interface
 * ---------------------
 * + getName()
 * + getTime()
 */

class Canvas;

class CanvasMemento {
    friend class Canvas;
    const std::vector<std::string> shapes;
public:
    CanvasMemento(std::vector<std::string> shapes) : shapes(shapes) {};
};

class Canvas {
    std::vector<std::string> shapes;
public:
    void addShape(const std::string & newShape) {
        shapes.push_back(newShape);
    };
    void clearAll() {
        shapes.clear();
    };
    std::vector<std::string> getShapes() { return shapes; };
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
