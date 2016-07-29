#pragma once

#include <string>

#include "Widget.h"
#include "../rendering/SpriteFont.h"
#include "../rendering/Color.h"

namespace age {
    
    class Label : public Widget {
    public:
        Label(GUIManager* guiManager, const glm::vec2& pos, const std::string& text = "");
        virtual ~Label() {};
        
        void setText(const std::string& text);
        void setColor(const Color& color);
        void setScale(const glm::vec2& scale);
        glm::vec2 getSize() const;
        void setJustification(Justification justification);
        Justification getJustification() const;
        
        virtual void draw(IRenderer* renderer) override;        
        virtual glm::vec4 getAABB() const override;
        
    private:
        std::string m_text;
        SpriteFont* m_spriteFont = nullptr;
        glm::vec2 m_scale = {1.0f, 1.0f};
        Justification m_justification = Justification::LEFT;
        float m_depth = 0;
        Color m_color;
    };
    
}