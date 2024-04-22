#include "PreCompile.h"
#include "BabaEditor.h"
#include "PlayGameMode.h"
#include "ContentsHelper.h"
#include "BabaBase.h"
#include "ActiveWord.h"
#include "NameWord.h"
#include "IsWord.h"

BabaEditor::BabaEditor()
{
	Off();
}

BabaEditor::~BabaEditor()
{
}

void BabaEditor::Init()
{
}

void BabaEditor::Tick(ULevel* Level, float _Delta)
{
	std::string str = Level->GetName();

	if (str._Equal("PlayLevel")) {
		On();
		if (GameMode == nullptr) {
			GameMode = dynamic_cast<APlayGameMode*>(Level->GetGameMode().get());
		}
	}

	else {
		Off();
	}

}

void BabaEditor::OnGui(ULevel* Level, float _Delta)
{
	ImGui::InputInt2("Location", Location);

	GEngine->EngineWindow.GetScreenMousePos();


	if (true == ImGui::Button("Baba")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(1);
		EditorSwitch(Location[0], Location[1], 1);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Wall")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(2);
		EditorSwitch(Location[0], Location[1], 2);
	}



	if (true == ImGui::Button("Is")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(11);
		EditorSwitch(Location[0], Location[1], 11);
	}


	if (true == ImGui::Button("Push")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(21);
		EditorSwitch(Location[0], Location[1], 21);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Move")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(22);
		EditorSwitch(Location[0], Location[1], 22);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Pull")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(23);
		EditorSwitch(Location[0], Location[1], 23);
	}


	if (true == ImGui::Button("NameBaba")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(31);
		EditorSwitch(Location[0], Location[1], 31);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("NameWall")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(32);
		EditorSwitch(Location[0], Location[1], 32);
	}


	if (true == ImGui::Button("Clear")) {
		for (ABabaBase* Baba : Tiles) {
			Baba->Destroy();
		}
		Tiles.clear();
		TileData.clear();
	}


	if (true == ImGui::InputText("FileName", FileName, 25)) {
	}

	if (true == ImGui::Button("Save")) {
		if (TileData.empty() == true) {
			str = "FileSaveFail";
			FileState = true;
			return;
		}
		UEngineSerializer Ser;
		for (int i : TileData) {
			Ser << i;
		}
		std::string Str = FileName;
		UEngineFile File = Dir.GetPathFromFile(Str + ".Data");
		File.Open(EIOOpenMode::Write, EIODataType::Binary);
		File.Save(Ser);
		str = "FileSave";
		FileState = true;
	}

	if (true == ImGui::Button("Load")) {
		UEngineSerializer Ser;
		std::string Str = FileName;
		UEngineFile File = Dir.GetPathFromFile(Str + ".Data");
		if (false == File.IsExists()) {
			str = "File is no exist";
			FileState = true;
			return;
		}
		File.Open(EIOOpenMode::Read, EIODataType::Binary);
		File.Load(Ser);
		str = "FileLoad";
		FileState = true;
	}

	if (FileState == true) {
		ImGui::Text(str.c_str());
		_DeltaTime += _Delta;
		if (_DeltaTime >= 5.0f) {
			_DeltaTime = 0.f;
			FileState = false;
		}
	}
}

void BabaEditor::EditorSwitch(int _X, int _Y, int _Index)
{
	switch (_Index)
	{
	case 1:
	{
		Tiles.push_back(GameMode->SpawnBaba(Location[0], Location[1], "Baba").get());
	}
	break;
	case 2:
	{
		Tiles.push_back(GameMode->SpawnBaba(Location[0], Location[1], "Wall").get());
	}
	break;
	case 11:
	{
		IsWord* Baba = GameMode->SpawnIs(Location[0], Location[1]).get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 21:
	{
		ActiveWord* Baba = GameMode->SpawnActive(Location[0], Location[1], "Push").get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 22:
	{
		ActiveWord* Baba = GameMode->SpawnActive(Location[0], Location[1], "Move").get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 23:
	{
		ActiveWord* Baba = GameMode->SpawnActive(Location[0], Location[1], "Pull").get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 31:
	{
		NameWord* Baba = GameMode->SpawnName(Location[0], Location[1], BabaState::IsBaba).get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 32:
	{
		NameWord* Baba = GameMode->SpawnName(Location[0], Location[1], BabaState::IsRock).get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	default:
		break;
	}
}
