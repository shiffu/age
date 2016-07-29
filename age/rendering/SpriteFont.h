/* 
    This is a modified version of the SpriteFont class from the
    Seed Of Andromeda source code.
    Use it for any of your projects, commercial or otherwise,
    free of charge, but do not remove this disclaimer.

    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS
    ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO
    EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
    INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
    RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
    ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
    OF THIS SOFTWARE.

    November 28 2014
    Original Author: Cristian Zaloj
    Modified By: Benjamin Arnold
    July 7 2016
    Modified By: Jean-Christophe Pennel
*/

#pragma once

#include <SDL2_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include <map>
#include <vector>

#include "Color.h"
#include "Vertex.h"
#include "BatchRenderer2D.h"

namespace age {

    struct CharGlyph {
        char character;
        int xMin;
        int xMax;
        int yMin;
        int yMax;
        int advance;
        glm::vec4 uvRect;
        glm::vec2 size;
    };

    #define FIRST_PRINTABLE_CHAR ((char)32)
    #define LAST_PRINTABLE_CHAR ((char)126)

    // For text justification
    enum class Justification {
        LEFT, MIDDLE, RIGHT
    };
    
    class SpriteFont {
    public:
        static const int PADDING = 7;
        
        SpriteFont(const char* font, int size, char charStart, char charEnd);
        SpriteFont(const char* font, int size) :
            SpriteFont(font, size, FIRST_PRINTABLE_CHAR, LAST_PRINTABLE_CHAR) {
        }
        ~SpriteFont();
        
        // Destroys the font resources
        void dispose();

        int getFontMaxHeight() const {
            return m_fontMaxHeight;
        }

        // Returns the size of the text
        glm::vec2 getSize(const char* s);

        // Render using a BatchRenderer2D
        void draw(IRenderer* renderer, const char* s, glm::vec2 position, glm::vec2 scaling,
                  float depth, Color color, int padding = PADDING, Justification just = Justification::LEFT);
        
    private:
        static std::vector<int>* createRows(glm::ivec4* rects, int rectsLength, int r, int padding, int& w);

        int m_regStart;
        int m_regLength;
        CharGlyph* m_glyphs = nullptr;
        int m_fontMaxHeight;

        Texture* m_texture;
    };

}
