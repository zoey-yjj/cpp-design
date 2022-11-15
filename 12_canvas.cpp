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
    const std::vector<std::string> shapes;  // only canvas class has access to this
public:
    CanvasMemento(std::vector<std::string> shapes) : shapes(shapes) {};
};

class Canvas {
    std::vector<std::string> shapes;
    std::vector<CanvasMemento*> oldStates;
public:
    ~Canvas() {
        for (auto p : oldStates) {
            delete p;
        }
        oldStates.clear();
    }
    void addShape(const std::string & newShape) {
        oldStates.push_back(new CanvasMemento(shapes));
        shapes.push_back(newShape);
    };
    void undo() {
        CanvasMemento *previousState = oldStates.back();
        oldStates.pop_back();
        shapes = previousState->shapes;
        delete previousState;
    }
    void clearAll() {
        shapes.clear();
    };
    std::vector<std::string> getShapes() { return shapes; };
};

int main(int argc, const char * argv[]) {
    Canvas *canvas = new Canvas;
    
    canvas->addShape("rhombus");
    canvas->addShape("triangle");
    canvas->addShape("square");
    canvas->addShape("circle");
    
    for (auto shape : canvas->getShapes()) {
        std::cout << shape << ", ";
    };
    
    std::cout << "\n";
    
    canvas->undo();
    
    for (auto shape : canvas->getShapes()) {
        std::cout << shape << ", ";
    };
    
    std::cout << "\n";
    
    canvas->addShape("rhombus");
    canvas->addShape("triangle");
    canvas->addShape("square");
    canvas->addShape("circle");
    canvas->undo();
    
    for (auto shape : canvas->getShapes()) {
        std::cout << shape << ", ";
    };
    
    std::cout << "\n";
 
    delete canvas;

    return 0;
}
