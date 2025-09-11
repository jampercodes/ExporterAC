#include <unordered_map>
#include <string>

fbxMenager setup_fbx(std::string);

enum part_type
{
    Chassi,
    wheel,
    engene,
    exhaust,
    fixture
};

class fbxMenager
{
public:
    void SaveMeshsFBX(AuCarExpArray<AuCarExpMesh*>& meshes, int mesh_count, const wchar_t* filename);

    void save_fbx();
};