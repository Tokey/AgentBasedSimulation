// Fill out your copyright notice in the Description page of Project Settings.


#include "BoidManager.h"

#include "Kismet/GameplayStatics.h"

ABoidManager::ABoidManager()
{
	PrimaryActorTick.bCanEverTick = true;
}


void ABoidManager::BeginPlay()
{
	InitializeBoids();
}

void ABoidManager::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);
	DeltaTimeGlobal = DeltaTime;
	MoveAllBoidsToNewPosition();
}

void ABoidManager::InitializeBoids()
{
	for(int i=0;i<NumberOfBoids;i++)
	{
		

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		FVector Location  = FVector( FMath::RandRange(0,1000),FMath::RandRange(0,1000),100);
		FRotator Rotation  = FRotator(0,0,0);
		
		GetWorld()->SpawnActor<ABoidActor>(NewBoidClass, Location, Rotation, ActorSpawnParams);
		BoidsToSpawn.Add(NewBoidClass);
	}
	
	//Cast<ABoidActor>(BoidsInLevel[0])->BoidMovement->AddInputVector( BoidsInLevel[0]->GetActorLocation() * 100 );
}

void ABoidManager::MoveAllBoidsToNewPosition()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoidActor::StaticClass(), BoidsInLevel);
	FVector v1,v2,v3,v4;
	for(int i=0; i< BoidsInLevel.Num();i++)
	{
		v1= Rule1AntiFlock * DeltaTimeGlobal * Rule1(Cast<ABoidActor>(BoidsInLevel[i]));
		v2= Rule2AntiFlock * DeltaTimeGlobal * Rule2(Cast<ABoidActor>(BoidsInLevel[i]));
		v3= Rule3AntiFlock * DeltaTimeGlobal * Rule3(Cast<ABoidActor>(BoidsInLevel[i]));
		v4 = Rule4AntiFlock * DeltaTimeGlobal * TendToPlace(Cast<ABoidActor>(BoidsInLevel[i]));
		LimitVelocity(Cast<ABoidActor>(BoidsInLevel[i]));
		UE_LOG(LogTemp, Warning, TEXT("Boid # %d :: v1 : %f %f %f" ),i,v1.X,v1.Y,v1.Z );
		UE_LOG(LogTemp, Warning, TEXT("Boid # %d :: v2 : %f %f %f" ),i,v2.X,v2.Y,v2.Z );
		UE_LOG(LogTemp, Warning, TEXT("Boid # %d :: v3 : %f %f %f" ),i,v3.X,v3.Y,v3.Z );

		
		Cast<ABoidActor>(BoidsInLevel[i])->BoidMovement->Velocity = BoidsInLevel[i]->GetVelocity() + v1 + v2 + v3+v4;
		FVector Loc = BoidsInLevel[i]->GetActorLocation() + BoidsInLevel[i]->GetVelocity();
		UE_LOG(LogTemp, Warning, TEXT("New Loc Boid # %d :: v1 : %f %f %f" ),i,Loc.X,Loc.Y,Loc.Z );
		BoidsInLevel[i]->SetActorLocation(Loc);
	}
}

FVector ABoidManager::Rule1(ABoidActor* Boid)
{
	FVector PCj;
	
	
	for(int i=0; i< BoidsInLevel.Num();i++)
	{
		if(Boid != BoidsInLevel[i])
		{
			PCj = PCj + BoidsInLevel[i]->GetActorLocation();
		}
	}
	PCj = PCj / (NumberOfBoids -1);

	return (PCj - Boid->GetActorLocation())/100;
}

FVector ABoidManager::Rule2(ABoidActor* Boid)
{
	FVector c = FVector(0,0,0);
	for(int i=0; i< BoidsInLevel.Num();i++)
	{
		if(Boid != BoidsInLevel[i])
		{
			if(FVector::Dist(BoidsInLevel[i]->GetActorLocation() , Boid->GetActorLocation()) <100.f)
			{
				c = c - (BoidsInLevel[i]->GetActorLocation() - Boid->GetActorLocation());
			}
		}
	}

	return c;
}

FVector ABoidManager::Rule3(ABoidActor* Boid)
{
	FVector Velocity;
	for(int i=0; i< BoidsInLevel.Num();i++)
	{
		if(Boid != BoidsInLevel[i])
		{
			Velocity  = Velocity + BoidsInLevel[i]->GetVelocity();
		}
	}

	Velocity = Velocity / (NumberOfBoids-1);

	return Velocity-Boid->GetVelocity();
}


FVector ABoidManager::TendToPlace(ABoidActor* Boid)
{
	FVector Place = FVector(0,0,900);
	return (Place - Boid->GetActorLocation())/100;
}

void ABoidManager::LimitVelocity(ABoidActor* Boid)
{
	float vlim = 20;
	FVector v;

	if(Boid->GetVelocity().Size() > vlim)
	{
		Cast<ABoidActor>(Boid)->BoidMovement->Velocity = (Cast<ABoidActor>(Boid)->BoidMovement->Velocity/Boid->GetVelocity().Size() )* vlim;
	}
}

