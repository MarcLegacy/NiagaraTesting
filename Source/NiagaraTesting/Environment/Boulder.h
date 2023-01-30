// Personal Project made by Marc Meijering, if code is taken from others it will be specified in the same file.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boulder.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;
UCLASS()
class NIAGARATESTING_API ABoulder : public AActor
{
	GENERATED_BODY()
	
public:	
	ABoulder();

	FORCEINLINE USceneComponent* GetRoot() const { return Root; }
	FORCEINLINE UStaticMeshComponent* GetStaticMeshComponent() const { return StaticMeshComponent; }
	FORCEINLINE UNiagaraSystem* GetNiagaraSystem() const { return NiagaraSystem; }
	FORCEINLINE UNiagaraComponent* GetNiagaraComponent() const { return NiagaraComponent; }

	UFUNCTION(BlueprintCallable)
		void PickUpBoulder();

private:
	void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* StaticMeshComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UNiagaraSystem* NiagaraSystem = nullptr;

	UPROPERTY()
		UNiagaraComponent* NiagaraComponent = nullptr;
};
