#pragma once 

#include "debug.h"
#include "scene.h"

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
        static bool _first_time;
        wrapped_window_t _win;
        SceneManager _render;
	public:
        operator GLFWwindow*();
        
        SceneManager& getSceneManager() {
            return _render;
        }
        
        /*
        void frame() {
            _render();
        }

        void setSceneManager(SceneManager& other) {

        }*/ // Слишком опасно давать доступ к изменению менеджера. Нужно будет когда нибудь сделать с проверками (привязать к .frame?) \zerochar

        Window(std::string_view name);

        bool isShouldClose();
    };
}




