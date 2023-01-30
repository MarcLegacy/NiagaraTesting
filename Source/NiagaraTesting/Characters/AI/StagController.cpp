// Personal Project made by Marc Meijering, if code is taken from others it will be specified in the same file.


#include "StagController.h"

#include "Stag.h"
#include "BehaviorTree/BehaviorTree.h"
#include "NiagaraTesting/Utility/Logger.h"

AStagController::AStagController()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AStagController::BeginPlay()
{
    Super::BeginPlay();

    if (const AStag* Stag = GetPawn<AStag>(); FLogger::CheckAndLogIsValidPtr(Stag, __FUNCTION__) && FLogger::CheckAndLogIsValidPtr(Stag->GetBehaviorTree(), __FUNCTION__))
    {
        UseBlackboard(Stag->GetBehaviorTree()->BlackboardAsset, BlackboardComponent);
    }
}

void AStagController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (const AStag* Stag = GetPawn<AStag>(); FLogger::CheckAndLogIsValidPtr(Stag, __FUNCTION__))
    {
        RunBehaviorTree(Stag->GetBehaviorTree());
    }
}
