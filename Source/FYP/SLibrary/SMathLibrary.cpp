// Fill out your copyright notice in the Description page of Project Settings.


#include "./SMathLibrary.h"

float USMathLibrary::SignedAngleBetweenTwoVectors(FVector v1, FVector v2)
{
	v1.Normalize();
	v2.Normalize();
	const float DotProduct  = v1.Dot(v2);
	const FVector CrossProduct = v1.Cross(v2);

	if(CrossProduct.Z>=0)
	{
		return FMath::FMath::RadiansToDegrees(acos(DotProduct));
	}else
	{
		return FMath::FMath::RadiansToDegrees(acos(DotProduct)*-1);
	}
}
