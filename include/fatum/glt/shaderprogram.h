#pragma once

#include <glad/glad.h>
#include "shader.h"
#include "../resources.h"


namespace fatum::gl {
    struct ShaderProgram {
        GLuint ptr;

        static void init(GLuint& ptr, const Shader& vertex, const  Shader& fragment) {
            ptr = glCreateProgram();
            glAttachShader(ptr, vertex);
            glAttachShader(ptr, fragment);
            glLinkProgram(ptr);

            GLint success;
            GLchar infoLog[512];
            glGetProgramiv(ptr, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(ptr, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
            }
        }
    public:

        operator GLuint() { return ptr; }

        GLuint getUniform(std::string_view name) {
            return glGetUniformLocation(ptr, name.data());
        }
        ShaderProgram(std::string_view vertex_path, std::string_view fragment_path) {
            init(ptr,
                { ResourceLoader::getInstance().exctract(vertex_path) , Shader::Type::Vertex },
                { ResourceLoader::getInstance().exctract(fragment_path) , Shader::Type::Fragment }
            );
        }
        ShaderProgram(const Shader& vertex, const Shader& fragment) {
            init(ptr, vertex, fragment);
        }
    };
}