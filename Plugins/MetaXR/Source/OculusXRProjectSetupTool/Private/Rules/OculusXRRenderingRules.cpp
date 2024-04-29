﻿// Copyright (c) Meta Platforms, Inc. and affiliates.

#include "OculusXRRenderingRules.h"
#include "CoreMinimal.h"
#include "AndroidRuntimeSettings.h"
#include "EngineUtils.h"
#include "OculusXRHMDRuntimeSettings.h"
#include "OculusXRPSTUtils.h"
#include "OculusXRRuleProcessorSubsystem.h"
#include "Engine/PostProcessVolume.h"
#include "Engine/RendererSettings.h"

namespace OculusXRRenderingRules
{
	bool FUseVulkanRule::IsApplied() const
	{
		const UAndroidRuntimeSettings* Settings = GetMutableDefault<UAndroidRuntimeSettings>();

		return Settings->bSupportsVulkan && !Settings->bBuildForES31;
	}

	void FUseVulkanRule::ApplyImpl(bool& OutShouldRestartEditor)
	{
		OCULUSXR_UPDATE_SETTINGS(UAndroidRuntimeSettings, bSupportsVulkan, true);
		OCULUSXR_UPDATE_SETTINGS(UAndroidRuntimeSettings, bBuildForES31, false);
		OutShouldRestartEditor = false;
	}

	bool FUseHalfPrecisionFloatRule::IsApplied() const
	{
		const URendererSettings* Settings = GetMutableDefault<URendererSettings>();

		return Settings->MobileFloatPrecisionMode == EMobileFloatPrecisionMode::Half;
	}

	void FUseHalfPrecisionFloatRule::ApplyImpl(bool& OutShouldRestartEditor)
	{
		OCULUSXR_UPDATE_SETTINGS(URendererSettings, MobileFloatPrecisionMode, EMobileFloatPrecisionMode::Half);
		OutShouldRestartEditor = true;
	}

	bool FEnableInstancedStereoRule::IsApplied() const
	{
		const URendererSettings* Settings = GetMutableDefault<URendererSettings>();
		return Settings->bMultiView != 0;
	}

	void FEnableInstancedStereoRule::ApplyImpl(bool& OutShouldRestartEditor)
	{
		OCULUSXR_UPDATE_SETTINGS(URendererSettings, bMultiView, 1);
		OutShouldRestartEditor = true;
	}

	bool FEnableForwardShadingRule::IsApplied() const
	{
		const URendererSettings* Settings = GetMutableDefault<URendererSettings>();

		return Settings->MobileShadingPath == EMobileShadingPath::Forward;
	}

	void FEnableForwardShadingRule::ApplyImpl(bool& OutShouldRestartEditor)
	{
		OCULUSXR_UPDATE_SETTINGS(URendererSettings, MobileShadingPath, EMobileShadingPath::Forward);
		OutShouldRestartEditor = true;
	}

	bool FEnableMSAARule::IsApplied() const
	{
		const URendererSettings* Settings = GetMutableDefault<URendererSettings>();
		return Settings->MobileAntiAliasing == EMobileAntiAliasingMethod::MSAA
			&& Settings->MSAASampleCount == ECompositingSampleCount::Four;
	}

	void FEnableMSAARule::ApplyImpl(bool& OutShouldRestartEditor)
	{
		OCULUSXR_UPDATE_SETTINGS(URendererSettings, MobileAntiAliasing, EMobileAntiAliasingMethod::MSAA);
		OCULUSXR_UPDATE_SETTINGS(URendererSettings, MSAASampleCount, ECompositingSampleCount::Four);

		OutShouldRestartEditor = false;
	}

	bool FEnableOcclusionCullingRule::IsApplied() const
	{
		const URendererSettings* Settings = GetMutableDefault<URendererSettings>();

		return Settings->bOcclusionCulling;
	}

	void FEnableOcclusionCullingRule::ApplyImpl(bool& OutShouldRestartEditor)
	{
		OCULUSXR_UPDATE_SETTINGS(URendererSettings, bOcclusionCulling, 1);
		OutShouldRestartEditor = false;
	}

	bool FEnableDynamicFoveationRule::IsApplied() const
	{
		const UOculusXRHMDRuntimeSettings* Settings = GetMutableDefault<UOculusXRHMDRuntimeSettings>();

		return Settings->bDynamicFoveatedRendering;
	}

	void FEnableDynamicFoveationRule::ApplyImpl(bool& OutShouldRestartEditor)
	{
		OCULUSXR_UPDATE_SETTINGS(UOculusXRHMDRuntimeSettings, bDynamicFoveatedRendering, true);
		OutShouldRestartEditor = false;
	}

#ifdef WITH_OCULUS_BRANCH
	bool FEnableDynamicResolutionRule::IsApplied() const
	{
		const UOculusXRHMDRuntimeSettings* Settings = GetMutableDefault<UOculusXRHMDRuntimeSettings>();

		return Settings->bDynamicResolution;
	}

	void FEnableDynamicResolutionRule::ApplyImpl(bool& OutShouldRestartEditor)
	{
		OCULUSXR_UPDATE_SETTINGS(UOculusXRHMDRuntimeSettings, bDynamicResolution, true);
		OutShouldRestartEditor = false;
	}
#endif

