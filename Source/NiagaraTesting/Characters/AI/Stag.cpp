// Personal Project made by Marc Meijering, if code is taken from others it will be specified in the same file.


#include "Stag.h"

#include "BehaviorTree/BehaviorTree.h"
#include "NiagaraTesting/Utility/Logger.h"

AStag::AStag()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AStag::BeginPlay()
{
	Super::BeginPlay();

	FLogger::CheckAndLogIsPropertySet(this, BehaviorTree, GET_MEMBER_NAME_CHECKED(AStag, BehaviorTree));
}


