// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ASAICharacter::ASAICharacter()
{
 	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

}



void ASAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// bind to event
	PawnSensingComp->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSeen);
}

void ASAICharacter::OnPawnSeen(APawn* pawn)
{
	AAIController* AC = Cast<AAIController>(GetController());

	if(AC)
	{
		UBlackboardComponent* BC = AC->GetBlackboardComponent();

		BC->SetValueAsObject("TargetActor", pawn);

		DrawDebugString(GetWorld(),GetActorLocation(),"PlayerSpotted",nullptr);

	}

}

// Called to bind functionality to input
void ASAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

