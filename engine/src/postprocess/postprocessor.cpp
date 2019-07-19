#include "postprocess/postprocessor.h"

#include "resources/mesh.h"
#include "resources/material.h"
#include "resources/rendertexture.h"

#include "commandbuffer.h"

#include "filters/blur.h"

static Blur *s_pBlur = nullptr;

PostProcessor::PostProcessor() :
        m_pMaterial(nullptr) {

    m_pResultTexture = Engine::objectCreate<RenderTexture>();
    m_pResultTexture->setTarget(Texture::R11G11B10Float);

    m_pMesh = Engine::loadResource<Mesh>(".embedded/plane.fbx/Plane001");
}

PostProcessor::~PostProcessor() {

}

RenderTexture *PostProcessor::draw(RenderTexture *source, ICommandBuffer &buffer) {
    if(m_pMaterial) {
        m_pMaterial->setTexture("rgbMap", source);

        buffer.setRenderTarget({m_pResultTexture});
        buffer.drawMesh(Matrix4(), m_pMesh, ICommandBuffer::UI, m_pMaterial);

        return m_pResultTexture;
    }
    return source;
}

void PostProcessor::resize(uint32_t width, uint32_t height) {
    m_pResultTexture->resize(width, height);
}

Blur *PostProcessor::blur() {
    if(s_pBlur == nullptr) {
        s_pBlur = new Blur();
    }
    return s_pBlur;
}
