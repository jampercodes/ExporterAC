// hear we wil call all funks frome the fbx sdk to make a fbx file
#include "../Include/stdafx.h"
#include "../Include/fbx.h"

FbxManager* lSdkManager;
FbxIOSettings* ios;
FbxScene* lScene;
FbxNode* lRootNode;

std::string lFilename;


void add_mesh (const AuCarExpMesh* mesh, const wchar_t* Wname, FbxDouble3 extraOfset)
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



    //make material
    FbxSurfacePhong *lMaterial = FbxSurfacePhong::Create(lScene, FbxString(name.c_str()));
    lMaterial->Diffuse.Set(FbxDouble3 (1, 1, 1));

    //seting texture
    static FbxFileTexture *texture = FbxFileTexture::Create(lScene, FbxString(name.c_str()));
    texture->SetFileName("null.dds");   // VERY IMPORTANT
    texture->SetTranslation(0.0, 0.0);
    texture->SetScale(1.0, 1.0);
    texture->SetRotation(0.0, 0.0);

    lMaterial->Diffuse.ConnectSrcObject(texture);



    //save mesh
    FbxMesh* lMesh = FbxMesh::Create(lScene, name.c_str());


    lMesh->InitControlPoints(mesh->GetVertexCount());
    AuCarExpVertex* vertexBuffer = mesh->GetVertexBuffer();

    for (int i = 0; i < mesh->GetVertexCount(); i++)
    {
        lMesh->SetControlPointAt(FbxVector4(vertexBuffer[i].Position.x, vertexBuffer[i].Position.y, vertexBuffer[i].Position.z), i);
    }

    // UV: sdk ref - test
    FbxLayer* lLayer = lMesh->GetLayer(0);
    if (lLayer == NULL)
    {
        lMesh->CreateLayer();
        lLayer = lMesh->GetLayer(0);
    }

    FbxLayerElementUV* lUVDiffuseLayer = FbxLayerElementUV::Create(lMesh, "DiffuseUV");
    lUVDiffuseLayer->SetMappingMode(FbxLayerElement::eByPolygonVertex);
    lUVDiffuseLayer->SetReferenceMode(FbxLayerElement::eIndexToDirect);
    lLayer->SetUVs(lUVDiffuseLayer, FbxLayerElement::eTextureDiffuse);


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

    lNode->LclTranslation.Set(FbxDouble3 (Ttransform[12] * extraOfset[0], Ttransform[13] * extraOfset[1], Ttransform[14] * extraOfset[2]));

    lNode->LclScaling.Set(FbxDouble3 (Tscale.value[0], Tscale.value[1], Tscale.value[2]));

    lNode->LclRotation.Set(FbxDouble3 (TRotationEulerDegrees.x, TRotationEulerDegrees.y, TRotationEulerDegrees.z));

    lNode->AddMaterial(lMaterial);
}

// special mesh funks
void add_tire_mesh (const AuCarExpMesh* mesh, const wchar_t* Wname)
{ // clone the wheel to the other side, add a empty for ac

    add_mesh(mesh, Wname);

    add_mesh(mesh, Wname, FbxDouble3(-1, 1, 1));
}

void add_rim_mesh (const AuCarExpMesh* mesh, const wchar_t* Wname)
{ // clone the wheel to the other side, add a empty for ac

    add_mesh(mesh, Wname);

    add_mesh(mesh, Wname, FbxDouble3(-1, 1, 1));
}

void add_suspension_mesh (const AuCarExpMesh* mesh, const wchar_t* Wname)
{ // clone the wheel to the other side, add a empty for ac

    add_mesh(mesh, Wname);

    add_mesh(mesh, Wname, FbxDouble3(-1, 1, 1));
}


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



void add_mesh (const AuCarExpMesh* mesh, const wchar_t* Wname, SpecialMesh specialmesh)
{
    switch(specialmesh)
    {
        case tire:
            add_tire_mesh(mesh, Wname);
            break;
        case rim:
            add_rim_mesh(mesh, Wname);
            break;
        case suspension:
            add_suspension_mesh(mesh, Wname);
            break;
    }
}

void add_mesh (const AuCarExpMesh* mesh, const wchar_t* Wname)
{
    add_mesh(mesh, Wname, FbxDouble3(1, 1, 1));
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
