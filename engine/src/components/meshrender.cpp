#include "components/meshrender.h"

#include "components/actor.h"
#include "components/transform.h"
#include "commandbuffer.h"

#define MESH "Mesh"
#define MATERAILS "Materials"

MeshRender::MeshRender() :
        m_pMesh(nullptr) {
}

void MeshRender::draw(ICommandBuffer &buffer, int8_t layer) {
    Actor *a    = actor();
    if(m_pMesh && layer & a->layers()) {
        if(layer & ICommandBuffer::RAYCAST) {
            buffer.setColor(ICommandBuffer::idToColor(a->uuid()));
        }

        for(uint32_t s = 0; s < m_pMesh->surfacesCount(); s++) {
            MaterialInstance *material   = (s < m_Materials.size()) ? m_Materials[s] : nullptr;
            buffer.drawMesh(a->transform()->worldTransform(), m_pMesh, s, layer, material);
        }
        buffer.setColor(Vector4(1.0f));
    }
}

Mesh *MeshRender::mesh() const {
    return m_pMesh;
}

void MeshRender::setMesh(Mesh *mesh) {
    m_pMesh    = mesh;
    if(m_pMesh) {
        for(auto it : m_Materials) {
            delete it;
        }
        m_Materials.clear();
        for(uint32_t s = 0; s < mesh->surfacesCount(); s++) {
            for(uint32_t l = 0; l < mesh->lodsCount(s); l++) {
                m_Materials.push_back(mesh->material(s, l)->createInstance());
            }
        }
    }
}

MaterialArray MeshRender::materials() const {
    return m_Materials;
}

void MeshRender::setMaterials(const MaterialArray &material) {
    for(uint32_t index = 0; index < m_Materials.size(); index++) {
        if(index < material.size() && m_Materials[index] != material[index]) {
            Material *org = nullptr;
            if(m_Materials[index]) {
                org = m_Materials[index]->material();
            }

            Material *dst = material[index]->material();
            if(org != dst) {
                MaterialInstance *inst  = m_Materials[index];
                delete inst;

                m_Materials[index]  = dst->createInstance();
            }
        }
    }
}

Material *MeshRender::material(int index) const {
    if(index < m_Materials.size()) {
        if(m_Materials[index]) {
            return m_Materials[index]->material();
        }
    }
    return nullptr;
}

void MeshRender::setMaterial(Material *material, int index) {
    if(material && index < m_Materials.size()) {
        if(m_Materials[index]) {
            delete m_Materials[index];
        }
        m_Materials[index]  = material->createInstance();
    }
}

uint32_t MeshRender::materialCount() const {
    return m_Materials.size();
}

void MeshRender::loadUserData(const VariantMap &data) {
    Component::loadUserData(data);
    {
        auto it = data.find(MESH);
        if(it != data.end()) {
            setMesh(Engine::loadResource<Mesh>((*it).second.toString()));
        }
    }
    if(m_pMesh) {
        auto it = data.find(MATERAILS);
        if(it != data.end()) {
            VariantList list    = (*it).second.value<VariantList>();
            int32_t i  = 0;
            for(auto it : list) {
                setMaterial(Engine::loadResource<Material>(it.toString()), i);
                i++;
            }
        }
    }
}

VariantMap MeshRender::saveUserData() const {
    VariantMap result   = Component::saveUserData();
    {
        string ref  = Engine::reference(mesh());
        if(!ref.empty()) {
            result[MESH]    = ref;
        }
    }
    {
        VariantList list;
        for(MaterialInstance *it : materials()) {
            string ref  = Engine::reference(it->material());
            if(!ref.empty()) {
                list.push_back(ref);
            }
        }
        result[MATERAILS]   = list;
    }
    return result;
}