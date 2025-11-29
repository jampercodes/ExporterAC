// hear we wil call all funks frome the fbx sdk to make a fbx file
#include "../Include/fbx.h"

void init_fbx()
{
    lSdkManager = FbxManager::Create();

    ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
    lSdkManager->SetIOSettings(ios);

    lScene = FbxScene::Create(lSdkManager,"car");

    lRootNode = lScene->GetRootNode();
}

void add_mesh ()
{

}
