#pragma once

#include"Texture.h"
#include"Sprite.h"


class Shadow
{
private:

public:
	
	Shadow();
	~Shadow();

	//�e���o�邩�ǂ���
	bool stageShadow[10][10];
	enum LightWay{EAST,WEST,SOUTH,NORTH};
	LightWay lightWay;

	void MoveShadow(int x, int y , int m);
	void DrawShadow(int x, int y,int Pixel,Sprite sprite,Texture tex);

};
