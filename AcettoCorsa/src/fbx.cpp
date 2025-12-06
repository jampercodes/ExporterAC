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

    FbxNode* lNode = FbxNode::Create(lScene, name.c_str());

    FbxMesh* lMesh = FbxMesh::Create(lScene, name.c_str());
    lNode->AddNodeAttribute(lMesh);

    lRootNode->AddChild(lNode);

    //loding model

}

void save_FBX ()
{
    FbxExporter* lExporter = FbxExporter::Create(lSdkManager, "");

    bool lExportStatus = lExporter->Initialize(lFilename.c_str(), -1, lSdkManager->GetIOSettings());

    if(!lExportStatus) {
        //print err
        return;
    }

    lExporter->Export(lScene);

    lSdkManager->Destroy();
}
