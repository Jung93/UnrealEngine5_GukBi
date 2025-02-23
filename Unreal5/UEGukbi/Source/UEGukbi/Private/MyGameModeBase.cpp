// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyTutoPawn.h"

AMyGameModeBase::AMyGameModeBase()
{
	//BluePrint Class type�� ������ ���� ���� _C�� �ٿ����Ѵ�
	static ConstructorHelpers::FClassFinder<AMyTutoPawn> pawn(TEXT("/Script/Engine.Blueprint'/Game/BluePrints/BP_MyTutoPawn.BP_MyTutoPawn_C'"));

	if (pawn.Succeeded())
	{
		DefaultPawnClass = pawn.Class;
	}


}
