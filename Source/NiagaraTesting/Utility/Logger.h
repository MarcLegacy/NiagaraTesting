// Personal Project made by Marc Meijering, if code is taken from others it will be specified in the same file.

#pragma once

#include "CoreMinimal.h"

class NIAGARATESTING_API FLogger
{
public:
	FLogger() = default;
	~FLogger() = default;

	static void LogMessage(const FString& Message, const bool bToScreen = true, const float DisplayTime = STANDARD_DISPLAY_TIME);
	static void LogWarning(const FString& Message, const bool bToScreen = true, const float DisplayTime = STANDARD_DISPLAY_TIME);
	static void LogError(const FString& Message, const bool bToScreen = true, const float DisplayTime = STANDARD_DISPLAY_TIME);
	static void LogFatal(const FString& Message, const bool bToScreen = true, const float DisplayTime = STANDARD_DISPLAY_TIME);

	   /**
		* @brief
		* @param CurrentActor: pass in 'this' to get the Actor.
		* @param PropertyName: pass in 'GET_MEMBER_NAME_CHECKED(ClassName, MemberName) to get the name of the property.
		*/
	static void LogPropertyNotSet(const AActor* CurrentActor, const FName& PropertyName, const bool bToScreen = true, const float DisplayTime = STANDARD_DISPLAY_TIME);

	template <typename T>
	static void LogNullptr(const FString& FunctionName, const bool bToScreen = true, const float DisplayTime = STANDARD_DISPLAY_TIME);

	 /**
	  * @brief
	  * @param CurrentActor: pass in 'this' to get the Actor.
	  * @param Property: property to check.
	  * @param PropertyName: Pass in 'GET_MEMBER_NAME_CHECKED(ClassName, MemberName) to get the name of the property.
	  */
	static bool CheckAndLogIsPropertySet(const AActor* CurrentActor, const UObject* Property, const FName& PropertyName, const bool bToScreen = true, const float DisplayTime = STANDARD_DISPLAY_TIME);

	template <typename T>
	static bool CheckAndLogIsValidPtr(const T* ObjectToCheck, const FString& FunctionName, const bool bToScreen = true, const float DisplayTime = STANDARD_DISPLAY_TIME);

private:
	// 'static' is needed because the variable is used in static functions.
	// 'constexpr' is added so that the variable is evaluated at compile-time.
	static constexpr uint64 DEFAULT_SLOT = -1;
	static constexpr float STANDARD_DISPLAY_TIME = 5.0f;
};

template <typename T>
void FLogger::LogNullptr(const FString& FunctionName, const bool bToScreen, const float DisplayTime)
{
	if (FunctionName == "")
	{
		LogError(T::StaticClass()->GetName() + " is a nullptr!", bToScreen, DisplayTime);
	}
	else
	{
		LogError(FunctionName + ": " + T::StaticClass()->GetName() + " is a nullptr!", bToScreen, DisplayTime);
	}
}

template <typename T>
bool FLogger::CheckAndLogIsValidPtr(const T* ObjectToCheck, const FString& FunctionName, const bool bToScreen,
	const float DisplayTime)
{
	if (ObjectToCheck == nullptr)
	{
		LogNullptr<T>(FunctionName, bToScreen, DisplayTime);
		return false;
	}

	return true;
}
