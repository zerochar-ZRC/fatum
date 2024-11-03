#pragma once
namespace fatum::gl {
    struct Vertex {
        float x;
        float y;
        float z = 0;
        Vertex(float x, float y, float z = 0) : x(x),y(y),z(z){}
    };
}