// Personal Project made by Marc Meijering, if code is taken from others it will be specified in the same file.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FindRandomPosition.generated.h"

UCLASS()
class NIAGARATESTING_API UFindRandomPosition : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UFindRandomPosition();

private:
	void InitializeFromAsset(UBehaviorTree& Asset) override;

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float SearchRadius = 5.0f;

	UPROPERTY(EditAnywhere, Category = Blackboard, meta = (AllowPrivateAccess = "true"))
		FBlackboardKeySelector RandomPositionKey;
};
	

