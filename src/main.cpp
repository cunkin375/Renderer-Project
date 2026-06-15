#include <iostream>

#include "Define/Enums.hpp"
#include "Backend/Backend.hpp"
#include "Renderer/Renderer.hpp"

int main() 
{
    std::cout << "Pre-Window\n";

    if (!Backend::Init(API::OPENGL, WindowMode::WINDOWED))
    {
        std::cerr << "Backend failed to initialize!\n";
        std::exit(-1);
    }

    while (Backend::WindowIsOpen())
    {
        Backend::BeginFrame();
        Backend::Update();
        Renderer::Render();
        Backend::EndFrame();
    }

    Backend::Destroy();

    std::cout << "Hello, world!\n";

}
