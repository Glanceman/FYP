// Fill out your copyright notice in the Description page of Project Settings.


#include "./SToolLibrary.h"

#include "FYP/Enum/EMaterialParams.h"
#include "Materials/MaterialInstanceDynamic.h"

void USToolLibrary::ApplyMaterialParams(TMap<EMaterialParams, FVector3f> Params, UMaterialInstanceDynamic* MaterialInstanceDynamic)
{

	if(MaterialInstanceDynamic==nullptr) return;
	for(const TPair<EMaterialParams, FVector3f>Param:Params)
	{
		switch (Param.Key)
		{
		case EMaterialParams::BaseColor:
			{
				FLinearColor Color = Param.Value;
				MaterialInstanceDynamic->SetVectorParameterValue(TEXT("Color"),Color);	
			}
			break;
		case EMaterialParams::Roughness:
			{
				float Val = Param.Value.Length();
				MaterialInstanceDynamic->SetScalarParameterValue(TEXT("Roughness"),Val);	
			}
			break;
		case EMaterialParams::EmissionStrength:
			{
				float Val = Param.Value.Length();
				MaterialInstanceDynamic->SetScalarParameterValue(TEXT("EmissionStrength"),Val);	
			}
			break;
		case EMaterialParams::NONE: break;
		default: ;
		}
	}
}
