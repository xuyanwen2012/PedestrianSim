#pragma once

#include "Editor.h"
#include "LightingBuildOptions.h"

class FSpawnManager
{
public:
   FSpawnManager();

   void InitializeNavMesh() const;

private:

   UWorld* World = GEditor->GetEditorWorldContext().World();
   FLightingBuildOptions LightOptions;
};
