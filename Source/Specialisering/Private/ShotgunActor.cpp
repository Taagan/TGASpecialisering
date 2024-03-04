// Fill out your copyright notice in the Description page of Project Settings.


#include "ShotgunActor.h"
#include "GSM_Shotgun.h"

AShotgunActor::AShotgunActor()
{
	myGunStateMachine = new GSM_Shotgun();
}
