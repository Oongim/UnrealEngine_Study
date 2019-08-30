// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "Blueprint/UserWidget.h"
#include "ABCharacterWidget.generated.h"

/**
 *
 */
UCLASS()
class ARENABATTLE_API UABCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

	public:
	void BindCharacterStat(class UABCharacterStatComponent* NewCharacterStat);
protected:
	/*
	UI 시스템이 준비되면 NativeConstruct 함수가 호출되는데
	UI 생성은 플레이어 컨트롤러의 BeginPlay에서 호출되므로
	BeginPlay전에 호출된 PostInitializeComponents 함수에서 발생한 명령은 반영되지 않는다.
	따라서 현재 구조에서는 NativeConstruct 함수에서 위젯 내용을 업데이트하는 로직을 구현하는 것이 필요하다.
	*/
	virtual void NativeConstruct() override;
	void UpdateHPWidget();
private:
	/*약포인터
	캐릭터 위젯은 캐릭터와 생사를 같이(?)하기 때문에 약 포인터의 사용은 필요없지만
	학슴을 위한 용도로 사용
	만약 UI와 캐릭터가 서로 다른 액터라면 약 포인터를 사용하는 것이 바람직하다.
	*/
	TWeakObjectPtr<class UABCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
	class UProgressBar* HPProgressBar;
};
