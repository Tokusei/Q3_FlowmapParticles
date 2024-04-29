// Copyright (c) Meta Platforms, Inc. and affiliates.

#pragma once

#include "OculusXRSceneTypes.h"
#include <Subsystems/GameInstanceSubsystem.h>
#include <Tickable.h>

#include "OculusXRSceneSubsystem.generated.h"

UCLASS()
class UOculusXRSceneSubsystem : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()
public:
	UOculusXRSceneSubsystem();

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// FTickableGameObject implementation Begin
	virtual ETickableTickType GetTickableTickType() const override;
	virtual bool IsAllowedToTick() const override final;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UOculusXRSceneSubsystem, STATGROUP_Tickables); }
	// FTickableGameObject implementation End


private:
};
