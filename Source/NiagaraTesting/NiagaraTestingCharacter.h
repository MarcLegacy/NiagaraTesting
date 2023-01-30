// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NiagaraTestingCharacter.generated.h"

class AStag;
class UNiagaraComponent;
class UNiagaraSystem;
class ABoulder;

UCLASS(config=Game)
class ANiagaraTestingCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANiagaraTestingCharacter();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
		void PlaceBoulder();

	UFUNCTION(BlueprintCallable)
		void PickUpBoulder();

private:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	void MoveForward(float Value);
	void MoveRight(float Value);

    void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* CameraBoom = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FollowCamera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ABoulder> BoulderClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UNiagaraSystem* NiagaraSystem = nullptr;

	UPROPERTY()
	    UNiagaraComponent* NiagaraComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float InteractDistance = 700.0f;

	UPROPERTY()
		TArray<UNiagaraComponent*> SavedNiagaraComponents = {};
};

