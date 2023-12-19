// Copyright 2023 Device. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "ComputerStatusBPLibrary.generated.h"

UENUM(BlueprintType)
enum E_BXSNotifyCompletionState
{
	None,
	Pending,
	Success,
	Fail,
};

UCLASS()
class UComputerStatusBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	//
	//
	/////////////////////////////////////////////////////////
	//     ::Windows Status::                                  //
	/////////////////////////////////////////////////////////
	//
	//
	/*Get Local IPAddress,etc.192.168.0.1*/
	UFUNCTION(BlueprintPure, Category = "BXS|Windows")
		static FString GetLocalIPAddress();

	/*Get Local Mac Address*/
	UFUNCTION(BlueprintPure, Category = "BXS|Windows")
		static FString GetMac(FString& mac, FString& LocalIP);

	/*Get Local GPU Info*/
	UFUNCTION(BlueprintPure, Category = "BXS|Windows|GPU")
		static void GetGPUInfo(FString& DeviceDescription, FString& Provider, FString& DriverVersion, FString& DriverDate, FString& RHIName);

	/*Get Local CPU Info*/
	UFUNCTION(BlueprintPure, Category = "BXS|Windows|CPU")
		static void GetCPUInfo(FString& CPUBrand);

	/*Get Keyboard  Clip Info*/
	UFUNCTION(BlueprintPure, Category = "BXS|Windows|Clipboard", Meta = (DisplayName = " Get Clipboard"))
		static FString GetClipboard();


	/*Get Window Bounds*/
	UFUNCTION(BlueprintPure, Category = "BXS|Windows", Meta = (DisplayName = "Get Window Bounds", Keywords = "Get Window Bounds"))
		static void GetWindowBounds(bool& Success, int32& X, int32& Y, int32& Width, int32& Height);

	/*Get Mouse  Info*/
	UFUNCTION(BlueprintPure, Category = "BXS|Windows", Meta = (DisplayName = "Get Mouse Position"))
		static void GetMousePosition(bool& Success, int32& X, int32& Y);

	//
	//
	/////////////////////////////////////////////////////////
	//     ::Editor Status::                                  //
	/////////////////////////////////////////////////////////
	//
	//
	/*Create an editor notification*/
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "BXS|PIE")
		static void CreateEditorNotification(const FText Message, const E_BXSNotifyCompletionState notifyType = E_BXSNotifyCompletionState::None,
			const float fadeInDuration = 0.5f, const float expireDuration = 1.0f,
			const float fadeOutDuration = 2.0f, const bool useThrobber = false,
			const bool useSuccessFailIcons = true, const bool useLargeFont = true,
			const bool fireAndForget = true, const bool allowThrottleWhenFrameRateIsLow = false);

	/*Encrypt Version, Like GetHashMD5*/
	UFUNCTION(BlueprintCallable, Category = "BXS|PIE")
		static 	FString EncryptVersion(const FString& Content, const FString& key);

	//
	//
	/////////////////////////////////////////////////////////
	//     ::Time Status::                                  //
	/////////////////////////////////////////////////////////
	//
	//
	/*Get Cycles Time*/
	UFUNCTION(BlueprintPure, Category = "BXS|Time")
		static int64 GetCyclesTime();

	/*Get Tamp Time*/
	UFUNCTION(BlueprintPure, Category = "BXS|Time")
		static int64 GetTimestamp();

	/*Get Date Time*/
	UFUNCTION(BlueprintPure, Category = "BXS|Time")
		static FDateTime TimestampToDatetime(int64 UnixTime);

	/*Get Now Time*/
	UFUNCTION(BlueprintPure, Category = "BXS|Time")
		static FDateTime GetNowUtc();

	//
	//
	/////////////////////////////////////////////////////////
	//     ::Path Status::                                  //
	/////////////////////////////////////////////////////////
	//
	//
	/* Get Game Path */
	UFUNCTION(BlueprintPure, Category = "BXS|Files", meta = (Keywords = "Get Game Path"))
		static FString GetGamePath();

	/* Get Saved Path */
	UFUNCTION(BlueprintPure, Category = "BXS|Files", meta = (Keywords = "Get Saved Path"))
		static FString GetSavedPath();

	/* Get Config Path */
	UFUNCTION(BlueprintPure, Category = "BXS|Files", meta = (Keywords = "Get Config Path"))
		static FString GetConfigPath();

	/* Get Logs Path */
	UFUNCTION(BlueprintPure, Category = "BXS|Files", meta = (Keywords = "Get Logs Path"))
		static FString GetLogsPath();

	/* Get Binary Path */
	UFUNCTION(BlueprintPure, Category = "BXS|Files", meta = (Keywords = "Get Binary Path"))
		static FString GetBinaryPath();

};
