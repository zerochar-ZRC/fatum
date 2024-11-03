// TODO: Не уверен с названием файла. Стоит изменить в будущем. \zerochar
#pragma once 

#include "debug.h"

#include <memory>
#include <iostream>
#include <string_view>
#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace fatum {

    namespace {
        struct lambda_window_deleter {
            void operator()(GLFWwindow* ptr) {
                glfwDestroyWindow(ptr);
            }
        };
    }
    
	class Window {
        using wrapped_window_t = std::unique_ptr<GLFWwindow, lambda_window_deleter>;
        static bool opengl_init;
        wrapped_window_t _win;
        friend class SceneManager;
	public:
        operator GLFWwindow* () {
            return _win.get();
        }

		Window(std::string_view name) {
            if (!opengl_init){
                opengl_init = true;
                glfwSetErrorCallback(&glfwError);
                if (!glfwInit()) exit(-10);
               
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                 

            }
            
            _win.reset(glfwCreateWindow(640, 480, name.data(), nullptr, nullptr));
            if (!_win)
            {
                glfwTerminate();
                exit(-100);
            }
            glfwSetFramebufferSizeCallback(_win.get(), framebuffer_size_callback);
            glfwMakeContextCurrent(_win.get());
            if (!gladLoadGL()) exit(-100);


            glfwSetCursorPosCallback(_win.get(), mouse_move);
            
                //logger.entryCrash("GladGL");
        }

        bool isShouldClose() { return glfwWindowShouldClose(_win.get()); }
	private:
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        }
        static void glfwError(int id, const char* description)
        {
            std::cout << description << std::endl;
            //fatum::Logger::entryAnon(description, fatum::Logger::FAILED);
        }
        static void mouse_move(GLFWwindow* win, double x, double y) {
            
        }
	};
    inline bool Window::opengl_init = false;
}




