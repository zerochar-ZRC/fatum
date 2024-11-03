#include "../include/fatum/scene.h"

using namespace fatum;

void SceneManager::operator()()
{
	if (_render_scene == UINT32_MAX) return;
	
	std::unique_ptr<IScene>& p_render_scene = _renders[_render_scene];
	p_render_scene->thisTime = std::chrono::high_resolution_clock::now();
	/*for (unsigned int i = 1; i != VK_OEM_CLEAR; i++) {
		if (!(GetKeyState(i) & 0x8000)) continue;
		p_render_scene->_handler(input::Hook::Data{ input::Hook::KeyPressed, i });
	}*/

	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT);

	p_render_scene->onPreDraw();
	//p_render_scene->_handler(input::Hook::Data{ input::Hook::PreUpdate });
	//p_render_scene->parent._handler(input::Hook::Data{ input::Hook::PreUpdate });
	
	for (object::IDrawable* obj : p_render_scene->listned) {
		obj->onUpdate();
	}



	p_render_scene->onPostDraw();
	//p_render_scene->_handler(input::Hook::PostRender);
	//p_render_scene->parent._handler(input::Hook::PostRender);
	
	glfwSwapBuffers(_target_window);
}

void SceneManager::switchScene(uint8_t id)
{
	IScene* p_render_scene = _renders[_render_scene].get();

	if (!p_render_scene->onTryLeave(_render_scene, id)) return;

	p_render_scene->onLeave();

	_render_scene = id;
	p_render_scene = _renders[_render_scene].get();

	if (p_render_scene->fisrt_frame) { p_render_scene->onFirst(); p_render_scene->fisrt_frame = false; }
	p_render_scene->onEnter();

}
