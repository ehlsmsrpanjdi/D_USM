#pragma once
#include <Enginecore/Actor.h>
#include <EngineCore/SpriteRenderer.h>


enum class BabaState;
// Ό³Έν :
class Dust : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	Dust();
	~Dust();

	// delete Function
	Dust(const Dust& _Other) = delete;
	Dust(Dust&& _Other) noexcept = delete;
	Dust& operator=(const Dust& _Other) = delete;
	Dust& operator=(Dust&& _Other) noexcept = delete;

	void SetReleaseLocation(char _Input);
	void SetColor(BabaState _State);
	FVector ColorValue = FVector::Zero;
	float4 ColorChange(float4 _Color) {
		return ColorChange(_Color.X, _Color.Y, _Color.Z);
	}

	float4 ColorChange(float _X, float _Y, float _Z) {
		float4 Color = float4::Zero;
		Color.X = _X / 255.f;
		Color.Y = _Y / 255.f;
		Color.Z = _Z / 255.f;
		Color.W = 1.f;
		return Color;
	}
	float4 ColorChange(int _X, int _Y, int _Z) {
		float4 Color = float4::Zero;
		Color.X = static_cast<float>(_X) / 255.f;
		Color.Y = static_cast<float>(_Y)  / 255.f;
		Color.Z = static_cast<float>(_Z)  / 255.f;
		Color.W = 1.f;
		return Color;
	}
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetInputBaseLocation(FVector _Scale);

private:
	USpriteRenderer* Renderer = nullptr;
	FVector Scale = FVector::Zero;
	float ReleaseTime = 0.f;
	float TotalTime = 0.f;
	char ReleaseLocation = '0';
};
