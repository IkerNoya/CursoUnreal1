// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidget.h"

/*
 * Binds a c++ para UI simple
 * Creacion de todo desde c++ para UI compleja
 */


void UGameWidget::Load()
{
	const FName TextName = FName(TEXT("Puntuacion"));

	if(TextBlock==nullptr)
	{
		UTextBlock* TextBlockReference = Cast<UTextBlock>(WidgetTree->FindWidget(TextName));
		if(TextBlockReference)
		{
			TextBlock=TextBlockReference;
		}
	}
}
void UGameWidget::SetScore_Implementation(int Score)
{
	SetScore(Score);
	if(TextBlock!=nullptr)
	{
		TextBlock->SetText(FText::FromString(FString(("Score: ")) + FString::FromInt(Score)));
	}
}
void UGameWidget::OnGameOver(int Score)
{
	if(TextBlock!=nullptr)
	{
		TextBlock->SetText(FText::FromString((FString(TEXT("Score: ") + FString::FromInt(Score) + TEXT("\n Presiona R para Reiniciar")))));
	}
}
