#include"Shadow.h"


Shadow::Shadow()
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			//�e�̔z��̏�����
			stageShadow[x][y] = false;
		}
	}
	lightWay = WEST;
}
Shadow::~Shadow()
{

}

void Shadow::MoveShadow(int x, int y, int m)
{
	for (int shadow = 0; shadow < m; shadow++)
	{
		switch (lightWay)
		{
			case EAST://��
				stageShadow[y][x + shadow] = true;
				break;
			case WEST://��
				shadow * -1;
				stageShadow[y][x + shadow] = true;
				break;
			case SOUTH://��
				stageShadow[y + shadow][x] = true;
				break;
			case NORTH://�k
				shadow * -1;
				stageShadow[y + shadow][x] = true;
				break;
		}
	}
}


void Shadow::DrawShadow(int x , int y ,int Pixel, Sprite sprite, Texture tex)
{
	if (stageShadow[y][x] == true)
	{
		sprite.SetPos(Pixel / 2 + Pixel * x, Pixel / 2 + Pixel * y);
		sprite.Draw(tex);
	}
}
