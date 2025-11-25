// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class UParticleSystemComponent;

UCLASS()
class TOONTANKS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	float Speed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	UStaticMeshComponent* BulletMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mesh")
	UParticleSystemComponent* ProjectileParticle;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AActor* OwnerActor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetOwnerActor(AActor* Actor) { OwnerActor = Actor; }

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
