#pragma once
#include "ECS.h"
//component class for getting, setting up, and updating x,y position of entities
class PositionComponent : public Component
{
private:
	//xpos for component
	int xpos;
	//ypos for component
	int	ypos;
public:
	
	PositionComponent(int x=0, int y=0)
	{
		xpos = x;
		ypos = y;
	}
	//return xpos so we can get the value
	int x() { return xpos; }
	//return ypos so we can get the value
	int y() { return ypos; }
	//like unity onAwake so as it starts up we set the x and y pos to 0
	void init() override
	{
		xpos = 0;
		ypos = 0;
	}

	void update() override
	{
		xpos++;
		ypos++;
	}
	//literally sets the x and y pos to wahtever we set the parameters to
	void setPos(int x, int y)
	{
		xpos = x;
		ypos = y;
	}


};