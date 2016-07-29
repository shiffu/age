#pragma once

#include <string>
#include "../rendering/Color.h"

class SDL_Window;

namespace age {
    
    enum class WindowFlag {
        NONE,
        FULLSCREEN,
        BORDERLESS,
        RESIZABLE,
        MINIMIZE,
        MAXIMIZE
    };
    
    
    class Window {
    public:
        Window(const std::string& name, unsigned int width, unsigned int height,
               WindowFlag flags = WindowFlag::NONE);
        ~Window();
        
        void init();
        void destroy();
        
        void swapBuffers() const;
        
        void setSize(const glm::vec2& size);
        void setSize(int width, int height);
        glm::vec2 getSize() const;
        
    private:
        SDL_Window*	m_window = nullptr;
        WindowFlag m_flags;
        Color m_backgroundColor = Color(0x000000FF);
        std::string m_title;
        // TODO: get rid of the m_width and m_height (and m_flags)
        int m_width;
        int m_height;
    };
    
}