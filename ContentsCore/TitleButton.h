#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

// Ό³Έν :
class TitleButton : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	TitleButton();
	~TitleButton();

	// delete Function
	TitleButton(const TitleButton& _Other) = delete;
	TitleButton(TitleButton&& _Other) noexcept = delete;
	TitleButton& operator=(const TitleButton& _Other) = delete;
	TitleButton& operator=(TitleButton&& _Other) noexcept = delete;

	void SetNum(int _Num) {
		Num = _Num;
		if (Num == 1) {
			Renderer->SetSprite("StartTheGameBtn.png");
		}
		else {
			Renderer->SetSprite("ExitTheGameBtn.png");
		}
	}
	int Num;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;



private:
	USpriteRenderer* Renderer = nullptr;
};
