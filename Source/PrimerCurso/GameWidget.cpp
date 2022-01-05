// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidget.h"

#include "../../Plugins/Developer/RiderLink/Source/RD/thirdparty/spdlog/include/spdlog/fmt/bundled/format.h"

void UGameWidget::Load()
{
	const FName TextName = FName(TEXT("Puntuacion"));

	if(TextBlock==nullptr)
	{
		TextBlock = (UTextBlock*)(WidgetTree->FindWidget(TextName));
	}
}
void UGameWidget::SetScore(int Score)
{
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("SOY NULL"));

	if(TextBlock!=nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, TEXT("NO SOY NULL"));
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
