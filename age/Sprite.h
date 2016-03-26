#pragma once

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif

#include <vector>
#include <glm/glm.hpp>

#include "Color.h"
#include "Vertex.h"
#include "Texture.h"
#include "IRigidBody.h"
#include "IPhysicsEngine.h"

namespace age {

	class Sprite
	{
        friend class BatchRenderer2D;
        
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height);
        
		void setPosition(float x, float y);
        glm::vec2 getPosition() const { return m_pos; };
        void setAngle(float angle);
        
        void setColor(Color color);
        void setTexture(Texture* texture);
        
        void setRigidBody(IPhysicsEngine* physicsEngine, IRigidBody::Type bodyType,
                          float density, float friction, float restitution);
        void updateFromPhysics();
        
	private:
        static const unsigned char SPRITE_SIZE = 4;
        glm::vec2 rotateVertex(const glm::vec2& pos, float angle);

        glm::vec2 m_pos;
		float m_width = 0;
		float m_height = 0;
        float m_depth = 0;
        std::vector<Vertex> m_vertexData;
		Color m_color = Color();
        Texture* m_texture = nullptr;
        IRigidBody* m_rigidBody = nullptr;
	};

}

