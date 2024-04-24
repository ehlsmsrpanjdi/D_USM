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

	float4 MousePos = GEngine->EngineWindow.GetScreenMousePos();
	MousePos = Level->GetMainCamera()->ScreenPosToWorldPos(MousePos);

	int XPos = MousePos.X / 32;
	int YPos = MousePos.Y / 32;

	ImGui::Text(("Mouse X : " + (std::to_string(MousePos.X))).c_str());
	ImGui::Text(("Mouse Y : " + (std::to_string(MousePos.Y))).c_str());
	
	ImGui::Text(("Mouse intX : " + (std::to_string(XPos))).c_str());
	ImGui::Text(("Mouse intY : " + (std::to_string(YPos))).c_str());


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
	ImGui::SameLine();
	if (true == ImGui::Button("Rock")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(2);
		EditorSwitch(Location[0], Location[1], 3);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Flag")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(2);
		EditorSwitch(Location[0], Location[1], 4);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Skull")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(2);
		EditorSwitch(Location[0], Location[1], 5);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Water")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(2);
		EditorSwitch(Location[0], Location[1], 6);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Lava")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(2);
		EditorSwitch(Location[0], Location[1], 7);
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
		Ser << TileData;
		std::string Str = FileName;
		UEngineFile File = Dir.GetPathFromFile(Str + ".Data");
		File.Open(EIOOpenMode::Write, EIODataType::Binary);
		File.Save(Ser);
		str = "FileSave";
		FileState = true;
	}

	if (true == ImGui::Button("Load")) {

		for (ABabaBase* Baba : Tiles) {
			Baba->Destroy();
		}
		Tiles.clear();
		TileData.clear();

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
		Ser >> TileData;
		int Index = 0;
		while (TileData.size() > Index) {
			EditorSwitch(TileData[Index], TileData[Index + 1],TileData[Index + 2]);
			Index += 3;
		}
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
		Tiles.push_back(GameMode->SpawnBaba(_X,_Y, "Baba").get());
	break;
	case 2:
		Tiles.push_back(GameMode->SpawnBaba(_X, _Y, "Wall").get());
	case 3:
		Tiles.push_back(GameMode->SpawnBaba(_X, _Y, "Rock").get());
		break;
	case 4:
		Tiles.push_back(GameMode->SpawnBaba(_X, _Y, "Flag").get());
		break;
	case 5:
		Tiles.push_back(GameMode->SpawnBaba(_X, _Y, "Skull").get());
		break;
	case 6:
		Tiles.push_back(GameMode->SpawnBaba(_X, _Y, "Water").get());
		break;
	case 7:
		Tiles.push_back(GameMode->SpawnBaba(_X, _Y, "Lava").get());
		break;
	break;
	case 11:
	{
		IsWord* Baba = GameMode->SpawnIs(_X, _Y).get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 21:
	{
		ActiveWord* Baba = GameMode->SpawnActive(_X, _Y, "Push").get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 22:
	{
		ActiveWord* Baba = GameMode->SpawnActive(_X, _Y, "Move").get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 23:
	{
		ActiveWord* Baba = GameMode->SpawnActive(_X, _Y, "Pull").get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 31:
	{
		NameWord* Baba = GameMode->SpawnName(_X, _Y, BabaState::IsBaba).get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 32:
	{
		NameWord* Baba = GameMode->SpawnName(_X, _Y, BabaState::IsWall).get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	default:
		break;
	}
}
