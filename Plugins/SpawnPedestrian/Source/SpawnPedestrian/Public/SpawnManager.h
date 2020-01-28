#pragma once

#include "Editor.h"
#include "LightingBuildOptions.h"
#include "PedestrianCharacter.h"

class FSpawnManager
{
public:
   FSpawnManager();

   void InitializeMap() const;
   void InitializeNavMesh() const;
   void InitializePedestrian() const;

   static FString InContent(const FString& RelativePath);

protected:

   TSubclassOf<APedestrianCharacter> PedestrianCharacterBP;

   // Here we have some information of the NavMesh
   // TODO: add a reference to NavMesh
   FVector NavMeshOrigin;
   FVector NavMeshExtend;
   // ANavMeshBoundsVolume

private:

   UWorld* World = GEditor->GetEditorWorldContext().World();
   FLightingBuildOptions LightOptions;
};
