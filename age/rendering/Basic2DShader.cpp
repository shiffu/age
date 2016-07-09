#include "Basic2DShader.h"

namespace age {
    
    void Basic2DShader::init() {
        //TODO: manage shaders path in the resource manager?
        compileShaders("../age/rendering/shaders/basic");
        
        bindAttribute("position");
        bindAttribute("color");
        bindAttribute("uv");
        
        linkProgram();
        
        // Set texture slot
        bind();
        setUniform("texSampler", 0);
        unbind();
    }
    
    void Basic2DShader::setProjectionMatrix(glm::mat4 projectionMatrix) {
        setUniform("projection", projectionMatrix);
    }

}