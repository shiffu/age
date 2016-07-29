#pragma once

#include <vector>

#include "../input/InputManager.h"


namespace age {
    
    class Camera2D;
    class Window;
    class Theme;
    class IRenderer;
    class Widget;
    class Button;
    class Label;
    
    struct Edge {
        int distance;
        Widget* widget;
        
        Edge(int aDistance, Widget* aWidget) : distance(aDistance), widget(aWidget) {}
    };
    
    class GUIManager {
    public:
        GUIManager() {};
        ~GUIManager();
        
        void setCamera(const Camera2D* camera) { m_camera = camera; }
        void setWindow(const Window* window) { m_window = window; }
        void setTheme(Theme* theme) { m_theme = theme; }
        const Theme* getTheme() const { return m_theme; }
        void render(IRenderer* renderer);
        
        void handleInputs(const InputManager& inputManager);
        
        void setMouseEventsAware(Widget* widget);
        
        // Widgets factory methods
        Button* getButton(const glm::vec2& pos, const glm::vec2& size);
        Button* getButton(const glm::vec2& pos, const glm::vec2& size, const std::string& text);
        Label* getLabel(const glm::vec2& pos, const std::string& text);
        
    private:
        std::vector<Widget*> getTargetWidgets(glm::vec2 mousePosition);
        
    private:
        const Camera2D* m_camera = nullptr;
        const Window* m_window = nullptr;
        const Theme* m_theme = nullptr;
        
        std::vector<Widget*> m_widgets = {};
        std::vector<Widget*> m_eventsAwareWidgets = {};
        
        bool m_sortEdges = true;
        std::vector<Edge> m_leftEdges;
        std::vector<Edge> m_rightEdges;
        std::vector<Edge> m_topEdges;
        std::vector<Edge> m_bottomEdges;
    };
    
}
