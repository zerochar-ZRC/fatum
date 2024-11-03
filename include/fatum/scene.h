#pragma once
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <chrono>
#include <thread>
#include <algorithm>
#include <ranges>
#include "drawable/object.h"
#include "manager.h"

namespace fatum {


	class SceneManager;
	class IScene;

	
	namespace{
		
		struct scene_info {
			using sc_constructor = std::function<std::unique_ptr<IScene>
				(std::string_view, size_t, SceneManager&)
			>;

			std::string name;
			sc_constructor init;
			size_t index;
			scene_info(std::string_view name,size_t index,sc_constructor func) : 
				name(name),index(index),init(func){}
		};
	}

	class SceneManager {
		
		std::vector<std::unique_ptr<IScene>> _renders;
		std::vector<scene_info> _sc_database;
		//input::Hook::Handler _handler{};
		Window& _target_window;

		unsigned int _render_time = 0;

		unsigned int _render_scene = UINT32_MAX;
	public:

		void operator()();

		void build() {

			std::ranges::sort(_sc_database, [](size_t pt, size_t nt)->bool {return pt < nt; }, &scene_info::index);

			for (scene_info& sc_info : _sc_database) {
				if (std::find_if(_renders.begin(), _renders.end(),
					[&sc_info](auto& uniq) -> bool {return uniq->getName() == sc_info.name; }) != _renders.end()) continue;
				_renders.push_back(sc_info.init(sc_info.name, _renders.size(), *this));
			}
			if (_render_scene==UINT32_MAX){
				_render_scene = 0;
				switchScene(0);
			}
			_sc_database.clear();
		}
		
		void switchScene(uint8_t id); 

		template <std::derived_from<IScene> Tregistred>
		void registerScene(std::string_view name, size_t prefered_index = 0Ui64) {
			_sc_database.emplace_back(name, prefered_index,
				[](std::string_view n, size_t i, SceneManager& s) -> std::unique_ptr<IScene> {
					return std::make_unique<Tregistred>(n, i, s);
				}
			);
		}

		SceneManager(Window& w) : _target_window(w){}
	};

	class IScene {
		std::string name;
		size_t id;

		struct priorited_object {
			object::IDrawable* object;
			unsigned int priority;
			operator object::IDrawable*() { return object; }
		};
		std::vector<priorited_object> listned{};
		SceneManager& parent;
		bool fisrt_frame = true;

		friend class SceneManager;
		std::chrono::high_resolution_clock::time_point thisTime = std::chrono::high_resolution_clock::now();
		std::chrono::high_resolution_clock::time_point lastTime = thisTime;
		

	protected:
			
		const std::vector<priorited_object>& getObjects(){
			return listned;
		}

		template <std::derived_from<object::IDrawable> TDrawable>
		void addObject(TDrawable* object_add,unsigned priority=42) {
			listned.emplace_back(object_add,priority);
			std::ranges::sort(listned, [](const priorited_object&  left, const priorited_object&  right)->bool { return left.priority < right.priority; });
		}


		virtual void onFirst() {}
		virtual void onEnter() {}

		virtual void onPreDraw() {}
		virtual void onPostDraw() {}
		
		virtual bool onTryLeave(size_t from,size_t to) { return true; }
		virtual void onLeave() {}
		
		virtual void onDispose() {}

		void switchScene(unsigned int id) { parent.switchScene(id); }

	public:
		std::chrono::nanoseconds delta_time{};

		constexpr std::string_view getName() const { return name; }
		constexpr size_t getID() const { return id; }
		IScene(std::string_view _name, size_t _id, SceneManager& _parent) : id(_id), name(_name), parent(_parent) {}

		IScene(const IScene&) = delete;
		IScene& operator=(const IScene&) = delete;
		IScene(IScene&&) = default;
		IScene& operator=(IScene&&) = default;

		virtual ~IScene() = default;
	};

}