// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "AnalyticsBlueprintLibraryPrivatePCH.h"

DEFINE_LOG_CATEGORY_STATIC(LogAnalyticsBPLib, Display, All);

/**
 * Converts the UObject accessible array into the native only analytics array type
 */
static inline TArray<FAnalyticsEventAttribute> ConvertAttrs(const TArray<FAnalyticsEventAttr>& Attributes)
{
	TArray<FAnalyticsEventAttribute> Converted;
	Converted.AddZeroed(Attributes.Num());
	for (int32 Index = 0; Index < Attributes.Num(); Index++)
	{
		Converted[Index].AttrName = Attributes[Index].Name;
		Converted[Index].AttrValue = Attributes[Index].Value;
	}
	return Converted;
}


UAnalyticsBlueprintLibrary::UAnalyticsBlueprintLibrary(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
}

bool UAnalyticsBlueprintLibrary::StartSession()
{
	TSharedPtr<IAnalyticsProvider> Provider = FAnalytics::Get().GetDefaultConfiguredProvider();
	if (Provider.IsValid())
	{
		return Provider->StartSession();
	}
	else
	{
		UE_LOG(LogAnalyticsBPLib, Warning, TEXT("StartSession: Failed to get the default analytics provider. Double check your [Analytics] configuration in your INI"));
	}
	return false;
}

bool UAnalyticsBlueprintLibrary::StartSessionWithAttributes(const TArray<FAnalyticsEventAttr>& Attributes)
{
	TSharedPtr<IAnalyticsProvider> Provider = FAnalytics::Get().GetDefaultConfiguredProvider();
	if (Provider.IsValid())
	{
		return Provider->StartSession(ConvertAttrs(Attributes));
	}
	else
	{
		UE_LOG(LogAnalyticsBPLib, Warning, TEXT("StartSessionWithAttributes: Failed to get the default analytics provider. Double check your [Analytics] configuration in your INI"));
	}
	return false;
}

void UAnalyticsBlueprintLibrary::EndSession()
{
	TSharedPtr<IAnalyticsProvider> Provider = FAnalytics::Get().GetDefaultConfiguredProvider();
	if (Provider.IsValid())
	{
		Provider->EndSession();
	}
	else
	{
		UE_LOG(LogAnalyticsBPLib, Warning, TEXT("EndSession: Failed to get the default analytics provider. Double check your [Analytics] configuration in your INI"));
	}
}

void UAnalyticsBlueprintLibrary::FlushEvents()
{
	TSharedPtr<IAnalyticsProvider> Provider = FAnalytics::Get().GetDefaultConfiguredProvider();
	if (Provider.IsValid())
	{
		Provider->FlushEvents();
	}
	else
	{
		UE_LOG(LogAnalyticsBPLib, Warning, TEXT("FlushEvents: Failed to get the default analytics provider. Double check your [Analytics] configuration in your INI"));
	}
}

void UAnalyticsBlueprintLibrary::RecordEvent(const FString& EventName)
{
	TSharedPtr<IAnalyticsProvider> Provider = FAnalytics::Get().GetDefaultConfiguredProvider();
	if (Provider.IsValid())
	{
		Provider->RecordEvent(EventName);
	}
	else
	{
		static bool bHasLogged = false;
		if (!bHasLogged)
		{
			UE_LOG(LogAnalyticsBPLib, Warning, TEXT("RecordEvent: Failed to get the default analytics provider. Double check your [Analytics] configuration in your INI"));
		}
	}
}

void UAnalyticsBlueprintLibrary::RecordEventWithAttribute(const FString& EventName, const FString& AttributeName, const FString& AttributeValue)
{
	TSharedPtr<IAnalyticsProvider> Provider = FAnalytics::Get().GetDefaultConfiguredProvider();
	if (Provider.IsValid())
	{
		FAnalyticsEventAttribute Attribute(AttributeName, AttributeValue);
		Provider->RecordEvent(EventName, Attribute);
	}
	else
	{
		static bool bHasLogged = false;
		if (!bHasLogged)
		{
			UE_LOG(LogAnalyticsBPLib, Warning, TEXT("RecordEventWithAttribute: Failed to get the default analytics provider. Double check your [Analytics] configuration in your INI"));
		}
	}
}

