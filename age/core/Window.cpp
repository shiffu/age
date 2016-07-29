#include "Window.h"
#include "Utils.h"
#include "Error.h"

#include <SDL2/SDL.h>

namespace age {
    
    Window::Window(const std::string& title, unsigned int width, unsigned int height,
                   WindowFlag flags /* = WindowFlag::NONE */)
                    : m_title(title), m_width(width), m_height(height), m_flags(flags) {
    };
    
    Window::~Window() {};
    
    void Window::init() {

        unsigned int SDLWindowFlags = SDL_WINDOW_OPENGL;
        if (m_flags == WindowFlag::BORDERLESS) {
            SDLWindowFlags |= SDL_WINDOW_BORDERLESS;
        }
        if (m_flags == WindowFlag::FULLSCREEN) {
            SDLWindowFlags |= SDL_WINDOW_FULLSCREEN;
        }
        if (m_flags == WindowFlag::MAXIMIZE) {
            SDLWindowFlags |= SDL_WINDOW_MAXIMIZED;
        }
        if (m_flags == WindowFlag::MINIMIZE) {
            SDLWindowFlags |= SDL_WINDOW_MINIMIZED;
        }
        if (m_flags == WindowFlag::RESIZABLE) {
            SDLWindowFlags |= SDL_WINDOW_RESIZABLE;
        }
        
        m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    m_width, m_height, SDLWindowFlags);
        
        if (m_window == nullptr) {
            fatalError("Error creating the window!");
        }
        
        // Create the OpenGL Context
        SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
        if (glContext == nullptr) {
            fatalError(std::string("Error creating the OpenGL Context: ") + SDL_GetError());
        }
        Utils::logGlErrors("SDL GL Context creation failed");
    }
    
    void Window::destroy() {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    void Window::swapBuffers() const {
        SDL_GL_SwapWindow(m_window);
    }
    
    void Window::setSize(int width, int height) {
        SDL_SetWindowSize(m_window, width, height);
    }
    
    void Window::setSize(const glm::vec2& size) {
        SDL_SetWindowSize(m_window, size.x, size.y);
    }
    
    glm::vec2 Window::getSize() const {
        int w, h;
        SDL_GetWindowSize(m_window, &w, &h);
        return glm::vec2(w, h);
    }

}