	bool FDisableLensFlareRule::IsApplied() const
	{
		const URendererSettings* Settings = GetMutableDefault<URendererSettings>();
		for (TActorIterator<APostProcessVolume> ActorItr(GEditor->GetEditorWorldContext().World()); ActorItr; ++ActorItr)
		{
			if (ActorItr->Settings.LensFlareIntensity > 0.0f)
			{
				return false;
			}
		}
		return Settings->bDefaultFeatureLensFlare == 0;
	}

	void FDisableLensFlareRule::ApplyImpl(bool& OutShouldRestartEditor)
	{
		OCULUSXR_UPDATE_SETTINGS(URendererSettings, bDefaultFeatureLensFlare, false);

		for (TActorIterator<APostProcessVolume> ActorItr(GEditor->GetEditorWorldContext().World()); ActorItr; ++ActorItr)
		{
			ActorItr->Settings.LensFlareIntensity = 0.0f;
		}
		GetMutableDefault<URendererSettings>()->SaveConfig();
		OutShouldRestartEditor = false;
	}

	bool FDisablePostProcessingRule::IsApplied() const
	{
		const URendererSettings* Settings = GetMutableDefault<URendererSettings>();

		return Settings->bMobilePostProcessing == 0;
	}

	void FDisablePostProcessingRule::ApplyImpl(bool& OutShouldRestartEditor)
	{
		OCULUSXR_UPDATE_SETTINGS(URendererSettings, bMobilePostProcessing, 0);
		OutShouldRestartEditor = true;
	}

	bool FDisableAmbientOcclusionRule::IsApplied() const
	{
		const URendererSettings* Settings = GetMutableDefault<URendererSettings>();

		return Settings->bMobileAmbientOcclusion == 0;
	}

	void FDisableAmbientOcclusionRule::ApplyImpl(bool& OutShouldRestartEditor)
	{
		OCULUSXR_UPDATE_SETTINGS(URendererSettings, bMobileAmbientOcclusion, 0);
		OutShouldRestartEditor = true;
	}

	bool FEnableMultiViewRule::IsApplied() const
	{
		return GetMutableDefault<URendererSettings>()->bMobileMultiView != 0;
	}

	void FEnableMultiViewRule::ApplyImpl(bool& OutShouldRestartEditor)
	{
		OCULUSXR_UPDATE_SETTINGS(URendererSettings, bMobileMultiView, 1);
		OutShouldRestartEditor = true;
	}

	bool FEnableStaticLightingRule::IsApplied() const
	{
		return GetMutableDefault<URendererSettings>()->bAllowStaticLighting;
	}

	void FEnableStaticLightingRule::ApplyImpl(bool& OutShouldRestartEditor)
	{
		OCULUSXR_UPDATE_SETTINGS(URendererSettings, bAllowStaticLighting, true);
		OutShouldRestartEditor = true;
	}

	bool FDisableMobileShaderStaticAndCSMShadowReceiversRule::IsApplied() const
	{
		return !GetMutableDefault<URendererSettings>()->bMobileEnableStaticAndCSMShadowReceivers;
	}

	void FDisableMobileShaderStaticAndCSMShadowReceiversRule::ApplyImpl(bool& OutShouldRestartEditor)
	{
		OCULUSXR_UPDATE_SETTINGS(URendererSettings, bMobileEnableStaticAndCSMShadowReceivers, false);
		OutShouldRestartEditor = false;
	}

	bool FDisableMobileShaderStaticAndCSMShadowReceiversRule::IsValid()
	{
		const UOculusXRRuleProcessorSubsystem* RuleProcessorSubsystem = GEngine->GetEngineSubsystem<UOculusXRRuleProcessorSubsystem>();
		return !RuleProcessorSubsystem->DynamicLightsExistInProject();
	}

	bool FDisableMobileShaderAllowDistanceFieldShadowsRule::IsApplied() const
	{
		return !GetMutableDefault<URendererSettings>()->bMobileAllowDistanceFieldShadows;
	}

	void FDisableMobileShaderAllowDistanceFieldShadowsRule::ApplyImpl(bool& OutShouldRestartEditor)
	{
		OCULUSXR_UPDATE_SETTINGS(URendererSettings, bMobileAllowDistanceFieldShadows, false);
		OutShouldRestartEditor = true;
	}

	bool FDisableMobileShaderAllowDistanceFieldShadowsRule::IsValid()
	{
		const UOculusXRRuleProcessorSubsystem* RuleProcessorSubsystem = GEngine->GetEngineSubsystem<UOculusXRRuleProcessorSubsystem>();
		return !RuleProcessorSubsystem->DynamicLightsExistInProject();
	}

	bool FDisableMobileShaderAllowMovableDirectionalLightsRule::IsApplied() const
	{
		return !GetMutableDefault<URendererSettings>()->bMobileAllowMovableDirectionalLights;
	}

	void FDisableMobileShaderAllowMovableDirectionalLightsRule::ApplyImpl(bool& OutShouldRestartEditor)
	{
		OCULUSXR_UPDATE_SETTINGS(URendererSettings, bMobileAllowMovableDirectionalLights, false);
		OutShouldRestartEditor = true;
	}

	bool FDisableMobileShaderAllowMovableDirectionalLightsRule::IsValid()
	{
		const UOculusXRRuleProcessorSubsystem* RuleProcessorSubsystem = GEngine->GetEngineSubsystem<UOculusXRRuleProcessorSubsystem>();
		return !RuleProcessorSubsystem->DynamicLightsExistInProject();
	}
} // namespace OculusXRRenderingRules
