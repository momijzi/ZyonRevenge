#pragma once

#include"Texture.h"
#include"Sprite.h"


class Shadow
{
private:

	
public:
	
	Shadow();
	~Shadow();

	//影が出るかどうか
	bool stageShadow[10][10];
	int lightWay;//光のある方向　東、南、西、北
	int X, Y;

	void MoveLight(int l);
	void SetLight() { lightWay = 0; }
	void MoveShadow(int x, int y , int m);
	void DrawShadow(int x, int y,int Pixel,int px,int py,Sprite *sprite,Texture &tex, int sw, int sh);

};
