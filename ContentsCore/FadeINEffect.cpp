#include "PreCompile.h"
#include "FadeINEffect.h"

struct FadeStruct {
	float4 FadeValue;
	float4 TimeSet;
};

FadeINEffect::FadeINEffect()
{
}

FadeINEffect::~FadeINEffect()
{

}

void FadeINEffect::Init()
{
	Resources->SettingConstantBuffer("FBaseRenderValue", BaseValue);
	SetMaterial("CircleFadeIN");

	CopyTarget = UEngineRenderTarget::Create();
	// 내가 바라보는 애들을 모아서 그릴수 있는 랜더타겟을 만들고 싶어.
	float4 Scale = GEngine->EngineWindow.GetWindowScale();
	CopyTarget->CreateTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, Scale, float4::Zero);
}

void FadeINEffect::Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget)
{
	CopyTarget->Copy(EffectTarget);
	EffectTarget->Clear();
	EffectTarget->Setting();

	Resources->SettingTexture("Image", CopyTarget->GetTexture(), "POINT");
	
	Render(0.0f);

}

void FadeINEffect::EffectON()
{
	Active(true);
}

void FadeINEffect::EffectOff()
{
	Active(false);
}

void FadeINEffect::SetEffect(bool _Triger)
{
	Active(_Triger);
}
