#pragma once
#include "BabaBase.h"
#include <EngineCore/EngineCore.h>
// Ό³Έν :
class AndWord : public ABabaBase
{
	GENERATED_BODY(AActor)

public:
	// constructor destructor
	AndWord();
	~AndWord();



	// delete Function
	AndWord(const AndWord& _Other) = delete;
	AndWord(AndWord&& _Other) noexcept = delete;
	AndWord& operator=(const AndWord& _Other) = delete;
	AndWord& operator=(AndWord&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void UpCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map);
	void AxisCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map);
	ABabaBase* WorldCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map, TilePoint _Tile);
	bool WordOnCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map, TilePoint _Tile);



	void ActiveUpdate(ABabaBase* _Left, ABabaBase* _Right);
	void WordChange(ABabaBase* _CurWord, ABabaBase* _Name);
	void ActiveChange(ActiveState* _CurWord, ABabaBase* _Active);
protected:


private:

};
