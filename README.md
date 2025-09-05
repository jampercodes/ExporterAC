# Exporter to AC

> [!WARNING]  
> This is still a havy work in progas use at your own risk.
> Please make an issue if you encounter bugs.

## build proces
You need to have python and Visual Studio 17 2022 c++ compiler installd

Run build.py

And in build/out you shud have: \
AcettoCorsax64.dll, \
AcettoCorsax64.exp, \
AcettoCorsax64.lib and \
AcettoCorsax86.lib

copy those 4 files to: \
[your_steam_lib]\Automation\UE427\AutomationGame\Content\ExportPlugins

## to do
<details open>
 <summary> </summary>

 <details>

<summary> export fbx</summary>

### fbx needs the file structuer to use emptys etc.

> priority: hig (working on it now)

</details>

<details>

<summary> export data</summary>

### data needs to be calculated and exported to a format that can be read by AC

> priority: low (wil use hardcoded values for now)

 </details>

 <details>

<summary> export audio </summary>

> priority: low (since AC does not **NEED** audio)

</details>

</details>