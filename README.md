# FATUM
FATUM - это основанная на OpenGL графическая 2D библиотека. Написанна на языке с++ с совместимостью CMAKE. 

**Используется с++ 20-го стандарта.**
# Подключение (CMAKE) (DEV)
Добавьте это в ваш CMakeList.txt вашего проекта
```CMAKE
add_subdirectory(path_to_fatum_folder) #Путь к всей папке. Не к include
target_link_libraries(${PROJECT_NAME} fatum) 
```

# Использование (DEV)
Ниже - пример простейшего окна с обьектом используя FATUM. В примере написанно то - что обязательно должно быть для функционирования кода. 


### sample_scene.h
```cpp
#include <fatum/scene.h>
#include <fatum/drawable/rectangle.h>

class Menu : public fatum::IScene {
	fatum::gl::ShaderProgram default_program{ 
		"path_for_your_zrc_vertex_shader",
		"path_for_your_zrc_fragment_shader"
	};

	fatum::object::Rectangle big_one{ default_program,
		-.5f,.5f,1.f,1.f
	};
public:

	void onFirst() override {
		addObject<fatum::object::Rectangle>(&big_one , 4);
		big_one.setColor({ 0,0,255 });
	}
  using IScene::IScene;	
};
```

### main.cpp
```cpp
#include "sample_scene.h"
#include <fatum/manager.h>


int main()
{ 
    fatum::Window a{ "aboba! v.0.0.1" };
    fatum::SceneManager manager{ a };
    fatum::ResourceLoader& loader = fatum::ResourceLoader::getInstance();
    loader.initialize(your_path_to_zrc_file); 
    
    manager.registerScene<Menu>("Menu");
    
    manager.build();

    while (!a.isShouldClose()) manager();
};
```

### Термины
ZRC - Zerochar's Resource Compiler (может быть найден в external/zrc, работает с аргументами и просто его запуском).
ZRC-файл - скомпилированный файл ZRC. (тип файла .zrc)
ZRP-файл - инфо о путях для автоматической генерации ZRC-файла (тип файла .zrp)

### Маленькие примечания к использованию
Убедитесь - что в ZRP-файле, если используете авто-компиляцию zrc-файла, всё верно в путях.
Убедитесь - что в cmake, если используете авто-компиляцию zrc-файла, всё верно в путях.

Проверьте есть ли у вас готовый zrc-файл в той же папке перед запуском .exe.

# Contributors
- Zerochar

# Dependency
- [GLFW](https://github.com/glfw/glfw)
- [GLAD](https://glad.dav1d.de/)
- [OpenGL](https://www.opengl.org/)
