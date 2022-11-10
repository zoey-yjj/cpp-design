#include <iostream>
#include <algorithm>

/*
 * Observer pattern
 *
 * 1. Only objects care about certain events to be notified 
 *    of the occurrence.
 * 2. Write program in terms of publishers and observers,
 *    publishers simply publish events and observers can
 *    choose whether or not to listen.
 * 
 * Subscriber Interface
 * ---------------------
 * + notify(extraInfo...)
 * 
 * Publisher
 * ---------------------
 * - substribers[]
 * ---------------------
 * + subscribe(Subscriber s)
 * - unsubscribe(Subscriber s)
 */

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
