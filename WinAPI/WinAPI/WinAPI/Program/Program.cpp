#include "framework.h"
#include "Program.h"

#include "Scene/PaintScene.h"
#include "Scene/CollisionScene.h"
#include "Scene/LineScene.h"
#include "Scene/LineCollisionScene.h"
#include "Scene/CannonScene.h"
#include "Scene/FortressScene.h"
#include "Scene/MazeScene.h"
#include "Scene/ArkanoidScene.h"

HDC Program::backbuffer = nullptr;

Program::Program()
{
	srand(time(nullptr));

	//_scene = make_shared<PaintScene>();
	//_scene = make_shared<CollisionScene>();
	//_scene = make_shared<LineScene>();
	//_scene = make_shared<LineCollisionScene>();
	//_scene = make_shared<CannonScene>();
	//_scene = make_shared<FortressScene>();
	_scene = make_shared<MazeScene>();
	//_scene = make_shared<ArkanoidScene>();

	HDC hdc = GetDC(hWnd);

	backbuffer = CreateCompatibleDC(hdc);
	_hBitMap = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT); // 그림을 그릴 도화지
	SelectObject(backbuffer, _hBitMap);
}

Program::~Program()
{
}

void Program::Update()
{
	_scene->Update();
}

void Program::Render(HDC hdc)
{
	_scene->Render(hdc);

	PatBlt(backbuffer, 0, 0, WIN_WIDTH, WIN_HEIGHT, WHITE);

	_scene->Render(backbuffer);

	// 복사
	BitBlt(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT,
		backbuffer, 0, 0, SRCCOPY);
}
