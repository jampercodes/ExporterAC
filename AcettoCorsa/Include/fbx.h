#include <unordered_map>
#include <string>

fbxMenager fbx;

void setup_fbx(std::string);

enum part_type
{
    Chassi,
    wheel
};

class fbxMenager
{
public:
    void add_mesh(part_type PartType);

    void save_fbx();
};