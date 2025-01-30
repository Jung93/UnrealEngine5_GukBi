#include "framework.h"
#include "Program.h"

#include "Scene/PaintScene.h"
#include "Scene/CollisionScene.h"
#include "Scene/LineScene.h"
#include "Scene/LineCollisionScene.h"
#include "Scene/CannonScene.h"
#include "Scene/FortressScene.h"

Program::Program()
{
	//_scene = make_shared<PaintScene>();
	//_scene = make_shared<CollisionScene>();
	//_scene = make_shared<LineScene>();
	//_scene = make_shared<LineCollisionScene>();
	//_scene = make_shared<CannonScene>();
	_scene = make_shared<FortressScene>();
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

}
