// Fill out your copyright notice in the Description page of Project Settings.

//�̷� ������ ���� Character��� Ŭ������ ��ӽ��� �������� �ű⼭ ����°� �������ϴ�

#include "ABPawn.h"

// Sets default values
AABPawn::AABPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent = Capsule;
	Mesh->SetupAttachment(Capsule);
	SpringArm->SetupAttachment(Capsule);
	Camera->SetupAttachment(SpringArm);
	//����Ī ������ ������ �� ī�޶� ������Ʈ�� �������� ������Ʈ�� �ڽ����� �����ϰ� 
	//Ʈ������ ������ �ʱ�ȭ�ϸ� ī�޶�� �ڵ����� ���������� ���� �ɸ�

	Capsule->SetCapsuleHalfHeight(88.0f);
	Capsule->SetCapsuleRadius(34.0f);
	//ĳ������ ���� ���̿� ĳ������ ���ѷ�
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	/*ĳ���͸� ������ �� ����� ����Ʈ������ 3���� ��ǥ��� �𸮾� ������ 3���� ��ǥ�谡 ���� �ٸ��� ������
	z������ -90�� ȸ������ �����ش�
	�𸮾� �������� ������ ���� ��ġ�� ���߾� ��ġ������ ĳ���� �ּ��� �ַ� �߹ٴڿ� ���� ��ġ�� ��� ������
	z������ ���� ���̸�ŭ ������� �Ѵ�.*/
	SpringArm->TargetArmLength = 400.0f;
	//ī�޶� �������� ���� 4����
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	//������Ʈ�� Y�� ȸ���� -15���� ������ ĳ���� ��� �ʸӷ� ����� ���̵��� ����Ī ������ ����

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(
		TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOARD.Succeeded())Mesh->SetSkeletalMesh(SK_CARDBOARD.Object);

	/*�ִϸ��̼� �������Ʈ�� �ִ� �׷��� ������ ���� �����ϴ� ĳ���� �ִϸ��̼� �ý����� ������Ų��
	�̷��� �ִϸ��̼� �ý����� C++ ���α׷����� �ִ� �ν��ͽ���� Ŭ������ �����ȴ�.*/
	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(
		TEXT("/Game/Book/Animations/WarriorAnimBluePrint.WarriorAnimBluePrint_C"));
	if (WARRIOR_ANIM.Succeeded())Mesh->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	
}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	Super::BeginPlay();

	//Mesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	////������ ���� �߿� �ּ��� �ε��ϴ� ��ɾ�� LoadObject<Ÿ��>
	//UAnimationAsset* AnimAsset = LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/Book/Animations/WarriorRun.WarriorRun"));
	//if (AnimAsset != nullptr) Mesh->PlayAnimation(AnimAsset, true);
	//�̹���� �Ⱦ��� �����ڿ��� �������Ʈ�� ���� �����ϱ�� ��
}

// Called every frame
void AABPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void AABPawn::PossessedBy(AController* NewController)
{
	ABLOG_S(Warning);
	Super::PossessedBy(NewController);
}
// Called to bind functionality to input, �Է� ������ ó���ϱ� ���� ������Ʈ�� �����ϴ� �Լ�
void AABPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//InputComponent�� ����� ���� ��� �Լ��� �Է� ������ ����(Binding)��Ű��, �Է� ��ȣ�� �ڵ����� ���� ��� �Լ��� ���ڷ� ���� ��
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AABPawn::LeftRight);
	/*BindAxis�� BindAction�̶�� �ΰ��� �Լ� ����
	���� ���� ��ȣ�� ���� �� �ֵ��� BindAxis�Լ��� ����� �Է� ������ �̸��� 
	�̿� ������ �𸮾� ������Ʈ �ν��Ͻ��� �Լ� �����͸� ����*/
}

void AABPawn::UpDown(float NewAxisValue)
{
	/*�� �Լ��� �� ����������Ʈ�� ����� ������ -1���� 1������ �Է� ���� �����ؼ� ���� �����̰� �ϴ� ���
	�̵��� ������ WorldDirection�� �����ؾ� �ϹǷ� ������ ���� ������ ���� �����ʹ�
	GetActorForwardVector �Լ��� ����� �������� �� ���� WorldDirection ���ڿ� �Ѱ��ش�.*/
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
	ABLOG(Warning, TEXT("%f"), NewAxisValue);
}

void AABPawn::LeftRight(float NewAxisValue)
{
	AddMovementInput(GetActorRightVector(), NewAxisValue);
	ABLOG(Warning, TEXT("%f"), NewAxisValue);
}
