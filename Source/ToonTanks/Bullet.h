// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"

#include "Bullet.generated.h"

class UParticleSystemComponent;
//class USphereComponent;

UCLASS()
class TOONTANKS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* BulletMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particule")
	UParticleSystemComponent* ProjectileParticle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Particule")
	UParticleSystemComponent* ExplosionParticle;

	UPROPERTY(VisibleDefaultsOnly, Category = "Collider")
	USphereComponent* CollisionComponent;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AActor* OwnerActor;
	UWorld* World;
	int BulletDamage = 10;
	float ImpulsePower = 1000.f;



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetOwnerActor(AActor* Actor) { OwnerActor = Actor; }

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBulletDamage(int Damage) { BulletDamage = Damage; }

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBulletImpulsion(float Impulse) { ImpulsePower = Impulse; }

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetupBulletParams(AActor* Actor, int Damage, float Impulse);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

};
