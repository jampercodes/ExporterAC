# Exporter to AC

> [!WARNING]  
> This is still heavy work in proges use at your own risk.
> Please make an issue if you encounter bugs.

## build process
You need to have Python and Visual Studio 17 2022 C++ compiler installed

Run build.py

And in build/out you should have: \
AcettoCorsax64.dll, \
AcettoCorsax64.exp, \
AcettoCorsax64.lib and \
AcettoCorsax86.lib

Copy those 4 files to: \
[your_steam_lib]\Automation\UE427\AutomationGame\Content\ExportPlugins

## to do
<details>

<summary> export fbx</summary>

### fbx needs the file structure to use emptys etc.

> priority: high (working on it now)

- [x] exporting the mesh
- [ ] adding the uv´s normol maps to make it export in to ks editor  
- [ ] fixing the rotation on some objects  

</details>

<details>

<summary> export data</summary>

### data needs to be calculated and exported to a format that can be read by AC

> priority: low (wil use hardcoded values for now)

</details>
