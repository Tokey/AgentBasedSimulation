// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidActor.h"

#include "Camera/CameraComponent.h"

// Sets default values
ABoidActor::ABoidActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoidMovement = CreateDefaultSubobject<UFloatingPawnMovement>("FloatingPawnMovement");
	BoidMovement->Velocity = FVector(100,10,0);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	/*Camera = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	Camera->SetRelativeLocation(FVector(-500.f,0.f,0.f));
	Camera->SetupAttachment(Mesh);*/
	
}

// Called when the game starts or when spawned
void ABoidActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoidActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*FVector forward = GetActorForwardVector();
	SetActorLocation( GetActorLocation() + forward * 10 );*/

	//BoidMovement->AddInputVector(GetActorForwardVector()*20);

	//UE_LOG(LogTemp, Warning, TEXT("HELLO"));
}