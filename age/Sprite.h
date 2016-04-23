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
#include "IRenderable2D.h"
#include "IRigidBody.h"
#include "IPhysicsEngine.h"

namespace age {

    class Sprite : public IRenderable2D
	{
	public:
		Sprite();
		~Sprite();

		void init(float x, float y, float width, float height);
        
        void setPosition(glm::vec2 pos);
        void setPosition(float x, float y);
        glm::vec2 getPosition() const { return m_pos; };
        void setAngle(float angle);
        
        void setColor(Color color);
        void setTexture(Texture* texture);
        
        const std::vector<Vertex>& getVertices() const override;
        const std::vector<unsigned short>& getIndices() const override;
        GLuint getTextureId() const override;
        unsigned int getDepth() const override;

        void setRigidBody(IPhysicsEngine* physicsEngine, IRigidBody::Type bodyType,
                          float density, float friction, float restitution);
        void updateFromPhysics();

    protected:
        std::vector<Vertex> m_vertices;
        std::vector<unsigned short> m_indices;
        Texture* m_texture = nullptr;
        
	private:
        static const unsigned char SPRITE_SIZE = 4;
        glm::vec2 rotateVertex(const glm::vec2& pos, float angle);

        glm::vec2 m_pos;
		float m_width = 0;
		float m_height = 0;
        float m_depth = 0;
		Color m_color = Color();
        IRigidBody* m_rigidBody = nullptr;
	};

}

