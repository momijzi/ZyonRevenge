#include"Shadow.h"


Shadow::Shadow()
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			//影の配列の初期化
			stageShadow[x][y] = false;
		}
	}
	lightWay = 0;
	X = -1, Y = -1;
}
Shadow::~Shadow()
{

}
void Shadow::MoveLight(int l)
{
	lightWay += l;

	//範囲外に値が行ったとき最初または最後に戻す
	if (lightWay > 3)
	{
		lightWay = 0;
	}
	else if (lightWay < 0)
	{
		lightWay = 3;
	}
}

void Shadow::MoveShadow(int x, int y, int m)
{
	//２より大きいのは定数となっている壁なので定数分だけマイナス
	if (m > 2)
	{
		m -= 2;
	}
	//なにも受け付けない外壁はマイナスなので正の数に変更
	else if (m < 0)
	{
		m = m * -1;
	}
	for (int shadow = 1; shadow <= m; shadow++)
	{
		X = -1, Y = -1;
		
		switch (lightWay)
		{
			case 0://東
				Y = y;
				X = x - shadow;
				break;
			case 1://南
				X = x;
				Y = y - shadow;
				break;
			case 2://西
				X = x + shadow;
				Y = y;
				break;
			case 3://北
				X = x;
				Y = y + shadow;
				break;
		}
		if (X >= 0 && X < 10 && Y >= 0 && Y < 10)
		{
			stageShadow[Y][X] = true;
		}
	}
}


void Shadow::DrawShadow(int x , int y ,int Pixel,int px,int py, Sprite *sprite, Texture &tex,int sw,int sh)
{
	if (stageShadow[y][x] == true)
	{
		sprite->SetPos( Pixel * x - Pixel * px + sw / 2,
			 Pixel * y - Pixel * py + sh / 2);
		sprite->Draw(tex);
	}
}
