#include "Backend/Backend.hpp"
#include "App/Enums.hpp"
#include "Renderer/Renderer.hpp"
#include <iostream>

int main() 
{
    if (!Backend::Init(API::OPENGL, WindowMode::WINDOWED))
    {
        std::cerr << "Backend failed to initialize!\n";
        std::exit(-1);
    }

    std::cout << "Pre-Window\n";

    // TODO: make window :D
    while (Backend::WindowIsOpen())
    {
        Backend::BeginFrame();
        Renderer::Render();
        Backend::EndFrame();
    }

    std::cout << "Hello, world!\n";

}
