#pragma once

#include "fbxsdk.h"
#include "AutomationExportExample.h"

void init_fbx();
void add_mesh (const AuCarExpMesh* mesh, const wchar_t* Wname);
void save_FBX (std::wstring ExportDirectory);