// Personal Project made by Marc Meijering, if code is taken from others it will be specified in the same file.


#include "UpdateMoveSpeed.h"

#include "AIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NiagaraTesting/Utility/Logger.h"

UUpdateMoveSpeed::UUpdateMoveSpeed()
{
    NodeName = TEXT("UpdateMoveSpeed");
    bNotifyBecomeRelevant = true;
}

void UUpdateMoveSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::OnBecomeRelevant(OwnerComp, NodeMemory);

    const ACharacter* Character = OwnerComp.GetAIOwner()->GetPawn<ACharacter>();
    if (!FLogger::CheckAndLogIsValidPtr(Character, __FUNCTION__)) return;

    Character->GetCharacterMovement()->MaxWalkSpeed = MoveSpeed;
}
