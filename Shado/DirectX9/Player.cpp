#include"Player.h"



//コンストラクタという名の初期化
Player::Player()
{
	playerX = 1 ;//配列なので　-1の数を入力せよ
	playerY = 8 ;
	mPlayerX = 0;
	mPlayerY = 0;
	//pWay = UP;
}
//デストラクタという名の解放
Player::~Player()
{

}

void Player::movePlayer(int map)
{
	//床であるなら進める
	if (map == 0 || map == -2)
	{
		playerX += mPlayerX;
		playerY += mPlayerY;

		//if (mPlayerX == 0 && mPlayerY < 0)
		//{
		//	pWay = UP;//上
		//}
		//else if (mPlayerX == 0 && mPlayerY > 0)
		//{
		//	pWay = DOWN;//下
		//}
		//else if (mPlayerX < 0 && mPlayerY == 0)
		//{
		//	pWay = LEFT;//左
		//}
		//else
		//{
		//	pWay = RIGHT;//右
		//}
	}
}


void Player::Drawplayer(int screenWidth, int screenHeight,Sprite *sprite,Texture &tex)
{
	sprite->SetPos(screenWidth / 2, screenHeight / 2);
	sprite->Draw(tex);
}

