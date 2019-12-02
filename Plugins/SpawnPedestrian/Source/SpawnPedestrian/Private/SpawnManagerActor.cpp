// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManagerActor.h"
#include "Kismet/GameplayStatics.h"
#include "PedestrianCharacter.h"

ASpawnManagerActor::ASpawnManagerActor()
{
   PrimaryActorTick.bCanEverTick = true;

   // Initialize this actor
   // 
   TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Render"));
   TextRenderComponent->Text = FText::FromString("Spawn Manager");

   SetActorLocation(FVector::ZeroVector);
}

void ASpawnManagerActor::SpawnNextSplineCharacter()
{
   float CurrentDistance{};
   int SplineCharacterIndex{};

   // Do this on each spline
   // 
   for (const auto& Ref : SplineRef)
   {
      ASpline* CurrentSpline = Ref;

      const float Length = CurrentSpline->SplineComponent->GetSplineLength();
      const float Num = static_cast<float>(CurrentSpline->NumberOfCharacters);

      const float SplineDivision = Length / Num;

      for (auto i = 0; i < Num; ++i)
      {
         // Determine spawn location
         // 
         auto NewLocation = CurrentSpline->SplineComponent->GetLocationAtDistanceAlongSpline(
            CurrentDistance, ESplineCoordinateSpace::World);

         auto NewRotation = CurrentSpline->SplineComponent->GetRotationAtDistanceAlongSpline(
            CurrentDistance, ESplineCoordinateSpace::World);

         auto a = CurrentSpline->SpawnableSplineCharacters[SplineCharacterIndex];

         //GetWorld()->SpawnActor(, FTransform(NewRotation, NewLocation));
         // APedestrianCharacter::StaticClass()
         auto Pedestrian = GetWorld()->SpawnActor<APedestrianCharacter>(NewLocation, NewRotation);

         // Initialize the spawned actor
         // 
         Pedestrian->SplineRef = CurrentSpline;
         Pedestrian->DistanceAloneSpline = CurrentDistance;
         Pedestrian->SpawnDefaultController();

         // Update distance alone the spline
         //
         CurrentDistance += SplineDivision;

         // Has Reached End of the array
         // 
         if (SplineCharacterIndex >= CurrentSpline->SpawnableSplineCharacters.Num() - 1)
         {
            SplineCharacterIndex = 0;
         }
         else
         {
            ++SplineCharacterIndex;
         }
      }

      CurrentDistance = 0;
   }
}

void ASpawnManagerActor::BeginPlay()
{
   Super::BeginPlay();

   TArray<AActor*> FoundActors;
   UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpline::StaticClass(), FoundActors);

   for (auto TActor : FoundActors)
   {
      ASpline* Spline = Cast<ASpline>(TActor);

      if (Spline != nullptr)
      {
         SplineRef.Add(Spline);
      }
   }
}

void ASpawnManagerActor::Tick(const float DeltaTime)
{
   Super::Tick(DeltaTime);
}

void ASpawnManagerActor::InitializeDebugScene()
{
   // Initialize Debug splines
   //
   auto Spline = GetWorld()->SpawnActor<ASpline>();

   Spline->NumberOfCharacters = 4;

   for (int i = 0; i < 8; ++i)
   {
      Spline->SplineComponent->AddSplineLocalPoint(FVector{i * 100.0f, i * 100.0f, 0});
   }

   SplineRef.Add(Spline);
}
