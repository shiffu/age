#include "SpriteFont.h"

#include "SpriteBatch.h"
#include "Sprite.h"

#include <SDL2/SDL.h>


#define MAX_TEXTURE_RES 4096

namespace age {
    
    int closestPow2(int i) {
        i--;
        int pi = 1;
        while (i > 0) {
            i >>= 1;
            pi <<= 1;
        }
        
        return pi;
    }

    SpriteFont::SpriteFont(const char* fontFilename, int size, char charStart, char charEnd) {
        
        // Initialize SDL_ttf
        if (!TTF_WasInit()) {
            TTF_Init();
        }
        
        TTF_Font* font = TTF_OpenFont(fontFilename, size);
        if (font == nullptr) {
            fprintf(stderr, "Failed to open TTF font %s\n", fontFilename);
            fflush(stderr);
            throw 281;
        }
        
        //TTF_SetFontKerning(font, 0);
        
        m_fontMaxHeight = TTF_FontHeight(font);
        m_regStart = charStart;
        m_regLength = charEnd - charStart + 1;
        int padding = size / 8;

        // First measure all the regions
        glm::ivec4* glyphUV = new glm::ivec4[m_regLength];
        m_glyphs = new CharGlyph[m_regLength + 1];
        int i = 0, xMin, xMax, yMin, yMax, advance;
        
        for (char c = charStart; c <= charEnd; c++) {
            TTF_GlyphMetrics(font, c, &xMin, &xMax, &yMin, &yMax, &advance);
            
            // Width
            glyphUV[i].z = xMax - xMin;
            glyphUV[i].x = 0;
            
            // Height
            glyphUV[i].w = yMax - yMin;
            glyphUV[i].y = 0;
            
            m_glyphs[i].size = glm::vec2(glyphUV[i].z, glyphUV[i].w);
            m_glyphs[i].xMin = xMin;
            m_glyphs[i].xMax = xMax;
            m_glyphs[i].yMin = yMin;
            m_glyphs[i].yMax = yMax;
            m_glyphs[i].advance = advance;

            i++;
        }

        // Find best partitioning of glyphs
        int nbRows = 1, w, h, bestTexWidth = 0, bestTexHeight = 0, area = MAX_TEXTURE_RES * MAX_TEXTURE_RES, bestNbRows = 0;
        std::vector<int>* bestPartition = nullptr;
        
        while (nbRows <= m_regLength) {
            h = nbRows * (padding + m_fontMaxHeight) + padding;
            auto glyphsRows = createRows(glyphUV, m_regLength, nbRows, padding, w);

            // Desire a power of 2 for the texture dims
            w = closestPow2(w);
            h = closestPow2(h);

            // A texture must be feasible
            if (w > MAX_TEXTURE_RES || h > MAX_TEXTURE_RES) {
                nbRows++;
                delete[] glyphsRows;
                continue;
            }

            // Check for minimal area
            if (w * h < area) {
                if (bestPartition) {
                    delete[] bestPartition;
                }
                
                bestPartition = glyphsRows;
                bestTexWidth = w;
                bestTexHeight = h;
                bestNbRows = nbRows;
                area = bestTexWidth * bestTexHeight;
                nbRows++;
            } else {
                delete[] glyphsRows;
                break;
            }
        }

        // Can a bitmap font be made?
        if (!bestPartition) {
            fprintf(stderr, "Failed to Map TTF font %s to texture. Try lowering resolution.\n", fontFilename);
            fflush(stderr);
            throw 282;
        }
        
        // Create the texture
        GLuint textureID;
        glGenTextures(1, &textureID);
        m_texture = new Texture(textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bestTexWidth, bestTexHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        // Now draw all the glyphs in the texture
        SDL_Color fg = { 255, 255, 255, 255 };
        int yOffset = padding;
        
        for (int ri = 0; ri < bestNbRows; ri++) {
            
            int xOffset = padding;
            for (int ci = 0; ci < bestPartition[ri].size(); ci++) {
                int glyphIdx = bestPartition[ri][ci];

                SDL_Surface* glyphSurface = TTF_RenderGlyph_Blended(font, (char)(charStart + glyphIdx), fg);

                // TODO: Make a function for this invertY Code (used in ResourceManager as well)
                // Invert Y
                int channels = glyphSurface->format->BytesPerPixel;
                unsigned char* img = (unsigned char*)glyphSurface->pixels;
                for(int j = 0; j*2 < glyphSurface->h; ++j) {
                    int index1 = j * glyphSurface->w * channels;
                    int index2 = (glyphSurface->h - 1 - j) * glyphSurface->w * channels;
                    
                    for(int i = glyphSurface->w * channels; i > 0; --i) {
                        unsigned char temp = img[index1];
                        img[index1] = img[index2];
                        img[index2] = temp;
                        ++index1;
                        ++index2;
                    }
                }

                // Save glyph image and update UV coordinates
                // bestTexHeight - yOffset - 1 - glyphSurface->h
                glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset,
                                glyphSurface->w, glyphSurface->h,
                                GL_BGRA, GL_UNSIGNED_BYTE, glyphSurface->pixels);
                
                glyphUV[glyphIdx].x = xOffset;
                glyphUV[glyphIdx].y = yOffset;
                glyphUV[glyphIdx].z = glyphSurface->w;
                glyphUV[glyphIdx].w = glyphSurface->h;

                SDL_FreeSurface(glyphSurface);
                glyphSurface = nullptr;

                xOffset += glyphUV[glyphIdx].z + padding;
            }
            yOffset += m_fontMaxHeight + padding;
        }

        // Draw the unsupported glyph
        int rs = padding - 1;
        int* pureWhiteSquare = new int[rs * rs];
        memset(pureWhiteSquare, 0xffffffff, rs * rs * sizeof(int));
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, rs, rs, GL_RGBA, GL_UNSIGNED_BYTE, pureWhiteSquare);
        delete[] pureWhiteSquare;
        pureWhiteSquare = nullptr;

