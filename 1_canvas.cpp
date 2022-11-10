#include <iostream>
#include <vector>

/*
 * Command pattern
 *
 * 1. Reduce coupling between classes that call one another
 * 2. Make functionality more reusable between similar classes.
 * 3. Represent events or changes that can occur in program
 *    as their own classes, which implement a common 
 *    command interface.
 * 
 */

class Canvas {
    std::vector<std::string> shapes;
public:
    void addShape(const std::string &newShape) {
        shapes.push_back(newShape);
    };
    void clearAll() {
        shapes.clear();
    };
    std::vector<std::string> getShapes() { return shapes; };
};

class Command {
public:
    virtual ~Command() {};
    virtual void execute() = 0;
};

class Button {
    Command *command;
public:
    Button(Command *command) : command(command) {};
    void click() {
        command->execute();
    }
};

class AddShapeCommand: public Command {
    std::string shapeName;
    Canvas *canvas;
public:
    AddShapeCommand(const std::string &shapeName, Canvas *canvas):
        shapeName(shapeName), canvas(canvas) {};
    void execute() {
        canvas->addShape(shapeName);
    }
};

class ClearCommand: public Command {
    Canvas *canvas;
public:
    ClearCommand(Canvas *canvas) : canvas(canvas) {};
    void execute() {
        canvas->clearAll();
    }
};

std::string vectorToString(std::vector<std::string> v) {
    std::string result = "";
    for(int i=0; i < v.size(); i++) {
        result.append(v.at(i) + ", ");
    }
    return result;
}

int main(int argc, const char * argv[]) {
    Canvas *canvas = new Canvas;
    
    Button *addTriangleButton = new Button(new AddShapeCommand("triangle", canvas));
    Button *addSquareButton = new Button(new AddShapeCommand("square", canvas));
    Button *clearButton = new Button(new ClearCommand(canvas));
    
    addTriangleButton->click();
    std::cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";
    addSquareButton->click();
    addSquareButton->click();
    addTriangleButton->click();
    std::cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";
    clearButton->click();
    std::cout << "Current canvas state: " << vectorToString(canvas->getShapes()) << "\n";
    
    delete canvas;
    return 0;
}
