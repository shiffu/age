#include "Theme.h"
#include "../rendering/Texture.h"

namespace age {
 
    void Theme::setFontSize(int size) {
        m_fontSize = size;
    }
    
    int Theme::getFontSize() const {
        return m_fontSize;
    }

    void Theme::setFont(const std::string& font) {
        m_font = font;
    }
    
    const std::string& Theme::getFont() const {
        return m_font;
    }

    void Theme::setButtonTexture(Texture* texture) {
        m_buttonTexture = texture;
    }

    Texture* Theme::getButtonTexture() const {
        return m_buttonTexture;
    }
    
    glm::vec4 Theme::convertToTextureCoordinates(const glm::vec4& screenCoordinates) {
        unsigned int w = m_buttonTexture->getWidth();
        unsigned int h = m_buttonTexture->getHeight();
        glm::vec4 uv = {screenCoordinates.x / w, (h - screenCoordinates.y) / h,
                        screenCoordinates.z / w, (h - screenCoordinates.w) / h};
        return uv;
    }

    void Theme::setDefaultUV(glm::vec4 uv) {
        m_defaultUV = convertToTextureCoordinates(uv);
    }
    
    void Theme::setPressedUV(glm::vec4 uv) {
        m_pressedUV = convertToTextureCoordinates(uv);
    }
    
    void Theme::setHoverUV(glm::vec4 uv) {
        m_hoverUV = convertToTextureCoordinates(uv);
    }
    
    glm::vec4 Theme::getDefaultUV() const {
        return m_defaultUV;
    }
    
    glm::vec4 Theme::getPressedUV() const {
        return m_pressedUV;
    }
    
    glm::vec4 Theme::getHoverUV() const {
        return m_hoverUV;
    }

}
