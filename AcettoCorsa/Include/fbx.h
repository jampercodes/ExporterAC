#pragma once

#include "fbxsdk.h"
#include "AutomationExportExample.h"
#include "helper.h"

enum SpecialMesh
{
    tire,
    rim,
    suspension,
};


void init_fbx(std::wstring ExportDirectory);
void add_mesh (const AuCarExpMesh* mesh, const wchar_t* Wname);
void add_mesh (const AuCarExpMesh* mesh, const wchar_t* Wname, SpecialMesh specialmesh);
void save_FBX ();