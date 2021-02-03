/// Various data structures for simplifying font handling.
#ifndef TYPES_H
#define TYPES_H

/// Represents a point in 2D rectangular-coordinate space.
struct vector2_t
{
    float x, y;

    /// Default constructor that sets components to 0.
    vector2_t() : x(0), y(0) {}

    /// Constructs a 2D vector from components.
    vector2_t(float x, float y) : x(x), y(y) {}

    /// Copy constructor.
    vector2_t(const vector2_t& Copy) : x(Copy.x), y(Copy.y) {}

    /// Assignment operator.
    inline vector2_t& operator=(const vector2_t& Copy)
    {
        x = Copy.x; y = Copy.y; return (*this);
    }
};

/// A rectangle at a certain point in space.
struct rect_t
{
    rect_t(float x, float y, int w, int h) : x(x), y(y), w(w), h(h) {}
    rect_t() : x(0.f), y(0.f), w(0), h(0) {}

    float x, y;
    int   w, h;
};

/**
 * Represents a 32-bit floating point color (RGBA).
 *  Limited to the range [0, 1].
 **/
struct color4f_t
{
    color4f_t() : r(1), g(1), b(1), a(1) {}
    color4f_t(float r, float g, float b, float a) :
        r(r), g(g), b(b), a(a) {}
    float r, g, b, a;
};


struct vertex2_t
{
    vector2_t  position;   ///< Vertex position
    vector2_t  tc;         ///< Vertex texture coordinates
    color4f_t color;      ///< Vertex color
};

#endif // TYPES_HPP
