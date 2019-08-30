// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "ABPawn.generated.h"

UCLASS()
class ARENABATTLE_API AABPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AABPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* newController) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category=Collision)
	UCapsuleComponent* Capsule;
	//폰의 움직임을 담당하는 충돌 컴포넌트,폰을 대표해 움직일 예정이므로 루트 컴포넌트로 설정

	UPROPERTY(VisibleAnywhere, Category = Visual)
	USkeletalMeshComponent* Mesh;
	//캐릭터 애셋을 보여주고 추가로 애니메이션도 담당한다.

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UFloatingPawnMovement* Movement;
	//플레이어 입력에 따라 캐릭터가 움직이도록 설정해주는 컴포넌트, 중력을 고려하지 않은 간단한 움직임 구현

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;
	//스프링암은 삼인칭 구도를 편리하게 설정할 수 있는 부가 컴포넌트

	UPROPERTY(VisibleAnywhere, Category = Collision)
	UCameraComponent* Camera;
	//폰에 카메라 컴포넌트를 부탁하면 카메라가 바라보는 게임 세계의 화면을 플레이어 화면으로 전송

private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
};
