#pragma once

#include "fbxsdk.h"
#include "AutomationExportExample.h"
#include "helper.h"

void init_fbx(std::wstring ExportDirectory);
void add_mesh (const AuCarExpMesh* mesh, const wchar_t* Wname);
void save_FBX ();