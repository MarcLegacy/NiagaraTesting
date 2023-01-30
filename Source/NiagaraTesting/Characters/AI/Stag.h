// Personal Project made by Marc Meijering, if code is taken from others it will be specified in the same file.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Stag.generated.h"

class UBehaviorTree;
UCLASS()
class NIAGARATESTING_API AStag : public ACharacter
{
	GENERATED_BODY()

public:
	AStag();

	FORCEINLINE UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

private:
	void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UBehaviorTree* BehaviorTree = nullptr;

};
