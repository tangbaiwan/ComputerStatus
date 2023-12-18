// Copyright Epic Games, Inc. All Rights Reserved.

#include "ComputerStatusBPLibrary.h"
#include "ComputerStatus.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformDriver.h"

#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Runtime/Networking/Public/Networking.h"

UComputerStatusBPLibrary::UComputerStatusBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

FString UComputerStatusBPLibrary::GetLocalIPAddress()
{
	FString IPAddressStr;
	bool canBind = false;
	TSharedPtr<FInternetAddr> LocalAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->GetLocalHostAddr(*GLog, canBind);
	if (LocalAddr.IsValid())
	{
		IPAddressStr = LocalAddr->ToString(false);
	}
	return IPAddressStr;
}

FString UComputerStatusBPLibrary::GetMac()
{
	return "";
}

void UComputerStatusBPLibrary::GetGPUInfo(FString& DeviceDescription, FString& Provider, FString& DriverVersion, FString& DriverDate, FString& RHIName)
{
	FGPUDriverInfo GPUDriverInfo = FPlatformMisc::GetGPUDriverInfo(GRHIAdapterName);

	DeviceDescription = GPUDriverInfo.DeviceDescription;
	Provider = GPUDriverInfo.ProviderName;
	DriverVersion = GPUDriverInfo.UserDriverVersion;
	DriverDate = GPUDriverInfo.DriverDate;
	RHIName = GPUDriverInfo.RHIName;
}

void UComputerStatusBPLibrary::GetCPUInfo(FString& CPUBrand)
{
	CPUBrand = FPlatformMisc::GetCPUBrand();
}

FString UComputerStatusBPLibrary::GetClipboard()
{
	FString Value = TEXT("");
	FPlatformApplicationMisc::ClipboardPaste(Value);
	return Value;
}

void UComputerStatusBPLibrary::GetWindowBounds(bool& Success, int32& X, int32& Y, int32& Width, int32& Height)
{
	Success = false;
	X = 0;
	Y = 0;
	Width = 0;
	Height = 0;

	if (GEngine == nullptr)
	{
		return;
	}

	UGameViewportClient* ViewportClient = GEngine->GameViewport;
	if (ViewportClient == nullptr)
	{
		return;
	}

	TSharedPtr<SWindow> Window = ViewportClient->GetWindow();
	if (!Window.IsValid())
	{
		return;
	}

	FVector2D Position = Window->GetPositionInScreen();
	FVector2D Size = Window->GetSizeInScreen();

	Success = true;
	X = Position.X;
	Y = Position.Y;
	Width = Size.X;
	Height = Size.Y;
}

void UComputerStatusBPLibrary::GetMousePosition(bool& Success, int32& X, int32& Y)
{
	Success = false;
	X = 0;
	Y = 0;

	if (GEngine == nullptr)
	{
		return;
	}

	UGameViewportClient* ViewportClient = GEngine->GameViewport;
	if (ViewportClient == nullptr)
	{
		return;
	}

	FViewport* Viewport = ViewportClient->Viewport;
	if (Viewport == nullptr)
	{
		return;
	}

	int32 MouseX = Viewport->GetMouseX();
	int32 MouseY = Viewport->GetMouseY();
	if ((MouseX < 0) || (MouseY < 0))
	{
		return;
	}

	FIntPoint Size = Viewport->GetSizeXY();
	if ((Size.X <= 0) || (Size.Y <= 0))
	{
		return;
	}
	if ((Size.X < MouseX) || (Size.Y < MouseY))
	{
		return;
	}

	Success = true;
	X = MouseX / static_cast<double>(Size.X);
	Y = MouseY / static_cast<double>(Size.Y);
}

void UComputerStatusBPLibrary::CreateEditorNotification(const FText Message, const E_BXSNotifyCompletionState notifyType /*= E_BXSNotifyCompletionState::None*/,
	const float fadeInDuration /*= 0.5f*/,
	const float expireDuration /*= 1.0f*/,
	const float fadeOutDuration /*= 2.0f*/,
	const bool useThrobber /*= false*/,
	const bool useSuccessFailIcons /*= true*/,
	const bool useLargeFont /*= true*/,
	const bool fireAndForget /*= true*/,
	const bool allowThrottleWhenFrameRateIsLow /*= false*/)
{
		FNotificationInfo Info(Message);
	Info.FadeInDuration = fadeInDuration;
	Info.ExpireDuration = expireDuration;
	Info.FadeOutDuration = fadeOutDuration;
	Info.bUseThrobber = useThrobber;
	Info.bUseSuccessFailIcons = useSuccessFailIcons;
	Info.bUseLargeFont = useLargeFont;
	Info.bFireAndForget = fireAndForget;
	Info.bAllowThrottleWhenFrameRateIsLow = allowThrottleWhenFrameRateIsLow;
	auto NotificationItem = FSlateNotificationManager::Get().AddNotification(Info);
	NotificationItem->SetCompletionState((SNotificationItem::ECompletionState)notifyType);
	NotificationItem->ExpireAndFadeout();
}

void UComputerStatusBPLibrary::ClearLog()
{
 	/*if (TSharedPtr<SOutputLog> OutputLogPinned = OutputLog.Pin())
 	{
 		if (OutputLogPinned->CanClearLog())
 		{
 			OutputLogPinned->OnClearLog();
 		}
 	}
 
 	if (TSharedPtr<SOutputLog> OutputLogPinned = OutputLogDrawer.Pin())
 	{
 		if (OutputLogPinned->CanClearLog())
 		{
 			OutputLogPinned->OnClearLog();
 		}
 	}*/
}

int64 UComputerStatusBPLibrary::GetCyclesTime()
{
	return FPlatformTime::Cycles64();
}

int64 UComputerStatusBPLibrary::GetTimestamp()
{
	FDateTime Time = FDateTime::Now();
	int64 Timestamp = Time.ToUnixTimestamp();
	return Timestamp;
}

FDateTime UComputerStatusBPLibrary::TimestampToDatetime(int64 UnixTime)
{
	FDateTime Time = FDateTime::FromUnixTimestamp(UnixTime);
	return Time;
}

FDateTime UComputerStatusBPLibrary::GetNowUtc()
{
	return FDateTime::UtcNow();
}

FString UComputerStatusBPLibrary::GetGamePath()
{
	return FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
}

FString UComputerStatusBPLibrary::GetSavedPath()
{
	return FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir());
}

FString UComputerStatusBPLibrary::GetConfigPath()
{
	return FPaths::ConvertRelativePathToFull(FPaths::ProjectConfigDir());
}

FString UComputerStatusBPLibrary::GetLogsPath()
{
	return FPaths::ConvertRelativePathToFull(FPaths::ProjectLogDir());
}

FString UComputerStatusBPLibrary::GetBinaryPath()
{
	return FString(FPlatformProcess::BaseDir());
}

