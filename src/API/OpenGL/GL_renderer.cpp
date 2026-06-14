#include "GL_renderer.hpp"
#include "Types/GL_Shader.hpp"
#include "Types/GL_SSBO.hpp"

#include <iostream>
#include <unordered_map>

namespace OpenGLRenderer {
    std::unordered_map<std::string, OpenGLShader> g_shaders;
    std::unordered_map<std::string, OpenGLSSBO> g_shader_storage_buffer_objects;
    
    void Init() 
    {
        LoadShaders();
        std::cout << "Shaders Loaded!\n";
    }

    void LoadShader(const Filename& name,             
                    const ShaderPaths& shader_paths,  
                    const DefineDirectives& defines = {})
    {
        const auto [it, inserted] = g_shaders.try_emplace(name, shader_paths, "", defines);
        if (!inserted) { std::cerr << "Renderer::LoadShader() failed: '" << name << "' already exists\n!"; }
    }

    void LoadShader(const SubDirectory& sub_directory, 
                    const Filename& name, 
                    const ShaderPaths& shader_paths, 
                    const DefineDirectives& defines = {})
    {
        const auto [it, inserted] = g_shaders.try_emplace(name, shader_paths, sub_directory, defines);
        if (!inserted) { std::cerr << "Renderer::LoadShader() failed: '" << name << "' already exists\n!"; }
    }

    void LoadShaders()
    {
        LoadShader(Filename{ "Test" }, ShaderPaths{ "fragment_shader_460.frag", "vertex_shader_460.vert" });
    }

    void Render()
    {
    }

}
