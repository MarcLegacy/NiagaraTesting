// Personal Project made by Marc Meijering, if code is taken from others it will be specified in the same file.


#include "StagController.h"

#include "Stag.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraTesting/NiagaraTestingCharacter.h"
#include "NiagaraTesting/Utility/Logger.h"

AStagController::AStagController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AStagController::BeginPlay()
{
    Super::BeginPlay();

    if (const AStag* Stag = GetPawn<AStag>(); FLogger::CheckAndLogIsValidPtr(Stag, __FUNCTION__) && FLogger::CheckAndLogIsValidPtr(Stag->GetBehaviorTree(), __FUNCTION__))
    {
        UseBlackboard(Stag->GetBehaviorTree()->BlackboardAsset, BlackboardComponent);
    }
}

void AStagController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    const AStag* Stag = GetPawn<AStag>();
    if (!FLogger::CheckAndLogIsValidPtr(Stag, __FUNCTION__)) return;

    const ANiagaraTestingCharacter* PlayerCharacter = Cast<ANiagaraTestingCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (!FLogger::CheckAndLogIsValidPtr(PlayerCharacter, __FUNCTION__)) return;

    BlackboardComponent->SetValueAsBool("IsPlayerInRange", Stag->GetDistanceTo(PlayerCharacter) < Stag->GetFleeDistance());
}

void AStagController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (const AStag* Stag = GetPawn<AStag>(); FLogger::CheckAndLogIsValidPtr(Stag, __FUNCTION__))
    {
        RunBehaviorTree(Stag->GetBehaviorTree());
    }
}
