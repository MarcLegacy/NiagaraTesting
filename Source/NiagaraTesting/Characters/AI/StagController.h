// Personal Project made by Marc Meijering, if code is taken from others it will be specified in the same file.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "StagController.generated.h"

UCLASS()
class NIAGARATESTING_API AStagController : public AAIController
{
	GENERATED_BODY()

public:
	AStagController();

    FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComponent; }

private:
    void BeginPlay() override;
    void Tick(float DeltaSeconds) override;
    void OnPossess(APawn* InPawn) override;

    UPROPERTY()
        UBlackboardComponent* BlackboardComponent = nullptr;

};
