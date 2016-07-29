#pragma once

#include <functional>

#include <glm/glm.hpp>

namespace age {
    
    void doNothingFct();
    
    class GUIManager;
    class Theme;
    class IRenderer;
    
    class Widget {
        friend class GUIManager;
        
    public:
        Widget(GUIManager* guiManager, float x, float y);
        Widget(GUIManager* guiManager, const glm::vec2& pos);
        virtual ~Widget() {};
        
        // Return the Axis Aligned Bounding Box coordinates (bottom-left/top-right)
        virtual glm::vec4 getAABB() const = 0;
        
        virtual void draw(IRenderer* renderer) = 0;
        
        void setPosition(glm::vec2 pos) { m_pos = pos; }
        void setPosition(float x, float y) { m_pos.x = x; m_pos.y = y; }
        glm::vec2 getPosition() const { return m_pos; }
        
        void setLeftButtonPressedCallback(std::function<void()> fct);
        void setMiddleButtonPressedCallback(std::function<void()> fct);
        void setRightButtonPressedCallback(std::function<void()> fct);
        void setMouseHoverCallback(std::function<void()> fct);
        void setLostFocusCallback(std::function<void()> fct);
        
        bool hasFocus() const;
        
        virtual void resetDefaultState() {};
        virtual void onLeftButtonPressed();
        virtual void onMiddleButtonPressed();
        virtual void onRightButtonPressed();
        virtual void onMouseHover();
        virtual void onLostFocus();
        
    protected:
        glm::vec2 m_pos;
        GUIManager* m_guiManager;
        const Theme* m_theme = nullptr;
        bool m_notifyManagerOfMouseAwareness = true;
        bool m_hasFocus = false;
        
        std::function<void()> m_leftButtonPressedFct = doNothingFct;
        std::function<void()> m_middleButtonPressedFct = doNothingFct;
        std::function<void()> m_rightButtonPressedFct = doNothingFct;
        std::function<void()> m_mouseHoverFct = doNothingFct;
        std::function<void()> m_lostFocusFct = doNothingFct;
        
    private:
        void notifyManagerOfMouseAwareness();
    };
    
}
