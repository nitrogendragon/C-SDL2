#pragma once
//handles selection of animations and their various playback properties
//takes in index, frames and speed all as ints
struct Animation
{
	int index;
	int frames;
	int speed;

	Animation(){}
	//takes in index, frames and speed all as ints
	Animation(int i, int f, int s)
	{
		index = i;
		frames = f;
		speed = s;
	}
};