void UAnalyticsBlueprintLibrary::RecordEventWithAttributes(const FString& EventName, const TArray<FAnalyticsEventAttr>& Attributes)
{
	TSharedPtr<IAnalyticsProvider> Provider = FAnalytics::Get().GetDefaultConfiguredProvider();
	if (Provider.IsValid())
	{
		Provider->RecordEvent(EventName, ConvertAttrs(Attributes));
	}
	else
	{
		static bool bHasLogged = false;
		if (!bHasLogged)
		{
			UE_LOG(LogAnalyticsBPLib, Warning, TEXT("RecordEventWithAttributes: Failed to get the default analytics provider. Double check your [Analytics] configuration in your INI"));
		}
	}
}

void UAnalyticsBlueprintLibrary::RecordItemPurchase(const FString& ItemId, const FString& Currency, int32 PerItemCost, int32 ItemQuantity)
{
	TSharedPtr<IAnalyticsProvider> Provider = FAnalytics::Get().GetDefaultConfiguredProvider();
	if (Provider.IsValid())
	{
		Provider->RecordItemPurchase(ItemId, Currency, PerItemCost, ItemQuantity);
	}
	else
	{
		static bool bHasLogged = false;
		if (!bHasLogged)
		{
			UE_LOG(LogAnalyticsBPLib, Warning, TEXT("RecordEventWithAttributes: Failed to get the default analytics provider. Double check your [Analytics] configuration in your INI"));
		}
	}
}

void UAnalyticsBlueprintLibrary::RecordCurrencyPurchase(const FString& GameCurrencyType, int32 GameCurrencyAmount, const FString& RealCurrencyType, float RealMoneyCost, const FString& PaymentProvider)
{
	TSharedPtr<IAnalyticsProvider> Provider = FAnalytics::Get().GetDefaultConfiguredProvider();
	if (Provider.IsValid())
	{
		Provider->RecordCurrencyPurchase(GameCurrencyType, GameCurrencyAmount, RealCurrencyType, RealMoneyCost, PaymentProvider);
	}
	else
	{
		UE_LOG(LogAnalyticsBPLib, Warning, TEXT("RecordCurrencyPurchase: Failed to get the default analytics provider. Double check your [Analytics] configuration in your INI"));
	}
}

void UAnalyticsBlueprintLibrary::RecordCurrencyGiven(const FString& GameCurrencyType, int32 GameCurrencyAmount)
{
	TSharedPtr<IAnalyticsProvider> Provider = FAnalytics::Get().GetDefaultConfiguredProvider();
	if (Provider.IsValid())
	{
		Provider->RecordCurrencyGiven(GameCurrencyType, GameCurrencyAmount);
	}
	else
	{
		UE_LOG(LogAnalyticsBPLib, Warning, TEXT("RecordCurrencyGiven: Failed to get the default analytics provider. Double check your [Analytics] configuration in your INI"));
	}
}

FString UAnalyticsBlueprintLibrary::GetSessionId()
{
	TSharedPtr<IAnalyticsProvider> Provider = FAnalytics::Get().GetDefaultConfiguredProvider();
	if (Provider.IsValid())
	{
		return Provider->GetSessionID();
	}
	return FString();
}

void UAnalyticsBlueprintLibrary::SetSessionId(const FString& SessionId)
{
	TSharedPtr<IAnalyticsProvider> Provider = FAnalytics::Get().GetDefaultConfiguredProvider();
	if (Provider.IsValid())
	{
		Provider->SetSessionID(SessionId);
	}
	else
	{
		UE_LOG(LogAnalyticsBPLib, Warning, TEXT("SetSessionId: Failed to get the default analytics provider. Double check your [Analytics] configuration in your INI"));
	}
}

FString UAnalyticsBlueprintLibrary::GetUserId()
{
	TSharedPtr<IAnalyticsProvider> Provider = FAnalytics::Get().GetDefaultConfiguredProvider();
	if (Provider.IsValid())
	{
		return Provider->GetUserID();
	}
	return FString();
}

void UAnalyticsBlueprintLibrary::SetUserId(const FString& UserId)
{
	TSharedPtr<IAnalyticsProvider> Provider = FAnalytics::Get().GetDefaultConfiguredProvider();
	if (Provider.IsValid())
	{
		Provider->SetUserID(UserId);
	}
	else
	{
		UE_LOG(LogAnalyticsBPLib, Warning, TEXT("SetUserId: Failed to get the default analytics provider. Double check your [Analytics] configuration in your INI"));
	}
}

FAnalyticsEventAttr UAnalyticsBlueprintLibrary::MakeEventAttribute(const FString& AttributeName, const FString& AttributeValue)
{
	FAnalyticsEventAttr EventAttr;
	EventAttr.Name = AttributeName;
	EventAttr.Value = AttributeValue;
	return EventAttr;
}