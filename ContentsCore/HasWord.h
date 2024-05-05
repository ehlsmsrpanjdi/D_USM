#pragma once
#include "BabaBase.h"
#include <EngineCore/EngineCore.h>
// Ό³Έν :
class HasWord : public ABabaBase
{
	GENERATED_BODY(AActor)

public:
	// constructor destructor
	HasWord();
	~HasWord();



	// delete Function
	HasWord(const HasWord& _Other) = delete;
	HasWord(HasWord&& _Other) noexcept = delete;
	HasWord& operator=(const HasWord& _Other) = delete;
	HasWord& operator=(HasWord&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void UpCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map);
	void AxisCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map);
	ABabaBase* WorldCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map, TilePoint _Tile);
protected:


private:

};
