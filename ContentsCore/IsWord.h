#pragma once
#include "BabaBase.h"
#include <EngineCore/EngineCore.h>
// Ό³Έν :
class IsWord : public ABabaBase
{
	GENERATED_BODY(AActor)

public:
	// constructor destructor
	IsWord();
	~IsWord();



	// delete Function
	IsWord(const IsWord& _Other) = delete;
	IsWord(IsWord&& _Other) noexcept = delete;
	IsWord& operator=(const IsWord& _Other) = delete;
	IsWord& operator=(IsWord&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void UpCheck(std::map<__int64, std::list<ABabaBase*>>& _Map);
	void AxisCheck(std::map<__int64, std::list<ABabaBase*>>& _Map);
	ABabaBase* WorldCheck(std::map<__int64, std::list<ABabaBase*>>& _Map, TilePoint _Tile);
	

	void ActiveUpdate(ABabaBase* _Left, ABabaBase* _Right);
	void WordChange(ActiveState* _CurWord, ABabaBase* _Name);
	void ActiveChange(ActiveState* _CurWord, ABabaBase* _Active);

protected:


private:

};
