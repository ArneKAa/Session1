// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemode/PSGameModeBase.h"
#include "Character/PDCharacter.h"

APSGameModeBase::APSGameModeBase()
{
	
	static ConstructorHelpers::FClassFinder<APawn>
	
	PlayerPawnClassFinder(TEXT("/Game/Blueprints/Character/BP_PDCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
