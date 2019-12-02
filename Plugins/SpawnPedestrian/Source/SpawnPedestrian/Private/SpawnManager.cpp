#include "SpawnManager.h"

#include "Atmosphere/AtmosphericFog.h"
#include "Engine/SkyLight.h"
#include "Components/SkyLightComponent.h"

#include "EngineUtils.h"
#include "Engine/StaticMeshActor.h"
#include "NavMeshBoundsVolume.h"
#include "Builders/CubeBuilder.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "SpawnManagerActor.h"

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
   UE_LOG(LogTemp, Warning, TEXT("void SpawnManager::InitializeNavMesh() Called."));

   const FActorSpawnParameters SpawnParameters;

   const auto BoundsVolume = World->SpawnActorDeferred<ANavMeshBoundsVolume>(
      ANavMeshBoundsVolume::StaticClass(), FTransform());

   UCubeBuilder* CubeBuilder = Cast<UCubeBuilder>(GEditor->FindBrushBuilder(UCubeBuilder::StaticClass()));
   CubeBuilder->X = 200;
   CubeBuilder->Y = 200;
   CubeBuilder->Z = 200;
   CubeBuilder->Build(World, BoundsVolume);

   const FVector Scale = FVector(10.0f, 10.0f, 10.0f);

   BoundsVolume->SetActorScale3D(Scale);
   BoundsVolume->BrushBuilder = CubeBuilder;

   UGameplayStatics::FinishSpawningActor(BoundsVolume, FTransform());

   BoundsVolume->RebuildNavigationData();

   // Generate Debugging cube
   //
   // FVector Point = UKismetMathLibrary::RandomPointInBoundingBox(FVector::ZeroVector, 100 * Scale);
   const auto Manager = World->SpawnActor<ASpawnManagerActor>();
   Manager->InitializeDebugScene();
}
