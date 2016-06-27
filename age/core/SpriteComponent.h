#pragma once

#include <vector>
#include "../rendering/Vertex.h"
#include "Component.h"
#include "../rendering/IRenderable2D.h"

namespace age {

    class Texture;
	class Animator;

    class SpriteComponent : public Component, IRenderable2D {
    
    public:
        SpriteComponent(float width, float height);
        virtual ~SpriteComponent();
        
		void setTexture(Texture* texture);
		void setAnimator(Animator* animator) { m_animator = animator;  }

        virtual void render(IRenderer* renderer);
 
        const std::vector<Vertex>& getVertices() const;
        const std::vector<unsigned short>& getIndices() const;
        GLuint getTextureId() const;
        unsigned int getDepth() const;
	
	protected:
		virtual void updateVerticesUVs();

	protected:
        static const unsigned char NB_VERTICES = 4;
        static const unsigned char NB_INDICES = 6;

        float m_width;
        float m_height;
        unsigned int m_depth;

		glm::vec4 m_uvs{ 0.0f, 0.0f, 1.0f, 1.0f };
		std::vector<Vertex> m_vertices;
		std::vector<Vertex> m_tranformedVertices;
        std::vector<unsigned short> m_indices;
        Texture* m_texture = nullptr;
		Animator* m_animator = nullptr;
    };
    
}