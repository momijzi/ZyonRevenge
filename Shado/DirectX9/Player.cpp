#include"Player.h"



//�R���X�g���N�^�Ƃ������̏�����
Player::Player()
{
	playerX = 0;
	playerY = 0;
	mPlayerX = 0;
	mPlayerY = 0;
}
//�f�X�g���N�^�Ƃ������̉��
Player::~Player()
{

}

void Player::movePlayer()
{
	playerX += mPlayerX;
	playerY += mPlayerY;
}

void Player::Drawplayer(int screenWidth, int screenHeight,Sprite *sprite,Texture &tex)
{
	sprite->SetPos(screenWidth / 2, screenHeight / 2);
	sprite->Draw(tex);
}

