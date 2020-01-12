#include "SpawnManager.h"

#include "Atmosphere/AtmosphericFog.h"
#include "Engine/SkyLight.h"
#include "Components/SkyLightComponent.h"


#include "EngineUtils.h"
#include "Engine/StaticMeshActor.h"
#include "NavMeshBoundsVolume.h"
#include "Builders/CubeBuilder.h"
#include "EditorModeManager.h"


#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem.h"
#include "MyVolume.h"

#define DEBUG_PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

SpawnManager::SpawnManager()
{
   UE_LOG(LogTemp, Warning, TEXT("SpawnManager::SpawnManager() Called."));

   // build some lights
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

   World->SpawnActor<AMyVolume>();


   const FTransform ObjectTransform{
      FRotator(),
      FVector(),
      FVector(10.0f, 10.0f, 10.0f)
   };

   auto NewActorCreated = Cast<ANavMeshBoundsVolume>(
      GEditor->AddActor(CurrentLevel,
                        ANavMeshBoundsVolume::StaticClass(),
                        ObjectTransform, true,
                        RF_Public | RF_Standalone | RF_Transactional));

   NewActorCreated->SetActorLabel(TEXT("NavMesh"));
   NewActorCreated->SetActorRelativeLocation(FVector());
   NewActorCreated->SetActorRelativeScale3D(ObjectTransform.GetScale3D());


   UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
   NavSys->OnNavigationBoundsUpdated(NewActorCreated);



   UCubeBuilder* CubeBuilder = Cast<UCubeBuilder>(GEditor->FindBrushBuilder(UCubeBuilder::StaticClass()));
   CubeBuilder->X = 1000;
   CubeBuilder->Y = 1000;
   CubeBuilder->Z = 200;


   //ABrush* Brush = nullptr;
   bool bResult = CubeBuilder->Build(World);

   NewActorCreated->BrushBuilder = CubeBuilder;

   //NewActorCreated->Brush->BuildBound();

   //auto C = NewActorCreated->GetBrushComponent();
   //auto A = NewActorCreated->GetBounds();

   // Refresh editor
   //GEditor->EditorUpdateComponents();
   World->UpdateWorldComponents(true, false);
   NewActorCreated->RerunConstructionScripts();
   GLevelEditorModeTools().MapChangeNotify();

}
