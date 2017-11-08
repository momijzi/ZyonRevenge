#include"Player.h"
#include"Sprite.h"
#include"Texture.h"

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

void Player::Drawplayer(int Pixel , int screenWidth, int screenHeight)
{
	Sprite pSprite;
	pSprite.SetSize(Pixel, Pixel);
	pSprite.SetAngle(0);

	Texture player;
	player.Load(_T("Texture/Player.png"));

	pSprite.SetPos(screenWidth / 2, screenHeight / 2);
	pSprite.Draw(player);
}

