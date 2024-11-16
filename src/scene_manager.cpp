#include "../include/fatum/scene_manager.h"
using namespace fatum;

void SceneManager::build() {
	std::ranges::sort(_scenes_quened, [](size_t pt, size_t nt)->bool {return pt < nt; }, &scene_info::index);

	for (scene_info& sc_info : _scenes_quened) {
		if (std::find_if(_render_scenes.begin(), _render_scenes.end(),
			[&sc_info](auto& uniq) -> bool {return uniq->getName() == sc_info.name; }) != _render_scenes.end()) continue;
		_render_scenes.push_back(sc_info.init(sc_info.name, _render_scenes.size(), this));
	}
	if (_render_scene == UINT32_MAX) {
		_render_scene = 0;
		switchScene(0);
	}
	_scenes_quened.clear();
}

void SceneManager::frame()
{
	if (!_win_ptr) return;
	if (_render_scene == UINT32_MAX) return;
	_framelock = true;

	std::unique_ptr<IScene>& p_render_scene = _render_scenes[_render_scene];
	p_render_scene->thisTime = std::chrono::high_resolution_clock::now();

	glfwMakeContextCurrent(_win_ptr);
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT);

	p_render_scene->onPreDraw();
	for (object::IDrawable* obj : p_render_scene->listned) {
		obj->onUpdate();
	}
	p_render_scene->onPostDraw();

	glfwSwapBuffers(_win_ptr);
	_framelock = false;
}

void SceneManager::switchScene(uint8_t id)
{
	IScene* p_render_scene = _render_scenes[_render_scene].get();

	if (!p_render_scene->onTryLeave(_render_scene, id)) return;

	p_render_scene->onLeave();

	_render_scene = id;
	p_render_scene = _render_scenes[_render_scene].get();

	if (p_render_scene->fisrt_frame) { p_render_scene->onFirst(); p_render_scene->fisrt_frame = false; }
	p_render_scene->onEnter();

}
