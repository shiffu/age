#include "Widget.h"

#include "GUIManager.h"
#include "Theme.h"

namespace age {
    
    void doNothingFct() {}
    
    Widget::Widget(GUIManager* guiManager, float x, float y) : Widget(guiManager, glm::vec2(x, y)) {};
    Widget::Widget(GUIManager* guiManager, const glm::vec2& pos) : m_guiManager(guiManager), m_pos(pos) {
        m_theme = m_guiManager->getTheme();
    };
    
    void Widget::notifyManagerOfMouseAwareness() {
        if (m_notifyManagerOfMouseAwareness) {
            m_guiManager->setMouseEventsAware(this);
            m_notifyManagerOfMouseAwareness = false;
        }
    }

    void Widget::setLeftButtonPressedCallback(std::function<void()> fct) {
        notifyManagerOfMouseAwareness();
        m_leftButtonPressedFct = fct;
    }
    
    void Widget::setMiddleButtonPressedCallback(std::function<void()> fct) {
        notifyManagerOfMouseAwareness();
        m_middleButtonPressedFct = fct;
    }
    
    void Widget::setRightButtonPressedCallback(std::function<void()> fct) {
        notifyManagerOfMouseAwareness();
        m_rightButtonPressedFct = fct;
    }
    
    void Widget::setMouseHoverCallback(std::function<void()> fct) {
        notifyManagerOfMouseAwareness();
        m_mouseHoverFct = fct;
    }
    
    void Widget::setLostFocusCallback(std::function<void()> fct) {
        notifyManagerOfMouseAwareness();
        m_lostFocusFct = fct;
    }
    
    bool Widget::hasFocus() const {
        return m_hasFocus;
    }

    void Widget::onLeftButtonPressed() {
        m_hasFocus = true;
        m_leftButtonPressedFct();
    }
    
    void Widget::onMiddleButtonPressed() {
        m_hasFocus = true;
        m_middleButtonPressedFct();
    }
    
    void Widget::onRightButtonPressed() {
        m_hasFocus = true;
        m_rightButtonPressedFct();
    }
    
    void Widget::onMouseHover() {
        m_hasFocus = true;
        m_mouseHoverFct();
    }
    
    void Widget::onLostFocus() {
        m_hasFocus = false;
        m_lostFocusFct();
    }
    
}

