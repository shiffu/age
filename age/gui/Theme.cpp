#include "Theme.h"

#include <iostream>
#include <vector>
#include <map>

#include "../rendering/Texture.h"
#include "../core/ResourceManager.h"
#include "../core/StringUtil.h"
#include "../core/PropertyFileParser.h"

namespace age {

	using namespace std;

	glm::vec4 convert(vector<string>& listOfValues) {
		glm::vec4 uv = { stoi(StringUtil::trim(listOfValues[0])),
			stoi(StringUtil::trim(listOfValues[1])),
			stoi(StringUtil::trim(listOfValues[2])),
			stoi(StringUtil::trim(listOfValues[3]))
		};

		return uv;
	}

	void Theme::loadFromFile(const string& filename) {

		string themeFilePath = ResourceManager::instance().getThemePath(filename);
		PropertyFileParser pfp;
		pfp.parse(themeFilePath);
		string value;
		vector<string> values;

		// Font
		value = pfp.getValue("font.name");
		if (value != "") {
			setFont(value);
		}
		setFontSize(stoi(pfp.getValue("font.size", "32")));

		// Button
		value = pfp.getValue("button.texture");
		if (value != "") {
			setButtonTexture(age::ResourceManager::instance().loadTexture(value));

			values = pfp.getList("button.defaultUV");
			if (value != "") {
				setDefaultUV(convert(values));
			}
			values = pfp.getList("button.pressedUV");
			if (value != "") {
				setPressedUV(convert(values));
			}
			values = pfp.getList("button.hoverUV");
			if (value != "") {
				setHoverUV(convert(values));
			}
		}
	}

    void Theme::setFontSize(int size) {
        m_fontSize = size;
    }
    
    int Theme::getFontSize() const {
        return m_fontSize;
    }

    void Theme::setFont(const string& font) {
        m_font = font;
    }
    
    const string& Theme::getFont() const {
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
