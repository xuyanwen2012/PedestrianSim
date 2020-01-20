#include "SpawnManager.h"

#include "Atmosphere/AtmosphericFog.h"
#include "Engine/SkyLight.h"
#include "Components/SkyLightComponent.h"

#include "Components/BrushComponent.h"


#include "EngineUtils.h"
#include "Engine/StaticMeshActor.h"
#include "NavMeshBoundsVolume.h"
#include "Builders/CubeBuilder.h"
#include "EditorModeManager.h"


#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem.h"
#include "MyTestVolume.h"

#include "BSPOps.h"

#define DEBUG_PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

SpawnManager::SpawnManager()
{
   UE_LOG(LogTemp, Warning, TEXT("SpawnManager::SpawnManager() Called."));

   // Build some lights
   const auto Location = FVector(0.0f, 0.0f, 2000.0f);
   const auto Rotation = FRotator(0.0f, 0.0f, 0.0f);
   const FActorSpawnParameters SpawnParameters;

   World->SpawnActor<AAtmosphericFog>(Location, Rotation, SpawnParameters);

   const auto LightLocation = FVector(0.0f, 0.0f, 100000.0f);

   const auto Skylight = World->SpawnActor<ASkyLight>(LightLocation, Rotation, SpawnParameters);
   if (Skylight != nullptr)
   {
      Skylight->GetLightComponent()->SetIntensity(5.0f);
      GEditor->BuildLighting(LightOptions);
   }

   // Acquire all meshes
   for (TActorIterator<AStaticMeshActor> ActorItr(World); ActorItr; ++ActorItr)
   {
      auto Mesh = *ActorItr;

      auto Tmp = ActorItr->GetName();

      DEBUG_PRINT(Tmp);
      DEBUG_PRINT(ActorItr->GetActorLocation().ToString());
   }
}

void SpawnManager::InitializeNavMesh() const
{
   ULevel* CurrentLevel = World->GetCurrentLevel();

   // Cube Additive Brush
   UCubeBuilder* CubeAdditiveBrushBuilder = Cast<UCubeBuilder>(GEditor->FindBrushBuilder(UCubeBuilder::StaticClass()));
   CubeAdditiveBrushBuilder->X = 4096.0f;
   CubeAdditiveBrushBuilder->Y = 4096.0f;
   CubeAdditiveBrushBuilder->Z = 128.0f;
   CubeAdditiveBrushBuilder->Build(World);

   GEditor->Exec(World, TEXT("BRUSH MOVETO X=0 Y=0 Z=0"));
   //GEditor->Exec(World, TEXT("BRUSH ADDVOLUME CLASS=ANavMeshBoundsVolume"));
   GEditor->Exec(World, TEXT("BRUSH ADD"));

   // -------------

   const FVector SpawnLoc = FVector::ZeroVector;
   AVolume* Actor = World->SpawnActor<AVolume>(ANavMeshBoundsVolume::StaticClass(), SpawnLoc, FRotator::ZeroRotator);
   if (Actor)
   {
      Actor->PreEditChange(nullptr);

      ABrush* Brush = World->GetDefaultBrush();

      FBSPOps::csgCopyBrush(
         Actor,
         Brush,
         0,
         RF_Transactional,
         true,
         true
      );

      if (Actor->Brush)
      {
         for (int32 poly = 0; poly < Actor->Brush->Polys->Element.Num(); ++poly)
         {
            FPoly* Poly = &(Actor->Brush->Polys->Element[poly]);
            Poly->Material = nullptr;
         }
      }

      Actor->PostEditChange();
   }

   GEditor->RedrawLevelEditingViewports();
   if (Actor)
   {
      ULevel::LevelDirtiedEvent.Broadcast();
      World->BroadcastLevelsChanged();
   }

   // -------------


   GLevelEditorModeTools().MapChangeNotify();
}
