// Copyright Epic Games, Inc. All Rights Reserved.

#include "RESTGameMode.h"
#include "RESTHUD.h"
#include "RESTCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARESTGameMode::ARESTGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ARESTHUD::StaticClass();
}
