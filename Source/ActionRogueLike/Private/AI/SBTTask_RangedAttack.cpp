// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_RangedAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type USBTTask_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();

	if (ensure(MyController))
	{
		// Get Pawn Muzzle Location
		ACharacter* MyPawn = Cast<ACharacter>(MyController);
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		FVector MuzzleLocation = MyPawn->GetMesh()->GetSocketLocation("Muzzle_01");
		// Get Direction from Muzzle to Target
		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;

		// Set the Direction to Spawned Particles.
		FTransform SpawnTM = FTransform(Direction.Rotation(), MuzzleLocation);
		//Spawn Particle
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParameters);
	}
	

	return EBTNodeResult::Type();
}
