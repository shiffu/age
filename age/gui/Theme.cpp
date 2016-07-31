#include "Theme.h"

#include <iostream>
#include <vector>
#include <map>

#include "../rendering/Texture.h"
#include "../core/ResourceManager.h"
#include "../core/StringUtil.h"
#include "../core/PropertyFileParser.h"

namespace age {

	glm::vec4 convert(std::string& listOfValues) {
		std::vector<std::string> v = StringUtil::split(listOfValues, ',');
		glm::vec4 uv = { std::stoi(StringUtil::trim(v[0])),
			std::stoi(StringUtil::trim(v[1])),
			std::stoi(StringUtil::trim(v[2])),
			std::stoi(StringUtil::trim(v[3]))
		};

		return uv;
	}

	void Theme::loadFromFile(const std::string& filename) {
		using std::cout;
		using std::cerr;
		using std::endl;
		using std::map;
		using std::string;

		string themeFilePath = ResourceManager::instance().getThemePath(filename);
		PropertyFileParser pfp;
		pfp.parse(themeFilePath);
		string value;

		// Font
		value = pfp.getValue("font.name");
		if (value != "") {
			setFont(value);
		}
		setFontSize(std::stoi(pfp.getValue("font.size", "32")));

		// Button
		value = pfp.getValue("button.texture");
		if (value != "") {
			setButtonTexture(age::ResourceManager::instance().loadTexture(value));

			value = pfp.getValue("button.defaultUV");
			if (value != "") {
				setDefaultUV(convert(value));
			}
			value = pfp.getValue("button.pressedUV");
			if (value != "") {
				setPressedUV(convert(value));
			}
			value = pfp.getValue("button.hoverUV");
			if (value != "") {
				setHoverUV(convert(value));
			}
		}
	}

    void Theme::setFontSize(int size) {
        m_fontSize = size;
    }
    
    int Theme::getFontSize() const {
        return m_fontSize;
    }

    void Theme::setFont(const std::string& font) {
        m_font = font;
    }
    
    const std::string& Theme::getFont() const {
        return m_font;
    }

    void Theme::setButtonTexture(Texture* texture) {
        m_buttonTexture = texture;
    }

    Texture* Theme::getButtonTexture() const {
        return m_buttonTexture;
    }
    
    glm::vec4 Theme::convertToTextureCoordinates(const glm::vec4& screenCoordinates) {
        unsigned int w = m_buttonTexture->getWidth();
        unsigned int h = m_buttonTexture->getHeight();
        glm::vec4 uv = {screenCoordinates.x / w, (h - screenCoordinates.y) / h,
                        screenCoordinates.z / w, (h - screenCoordinates.w) / h};
        return uv;
    }

    void Theme::setDefaultUV(glm::vec4 uv) {
        m_defaultUV = convertToTextureCoordinates(uv);
    }
    
    void Theme::setPressedUV(glm::vec4 uv) {
        m_pressedUV = convertToTextureCoordinates(uv);
    }
    
    void Theme::setHoverUV(glm::vec4 uv) {
        m_hoverUV = convertToTextureCoordinates(uv);
    }
    
    glm::vec4 Theme::getDefaultUV() const {
        return m_defaultUV;
    }
    
    glm::vec4 Theme::getPressedUV() const {
        return m_pressedUV;
    }
    
    glm::vec4 Theme::getHoverUV() const {
        return m_hoverUV;
    }

}
