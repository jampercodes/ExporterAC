# Exporter to AC

> [!WARNING]  
> This is still a havy work in progas use at your own risk.
> Please make an issue if you encounter bugs.

## build proces
you need to open the .sln file and build an x64 and x86 version.

you need to add x64 to the x64 copild lib's
and x86 to the .dll

> [!NOTE]
> you shut have AutomationExportExamplex64.dll, AutomationExportExamplex64.exp, AutomationExportExamplex64.lib and AutomationExportExamplex86.lib
> you can egnore all other files

copy those 4 files to [your_steam_lib]\Automation\UE427\AutomationGame\Content\ExportPlugins

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