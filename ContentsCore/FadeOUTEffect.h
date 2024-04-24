#pragma once
#include <EngineCore/EngineRenderTarget.h>

// Ό³Έν :
class FadeOUTEffect : public UEffect
{
public:
	// constrcuter destructer
	FadeOUTEffect();
	~FadeOUTEffect();

	// delete Function
	FadeOUTEffect(const FadeOUTEffect& _Other) = delete;
	FadeOUTEffect(FadeOUTEffect&& _Other) noexcept = delete;
	FadeOUTEffect& operator=(const FadeOUTEffect& _Other) = delete;
	FadeOUTEffect& operator=(FadeOUTEffect&& _Other) noexcept = delete;

protected:
	void Init() override;
	void Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget) override;


private:
	std::shared_ptr<UEngineRenderTarget> CopyTarget;

};