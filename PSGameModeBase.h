// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PSGameModeBase.generated.h"

class APDCharacter;

/**
 * 
 */
UCLASS()
class PLAGUESPLATTERSOLO_API APSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	APSGameModeBase();

public:

	UPROPERTY(BlueprintReadWrite, Category = "DefaultPawn")
	class APDCharacter* PlayerCharacter;

};
