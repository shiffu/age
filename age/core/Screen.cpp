#include "Screen.h"

namespace age {
    
    void Screen::init() {
        onInit();
        m_screenState = ScreenState::INITIALIZED;
    }
    
    void Screen::destroy() {
        m_screenState = ScreenState::DESTROYED;
        onDestroy();
    }

}