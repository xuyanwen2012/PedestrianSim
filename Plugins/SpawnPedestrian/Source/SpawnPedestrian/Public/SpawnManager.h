#pragma once

#include "Editor.h"
#include "LightingBuildOptions.h"

class SpawnManager
{
public:
   SpawnManager();

   void InitializeNavMesh() const;

private:

   UWorld* World = GEditor->GetEditorWorldContext().World();
   FLightingBuildOptions LightOptions;
};
