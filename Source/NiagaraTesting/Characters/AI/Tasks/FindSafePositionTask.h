// Personal Project made by Marc Meijering, if code is taken from others it will be specified in the same file.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FindSafePositionTask.generated.h"

UCLASS()
class NIAGARATESTING_API UFindSafePositionTask : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UFindSafePositionTask();

private:
	const int TOTAL_TRIES = 10;

	void InitializeFromAsset(UBehaviorTree& Asset) override;

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float AvoidDistance = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float SearchDistance = 500.0f;

	UPROPERTY(EditAnywhere, Category = Blackboard, meta = (AllowPrivateAccess = "true"))
		FBlackboardKeySelector TargetPositionKey;
};
