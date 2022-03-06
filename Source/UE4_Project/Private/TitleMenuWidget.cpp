// Fill out your copyright notice in the Description page of Project Settings.


#include "TitleMenuWidget.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void UTitleMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UUserWidget* StartWidget = Cast<UUserWidget>(GetWidgetFromName(TEXT("start_button")));
	UUserWidget* OptionWidget= Cast<UUserWidget>(GetWidgetFromName(TEXT("option_button")));
	UUserWidget* ExitWidget = Cast<UUserWidget>(GetWidgetFromName(TEXT("exit_button")));

	

	StartButton = Cast<UButton>(StartWidget->GetWidgetFromName(TEXT("Button_0")));
	OptionButton = Cast<UButton>(OptionWidget->GetWidgetFromName(TEXT("Button_0")));
	ExitButton = Cast<UButton>(ExitWidget->GetWidgetFromName(TEXT("Button_0")));

	StartButton->OnClicked.AddDynamic(this, &UTitleMenuWidget::OnClick_Start);
	OptionButton->OnClicked.AddDynamic(this, &UTitleMenuWidget::OnClick_Option);
	ExitButton->OnClicked.AddDynamic(this, &UTitleMenuWidget::OnClick_Exit);
}

void UTitleMenuWidget::OnClick_Start()
{
	UGameplayStatics::OpenLevel(this, "Game_Ver2");
	MYLOG_S();
}

void UTitleMenuWidget::OnClick_Option()
{
	MYLOG_S();
}

void UTitleMenuWidget::OnClick_Exit()
{
	MYLOG_S();
}
