#pragma once
#include <functional>
#include <vector>
#include <memory>
#include <cstdint>
#include <concepts>
#include "drawable/object.h"

namespace fatum {
	class SceneManager;
	
	class IScene {
		std::string name;
		size_t id;

		struct priorited_object {
			object::IDrawable* object;
			unsigned int priority;
			operator object::IDrawable*() { return object; }
		};
		std::vector<priorited_object> listned{};
		SceneManager* parent;
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
		
		virtual bool onTryLeave(size_t from, size_t to) { return true; }
		virtual void onLeave() {}
		
		virtual void onDispose() {}

		void switchScene(unsigned int id);

	public:
		std::chrono::nanoseconds delta_time{};

		constexpr std::string_view getName() const { return name; }
		constexpr size_t getID() const { return id; }
		IScene(std::string_view _name, size_t _id, SceneManager* _parent) : id(_id), name(_name), parent(_parent) {}

		IScene(const IScene&) = delete;
		IScene& operator=(const IScene&) = delete;
		IScene(IScene&&) = default;
		IScene& operator=(IScene&&) = default;

		virtual ~IScene() = default;
	};

}