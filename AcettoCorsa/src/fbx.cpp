#include "fbx.h"

void setup_fbx(char *name) {
    return new fbxMenager;
}

void fbxMenager::SaveMeshsFBX(const AuCarExpArray<AuCarExpMesh*>& meshes, const wchar_t* name) {
    
}

void fbxMenager::save_fbx() {
        std::ofstream fbx("minimal.fbx", std::ios::binary);

    // 1. Header
    const char header[23] = "Kaydara FBX Binary  \x00\x1A\x00";
    fbx.write(header, 23);

    // 2. Version (7400 for FBX 2013) in little-endian
    uint32_t version = 7400;
    fbx.write(reinterpret_cast<char*>(&version), sizeof(version));

    // 3. Null record (end of node)
    char nullNode[13] = {0};
    fbx.write(nullNode, 13);

    fbx.close();
}

