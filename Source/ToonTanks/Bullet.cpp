// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h" 
#include "IDamageable.h"
#include "Bullet.h"

// Sets default values
ABullet::ABullet()
{
	// Use a sphere as a simple collision representation.
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	//Set the sphere's collision profile name to "Projectile".
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	// Event called when component hits something.
	CollisionComponent->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	CollisionComponent->SetNotifyRigidBodyCollision(true);
	// Set the sphere's collision radius.
	CollisionComponent->InitSphereRadius(30.0f);

	CollisionComponent->SetSimulatePhysics(true);
	CollisionComponent->SetEnableGravity(true);

	RootComponent = CollisionComponent;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Crée le composant Static Mesh
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	BulletMesh->SetupAttachment(RootComponent);

	ProjectileParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ProjectileParticle"));
	ProjectileParticle->SetupAttachment(RootComponent);

	ExplosionParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionParticle"));
	ExplosionParticle->SetupAttachment(RootComponent);

	World = GetWorld();
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->AddImpulse(GetActorForwardVector() * ImpulsePower, NAME_None, true);
	ExplosionParticle->DeactivateImmediate();

}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ProjectileParticle->HasCompleted() && ExplosionParticle->HasCompleted())
	{
		Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Destroy"));
	}
}

void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != OwnerActor)
	{
		CollisionComponent->DestroyComponent();
		BulletMesh->DestroyComponent();

		ProjectileParticle->Deactivate();
		ExplosionParticle->ActivateSystem();

		if (OtherActor && OtherActor != this)
		{
			if (OtherActor->Implements<UIDamageable>())
			{
				IIDamageable::Execute_TakeDamage(OtherActor, BulletDamage);
			}
		}
	}
	
}

void ABullet::SetupBulletParams(AActor* Actor, int Damage, float Impulse)
{
	OwnerActor = Actor;
	BulletDamage = Damage;
	ImpulsePower = Impulse;
}