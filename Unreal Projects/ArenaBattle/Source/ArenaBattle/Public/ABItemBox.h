// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/Actor.h"
#include "ABItemBox.generated.h"

UCLASS()
class ARENABATTLE_API AABItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	UPROPERTY(VisibleAnywhere, Category = Box)
	UBoxComponent* Trigger;						//플레이어와의 겹침을 갑지할 박스 콜리전 컴포넌트

	UPROPERTY(VisibleAnyWhere, Category = Box)
	UStaticMeshComponent* Box;

	UPROPERTY(VisibleAnyWhere, Category = Box)
	UParticleSystemComponent* Effect;
	
	/*
	 클래스의 정보를 저장하는 변수로 UClass의 포인터를 사용할 수도 있지만
	현재 프로젝트에 사용하는 모든 언리얼 오브젝트의 선언이 보이게 된다.
	 특정 클래스와 상속받은 클래스들로 목록을 한정하도록 TSubclassof라는 키워드를 제공
	이를 사용하면 목록에서 아이템 상자와 이를 선언한 클래스 목록만 볼 수 있다.
	*/
	UPROPERTY(EditInstanceOnly, Category = Box)
	TSubclassOf<class AABWeapon> WeaponItemClass;
	
private:
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEffectFinished(class UParticleSystemComponent* PSystem);
};
