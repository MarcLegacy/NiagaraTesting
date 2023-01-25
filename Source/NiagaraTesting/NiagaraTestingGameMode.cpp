// Copyright Epic Games, Inc. All Rights Reserved.

#include "NiagaraTestingGameMode.h"
#include "NiagaraTestingCharacter.h"
#include "UObject/ConstructorHelpers.h"

ANiagaraTestingGameMode::ANiagaraTestingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
