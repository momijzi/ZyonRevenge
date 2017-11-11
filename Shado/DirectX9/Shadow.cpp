#include"Shadow.h"


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
	lightWay = 0;
}
Shadow::~Shadow()
{

}

void Shadow::MoveShadow(int x, int y, int m)
{
	if (m > 1)
	{
		m--;
	}
	for (int shadow = 1; shadow <= m; shadow++)
	{
		switch (lightWay)
		{
			case 0://“Œ
				stageShadow[y][x - shadow] = true;
				break;
			case 1://“ì
				stageShadow[y - shadow][x] = true;
				break;
			case 2://¼
				stageShadow[y][x + shadow ] = true;
				break;
			case 3://–k
				stageShadow[y + shadow ][x] = true;
				break;
		}
	}
}


void Shadow::DrawShadow(int x , int y ,int Pixel,int px,int py, Sprite *sprite, Texture &tex)
{
	if (stageShadow[y][x] == true)
	{
		sprite->SetPos(Pixel / 2 + Pixel * x - Pixel * px, Pixel / 2 + Pixel * y - Pixel * py);
		sprite->Draw(tex);
	}
}
