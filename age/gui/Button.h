#pragma once

#include "Widget.h"
#include "../rendering/Sprite.h"
#include "Label.h"

namespace age {
    
    class Label;
    
    class Button : public Widget {
    public:
        Button(GUIManager* guiManager, const glm::vec2& pos, const glm::vec2& size);
        Button(GUIManager* guiManager, const glm::vec2& pos, const glm::vec2& size,
               const std::string& text, Justification justification = Justification::MIDDLE);
        virtual ~Button() {};
        
        virtual void draw(IRenderer* renderer) override;
        virtual glm::vec4 getAABB() const override;
        
        Label* getLabel();
        void setText(const std::string& text);
        void setLabelRatio(float ratio);
        float getLabelRatio() const;
        void setLabelOffset(glm::vec2 offset);
        glm::vec2 getLabelOffset() const;
        
        // Widget methods
        virtual void resetDefaultState() override;
        virtual void onLeftButtonPressed() override;
        virtual void onMiddleButtonPressed() override;
        virtual void onRightButtonPressed() override;
        virtual void onMouseHover() override;

    private:
        void computeLabelScaleAndOffset();
        
    private:
        glm::vec2 m_size;
        Sprite m_sprite;
        Label* m_label = nullptr;
        float m_labelRatio = 0.75f;
        glm::vec2 m_labelOffset = {0.0f, -5.0f};
    };
    
}