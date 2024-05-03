#include "PreCompile.h"
#include "BabaEditor.h"
#include "PlayGameMode.h"
#include "ContentsHelper.h"
#include "BabaBase.h"
#include "ActiveWord.h"
#include "NameWord.h"
#include "IsWord.h"
#include "AndWord.h"
#include "ContentsCore.h"
#include "BottomTile.h"
#include "TileMap.h"

BabaEditor::BabaEditor()
{
	Off();
}

BabaEditor::~BabaEditor()
{
}

void BabaEditor::EditorFunction()
{
	TilePoint TileLocation = { Location[0],Location[1] };
	if (TileMap::Tile.X < Location[0] || TileMap::Tile.Y < Location[1]) {
		return;
	}
	if (Location[0] < 0 || Location[1] < 0) {
		return;
	}
	if (nullptr == Baba_Actors[TileLocation]) {
		Baba_Actors[TileLocation] = EditorSwitch(Location[0], Location[1], SwitchNum);
		BabaData[TileLocation] = SwitchNum;
	}
}

void BabaEditor::EditorReleaseFunction()
{
	TilePoint TileLocation = { Location[0],Location[1] };
	if (nullptr != Baba_Actors[TileLocation]) {
		ContentsCore::GameMode->Baba_Actors[TileLocation].clear();
		std::vector<IsWord*> VecIs = ContentsCore::GameMode->Is_Vec;
		std::vector<AndWord*> VecAnd = ContentsCore::GameMode->And_Vec;
		for (IsWord* Is : VecIs) {
			if (Is->GetTile() == TileLocation) {
				Is = nullptr;
			}
		}
		for (AndWord* And : VecAnd) {
			if (And->GetTile() == TileLocation) {
				And = nullptr;
			}
		}

		Baba_Actors[TileLocation]->Destroy();
		Baba_Actors[TileLocation] = nullptr;
		BabaData[TileLocation] = 0;
	}
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

	if (UEngineInput::IsPress(VK_LBUTTON)) {
		EditorFunction();
	}

	if (UEngineInput::IsPress(VK_RBUTTON)) {
		EditorReleaseFunction();
	}


}

