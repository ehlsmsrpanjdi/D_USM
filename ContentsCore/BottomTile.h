#pragma once
#include <Enginecore/Actor.h>
#include <EngineCore/SpriteRenderer.h>


// Ό³Έν :
class BottomTile : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	BottomTile();
	~BottomTile();

	// delete Function
	BottomTile(const BottomTile& _Other) = delete;
	BottomTile(BottomTile&& _Other) noexcept = delete;
	BottomTile& operator=(const BottomTile& _Other) = delete;
	BottomTile& operator=(BottomTile&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;



private:
	USpriteRenderer* Renderer = nullptr;
};
