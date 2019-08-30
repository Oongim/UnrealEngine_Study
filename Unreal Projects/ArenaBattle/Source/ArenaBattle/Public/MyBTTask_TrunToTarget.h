// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTask_TrunToTarget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UMyBTTask_TrunToTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UMyBTTask_TrunToTarget();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
