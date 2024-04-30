#include "PreCompile.h"
#include "BabaEditor.h"
#include "PlayGameMode.h"
#include "ContentsHelper.h"
#include "BabaBase.h"
#include "ActiveWord.h"
#include "NameWord.h"
#include "IsWord.h"
#include "AndWord.h"


BabaEditor::BabaEditor()
{
	Off();
}

BabaEditor::~BabaEditor()
{
}

void BabaEditor::EditorFunction(int _LocationX, int _LocationY, int _Num)
{
	TileData.push_back(Location[_LocationX]);
	TileData.push_back(Location[_LocationY]);
	TileData.push_back(_Num);
	EditorSwitch(Location[_LocationX], Location[_LocationY], _Num);
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

	Int2D I2D = MousePosCul(Level);
	ImGui::Text(("Mouse intX : " + (std::to_string(I2D.X))).c_str());
	ImGui::Text(("Mouse intY : " + (std::to_string(I2D.Y))).c_str());


	if (true == ImGui::Button("Baba")) {
		{
			TileData.push_back(Location[0]);
			TileData.push_back(Location[1]);
			TileData.push_back(1);
			EditorSwitch(Location[0], Location[1], 1);
		}
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
		TileData.push_back(3);
		EditorSwitch(Location[0], Location[1], 3);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Flag")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(4);
		EditorSwitch(Location[0], Location[1], 4);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Skull")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(5);
		EditorSwitch(Location[0], Location[1], 5);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Water")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(6);
		EditorSwitch(Location[0], Location[1], 6);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Lava")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(7);
		EditorSwitch(Location[0], Location[1], 7);
	}


	if (true == ImGui::Button("Is")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(11);
		EditorSwitch(Location[0], Location[1], 11);
	}

	ImGui::SameLine();
	if (true == ImGui::Button("And")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(12);
		EditorSwitch(Location[0], Location[1], 12);
	}

	if (true == ImGui::Button("You")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(20);
		EditorSwitch(Location[0], Location[1], 20);
	}

	ImGui::SameLine();
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
	if (true == ImGui::Button("Stop")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(23);
		EditorSwitch(Location[0], Location[1], 23);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Hot")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(24);
		EditorSwitch(Location[0], Location[1], 24);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Pull")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(25);
		EditorSwitch(Location[0], Location[1], 25);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Win")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(26);
		EditorSwitch(Location[0], Location[1], 26);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Defeat")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(27);
		EditorSwitch(Location[0], Location[1], 27);
	}

	ImGui::SameLine();
	if (true == ImGui::Button("Sink")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(29);
		EditorSwitch(Location[0], Location[1], 29);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("Float")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(30);
		EditorSwitch(Location[0], Location[1], 30);
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
	ImGui::SameLine();
	if (true == ImGui::Button("NameRock")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(33);
		EditorSwitch(Location[0], Location[1], 33);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("NameFlag")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(34);
		EditorSwitch(Location[0], Location[1], 34);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("NameSkull")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(35);
		EditorSwitch(Location[0], Location[1], 35);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("NameWater")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(36);
		EditorSwitch(Location[0], Location[1], 36);
	}
	ImGui::SameLine();
	if (true == ImGui::Button("NameLava")) {
		TileData.push_back(Location[0]);
		TileData.push_back(Location[1]);
		TileData.push_back(37);
		EditorSwitch(Location[0], Location[1], 37);
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
			EditorSwitch(TileData[Index], TileData[Index + 1], TileData[Index + 2]);
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

void BabaEditor::EditorSwitch(int _X, int _Y, int _Index)
{
	switch (_Index)
	{
	case 1:
		Tiles.push_back(GameMode->SpawnBaba(_X, _Y, "Baba").get());
		break;
	case 2:
		Tiles.push_back(GameMode->SpawnBaba(_X, _Y, "Wall").get());
		break;
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
	case 11:
	{
		IsWord* Baba = GameMode->SpawnIs(_X, _Y).get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 12:
	{
		AndWord* Baba = GameMode->SpawnAnd(_X, _Y).get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 20:
	{
		ActiveWord* Baba = GameMode->SpawnActive(_X, _Y, "You").get();
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
		ActiveWord* Baba = GameMode->SpawnActive(_X, _Y, "Stop").get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 24:
	{
		ActiveWord* Baba = GameMode->SpawnActive(_X, _Y, "Hot").get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 25:
	{
		ActiveWord* Baba = GameMode->SpawnActive(_X, _Y, "Pull").get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 26:
	{
		ActiveWord* Baba = GameMode->SpawnActive(_X, _Y, "Win").get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 27:
	{
		ActiveWord* Baba = GameMode->SpawnActive(_X, _Y, "Defeat").get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	//case 28:
	//{
	//	ActiveWord* Baba = GameMode->SpawnActive(_X, _Y, "Hot").get();
	//	ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
	//	Tiles.push_back(Bababa);
	//}
	//break;
	case 29:
	{
		ActiveWord* Baba = GameMode->SpawnActive(_X, _Y, "Sink").get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 30:
	{
		ActiveWord* Baba = GameMode->SpawnActive(_X, _Y, "Float").get();
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
	case 33:
	{
		NameWord* Baba = GameMode->SpawnName(_X, _Y, BabaState::IsRock).get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 34:
	{
		NameWord* Baba = GameMode->SpawnName(_X, _Y, BabaState::IsFlag).get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 35:
	{
		NameWord* Baba = GameMode->SpawnName(_X, _Y, BabaState::IsSkull).get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 36:
	{
		NameWord* Baba = GameMode->SpawnName(_X, _Y, BabaState::IsWater).get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	case 37:
	{
		NameWord* Baba = GameMode->SpawnName(_X, _Y, BabaState::IsLava).get();
		ABabaBase* Bababa = static_cast<ABabaBase*>(Baba);
		Tiles.push_back(Bababa);
	}
	break;
	default:
		break;
	}
}
