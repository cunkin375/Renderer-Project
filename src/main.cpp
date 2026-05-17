#include "Backend/Backend.hpp"
#include "App/Enums.hpp"
#include "Renderer/Renderer.hpp"
#include <iostream>

int main() 
{
    if (!Backend::Init(API::OPENGL, WindowMode::WINDOWED)) {
        std::cout << "Backend failed to initialize!\n";
        std::exit(-1);
    }

    std::cout << "Hello, world!\n";

    // TODO: make window :D
    while (Backend::WindowIsOpen()) {
        Backend::BeginFrame();
        Renderer::Render();
        Backend::EndFrame();
    }
}
