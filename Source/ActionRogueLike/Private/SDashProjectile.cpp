// Fill out your copyright notice in the Description page of Project Settings.


#include "SDashProjectile.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ASDashProjectile::ASDashProjectile()
{
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;

	MoveComp->InitialSpeed = 6000.f;
}

void ASDashProjectile::BeginPlay()
{
	Super::BeginPlay();
	// set timer when spawned
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate,this, &ASDashProjectile::Explode_Implementation, DetonateDelay);
}

void ASDashProjectile::Explode_Implementation()
{
	// clear time if we hit
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);

	// regular explode
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(),GetActorRotation());

	EffectComp->DeactivateSystem();

	MoveComp->StopMovementImmediately();
	SetActorEnableCollision(false);


	//
	FTimerHandle TimerHandle_DelayedTeleport;

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport,this, &ASDashProjectile::TeleportInstigator, TeleportDelay);
	// not calling super becuase don't want to destroy

}

void ASDashProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if(ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(),ActorToTeleport->GetActorRotation());
	}
}


