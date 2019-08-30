// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "ABGameInstance.generated.h"

/*
CSV������ �ҷ����� ���� ���̺� �������� �� ���� �̸��� ������ ������ ����ü�� �����ؾ� �Ѵ�.
�𸮾� �������� �����ϴ� FTableRowBase ����ü�� ��ӹ��� FABCharacterData��� ����ü�� ����� �����ؾ��Ѵ�.

CSV������ �� ���� �̸��� ������ ��� ������ Ÿ�Կ� ���� �����ϴµ�
�̶� ���̺��� ù ��°�� ��ġ�� Namee �� �����ʹ� �𸮾� �������� �ڵ����� Ű ������ ����ϱ� ������ ���𿡼� �����Ѵ�.
*/
USTRUCT(BlueprintType)
struct FABCharacterData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	FABCharacterData() : Level(1), MaxHP(100.0f), Attack(10.0f), DropExp(10), NextExp(30) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 DropExp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 NextExp;
};

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UABGameInstance();

	virtual void Init() override;
	FABCharacterData* GetABCharacterData(int32 Level);

	/*
	���� �����߿��� �񵿱� ������� �ּ��� �ε��ϵ��� FStreamableManager����,
	�� Ŭ������ ������Ʈ���� �ϳ��� Ȱ��ȭ�ϴ� ���� ���� ������ ������ �ν��Ͻ��� �����ϴ� �� Ŭ�������� ��� ������ �����Ѵ�.
	*/
	FStreamableManager StreamableManager;
private:
	UPROPERTY()
	class UDataTable* ABCharacterTable;
};
