#pragma once
#include <stdint.h>
#include <glad/glad.h>
#include <algorithm>
#include <iostream>

namespace fatum::gl {

    struct HSVColor;

    class ranged_ufloat {
        float value, max;
#define _clamp(v) std::fmod(v, max)
    public:
        operator float() const { return value; }
        float get() const { return value; }


        float operator-(float v) {
            return _clamp(value - v);
        }
        float operator+(float v) {
            return _clamp(value + v);
        }
        float operator*(float v) {
            return _clamp(value * v);
        }
        float operator/(float v) {
            return _clamp(value / v);
        }
        void operator=(float v) {
            value = _clamp(v);
        }

        void operator/=(float v) {
            value = *this / v;
        }
        void operator*=(float v) {
            value = *this * v;
        }

        void operator+=(float v) {
            *this = value + v;
        }
        void operator-=(float v) {
            *this = value - v;
        }


        ranged_ufloat(float init = 0.f, float max = 1.f) : value(init), max(max) {}
    };
    /*class clamped_float {
        float value,min, max;
#define _clamp(v) std::clamp(v,min, max)
    public:
        operator float() const { return value; }
        float get() const { return value; }


        float operator-(float v) {
            return _clamp(value - v);
        }
        float operator+(float v) {
            return _clamp(value + v);
        }
        float operator*(float v) {
            return _clamp(value * v);
        }
        float operator/(float v) {
            return _clamp(value / v);
        }
        void operator=(float v) {
            value = _clamp(v);
        }

        void operator/=(float v) {
            value = *this / v;
        }
        void operator*=(float v) {
            value = *this * v;
        }

        void operator+=(float v) {
            *this = value + v;
        }
        void operator-=(float v) {
            *this = value - v;
        }


        clamped_float(float init = 0.f,float min=0.f ,float max = 1.f) : value(init),min(min), max(max) {}
    };*/

    struct RGBAColor {
        float r;
        float g;
        float b;
        float a;
        operator HSVColor();

        template <typename T, typename = std::enable_if_t<std::is_same_v<T, int>>>
        RGBAColor(T r = 255, T g = 255, T b = 255, T a = 255)
            : r(r / 255.f), g(g / 255.f), b(b / 255.f), a(a / 255.f) {}

        RGBAColor(float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f)
            : r(r), g(g), b(b), a(a) {}

    };

    struct HSVColor {
        ranged_ufloat h;
        float s;
        float v;

        operator RGBAColor();

        HSVColor(float h = 0, float s = 1, float v = 1) :
            h(h, 360.f),
            s(s),
            v(s) {}
    };


    static inline void setClearColor(const RGBAColor color) {
        glClearColor(color.r, color.g, color.b, color.a);
    }
}
