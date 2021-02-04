// Font class header.
#ifndef FONT_H
#define FONT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

#include "Shader.h"


// This Holds All Of The Information Related To Any
// FreeType Font That We Want To Create. 
struct FontData {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class OpenGLFont {

public:
    OpenGLFont(int screenHeight, int screenWidth, const char* fontPath, unsigned int fontSize, Shader& shadder);

    // Free All The Resources Associated With The Font.
    void Clean();

    // Print Text!
    void PrintText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);

private:
    // The Init Function Will Create A Font With
    // The Height h From The File fname.
    void Init(const char* fontPath, unsigned int fontSize);

    void ConfigureVAOAndVBO();
};

#endif