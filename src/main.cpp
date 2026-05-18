#include "Backend/Backend.hpp"
#include "App/Enums.hpp"
#include "Renderer/Renderer.hpp"
#include <iostream>

int main() 
{

    std::cout << "Pre-Window\n";

    if (!Backend::Init(API::OPENGL, WindowMode::WINDOWED))
    {
        std::cerr << "Backend failed to initialize!\n";
        std::exit(-1);
    }

    // TODO: make window :D
    while (Backend::WindowIsOpen())
    {
        Backend::BeginFrame();
        Renderer::Render();
        Backend::EndFrame();
    }

    std::cout << "Hello, world!\n";

}
