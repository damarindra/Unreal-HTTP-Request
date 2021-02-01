// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HttpRequestTypes.h"
#include "HttpRequest.generated.h"

class IHttpResponse;
typedef TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> FHttpResponsePtr;
class IHttpRequest;
typedef TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> FHttpRequestPtr;

UCLASS()
class REST_API AHttpRequest : public AActor
{
	GENERATED_BODY()

private:
	class FHttpModule* Http;
	FString ApiBaseUrl = TEXT("http://localhost:5000/api/");

	FString AuthorisationHeader = TEXT("Authorization");
	void SetAuthHash(FString Hash, FHttpRequestPtr& Request);

	FHttpRequestPtr RequestWithRoute(FString Route);
	void SetRequestHeaders(FHttpRequestPtr& Request);

	FHttpRequestPtr GetRequest(FString Subroute);
	FHttpRequestPtr PostRequest(FString Subroute, FString ContentJsonString);
	void Send(FHttpRequestPtr& Request);

	bool ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful);

	template <typename StructType>
	void GetJsonStringFromStruct(StructType FilledStruct, FString& StringOutput);
	template <typename StructType>
	void GetStructFromJsonString(FHttpResponsePtr Response, StructType& StructOutput);
	
public:	
	// Sets default values for this actor's properties
	AHttpRequest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Login(FRequestLogin LoginCredentials);
	void LoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	void FakeJsonRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	

};
