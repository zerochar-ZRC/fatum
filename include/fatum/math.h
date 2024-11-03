#pragma once
#include <type_traits>
namespace fatum {
	template<typename int_type> requires std::is_integral_v<int_type>
	struct Rect {
		Rect(int_type _x = 0, int_type _y = 0, int_type _w = 0, int_type _h = 0) : x(_x), y(_y), w(_w), h(_h) {}
		int_type x = 0;
		int_type y = 0;
		int_type w = 0;
		int_type h = 0;

		void operator+=(Rect other) {
			x += other.x;
			y += other.y;
			w += other.w;
			h += other.h;
		}
		void operator-=(Rect other) {
			x -= other.x;
			y -= other.y;
			w -= other.w;
			h -= other.h;
		}
		Rect&& operator-(Rect other) {
			return Rect{ x - other.x , y - other.y, w - other.w, h - other.h };
		}
		Rect&& operator+(Rect other) {
			return Rect{ x + other.x , y + other.y, w + other.w, h + other.h };
		}

		void operator*=(int multiyply) {
			x *= multiyply;
			y *= multiyply;
			w *= multiyply;
			h *= multiyply;
		}
		Rect&& operator*(int multiyply) {
			return Rect{ x * multiyply , y * multiyply, w * multiyply, h * multiyply };
		}



		bool isInside(Rect other) const {
			return other.x >= x && other.x <= x + w && other.y >= y && other.y <= y + h;
		}

		bool isZero(bool check_pos = true, bool check_size = true) const {
			return (check_pos ? x == 0 && y == 0 : true) && (check_size ? w == 0 && h == 0 : true);
		}
	};
	using uint = unsigned int;
	using uRect = Rect<uint>;
}