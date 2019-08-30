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
	UI �ý����� �غ�Ǹ� NativeConstruct �Լ��� ȣ��Ǵµ�
	UI ������ �÷��̾� ��Ʈ�ѷ��� BeginPlay���� ȣ��ǹǷ�
	BeginPlay���� ȣ��� PostInitializeComponents �Լ����� �߻��� ����� �ݿ����� �ʴ´�.
	���� ���� ���������� NativeConstruct �Լ����� ���� ������ ������Ʈ�ϴ� ������ �����ϴ� ���� �ʿ��ϴ�.
	*/
	virtual void NativeConstruct() override;
	void UpdateHPWidget();
private:
	/*��������
	ĳ���� ������ ĳ���Ϳ� ���縦 ����(?)�ϱ� ������ �� �������� ����� �ʿ������
	�н��� ���� �뵵�� ���
	���� UI�� ĳ���Ͱ� ���� �ٸ� ���Ͷ�� �� �����͸� ����ϴ� ���� �ٶ����ϴ�.
	*/
	TWeakObjectPtr<class UABCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
	class UProgressBar* HPProgressBar;
};
