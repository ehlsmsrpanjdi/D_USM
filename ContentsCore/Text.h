#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/SpriteRenderer.h>

// Ό³Έν :
class Text : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	Text();
	~Text();

	// delete Function
	Text(const Text& _Other) = delete;
	Text(Text&& _Other) noexcept = delete;
	Text& operator=(const Text& _Other) = delete;
	Text& operator=(Text&& _Other) noexcept = delete;

	void TextChange(std::string_view _TextName);
	void MulColor(float4 _Color) {
		Renderer->SetMulColor(_Color);
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	USpriteRenderer* Renderer = nullptr;
};
