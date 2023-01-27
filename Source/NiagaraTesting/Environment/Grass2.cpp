// Personal Project made by Marc Meijering, if code is taken from others it will be specified in the same file.

#include "Grass2.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraTesting/Utility/Logger.h"

AGrass2::AGrass2()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(Root);
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(Root);

	SphereCollider->OnComponentBeginOverlap.AddUniqueDynamic(this, &AGrass2::OnComponentBeginOverlap);
}

void AGrass2::SpawnNiagaraSystem()
{
	if (!CanSpawnNiagaraSystem) return;

	const ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	const double Yaw = UKismetMathLibrary::FindLookAtRotation(PlayerCharacter->GetActorLocation(), GetActorLocation()).Yaw;
	const FRotator Rotation = FRotator(0, Yaw, 0);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSystem, GetActorLocation(), Rotation);

	CanSpawnNiagaraSystem = false;
}

void AGrass2::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		SpawnNiagaraSystem();
	}
}

void AGrass2::BeginPlay()
{
	Super::BeginPlay();

	FLogger::CheckAndLogIsPropertySet(this, NiagaraSystem, GET_MEMBER_NAME_CHECKED(AGrass2, NiagaraSystem));
}

