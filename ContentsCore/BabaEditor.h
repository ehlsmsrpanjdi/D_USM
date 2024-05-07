#pragma once
#include <EngineCore/EngineEditorGUI.h>
#include <EngineCore/EngineDebugMsgWindow.h>
#include <EngineBase/EngineDirectory.h>

struct Int2D {
	int X = 0;
	int Y = 0;
};

class ABabaBase;

class APlayGameMode;
// Ό³Έν :
class BabaEditor : public UEngineDebugMsgWindow
{
public:
	// constructor destructor
	BabaEditor();
	~BabaEditor();

	// delete Function
	BabaEditor(const BabaEditor& _Other) = delete;
	BabaEditor(BabaEditor&& _Other) noexcept = delete;
	BabaEditor& operator=(const BabaEditor& _Other) = delete;
	BabaEditor& operator=(BabaEditor&& _Other) noexcept = delete;

	void Save(std::string_view File_Name);
	void Load(std::string_view File_Name);

protected:
	void Init() override;
	void Tick(ULevel* Level, float _Delta) override;
	void OnGui(ULevel* Level, float _Delta) override;

	Int2D MousePosCul(ULevel* _Level);

	APlayGameMode* GameMode = nullptr;

	int Location[2] = { 0, };
	
	char FileName[255] = "";

	UEngineDirectory Dir;
	std::map <struct TilePoint, AActor*> Baba_Actors;
	std::map<struct TilePoint, int> BabaData;
	std::vector<int> TileData;
	std::string str = "";

	bool FileState = false;
	float _DeltaTime = 0.f;
	int SwitchNum = 0;

	AActor* EditorSwitch(int _X, int _Y, int _Num);
	void SaveFunction();
	void ClearAll();
	void EditorFunction();
	void EditorReleaseFunction();



private:

};
