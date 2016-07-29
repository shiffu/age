#include "Label.h"

#include "Theme.h"

namespace age {

    Label::Label(GUIManager* guiManager, const glm::vec2& pos, const std::string& text /* = "" */)
    : Widget(guiManager, pos), m_text(text) {

        const std::string& font = m_theme->getFont();
        int fontSize = m_theme->getFontSize();
        m_spriteFont = new SpriteFont(font.c_str(), fontSize);
    }
    
    void Label::draw(IRenderer* renderer) {
        m_spriteFont->draw(renderer, m_text.c_str(), m_pos, m_scale, m_depth, m_color, 3, Justification::MIDDLE);
    }

    glm::vec2 Label::getSize() const {
        return m_spriteFont->getSize(m_text.c_str());
    }

    void Label::setJustification(Justification justification) {
        m_justification = justification;
    }
    
    Justification Label::getJustification() const {
        return m_justification;
    }

    glm::vec4 Label::getAABB() const {
        glm::vec2 size = getSize();
        float halfWidth = size.x / 2.0f;
        float halfHeight = size.y / 2.0f;
        
        return glm::vec4(m_pos.x - halfWidth, m_pos.y - halfHeight, m_pos.x + halfWidth, m_pos.y + halfHeight);
    }
    
    void Label::setText(const std::string& text) {
        m_text = text;
    }

    void Label::setColor(const Color& color) {
        m_color = color;
    }
    
    void Label::setScale(const glm::vec2& scale) {
        m_scale = scale;
    }

}