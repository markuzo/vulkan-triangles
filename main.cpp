#include <iostream>
#include <stdexcept>
#include <functional>

#include "HelloTriangleApplication.h"


int main() {
    HelloTriangleApplication app;

    try {
        app.run(); 
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl; 
    }

    return EXIT_SUCCESS;
}
