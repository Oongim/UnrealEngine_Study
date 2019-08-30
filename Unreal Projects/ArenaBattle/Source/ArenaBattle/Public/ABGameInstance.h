// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "ABGameInstance.generated.h"

/*
CSV파일을 불러오기 위해 테이블 데이터의 각 열의 이름과 유형이 동일한 구조체를 선언해야 한다.
언리얼 엔진에서 제공하는 FTableRowBase 구조체를 상속받은 FABCharacterData라는 구조체를 헤더에 선언해야한다.

CSV파일의 각 열의 이름과 동일한 멤버 변수를 타입에 맞춰 선언하는데
이때 테이블의 첫 번째에 위치한 Namee 열 데이터는 언리얼 엔진에서 자동으로 키 값으로 사용하기 때문에 선언에서 제외한다.
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
	게임 진행중에도 비동기 방식으로 애셋을 로딩하도록 FStreamableManager제공,
	이 클래스는 프로젝트에서 하나만 활성화하는 것이 좋기 때문에 유일한 인스턴스로 동작하는 이 클래스에서 멤버 변수로 선언한다.
	*/
	FStreamableManager StreamableManager;
private:
	UPROPERTY()
	class UDataTable* ABCharacterTable;
};
