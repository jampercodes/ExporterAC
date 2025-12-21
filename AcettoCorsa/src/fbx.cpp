// hear we wil call all funks frome the fbx sdk to make a fbx file
#include "../Include/stdafx.h"
#include "../Include/fbx.h"

FbxManager* lSdkManager;
FbxIOSettings* ios;
FbxScene* lScene;
FbxNode* lRootNode;

std::string lFilename;

void init_fbx(std::wstring ExportDirectory)
{

    // build wide path and convert to UTF-8 string
    std::wstring wpath = ExportDirectory + L"\\body.fbx";
    int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wpath.c_str(), -1, nullptr, 0, nullptr, nullptr);

    if (sizeNeeded > 0) {
        lFilename.resize(sizeNeeded); // includes null terminator
        WideCharToMultiByte(CP_UTF8, 0, wpath.c_str(), -1, &lFilename[0], sizeNeeded, nullptr, nullptr);
        if (!lFilename.empty() && lFilename.back() == '\0') lFilename.pop_back();
    }

    lSdkManager = FbxManager::Create();

    ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
    lSdkManager->SetIOSettings(ios);

    lScene = FbxScene::Create(lSdkManager,"car");

    lRootNode = lScene->GetRootNode();

}

void add_mesh (const AuCarExpMesh* mesh, const wchar_t* Wname)
{

    int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, Wname, -1, nullptr, 0, nullptr, nullptr);
    std::string name;
    if (sizeNeeded > 0) {
        name.resize(sizeNeeded); // includes null terminator
        WideCharToMultiByte(CP_UTF8, 0, Wname, -1, &name[0], sizeNeeded, nullptr, nullptr);
        if (!name.empty() && name.back() == '\0') name.pop_back(); // optional: remove trailing null
    }

    //save textures:
	for (unsigned int i = 0; i < mesh->GetIndexBufferCount(); i++)
	{
		AuExpManager::Instance()->AddImage(mesh->GetMaterial(i)->GetDiffuseMapData().Texture);
		AuExpManager::Instance()->AddImage(mesh->GetMaterial(i)->GetNormalMapData().Texture);
	}



    //make textures
    FbxSurfacePhong *lMaterial = FbxSurfacePhong::Create(lScene, FbxString(name.c_str()));
    lMaterial->Diffuse.Set(FbxDouble3 (1, 1, 1));


    //save mesh
    FbxMesh* lMesh = FbxMesh::Create(lScene, name.c_str());

    lMesh->InitControlPoints(mesh->GetVertexCount());
    AuCarExpVertex* vertexBuffer = mesh->GetVertexBuffer();

    for (int i = 0; i < mesh->GetVertexCount(); i++)
    {
        lMesh->SetControlPointAt(FbxVector4(vertexBuffer[i].Position.x, vertexBuffer[i].Position.y, vertexBuffer[i].Position.z), i);
    }


    //triangles:
	unsigned int indexBufferCount = mesh->GetIndexBufferCount();

	for (unsigned int i = 0; i < indexBufferCount; i++)
	{
		unsigned int indexCount = mesh->GetIndexCount(i);
		int* indexBuffer = mesh->GetIndexBuffer(i);
		for (unsigned int j = 0; j < indexCount; j += 3)
		{
            int index0 = indexBuffer[j];
			int index1 = indexBuffer[j + 1];
			int index2 = indexBuffer[j + 2];


            lMesh->BeginPolygon();
			lMesh->AddPolygon(index0);
			lMesh->AddPolygon(index1);
			lMesh->AddPolygon(index2);
            lMesh->EndPolygon();
		}
	}

    FbxNode* lNode = FbxNode::Create(lScene, name.c_str());
    lNode->AddNodeAttribute(lMesh);

    lRootNode->AddChild(lNode);

    auto Ttransform = mesh->GetTransform();
    auto TRotationEulerDegrees = mesh->GetRotationEulerDegrees();
    auto Tscale = mesh->GetScale();

    FbxDouble3 OldTransform = lNode->LclTranslation.Get();

    lNode->LclTranslation.Set(FbxDouble3 (Ttransform[12], Ttransform[13], Ttransform[14]));

    lNode->LclScaling.Set(FbxDouble3 (Tscale.value[0], Tscale.value[1], Tscale.value[2]));

    lNode->LclRotation.Set(FbxDouble3 (TRotationEulerDegrees.x, TRotationEulerDegrees.y, TRotationEulerDegrees.z));

    lNode->AddMaterial(lMaterial);
}

void save_FBX ()
{
    FbxExporter* lExporter = FbxExporter::Create(lSdkManager, "");

    bool lExportStatus = lExporter->Initialize(lFilename.c_str(), -1, lSdkManager->GetIOSettings());

    if(!lExportStatus) {
        //print err
        return;
    }

    lExporter->SetFileExportVersion(
        FBX_2014_00_COMPATIBLE,
        FbxSceneRenamer::eNone );

    lExporter->Export(lScene);

    lSdkManager->Destroy();
}
