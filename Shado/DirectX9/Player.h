#pragma once

#include"Texture.h"
#include"Sprite.h"

class Player
{
private:

public:
	
	Player();
	~Player();

	//プレイヤーの現在座標
	int playerX, playerY;

	//プレイヤーの現在向いている方向
	//enum PlayerWay{UP,DOWN,LEFT,RIGHT};
	//PlayerWay pWay;

	//プレイヤーの移動する方向を決めるための変数
	int mPlayerX, mPlayerY;

	//プレイヤー移動
	void movePlayer(int map);

	//プレイヤー描画
	void Drawplayer(int screenWidth, int screenHeight,Sprite *sprite,Texture &tex);

};