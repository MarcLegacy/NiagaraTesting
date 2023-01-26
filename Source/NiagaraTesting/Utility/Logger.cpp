// Fill out your copyright notice in the Description page of Project Settings.

#include "Logger.h"

void FLogger::LogMessage(const FString& Message, const bool bToScreen, const float DisplayTime)
{
    if (bToScreen)
    {
        GEngine->AddOnScreenDebugMessage(DEFAULT_SLOT, DisplayTime, FColor::White, Message);
    }

    UE_LOG(LogTemp, Display, TEXT("%s"), *Message);
}

void FLogger::LogWarning(const FString& Message, const bool bToScreen, const float DisplayTime)
{
    if (bToScreen)
    {
        GEngine->AddOnScreenDebugMessage(DEFAULT_SLOT, DisplayTime, FColor::Yellow, Message);
    }

    UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
}

void FLogger::LogError(const FString& Message, const bool bToScreen, const float DisplayTime)
{
    if (bToScreen)
    {
        GEngine->AddOnScreenDebugMessage(DEFAULT_SLOT, DisplayTime, FColor::Red, Message);
    }

    UE_LOG(LogTemp, Error, TEXT("%s"), *Message);
}

void FLogger::LogFatal(const FString& Message, const bool bToScreen, const float DisplayTime)
{
    if (bToScreen)
    {
        GEngine->AddOnScreenDebugMessage(DEFAULT_SLOT, DisplayTime, FColor::Red, Message);
    }

    UE_LOG(LogTemp, Fatal, TEXT("%s"), *Message);
}

void FLogger::LogPropertyNotSet(const AActor* CurrentActor, const FName& PropertyName, const bool bToScreen,
    const float DisplayTime)
{
    if (CheckAndLogIsValidPtr(CurrentActor, __FUNCTION__))
    {
        LogWarning(CurrentActor->GetActorNameOrLabel() + ": " + PropertyName.ToString() + " is not set!", bToScreen, DisplayTime);
    }
}


bool FLogger::CheckAndLogIsPropertySet(const AActor* CurrentActor, const UObject* Property, const FName& PropertyName,
    const bool bToScreen, const float DisplayTime)
{
    if (Property == nullptr)
    {
        LogPropertyNotSet(CurrentActor, PropertyName, bToScreen, DisplayTime);
        return false;
    }

    return true;
}
