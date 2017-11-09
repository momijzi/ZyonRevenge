#pragma once

#include"Texture.h"
#include"Sprite.h"

class Player
{
private:


public:
	//プレイヤーの座標X
	int playerX;
	//プレイヤーの座標Y
	int playerY;

	Player();
	~Player();

	int mPlayerX, mPlayerY;

	void movePlayer();
	void Drawplayer(int Pixel, int screenWidth, int screenHeight,Sprite sprite,Texture tex);

};