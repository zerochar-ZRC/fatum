#include "../include/fatum/gl_tweaks.h"
#include <cmath>
using namespace fatum::gl;

RGBAColor::operator HSVColor() {
    HSVColor    out;
    float      min, max, delta;

    min = r < g ? r : g;
    min = min < b ? min : b;

    max = r > g ? r : g;
    max = max > b ? max : b;

    out.v = max;                          
    delta = max - min;
    if (delta < 0.00001) return HSVColor{0,0,max};
    if (max > 0.0) out.s = (delta / max);                 
    else return HSVColor{ 0,0,max };
    
    if (r >= max) out.h = (g - b) / delta;  
    else if (g >= max) out.h = 2.f + (b - r) / delta; 
    else out.h = 4.f + (r - g) / delta; 

    out.h *= 60.0;   

    return out;
}
HSVColor::operator RGBAColor() {
    float      hh, p, q, t, ff;
    long        i;
    RGBAColor    out;

    if (s <= 0.0) {       // < is bogus, just shuts up warnings
        out.r = v;
        out.g = v;
        out.b = v;
        return out;
    }
    hh = h;
    if (hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = v * (1.f - s);
    q = v * (1.f - (s * ff));
    t = v * (1.f - (s * (1.f - ff)));

    switch (i) {
    case 0:
        out.r = v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = v;
        break;
    case 5:
    default:
        out.r = v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;
}