// Example usage for jcl library by Jon Little.

#include "jcl.h"

// Initialize objects from the lib
Jcl jcl;

void setup() {
    // Call functions on initialized library objects that require hardware
    jcl.begin();
}

void loop() {
    // Use the library's initialized objects and functions
    jcl.process();
}
