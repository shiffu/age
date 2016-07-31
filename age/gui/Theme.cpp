#include "Theme.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "../rendering/Texture.h"
#include "../core/ResourceManager.h"
#include "../core/StringUtil.h"

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

		std::string themeFilePath = ResourceManager::instance().getThemePath(filename);
		std::ifstream ifs(themeFilePath);
		
		if (ifs) {
			std::string line;
			size_t pos = 0;
			std::string key;
			std::string value;

			while (std::getline(ifs, line)) {
				// Check for comments
				if (line[0] == '#') {
					continue;
				}

				// Search for "=" separator (key/value)
				if ((pos = line.find("=")) != std::string::npos) {
					key = StringUtil::trim(line.substr(0, pos));
					value = StringUtil::trim(line.substr(pos + 1));
					
					//TODO: Remove this debugging log
					cout << "key:" << key << ", value:" << value << endl;

					if (key == "font.name") {
						setFont(value);
					}
					else if (key == "font.size") {
						setFontSize(std::stoi(value));
					}
					else if (key == "button.texture") {
						setButtonTexture(age::ResourceManager::instance().loadTexture(value));
					}
					else if (key == "button.defaultUV") {
						setDefaultUV(convert(value));
					}
					else if (key == "button.pressedtUV") {
						setPressedUV(convert(value));
					}
					else if (key == "button.hoverUV") {
						setHoverUV(convert(value));
					}
					else {
						//TODO: Implement proper error management
						cerr << "Uknown property " << key << endl;
					}
				}
			}

			ifs.close();
		}
		else {

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
