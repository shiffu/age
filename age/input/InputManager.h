#pragma once

#include <unordered_map>

namespace age {

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void keyPressed(unsigned int keyId);
		void keyReleased(unsigned int keyId);
		bool isKeyPressed(unsigned int keyId) const;

	private:
		std::unordered_map<unsigned int, bool> m_keyMap;
	};

}