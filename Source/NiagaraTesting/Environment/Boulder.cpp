// Personal Project made by Marc Meijering, if code is taken from others it will be specified in the same file.


#include "Boulder.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraTesting/Utility/Logger.h"

ABoulder::ABoulder()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(Root);
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Ignore);
}

void ABoulder::PickUpBoulder()
{
	if (FLogger::CheckAndLogIsValidPtr(NiagaraSystem, __FUNCTION__))
	{
		NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSystem, GetActorLocation());
	    NiagaraComponent->SetNiagaraVariablePosition("PlayerPosition", GetActorLocation());
		if (!Destroy())
		{
			SetActorLocation(FVector(0.0f, 0.0f, -500.0f));
		}
	}
}

void ABoulder::BeginPlay()
{
	FLogger::CheckAndLogIsPropertySet(this, NiagaraSystem, GET_MEMBER_NAME_CHECKED(ABoulder, NiagaraSystem));
}