void BabaEditor::OnGui(ULevel* Level, float _Delta)
{
	Int2D I2D = MousePosCul(Level);
	ImGui::Text(("Mouse intX : " + (std::to_string(I2D.X))).c_str());
	ImGui::Text(("Mouse intY : " + (std::to_string(I2D.Y))).c_str());

	Location[0] = I2D.X;
	Location[1] = I2D.Y;

	if (true == ImGui::Button("Baba")) {
		{
			SwitchNum = 1;
		}
	}

	ImGui::SameLine();
	if (true == ImGui::Button("Wall")) {
		SwitchNum = 2;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Rock")) {
		SwitchNum = 3;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Flag")) {
		SwitchNum = 4;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Skull")) {
		SwitchNum = 5;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Water")) {
		SwitchNum = 6;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Lava")) {
		SwitchNum = 7;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("Grass")) {
		SwitchNum = 8;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("Ice")) {
		SwitchNum = 9;
	}

	if (true == ImGui::Button("Is")) {
		SwitchNum = 11;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("And")) {
		SwitchNum = 12;
	}

	if (true == ImGui::Button("Melt")) {
		SwitchNum = 19;
	}
	ImGui::SameLine();

	if (true == ImGui::Button("You")) {
		SwitchNum = 20;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("Push")) {
		SwitchNum = 21;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Move")) {
		SwitchNum = 22;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Stop")) {
		SwitchNum = 23;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Hot")) {
		SwitchNum = 24;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Pull")) {
		SwitchNum = 25;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Win")) {
		SwitchNum = 26;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Defeat")) {
		SwitchNum = 27;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("Sink")) {
		SwitchNum = 28;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Float")) {
		SwitchNum = 29;
	}



	if (true == ImGui::Button("NameBaba")) {
		SwitchNum = 31;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("NameWall")) {
		SwitchNum = 32;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("NameRock")) {
		SwitchNum = 33;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("NameFlag")) {
		SwitchNum = 34;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("NameSkull")) {
		SwitchNum = 35;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("NameWater")) {
		SwitchNum = 36;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("NameLava")) {
		SwitchNum = 37;
	}
	ImGui::SameLine();
	if (true == ImGui::Button("NameGrass")) {
		SwitchNum = 38;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("NameIce")) {
		SwitchNum = 39;
	}

	if (true == ImGui::Button("Tile")) {
		SwitchNum = 40;
	}

	if (true == ImGui::Button("Clear")) {
		ClearAll();
	}


	if (true == ImGui::InputText("FileName", FileName, 25)) {
	}

	if (true == ImGui::Button("Save")) {
		SaveFunction();
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
		ClearAll();
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
		TilePoint Tile = {};
		while (TileData.size() > Index) {
			Tile.X = TileData[Index];
			Tile.Y = TileData[Index + 1];
			BabaData[Tile] = TileData[Index + 2];
			Baba_Actors[Tile] = EditorSwitch(TileData[Index], TileData[Index + 1], TileData[Index + 2]);
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

Int2D BabaEditor::MousePosCul(ULevel* _Level)
{
	float4 MousePos = GEngine->EngineWindow.GetScreenMousePos();
	MousePos = _Level->GetMainCamera()->ScreenPosToWorldPos(MousePos);

	int XPos = MousePos.X;
	int LocationX = 0;
	int LocationY = 0;
	int YPos = MousePos.Y;
	while (XPos > 16) {
		XPos -= 32;
		LocationX++;
	}
	while (YPos > 16) {
		YPos -= 32;
		LocationY++;
	}

	return Int2D{ LocationX,LocationY };
}

AActor* BabaEditor::EditorSwitch(int _X, int _Y, int _Num)
{
	ABabaBase* Baba = nullptr;
	switch (_Num)
	{
	case 1:
	{
		Baba = GameMode->SpawnBaba(_X, _Y, "Baba").get();
	}
	break;
	case 2:
	{
		Baba = GameMode->SpawnBaba(_X, _Y, "Wall").get();
	}
	break;
	case 3:
	{
		Baba = GameMode->SpawnBaba(_X, _Y, "Rock").get();
	}
	break;
	case 4:
	{
		Baba = GameMode->SpawnBaba(_X, _Y, "Flag").get();
	}
	break;
	case 5:
	{
		Baba = GameMode->SpawnBaba(_X, _Y, "Skull").get();
	}
	break;
	case 6:
	{
		Baba = GameMode->SpawnBaba(_X, _Y, "Water").get();
	}
	break;
	case 7:
	{
		Baba = GameMode->SpawnBaba(_X, _Y, "Lava").get();
	}
	break;
	case 8:
	{
		Baba = GameMode->SpawnBaba(_X, _Y, "Grass").get();
	}
	break;
	case 9:
	{
		Baba = GameMode->SpawnBaba(_X, _Y, "Ice").get();
	}
	break;
	case 11:
	{
		IsWord* Bababa = GameMode->SpawnIs(_X, _Y).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 12:
	{
		AndWord* Bababa = GameMode->SpawnAnd(_X, _Y).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 19:
	{
		ActiveWord* Bababa = GameMode->SpawnActive(_X, _Y, "Melt").get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 20:
	{
		ActiveWord* Bababa = GameMode->SpawnActive(_X, _Y, "You").get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 21:
	{
		ActiveWord* Bababa = GameMode->SpawnActive(_X, _Y, "Push").get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 22:
	{
		ActiveWord* Bababa = GameMode->SpawnActive(_X, _Y, "Move").get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 23:
	{
		ActiveWord* Bababa = GameMode->SpawnActive(_X, _Y, "Stop").get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 24:
	{
		ActiveWord* Bababa = GameMode->SpawnActive(_X, _Y, "Hot").get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 25:
	{
		ActiveWord* Bababa = GameMode->SpawnActive(_X, _Y, "Pull").get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 26:
	{
		ActiveWord* Bababa = GameMode->SpawnActive(_X, _Y, "Win").get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 27:
	{
		ActiveWord* Bababa = GameMode->SpawnActive(_X, _Y, "Defeat").get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 28:
	{
		ActiveWord* Bababa = GameMode->SpawnActive(_X, _Y, "Sink").get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 29:
	{
		ActiveWord* Bababa = GameMode->SpawnActive(_X, _Y, "Float").get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 31:
	{
		NameWord* Bababa = GameMode->SpawnName(_X, _Y, BabaState::IsBaba).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 32:
	{
		NameWord* Bababa = GameMode->SpawnName(_X, _Y, BabaState::IsWall).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 33:
	{
		NameWord* Bababa = GameMode->SpawnName(_X, _Y, BabaState::IsRock).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 34:
	{
		NameWord* Bababa = GameMode->SpawnName(_X, _Y, BabaState::IsFlag).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 35:
	{
		NameWord* Bababa = GameMode->SpawnName(_X, _Y, BabaState::IsSkull).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 36:
	{
		NameWord* Bababa = GameMode->SpawnName(_X, _Y, BabaState::IsWater).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 37:
	{
		NameWord* Bababa = GameMode->SpawnName(_X, _Y, BabaState::IsLava).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 38:
	{
		NameWord* Bababa = GameMode->SpawnName(_X, _Y, BabaState::IsGrass).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 39:
	{
		NameWord* Bababa = GameMode->SpawnName(_X, _Y, BabaState::IsIce).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 40:
	{
		BottomTile* Tile = GameMode->SpawnTile(_X, _Y).get();

		AActor* Actor = static_cast<AActor*>(Tile);
		return Actor;
	}
	default:
		break;
	}
	if (nullptr != Baba)
	{
		return static_cast<AActor*>(Baba);
	}
	else {
		return nullptr;
	}
}

void BabaEditor::SaveFunction()
{
	int i = 0;
	TileData.clear();
	for (std::pair<const TilePoint, AActor*>& Iter : Baba_Actors)
	{
		AActor*& BabaBase = Iter.second;
		TilePoint TileLocation = Iter.first;
		if (nullptr != BabaBase) {
			TileData.push_back(Iter.first.X);
			TileData.push_back(Iter.first.Y);
			TileData.push_back(BabaData[Iter.first]);
			++i;
		}
	}
}

void BabaEditor::ClearAll()
{
	for (std::pair<const TilePoint, AActor*>& Iter : Baba_Actors)
	{
		if (nullptr != Iter.second) {
			Iter.second->Destroy();
			Iter.second = nullptr;
		}
	}
	BabaData.clear();
	Baba_Actors.clear();
	ContentsCore::GameMode->ContainerReset();
}

