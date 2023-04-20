// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoidActor.h"

#include "BoidManager.generated.h"

/**
 * 
 */
UCLASS()
class BOIDS_API ABoidManager : public AActor
{

	GENERATED_BODY()
public:
	ABoidManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitializeBoids();
	void MoveAllBoidsToNewPosition();

	FVector Rule1(ABoidActor * Boid);
	FVector Rule2(ABoidActor * Boid);
	FVector Rule3(ABoidActor * Boid);
	FVector TendToPlace(ABoidActor * Boid); //TEND TO PLACE
	void LimitVelocity(ABoidActor * Boid); //TEND TO PLACE

	float DeltaTimeGlobal;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int NumberOfBoids = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Rule1AntiFlock = .3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Rule2AntiFlock = .2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Rule3AntiFlock =.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Rule4AntiFlock = .04f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ABoidActor> NewBoidClass;
	
	TArray <TSubclassOf<class ABoidActor>> BoidsToSpawn;

	
	TArray<AActor*> BoidsInLevel;

};
