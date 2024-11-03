#pragma once
#include <glad/glad.h>
#include <memory>
#include <array>
#include <iostream>
#include "../resources.h"

namespace fatum::object{
	struct IDrawable{

		virtual void onFirst() {}
		virtual void onEnter() {}
		virtual void onUpdate() {}
		virtual void onLeave() {}


		IDrawable() = default;
	protected:
		std::unordered_map<int, GLuint> uniform;
	};
}