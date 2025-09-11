/************************************************* *
** Copyright(c) 2021 -- Camshaft Software PTY LTD
************************************************** */

#pragma once

#include "AutomationExportExample.h"

class AuExpMesh
{
public:

	static void SaveMeshFile(const AuCarExpMesh* mesh, const wchar_t* filename);

	static void SaveFBXFile(AuCarExpArray<AuCarExpMesh*>& meshes, int mesh_count, const wchar_t* filename);
};
