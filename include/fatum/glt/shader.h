#pragma once 

#include <glad/glad.h>
#include <string_view>
#include <string>

namespace fatum::gl {
    class Shader {
        const std::string source;
        GLuint ptr;
    public:
        enum Type;
        const Type type;


        operator GLuint() const { return ptr; }
        std::string_view getSource() const { return source; }



        Shader(std::string_view _source, Type _type) : type(_type), source(_source) {
            ptr = glCreateShader(static_cast<int>(type));
            const char* cstr = source.c_str();
            glShaderSource(ptr, 1, &cstr, NULL);
            glCompileShader(ptr);

            GLint success;
            GLchar infoLog[512];
            glGetShaderiv(ptr, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(ptr, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
        }
        ~Shader() { glDeleteShader(ptr); }

        enum Type {
            Vertex = GL_VERTEX_SHADER,
            Fragment = GL_FRAGMENT_SHADER
        };

    };
}