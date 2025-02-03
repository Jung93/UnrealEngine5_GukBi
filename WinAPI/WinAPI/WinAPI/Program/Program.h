#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();
	void Render(HDC hdc);

	static HDC backbuffer;

private:

	shared_ptr<Scene> _scene;

	HBITMAP _hBitMap;

};

