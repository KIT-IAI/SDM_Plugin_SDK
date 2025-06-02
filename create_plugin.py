import os
import shutil
from pathlib import Path


class PluginParameter:
    def __init__(self, templateFolder, sdkFolder, pluginFolder, pluginName, pluginAction, applicationDebugPath, applicationReleasePath):
        self.templateFolder = templateFolder
        self.sdkFolder = sdkFolder
        self.pluginFolder = pluginFolder
        self.pluginName = pluginName
        self.pluginAction = pluginAction
        self.applicationDebugPath = applicationDebugPath
        self.applicationReleasePath = applicationReleasePath


def process_files(plugin_parameter):

    pathName = plugin_parameter.pluginName[0].lower() + plugin_parameter.pluginName[1:]
    
    templateFolder = Path(plugin_parameter.templateFolder).resolve()
    pluginFolder = Path(plugin_parameter.pluginFolder + "/" + plugin_parameter.pluginName).resolve()

    for root, subFolder, files in os.walk(templateFolder):

        subFolder[:] = [d for d in subFolder if not (d.startswith('.') or d == 'include' or d == 'lib' or d == 'out')]
        
        for file in files:
            source = Path(root) / file
            relative_path = source.relative_to(templateFolder)
            
            target = pluginFolder / str(relative_path).replace('myPlugin', pathName)

            target.parent.mkdir(parents=True, exist_ok=True)

            process_file(source, target, plugin_parameter)

    sdkFolder = Path(plugin_parameter.sdkFolder).resolve()

    shutil.copytree(sdkFolder / "include", pluginFolder / "include")
    shutil.copytree(sdkFolder / "lib", pluginFolder / "lib")
    
    print("New project created: " + plugin_parameter.pluginName)


def process_file(sourceFile, targetFile, plugin_parameter):

    className = plugin_parameter.pluginName;
    fileName = plugin_parameter.pluginName[0].lower() + plugin_parameter.pluginName[1:]
    
    with sourceFile.open("r") as source:
        content = source.read()

    content = content.replace('MyPlugin', className)
    content = content.replace('myPlugin', fileName)
    content = content.replace('myplugin', className.lower())
    content = content.replace('ActionName', plugin_parameter.pluginAction)
    
    targetFileName = str(targetFile).replace('myPlugin', fileName)

    if targetFileName.find("CMakeSettings.json"):
        content = content.replace('ApplicationDebugPath', plugin_parameter.applicationDebugPath + "/plugins/" + plugin_parameter.pluginName)
        content = content.replace('ApplicationReleasePath', plugin_parameter.applicationReleasePath + "/plugins/" + plugin_parameter.pluginName)
    
    with open(targetFileName, "w") as target:
        target.write(content)
    
    print("File processed: " + str(targetFileName))


plugin_parameter = PluginParameter("plugin_template", "plugin_sdk", "./KITModelViewer_Plugins", "NewPlugin", "New Plugin", "./KITModelViewer/Debug", "./KITModelViewer/Release")

process_files(plugin_parameter)

