#pragma once
#include <EngineCore/EngineRenderTarget.h>

// ���� :
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

	void EffectON()
	{
		Active(true);
	}

	void EffectOff()
	{
		Active(false);
	}
protected:
	void Init() override;
	void Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget) override;



private:
	std::shared_ptr<UEngineRenderTarget> CopyTarget;

};