        // Set some texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Create CharGlyph(s)
        for (i = 0; i < m_regLength; i++) {
            m_glyphs[i].character = (char)(charStart + i);
            m_glyphs[i].size = glm::vec2(glyphUV[i].z, glyphUV[i].w);
            m_glyphs[i].uvRect = glm::vec4(
                (float)glyphUV[i].x / (float)bestTexWidth,
                (float)glyphUV[i].y / (float)bestTexHeight,
                ((float)glyphUV[i].x + (float)glyphUV[i].z) / (float)bestTexWidth,
                ((float)glyphUV[i].y + (float)glyphUV[i].w) / (float)bestTexHeight
                );
        }
        
        // Unsupported glyph
        m_glyphs[m_regLength].character = ' ';
        m_glyphs[m_regLength].size = m_glyphs[0].size;
        m_glyphs[m_regLength].uvRect = glm::vec4(0, 0, (float)rs / (float)bestTexWidth, (float)rs / (float)bestTexHeight);

        glBindTexture(GL_TEXTURE_2D, 0);
        delete[] glyphUV;
        delete[] bestPartition;
        TTF_CloseFont(font);
    }
    
    SpriteFont::~SpriteFont() {
        dispose();
    }
    
    void SpriteFont::dispose() {
        if (m_texture) {
            delete m_texture;
            m_texture =nullptr;
        }
        
        if (m_glyphs) {
            delete[] m_glyphs;
            m_glyphs = nullptr;
        }
    }

    std::vector<int>* SpriteFont::createRows(glm::ivec4* rects, int rectsLength, int nbRows, int padding, int& w) {
        
        // Blank initialize
        std::vector<int>* glyphs = new std::vector<int>[nbRows]();
        
        int* rowsTotalWidth = new int[nbRows]();
        for (int i = 0; i < nbRows; i++) {
            rowsTotalWidth[i] = padding;
        }

        // Loop through all glyphs
        for (int i = 0; i < rectsLength; i++) {
            
            // Find best row for placement based on total row width (smallest is the best)
            int rowMinWidthIdx = 0;
            for (int j = 1; j < nbRows; j++) {
                if (rowsTotalWidth[j] < rowsTotalWidth[rowMinWidthIdx]) {
                    rowMinWidthIdx = j;
                }
            }

            // Add width to that row
            rowsTotalWidth[rowMinWidthIdx] += rects[i].z + padding;

            // Add glyph to the row list
            glyphs[rowMinWidthIdx].push_back(i);
        }

        // Find the max width
        w = 0;
        for (int i = 0; i < nbRows; i++) {
            if (rowsTotalWidth[i] > w) w = rowsTotalWidth[i];
        }

        delete [] rowsTotalWidth;
        
        return glyphs;
    }

    glm::vec2 SpriteFont::measure(const char* s) {
        
        glm::vec2 size(0, m_fontMaxHeight);
        float cw = 0;
        for (int si = 0; s[si] != 0; si++) {
            char c = s[si];
            if (c == '\n') {
                size.y += m_fontMaxHeight;
                if (size.x < cw)
                    size.x = cw;
                cw = 0;
            } else {
                // Check for correct glyph
                int gi = c - m_regStart;
                if (gi < 0 || gi >= m_regLength)
                    gi = m_regLength;
                cw += m_glyphs[gi].size.x;
            }
        }
        
        if (size.x < cw) {
            size.x = cw;
        }
        
        return size;
    }

    void SpriteFont::render(BatchRenderer2D& batch, const char* s, glm::vec2 position, glm::vec2 scaling,
                          float depth, Color color, int padding /* = PADDING*/, Justification just /* = Justification::LEFT */) {
        
        glm::vec2 curPos = position;
        
        // Apply justification
        if (just == Justification::MIDDLE) {
            curPos.x -= measure(s).x * scaling.x / 2;
        } else if (just == Justification::RIGHT) {
            curPos.x -= measure(s).x * scaling.x;
        }
        
        for (int si = 0; s[si] != 0; si++) {
            char c = s[si];
            if (c == '\n') {
                curPos.y += m_fontMaxHeight * scaling.y;
                curPos.x = position.x;
            } else {
                // Check for correct glyph
                int gi = c - m_regStart;
                if (gi < 0 || gi >= m_regLength)
                    gi = m_regLength;
                
                glm::vec2 dims = m_glyphs[gi].size * scaling;
                
                Sprite* sprite = new Sprite(dims);
                sprite->setColor(color);
                sprite->transferOwnership(true);
                sprite->setUV(m_glyphs[gi].uvRect);
                sprite->setTexture(m_texture);
                sprite->setPosition(curPos);
                
                sprite->render(&batch);
                
                curPos.x += (m_glyphs[gi].size.x + padding) * scaling.x;
            }
        }
    }

}