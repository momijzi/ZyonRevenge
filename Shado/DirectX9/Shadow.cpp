#include"Shadow.h"
#include"Sprite.h"
#include"Texture.h"

Shadow::Shadow()
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			//‰e‚Ì”z—ñ‚Ì‰Šú‰»
			stageShadow[x][y] = false;
		}
	}
}
Shadow::~Shadow()
{

}

void Shadow::DrawShadow(int x , int y ,int Pixel)
{
	Sprite sSprite;
	sSprite.SetSize(Pixel, Pixel);
	sSprite.SetAngle(0);

	Texture Shadow;
	Shadow.Load(_T("Texture/Shadow.png"));

	if (stageShadow[y][x] == true)
	{
		sSprite.SetPos(Pixel / 2 + Pixel * x, Pixel / 2 + Pixel * y);
		sSprite.Draw(Shadow);
	}
}
