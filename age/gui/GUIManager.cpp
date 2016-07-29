#include "GUIManager.h"

#include <algorithm>

#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "../rendering/Camera2D.h"
#include "../core/Window.h"
#include "Widget.h"
#include "Button.h"
#include "Label.h"

namespace age {
    
    GUIManager::~GUIManager() {
        for (auto w : m_widgets) {
            delete w;
        }
    }
    
    void GUIManager::render(IRenderer* renderer) {
        for (auto w : m_widgets) {
            w->draw(renderer);
        }
    }

    void GUIManager::handleInputs(const InputManager& inputManager) {

        for (auto w : m_widgets) {
            w->resetDefaultState();
        }

        std::vector<Widget*> targets = getTargetWidgets(inputManager.mousePosition());
        for (auto w : targets) {
            if (inputManager.isMouseButtonPressed(SDL_BUTTON_LEFT)) {
                w->onLeftButtonPressed();
            }
            else if (inputManager.isMouseButtonPressed(SDL_BUTTON_MIDDLE)) {
                w->onMiddleButtonPressed();
            }
            else if (inputManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
                w->onRightButtonPressed();
            }
            else {
                w->onMouseHover();
            }
        }
        
        // Check for widget that lost focus
        for (auto w : m_eventsAwareWidgets) {
            if (w->hasFocus() && find(targets.begin(), targets.end(), w) == targets.end()) {
                w->onLostFocus();
            }
        }
    }
    
    std::vector<Widget*> GUIManager::getTargetWidgets(glm::vec2 mousePosition) {

        //TODO: What if m_window or m_camera is null?
        glm::vec2 windowSize = m_window->getSize();
        glm::vec2 cameraSize = m_camera->getSize();
        mousePosition.x = mousePosition.x / windowSize.x * cameraSize.x;
        mousePosition.y = (windowSize.y - mousePosition.y) / windowSize.y * cameraSize.y;
        
        if (m_sortEdges) {
            std::stable_sort(m_leftEdges.begin(), m_leftEdges.end(),
                             [] (const Edge& a, const Edge& b) { return a.distance < b.distance; });
            
            std::stable_sort(m_rightEdges.begin(), m_rightEdges.end(),
                             [] (const Edge& a, const Edge& b) { return a.distance > b.distance; });
            
            std::stable_sort(m_topEdges.begin(), m_topEdges.end(),
                             [] (const Edge& a, const Edge& b) { return a.distance > b.distance; });
            
            std::stable_sort(m_bottomEdges.begin(), m_bottomEdges.end(),
                             [] (const Edge& a, const Edge& b) { return a.distance < b.distance; });
            
            m_sortEdges = false;
        }
        
        std::vector<Widget*> leftCandidates;
        for (auto& l : m_leftEdges) {
            if (mousePosition.x >= l.distance) {
                leftCandidates.push_back(l.widget);
            }
            else {
                break;
            }
        }
        
        std::vector<Widget*> rightCandidates;
        if (!leftCandidates.empty()) {
            for (auto& r : m_rightEdges) {
                if (mousePosition.x < r.distance) {
                    if (find(leftCandidates.begin(), leftCandidates.end(), r.widget) != leftCandidates.end()) {
                        rightCandidates.push_back(r.widget);
                    }
                }
                else {
                    break;
                }
            }
        }
        
        std::vector<Widget*> topCandidates;
        if (!rightCandidates.empty()) {
            for (auto& t : m_topEdges) {
                if (mousePosition.y < t.distance) {
                    if (find(rightCandidates.begin(), rightCandidates.end(), t.widget) != rightCandidates.end()) {
                        topCandidates.push_back(t.widget);
                    }
                }
                else {
                    break;
                }
            }
        }
        
        std::vector<Widget*> bottomCandidates;
        if (!topCandidates.empty()) {
            for (auto& b : m_bottomEdges) {
                if (mousePosition.y >= b.distance) {
                    if (find(topCandidates.begin(), topCandidates.end(), b.widget) != topCandidates.end()) {
                        bottomCandidates.push_back(b.widget);
                    }
                }
                else {
                    break;
                }
            }
        }
        
        return bottomCandidates;
    }
    
    void GUIManager::setMouseEventsAware(Widget* widget) {
        m_sortEdges = true;
        m_eventsAwareWidgets.push_back(widget);
        
        glm::vec4 aabb = widget->getAABB();
        m_leftEdges.push_back(Edge(aabb.x, widget));
        m_rightEdges.push_back(Edge(aabb.z, widget));
        m_topEdges.push_back(Edge(aabb.w, widget));
        m_bottomEdges.push_back(Edge(aabb.y, widget));
    }

    Button* GUIManager::getButton(const glm::vec2& pos, const glm::vec2& size) {
        Button* button = new Button(this, pos, size);
        m_widgets.push_back(button);
        setMouseEventsAware(button);
        
        return button;
    }
    
    Button* GUIManager::getButton(const glm::vec2& pos, const glm::vec2& size, const std::string& text) {
        Button* button = new Button(this, pos, size, text);
        m_widgets.push_back(button);
        setMouseEventsAware(button);
        
        return button;
    }
    
    Label* GUIManager::getLabel(const glm::vec2& pos, const std::string& text) {
        Label* label = new Label(this, pos, text);
        m_widgets.push_back(label);
        
        return label;
    }
}
