// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HttpRequestTypes.generated.h"

USTRUCT()
struct FRequestLogin {
	GENERATED_USTRUCT_BODY()
	UPROPERTY()
	FString Email;
	UPROPERTY()
	FString Password;

	FRequestLogin() {}
};

USTRUCT()
struct FResponseLogin {
	GENERATED_USTRUCT_BODY()
	UPROPERTY() int Id;
	UPROPERTY() FString Name;
	UPROPERTY() FString Hash;

	FResponseLogin() {}
};

USTRUCT()
struct FJsonPlaceholderModel1
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY() int userId;
	UPROPERTY() int id;
	UPROPERTY() FString title;
	UPROPERTY() bool completed;

	FJsonPlaceholderModel1(){}
};