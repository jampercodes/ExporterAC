#include "../Include/fbx.h"

//class methods
fbx_manager::fbx_manager(char *filename, char *filelocation) {
    
    M_file = fopen(*filelocation + *filename + ".fbx", "w");

    std::printf("Creating FBX file: %s%s.fbx\n", filelocation, filename);

    fprintf(M_file, "Kaydara FBX Binary  ");
    fprintf(M_file, "\x00\x1A\x00");
    fprintf(M_file, "%u", FBX_VERSION);
}

fbx_manager::~fbx_manager() {
    if (M_file) {
        fclose(M_file);
        M_file = nullptr;
    }
}

void fbx_manager::add_mesh() {
    if (!M_file) {
        return;
    }

    // add mesh data to the file
}

