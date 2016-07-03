#pragma once

#include <string>
#include "../rendering/Color.h"

class SDL_Window;

namespace age {
    
    enum class WindowFlag {
        FULLSCREEN,
        BORDERLESS,
        RESIZABLE,
        MINIMIZE,
        MAXIMIZE
    };
    
    
    class Window {
    public:
        Window(const std::string& name, unsigned int width, unsigned int height,
               WindowFlag flags = WindowFlag::MAXIMIZE);
        ~Window();
        
        void init();
        void destroy();
        
        void swapBuffers() const;
        
        int getWidth() const;
        int getHeight() const;
        void setSize(int width, int height);
        
    private:
        SDL_Window*	m_window = nullptr;
        WindowFlag m_flags;
        Color m_backgroundColor = Color(0x000000FF);
        std::string m_title;
        int m_width;
        int m_height;
    };
    
}