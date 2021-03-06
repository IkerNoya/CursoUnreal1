// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

#include "Blueprint/UserWidget.h"
#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class PRIMERCURSO_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	UTextBlock* TextBlock;
	
	void Load();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = UI)
	void SetScore(int Score);
	void SetScore_Implementation(int Score);
	
	void OnGameOver(int Score);

};
