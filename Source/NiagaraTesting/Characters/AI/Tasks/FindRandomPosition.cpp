// Personal Project made by Marc Meijering, if code is taken from others it will be specified in the same file.


#include "FindRandomPosition.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NiagaraTesting/Utility/Logger.h"

UFindRandomPosition::UFindRandomPosition()
{
    NodeName = TEXT("Find Random Position");

    RandomPositionKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UFindRandomPosition, RandomPositionKey));
}

void UFindRandomPosition::InitializeFromAsset(UBehaviorTree& Asset)
{
    Super::InitializeFromAsset(Asset);

    RandomPositionKey.ResolveSelectedKey(*GetBlackboardAsset());
}

EBTNodeResult::Type UFindRandomPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
    if (!FLogger::CheckAndLogIsValidPtr(NavigationSystem, __FUNCTION__)) return EBTNodeResult::Failed;

    FNavLocation NavLocation;

    if (NavigationSystem->GetRandomPointInNavigableRadius(OwnerComp.GetOwner()->GetActorLocation(), SearchRadius, NavLocation))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(RandomPositionKey.SelectedKeyName, NavLocation.Location);
    }

    FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    return EBTNodeResult::Succeeded;
}
