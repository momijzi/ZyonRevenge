#pragma once

#include"Texture.h"
#include"Sprite.h"

class Player
{
private:


public:
	//�v���C���[�̍��WX
	int playerX;
	//�v���C���[�̍��WY
	int playerY;

	Player();
	~Player();

	int mPlayerX, mPlayerY;

	void movePlayer();
	void Drawplayer(int Pixel, int screenWidth, int screenHeight,Sprite sprite,Texture tex);

};