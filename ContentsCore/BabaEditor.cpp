#include "PreCompile.h"
#include "BabaEditor.h"
#include "PlayGameMode.h"
#include "ContentsHelper.h"
#include "BabaBase.h"
#include "ActiveWord.h"
#include "NameWord.h"
#include "IsWord.h"
#include "AndWord.h"
#include "HasWord.h"
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

	ImGui::SameLine();
	if (true == ImGui::Button("Algae")) {
		SwitchNum = 51;
	}

	if (true == ImGui::Button("Box")) {
		SwitchNum = 52;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("Door")) {
		SwitchNum = 53;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("Crab")) {
		SwitchNum = 54;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("Jelly")) {
		SwitchNum = 55;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("Pillar")) {
		SwitchNum = 56;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("Key")) {
		SwitchNum = 57;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("Star")) {
		SwitchNum = 58;
	}

	if (true == ImGui::Button("Is")) {
		SwitchNum = 11;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("And")) {
		SwitchNum = 12;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("Has")) {
		SwitchNum = 13;
	}

	if (true == ImGui::Button("Open")) {
		SwitchNum = 17;
	}
	ImGui::SameLine();

	if (true == ImGui::Button("Shut")) {
		SwitchNum = 18;
	}
	ImGui::SameLine();

	if (true == ImGui::Button("Melt")) {
		SwitchNum = 19;
	}
	ImGui::SameLine();

	if (true == ImGui::Button("You")) {
		SwitchNum = 20;
	}

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

	ImGui::SameLine();
	if (true == ImGui::Button("NameAlgae")) {
		SwitchNum = 41;
	}

	if (true == ImGui::Button("NameBox")) {
		SwitchNum = 42;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("NameDoor")) {
		SwitchNum = 43;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("NameCrab")) {
		SwitchNum = 44;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("NameJelly")) {
		SwitchNum = 45;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("NamePillar")) {
		SwitchNum = 46;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("NameKey")) {
		SwitchNum = 47;
	}

	ImGui::SameLine();
	if (true == ImGui::Button("NameStar")) {
		SwitchNum = 48;
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
		Save(FileName);
	}

	if (true == ImGui::Button("Load")) {
		Load(FileName);
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
	case 13:
	{
		HasWord* Bababa = GameMode->SpawnHas(_X, _Y).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 17:
	{
		ActiveWord* Bababa = GameMode->SpawnActive(_X, _Y, "Open").get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 18:
	{
		ActiveWord* Bababa = GameMode->SpawnActive(_X, _Y, "Shut").get();
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
	break;
	case 41:
	{
		NameWord* Bababa = GameMode->SpawnName(_X, _Y, BabaState::IsAlgae).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 42:
	{
		NameWord* Bababa = GameMode->SpawnName(_X, _Y, BabaState::IsBox).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 43:
	{
		NameWord* Bababa = GameMode->SpawnName(_X, _Y, BabaState::IsDoor).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 44:
	{
		NameWord* Bababa = GameMode->SpawnName(_X, _Y, BabaState::IsCrab).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 45:
	{
		NameWord* Bababa = GameMode->SpawnName(_X, _Y, BabaState::IsJelly).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 46:
	{
		NameWord* Bababa = GameMode->SpawnName(_X, _Y, BabaState::IsPillar).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 47:
	{
		NameWord* Bababa = GameMode->SpawnName(_X, _Y, BabaState::IsKey).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 48:
	{
		NameWord* Bababa = GameMode->SpawnName(_X, _Y, BabaState::IsStar).get();
		Baba = static_cast<ABabaBase*>(Bababa);
	}
	break;
	case 51:
	{
		Baba = GameMode->SpawnBaba(_X, _Y, "Algae").get();
	}
	break;
	case 52:
	{
		Baba = GameMode->SpawnBaba(_X, _Y, "Box").get();
	}
	break;
	case 53:
	{
		Baba = GameMode->SpawnBaba(_X, _Y, "Door").get();
	}
	break;
	case 54:
	{
		Baba = GameMode->SpawnBaba(_X, _Y, "Crab").get();
	}
	break;
	case 55:
	{
		Baba = GameMode->SpawnBaba(_X, _Y, "Jelly").get();
	}
	break;
	case 56:
	{
		Baba = GameMode->SpawnBaba(_X, _Y, "Pillar").get();
	}
	break;
	case 57:
	{
		Baba = GameMode->SpawnBaba(_X, _Y, "Key").get();
	}
	break;
	case 58:
	{
		Baba = GameMode->SpawnBaba(_X, _Y, "Star").get();
	}
	break;
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
	BabaEditor::GameMode->ContainerReset();
}

void BabaEditor::Save(std::string_view File_Name)
{
	SaveFunction();
	if (TileData.empty() == true) {
		str = "FileSaveFail";
		FileState = true;
		return;
	}

	UEngineSerializer Ser;
	Ser << TileData;
	std::string Str = File_Name.data();
	UEngineFile File = Dir.GetPathFromFile(Str + ".Data");
	File.Open(EIOOpenMode::Write, EIODataType::Binary);
	File.Save(Ser);
	str = "FileSave";
	FileState = true;
}

void BabaEditor::Load(std::string_view File_Name)
{
	ClearAll();
	TileData.clear();
	UEngineSerializer Ser;
	std::string Str = File_Name.data();
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

