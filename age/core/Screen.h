#pragma once

#include <string>

namespace age {
    
    enum class ScreenState {
        NONE,
        INITIALIZED,
        ACTIVE,
        GO_NEXT,
        INACTIVE,
        DESTROYED
    };

    class Game;
    
    class Screen {
    public:
        virtual std::string getNext() const = 0;
        
        void setGame(Game* game) { m_game = game; }
        Game* getGame() { return m_game; }
        
        ScreenState getState() const { return m_screenState; };
        void setState(ScreenState state) { m_screenState = state; };
        
        void init();
        void destroy();
        
        virtual void onInit() {};
        virtual void onDestroy() {};
        virtual void onExit() {};
        
        virtual void onEntry() {};
        virtual void onInput() = 0;
        virtual void onUpdate(float deltaTime) = 0;
        virtual void onRender() = 0;
        
    private:
        ScreenState m_screenState = ScreenState::NONE;
        Game* m_game = nullptr;
    };
    
}