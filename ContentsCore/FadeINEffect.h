#pragma once
#include <EngineCore/EngineRenderTarget.h>

// Ό³Έν :
class FadeINEffect : public UEffect
{
public:
	// constrcuter destructer
	FadeINEffect();
	~FadeINEffect();

	// delete Function
	FadeINEffect(const FadeINEffect& _Other) = delete;
	FadeINEffect(FadeINEffect&& _Other) noexcept = delete;
	FadeINEffect& operator=(const FadeINEffect& _Other) = delete;
	FadeINEffect& operator=(FadeINEffect&& _Other) noexcept = delete;
	void EffectON();
	void EffectOff();
	void SetEffect(bool _Triger);

protected:
	void Init() override;
	void Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget) override;


private:
	std::shared_ptr<UEngineRenderTarget> CopyTarget;

};

