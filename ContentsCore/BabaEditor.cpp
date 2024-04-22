#include "PreCompile.h"
#include "BabaEditor.h"
#include "PlayGameMode.h"


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
		TileData[TilePoint(Location[0], Location[1])].push_back(1);
		GameMode->SpawnBaba(Location[0], Location[1], "Baba");
		//GameMode->spawn
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Wall")) {
		TileData[TilePoint(Location[0], Location[1])].push_back(2);
		GameMode->SpawnBaba(Location[0], Location[1], "Wall");
		//GameMode->spawn
	}



	if (true == ImGui::Button("Is")) {
		TileData[TilePoint(Location[0], Location[1])].push_back(11);
		GameMode->SpawnIs(Location[0], Location[1]);
	}


	if (true == ImGui::Button("Push")) {
		TileData[TilePoint(Location[0], Location[1])].push_back(21);
		GameMode->SpawnActive(Location[0], Location[1], "Push");
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Move")) {
		TileData[TilePoint(Location[0], Location[1])].push_back(22);
		GameMode->SpawnActive(Location[0], Location[1], "Move");
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Pull")) {
		TileData[TilePoint(Location[0], Location[1])].push_back(23);
		GameMode->SpawnActive(Location[0], Location[1], "Pull");
	}


	if (true == ImGui::Button("NameBaba")) {
		TileData[TilePoint(Location[0], Location[1])].push_back(31);
		GameMode->SpawnName(Location[0], Location[1], BabaState::IsBaba);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("NameWall")) {
		TileData[TilePoint(Location[0], Location[1])].push_back(32);
		GameMode->SpawnName(Location[0], Location[1], BabaState::IsRock);
	}
	ImGui::SameLine();

}

void BabaEditor::EditorSwitch(int _X, int _Y, int _Index)
{
	switch (_Index)
	{
	case 1:
		break;
	case 2:
		break;
	case 11:
		break;
	case 21:
		break;
	case 22:
		break;
	case 23:
		break;
	case 31:
		break;
	case 32:
		break;
	default:
		break;
	}
}
