#pragma once

struct HookData {
	struct Position { unsigned x; unsigned y; Position(unsigned x, unsigned y) : x(x),y(y){} };
	Position mouse_pos;
	Position d;
};

class Hook {
	std::vector<HookData>
public:

	Hook(){}
};