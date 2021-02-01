// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpRequest.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Json.h"
#include "JsonUtilities.h"

// Sets default values
AHttpRequest::AHttpRequest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// FRequestLogin LoginCredentials;
	// LoginCredentials.Email = TEXT("asdf@asdf.com");
	// LoginCredentials.Password = TEXT("asdfasdf");
	// Login(LoginCredentials);
}

// Called when the game starts or when spawned
void AHttpRequest::BeginPlay()
{
	Super::BeginPlay();
    Http = &FHttpModule::Get(); 
	
	ApiBaseUrl = "https://jsonplaceholder.typicode.com";
	FHttpRequestPtr Request = GetRequest("/todos/1");
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpRequest::FakeJsonRequestComplete);
	Send(Request);
}

// Called every frame
void AHttpRequest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FHttpRequestPtr AHttpRequest::RequestWithRoute(FString Route)
{
	FHttpRequestPtr Request = Http->CreateRequest();
	Request->SetURL(ApiBaseUrl + Route);
	SetRequestHeaders(Request);
	return Request;
}

void AHttpRequest::SetRequestHeaders(FHttpRequestPtr& Request)
{
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));
}

FHttpRequestPtr AHttpRequest::GetRequest(FString Subroute)
{
	FHttpRequestPtr Request = RequestWithRoute(Subroute);
	Request->SetVerb("GET");
	return Request;
}

FHttpRequestPtr AHttpRequest::PostRequest(FString Subroute, FString ContentJsonString)
{
	FHttpRequestPtr Request = RequestWithRoute(Subroute);
	Request->SetVerb("POST");
	Request->SetContentAsString(ContentJsonString);
	return Request;
}

void AHttpRequest::Send(FHttpRequestPtr& Request)
{
	Request->ProcessRequest();
}

bool AHttpRequest::ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful)
{
	if(!bWasSuccessful || !Response.IsValid()) false;
	if(EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Http Response returned error code: %d"), Response->GetResponseCode());
		return false;
	}
}

void AHttpRequest::SetAuthHash(FString Hash, FHttpRequestPtr& Request)
{
	Request->SetHeader(AuthorisationHeader, Hash);
}

template <typename StructType>
void AHttpRequest::GetJsonStringFromStruct(StructType FilledStruct, FString& StringOutput)
{
	FJsonObjectConverter::UStructToJsonObjectString(StructType::StaticStruct(), &FilledStruct, StringOutput, 0, 0);
}

template <typename StructType>
void AHttpRequest::GetStructFromJsonString(FHttpResponsePtr Response, StructType& StructOutput)
{
	StructType StructData;
	FString JsonString = Response->GetContentAsString();
	FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &StructOutput, 0, 0);
}


void AHttpRequest::Login(FRequestLogin LoginCredentials)
{
	FString ContentJsonString;
	GetJsonStringFromStruct(LoginCredentials, ContentJsonString);

	FHttpRequestPtr Request = PostRequest("user/login", ContentJsonString);
	Request->OnProcessRequestComplete().BindUObject(this, &AHttpRequest::LoginResponse);
	Send(Request);
}

void AHttpRequest::LoginResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if(!ResponseIsValid(Response, bWasSuccessful)) return;

	FResponseLogin LoginResponse;
	GetStructFromJsonString(Response, LoginResponse);

	UE_LOG(LogTemp, Warning, TEXT("Id is : %d"), LoginResponse.Id);
	UE_LOG(LogTemp, Warning, TEXT("Name is : %s"), *LoginResponse.Name);
}

void AHttpRequest::FakeJsonRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if(!ResponseIsValid(Response, bWasSuccessful)) return;

	FJsonPlaceholderModel1 JsonPlaceholder;
	GetStructFromJsonString(Response, JsonPlaceholder);

	{
		UE_LOG(LogTemp, Warning, TEXT("Id is : %d"), JsonPlaceholder.id);
		UE_LOG(LogTemp, Warning, TEXT("UserID is : %d"), JsonPlaceholder.userId);
		UE_LOG(LogTemp, Warning, TEXT("title is : %s"), *JsonPlaceholder.title);
		UE_LOG(LogTemp, Warning, TEXT("completed is : %s"), JsonPlaceholder.completed ? TEXT("True") : TEXT("False"));
	}
}



