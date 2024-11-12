#include "../include/fatum/window.h"
using namespace fatum;

bool Window::_first_time = false;


Window::operator GLFWwindow* () {
    return _win.get();
}
bool Window::isShouldClose() { 
    return glfwWindowShouldClose(_win.get()); 
}





#pragma region StaticGLFWcallbacks
static void _frameBCallb(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
static void _glfwErrorCOUT(int err_code, const char* err_msg ) {
    std::cout << 
        std::format("GLFW error was invoked.\n\t[{}]: {}",err_code,err_msg);
}
#pragma endregion


Window::Window(std::string_view name) : _render(this){
    if (!_first_time) {
        _first_time = true;
        glfwSetErrorCallback(&_glfwErrorCOUT);
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
    glfwSetFramebufferSizeCallback(_win.get(), _frameBCallb);
    
    if (!gladLoadGL()) exit(-100);



    //TODO: ������, ���������� �� ������� ���� � �������� ��������� (merge with keyboard) \zerochar
    glfwSetCursorPosCallback(*this,
        [](GLFWwindow* win, double x, double y) {

        }
    );

    //TODO: ���� ������ ������������ �� ���������� ��� ����� ������� ������ (��������� � �������) \zerochar
    //glfwSetKeyCallback(*this, _keyClk);
    //glfwSetMouseButtonCallback(*this, _mouseClk);

    //glfwSetCharCallback � glfwSetCharModsCallback � ��� ��������� ����� �������� Unicode.
    //glfwSetCursorPosCallback � ��� ������������ ����������� �������.
    //glfwSetCursorEnterCallback � ��� ������������ ��������� ������� � ���� � ������ �� ����.
    //glfwSetScrollCallback � ��� ��������� ������� ���������.
    //glfwSetJoystickCallback � ��� ������������ ����������� � ���������� ����������.
}

