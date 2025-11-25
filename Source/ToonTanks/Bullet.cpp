// Fill out your copyright notice in the Description page of Project Settings.

#include "Particles/ParticleSystemComponent.h" 
#include "Bullet.h"

// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Crée le composant Static Mesh
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));

	ProjectileParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileParticle"));

	RootComponent = BulletMesh;

	ProjectileParticle->SetupAttachment(BulletMesh);

	BulletMesh->SetNotifyRigidBodyCollision(true);
	BulletMesh->BodyInstance.SetCollisionProfileName("OverlapAllDynamic");
	BulletMesh->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	BulletMesh->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);
	//BulletMesh->OnComponentHit.AddDynamic(this, &ABullet::OnComponentBeginOverlap);

}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + GetActorForwardVector() * Speed * DeltaTime);
}

void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OwnerActor && OwnerActor != OtherActor)
	{
		Destroy();
	}

	UE_LOG(LogTemp, Warning, TEXT("Hit de fou"));

}

