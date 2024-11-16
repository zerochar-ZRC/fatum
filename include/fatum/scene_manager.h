#pragma once
#include <vector>
#include <string>
#include <string_view>
#include <memory>
#include <concepts>
#include <functional>
#include <cstdint>

#include <GLFW\glfw3.h>

#include "scene.h"
namespace fatum {
	namespace {

		struct scene_info {
			using sc_constructor = std::function<std::unique_ptr<IScene>
				(std::string_view, size_t, SceneManager*)
			>;
			std::string name;
			sc_constructor init;
			size_t index;
			scene_info(std::string_view name, size_t index, sc_constructor func) :
				name(name), index(index), init(func) {}
		};
	}
	class SceneManager {
		std::vector<scene_info> _scenes_quened{};
		std::vector<std::unique_ptr<IScene>> _render_scenes{};

		unsigned int _render_time = 0;
		unsigned int _render_scene = UINT32_MAX;
		
		GLFWwindow* _win_ptr = nullptr;
		bool _framelock = false;


		
	public:
		void setRenderTarget(GLFWwindow* win_ptr) {
			if (!_framelock) _win_ptr = win_ptr;
		}

		void frame();

		void switchScene(uint8_t id);



		void build();

		template <std::derived_from<IScene> Tregistred>
		void registerScene(std::string_view name, size_t prefered_index = 0Ui64) {
			_scenes_quened.emplace_back(name, prefered_index,
				[](std::string_view n, size_t i, SceneManager* s) -> std::unique_ptr<IScene> {
					return std::make_unique<Tregistred>(n, i, s);
				}
			);
		}


		SceneManager& operator=(SceneManager&&) = delete;
		SceneManager(SceneManager&&) = delete;

		SceneManager& operator=(const SceneManager&) = default;
		SceneManager(const SceneManager&) = default;

		SceneManager() = default;
	};
}