#include"Map.h"
#include"Sprite.h"
#include"Texture.h"

Map::Map()
{

}

Map::~Map()
{

}

void Map::DrawMap(int x,int y,int Pixel,int playerX,int playerY)
{
	Sprite mSprite;
	mSprite.SetSize(Pixel, Pixel);
	mSprite.SetAngle(0);

	Texture Block00;
	Block00.Load(_T("Texture/Box00.png"));
	Texture Block01;
	Block01.Load(_T("Texture/Box01.png"));
	Texture Block02;
	Block02.Load(_T("Texture/Box02.png"));
	Texture Block03;
	Block03.Load(_T("Texture/Box03.png"));
	Texture Cursor;
	Cursor.Load(_T("Texture/Cursor.png"));

	//ƒ}ƒbƒv‚Ì•`‰æ
	if (stageMapT1[y][x] == 1)
	{
		mSprite.SetPos(Pixel / 2 + Pixel * x - Pixel * playerX, Pixel / 2 + Pixel * y - Pixel * playerY);
		mSprite.Draw(Block00);
	}
	else if (stageMapT1[x][y] == 2)
	{
		mSprite.SetPos(Pixel / 2 + Pixel * x - Pixel * playerX, Pixel / 2 + Pixel * y - Pixel * playerY);
		mSprite.Draw(Block01);
	}
	else if (stageMapT1[x][y] == 3)
	{
		mSprite.SetPos(Pixel / 2 + Pixel * x - Pixel * playerX, Pixel / 2 + Pixel * y - Pixel * playerY);
		mSprite.Draw(Block02);
	}
	else if (stageMapT1[x][y] == 4)
	{
		mSprite.SetPos(Pixel / 2 + Pixel * x - Pixel * playerX, Pixel / 2 + Pixel * y - Pixel * playerY);
		mSprite.Draw(Block03);
	}
}