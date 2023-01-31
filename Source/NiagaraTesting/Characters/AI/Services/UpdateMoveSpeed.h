// Personal Project made by Marc Meijering, if code is taken from others it will be specified in the same file.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "UpdateMoveSpeed.generated.h"


UCLASS()
class NIAGARATESTING_API UUpdateMoveSpeed : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UUpdateMoveSpeed();
	void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float MoveSpeed = 300.0f;
};
