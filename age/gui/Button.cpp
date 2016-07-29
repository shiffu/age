#include "Button.h"
#include "GUIManager.h"
#include "Theme.h"
#include "../rendering/Sprite.h"

namespace age {

    
    Button::Button(GUIManager* guiManager, const glm::vec2& pos, const glm::vec2& size,
                   const std::string& text, Justification justification /* = Justification::MIDDLE */)
        : Button(guiManager, pos, size) {
        
            setText(text);
            m_label->setJustification(justification);
    }
    
    Button::Button(GUIManager* guiManager, const glm::vec2& pos, const glm::vec2& size)
        : Widget(guiManager, pos), m_size(size) {
        
        m_sprite.init(size);
        m_sprite.setPosition(pos);
        m_sprite.setTexture(m_theme->getButtonTexture());
        m_sprite.setUV(m_theme->getDefaultUV());
    }
    
    void Button::draw(IRenderer* renderer) {
        m_sprite.draw(renderer);
    }

    glm::vec4 Button::getAABB() const {
        float halfWidth = m_size.x / 2.0f;
        float halfHeight = m_size.y / 2.0f;
        
        return glm::vec4(m_pos.x - halfWidth, m_pos.y - halfHeight, m_pos.x + halfWidth, m_pos.y + halfHeight);
    }
    
    Label* Button::getLabel() {
        return m_label;
    }
    
    void Button::setText(const std::string& text) {
        if (m_label == nullptr) {
            m_label = m_guiManager->getLabel(m_pos, text);
        }
        else {
            m_label->setText(text);
        }
        computeLabelScaleAndOffset();
    }

    void Button::setLabelRatio(float ratio) {
        m_labelRatio = ratio;
        computeLabelScaleAndOffset();
    }
    
    float Button::getLabelRatio() const {
        return m_labelRatio;
    }

    void Button::setLabelOffset(glm::vec2 offset) {
        m_labelOffset = offset;
        computeLabelScaleAndOffset();
    }
    
    glm::vec2 Button::getLabelOffset() const {
        return m_labelOffset;
    }

    void Button::computeLabelScaleAndOffset() {
        glm::vec2 expectedLabelSize = m_size * m_labelRatio;
        glm::vec2 labelScale = expectedLabelSize / m_size;
        m_label->setScale(labelScale);
        m_label->setPosition(m_pos + m_labelOffset);
    }

    void Button::resetDefaultState() {
        m_sprite.setUV(m_theme->getDefaultUV());        
    }

    void Button::onLeftButtonPressed() {
        m_sprite.setUV(m_theme->getPressedUV());
        Widget::onLeftButtonPressed();
    }
    
    void Button::onMiddleButtonPressed() {
        m_sprite.setUV(m_theme->getPressedUV());
        Widget::onMiddleButtonPressed();
    }
    
    void Button::onRightButtonPressed() {
        m_sprite.setUV(m_theme->getPressedUV());
        Widget::onRightButtonPressed();
    }
    
    void Button::onMouseHover() {
        m_sprite.setUV(m_theme->getHoverUV());
        Widget::onMouseHover();
    }

}