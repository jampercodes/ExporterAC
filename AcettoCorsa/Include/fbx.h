#include <stdio.h>
#include <stdio.h>

class fbx_node {
private:
    char* node_name;

    fbx_node* chiled_nodes;
};

class fbx_manager {
public:
    fbx_manager(char *filename, char *filelocation);
    ~fbx_manager();
    
    void add_mesh();

private:
    FILE* M_file;
};


const unsigned int FBX_VERSION = 6000;