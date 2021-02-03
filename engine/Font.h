// Font class header.
#ifndef FONT_H
#define FONT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "TextShader.h"

// Some STL Headers
#include <vector>
#include <string>

// FreeType Headers
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

// Using The STL Exception Library Increases The
// Chances That Someone Else Using Our Code Will Correctly
// Catch Any Exceptions That We Throw.
#include <stdexcept>

// MSVC Will Spit Out All Sorts Of Useless Warnings If
// You Create Vectors Of Strings, This Pragma Gets Rid Of Them.
#pragma warning(disable: 4786)


// This Holds All Of The Information Related To Any
// FreeType Font That We Want To Create. 
struct FontData {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class OpenGLFont {

    TextShader* shader;

public:
    OpenGLFont(const char* vertexPath, const char* fragmentPath, int screenHeight, int screenWidth, const char* fontPath, unsigned int fontSize);

    ~OpenGLFont();

    // Free All The Resources Associated With The Font.
    void Clean();

    // Print Text!
    void PrintText(std::string text, float x, float y, float scale, glm::vec3 color);

private:
    // The Init Function Will Create A Font With
    // The Height h From The File fname.
    void Init(const char* fontPath, unsigned int fontSize);

    void ConfigureVAOAndVBO();
};

#endif