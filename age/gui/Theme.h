#pragma once

#include <string>
#include <glm/glm.hpp>

namespace age {
    
    class Texture;
    
    class Theme {
    public:
        Theme() {};
        ~Theme() {};
        
		void loadFromFile(const std::string& filename);

        void setFontSize(int size);
        int getFontSize() const;        
        void setFont(const std::string& font);
        const std::string& getFont() const;
        
        void setButtonTexture(Texture* texture);
        Texture* getButtonTexture() const;
        
        void setDefaultUV(glm::vec4 uv);
        void setPressedUV(glm::vec4 uv);
        void setHoverUV(glm::vec4 uv);
        glm::vec4 getDefaultUV() const;
        glm::vec4 getPressedUV() const;
        glm::vec4 getHoverUV() const;
        
    private:
        glm::vec4 convertToTextureCoordinates(const glm::vec4& screenCoordinates);
        
    private:
        std::string m_font = {};
        int m_fontSize = 32;
        Texture* m_buttonTexture = nullptr;
        glm::vec4 m_defaultUV = {0.0f, 0.0f, 1.0f, 1.0f};
        glm::vec4 m_pressedUV = {0.0f, 0.0f, 1.0f, 1.0f};
        glm::vec4 m_hoverUV = {0.0f, 0.0f, 1.0f, 1.0f};
    };
}