#include <iostream>
#include <stdexcept>
#include <functional>
#include <chrono>

#include "App.h"


int main() {
    App app;

    auto startTime = std::chrono::high_resolution_clock::now();

    try {
        app.run(); 

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl; 
    }

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    std::cout << "Program finished in " << time << " seconds." << std::endl;

    return EXIT_SUCCESS;
}
