#include "SpawnManager.h"

#include "Atmosphere/AtmosphericFog.h"
#include "Engine/SkyLight.h"
#include "Components/SkyLightComponent.h"

#include "EngineUtils.h"
#include "Engine/StaticMeshActor.h"
#include "Builders/CubeBuilder.h"
#include "EditorModeManager.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem.h"
#include "IPluginManager.h"

#define DEBUG_PRINT(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

FSpawnManager::FSpawnManager()
{
   UE_LOG(LogTemp, Warning, TEXT("SpawnManager::SpawnManager() Called."));

   // Load Assets
   auto a = InContent("BasePedestrian/Blueprints/BP_PedestrianCharacter.uasset");

   //static ConstructorHelpers::FObjectFinder<UClass> PedestrianCharacterFinder(ToCStr(a));
   //PedestrianCharacterBP = PedestrianCharacterFinder.Object;

   // Load Settings,
   // TODO: Get data from Sumo2Unreal here.
   //
   NavMeshOrigin = FVector::ZeroVector;
   NavMeshExtend = FVector(4096.0f, 4096.0f, 256.0f);
}

void FSpawnManager::InitializeMap() const
{
   const FVector Location = FVector(0.0f, 0.0f, 2000.0f);
   const FVector LightLocation = FVector(0.0f, 0.0f, 100000.0f);

   World->SpawnActor<AAtmosphericFog>(Location, FRotator::ZeroRotator);

   const ASkyLight* Skylight = World->SpawnActor<ASkyLight>(LightLocation, FRotator::ZeroRotator);
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

void FSpawnManager::InitializeNavMesh() const
{
   // Cube Additive Brush
   UCubeBuilder* CubeAdditiveBrushBuilder = Cast<UCubeBuilder>(
      GEditor->FindBrushBuilder(UCubeBuilder::StaticClass()));

   CubeAdditiveBrushBuilder->X = NavMeshExtend.X;
   CubeAdditiveBrushBuilder->Y = NavMeshExtend.Y;
   CubeAdditiveBrushBuilder->Z = NavMeshExtend.Z;
   CubeAdditiveBrushBuilder->Build(World);

   GEditor->Exec(World, TEXT("BRUSH MOVETO X=0 Y=0 Z=0"));
   GEditor->Exec(World, TEXT("BRUSH ADDVOLUME CLASS=NavMeshBoundsVolume"));

   GLevelEditorModeTools().MapChangeNotify();
}

void FSpawnManager::InitializePedestrian() const
{
   // Currently spawning one pedestrian at random position.
   // TODO: Spawn more
   const FVector NewLocation = UKismetMathLibrary::RandomPointInBoundingBox(
      NavMeshOrigin, NavMeshExtend);

   //World->SpawnActor<APedestrianCharacter>(PedestrianCharacterBP, NewLocation, FRotator::ZeroRotator);
}

FString FSpawnManager::InContent(const FString& RelativePath)
{
   static FString ContentDir = IPluginManager::Get().FindPlugin(TEXT("SpawnPedestrian"))->GetContentDir();

   return ContentDir / RelativePath;
}
