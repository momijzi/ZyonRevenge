#include"Player.h"



//�R���X�g���N�^�Ƃ������̏�����
Player::Player()
{
	playerX = 1 ;//�z��Ȃ̂Ł@-1�̐�����͂���
	playerY = 8 ;
	mPlayerX = 0;
	mPlayerY = 0;
	//pWay = UP;
}
//�f�X�g���N�^�Ƃ������̉��
Player::~Player()
{

}

void Player::movePlayer(int map)
{
	//���ł���Ȃ�i�߂�
	if (map == 0 || map == -2)
	{
		playerX += mPlayerX;
		playerY += mPlayerY;

		//if (mPlayerX == 0 && mPlayerY < 0)
		//{
		//	pWay = UP;//��
		//}
		//else if (mPlayerX == 0 && mPlayerY > 0)
		//{
		//	pWay = DOWN;//��
		//}
		//else if (mPlayerX < 0 && mPlayerY == 0)
		//{
		//	pWay = LEFT;//��
		//}
		//else
		//{
		//	pWay = RIGHT;//�E
		//}
	}
}


void Player::Drawplayer(int screenWidth, int screenHeight,Sprite *sprite,Texture &tex)
{
	sprite->SetPos(screenWidth / 2, screenHeight / 2);
	sprite->Draw(tex);
}

