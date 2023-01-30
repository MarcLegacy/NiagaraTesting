// Personal Project made by Marc Meijering, if code is taken from others it will be specified in the same file.


#include "FindSafePositionTask.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraTesting/NiagaraTestingCharacter.h"
#include "NiagaraTesting/Characters/AI/StagController.h"
#include "NiagaraTesting/Utility/Logger.h"

UFindSafePositionTask::UFindSafePositionTask()
{
    NodeName = TEXT("Find Safe Position");

    TargetPositionKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UFindSafePositionTask, TargetPositionKey));
}

void UFindSafePositionTask::InitializeFromAsset(UBehaviorTree& Asset)
{
    Super::InitializeFromAsset(Asset);

    TargetPositionKey.ResolveSelectedKey(*GetBlackboardAsset());
}

EBTNodeResult::Type UFindSafePositionTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const AStagController* Controller = OwnerComp.GetOwner<AStagController>();
    if (!FLogger::CheckAndLogIsValidPtr(Controller, __FUNCTION__)) return EBTNodeResult::Failed;

    const UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
    if (!FLogger::CheckAndLogIsValidPtr(NavigationSystem, __FUNCTION__)) return EBTNodeResult::Failed;

    const ANiagaraTestingCharacter* TargetCharacter = Cast<ANiagaraTestingCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (!FLogger::CheckAndLogIsValidPtr(TargetCharacter, __FUNCTION__)) return EBTNodeResult::Failed;

    FNavLocation NavLocation;
    FVector NewLocation = FVector(0.0f, 0.0f, 0.0f);

    for (int Tries = 0; Tries < TOTAL_TRIES; Tries++)
    {
        if (NavigationSystem->GetRandomPointInNavigableRadius(Controller->GetPawn()->GetActorLocation(), SearchDistance, NavLocation))
        {
            if (UKismetMathLibrary::Vector_Distance(NavLocation, TargetCharacter->GetActorLocation()) > AvoidDistance || Tries == TOTAL_TRIES - 1)
            {
                NewLocation = NavLocation;
                break;
            }
        }
    }

    if (NewLocation == FVector(0.0f, 0.0f, 0.0f))
    {
        FLogger::LogWarning("Invalid location found!");
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetPositionKey.SelectedKeyName, NewLocation);

    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}
