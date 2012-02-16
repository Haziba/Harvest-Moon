//================
//    HEADERS
//================
#include <stdint.h>
#include "gba.h"
#include "sprites.h"


enum directions { LEFT, RIGHT, UP, DOWN };

int min(int a, int b)
{
	return (a > b ? b : a);
}

int max(int a, int b)
{
	return (a < b ? b : a);
}

// Returns the number input as long as it is within the two set boundaries. If it isn't, returns the closest boundary
int constrain(int num, int minNum, int maxNum)
{
	return min(max(num, minNum), maxNum);
}

// Basic two-variable struct for recording vectors and such
struct coord
{
	int x;
	int y;
	coord()
	{ x=0; y=0; }
	coord(int xSet, int ySet)
	{ x=xSet; y=ySet; }
	coord Plus(int xPlus, int yPlus)
	{ return coord(x + xPlus, y + yPlus); }
	bool Is(coord isLoc)
	{ return x == isLoc.x && y == isLoc.y; }
	coord Times(int multiplier)
	{ return coord(x * multiplier, y * multiplier); }
};

// Iterates through the input sprite printing it to the screen. Does not print
// RGB(31,0,31) colours and doesn't print off the edge of the screen
void DrawSprite(uint16_t *sprite, int width, int height, int x, int y)
{
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
			if(sprite[i * width + j] > 0 && x + j < 240 && x + j >= 0 && y + i < 160 && y + i >= 0)
				PlotPixel8(x + j, y + i, sprite[i * width + j] + 1);
}

void DrawSprite(uint16_t *sprite, int width, int height, coord loc)
{
	DrawSprite(sprite, width, height, loc.x, loc.y);
}

// Class for player controlled character
class Character
{
private:
	enum CharAction {STAND, WALK, WATER, PICKUP};
	coord loc;
	directions direc;
	CharAction action;
	
	// Variables to pace the character's animation
	int animStep;
	int animPause;
	
	int speed;
public:
	Character()
	{
		direc = DOWN;
		action = STAND;
		loc = coord(0, 0);
		speed = 2;
	}

	// Returns last x position on the grid for erasing
	int LastXPos()
	{
		return (loc.x - (direc == RIGHT ? speed : 0)) / 16;
	}

	// Returns last y position on the grid for erasing
	int LastYPos()
	{
		return (loc.y - (direc == DOWN ? speed : 0)) / 16;
	}

	void Walk(directions d)
	{
		// If the player isn't watering or half way through picking up a turnip then walk
		if(action != WATER && (action != PICKUP || (action == PICKUP && animStep == 1)))
		{
			direc = d;
			action = WALK;
			switch(d)
			{
				case LEFT:
					loc.x-=speed;
					break;
				case RIGHT:
					loc.x+=speed;
					break;
				case UP:
					loc.y-=speed;
					break;
				case DOWN:
					loc.y+=speed;
					break;
			}
			// Keep the player within the screen boundaries
			loc.x = constrain(loc.x, 0, 224);
			loc.y = constrain(loc.y, 0, 138);
		}
	}
	
	void PickUp()
	{
		action = PICKUP;
		animPause = 10;
		animStep = 0;
	}

	void Update()
	{
		// Update the animation if the player isn't simply standing or holding a turnip
		if(action != STAND && !(action == PICKUP && animStep == 1))
		{
			if(animPause <= 0)
			{
				animPause = 10;
				animStep = (animStep + 1) % 4;
				if(animStep == 2 && action == WATER)
					action = STAND;
			}
			animPause--;
		}
		else
		{
			if(action == STAND)
				animStep = 0;
			animPause = 10;
		}
		
		// Check input and move character accordingly
		if(!(REG_P1 & KEY_RIGHT))
			Walk(RIGHT);
		else if(!(REG_P1 & KEY_LEFT))
			Walk(LEFT);
		else if(!(REG_P1 & KEY_UP))
			Walk(UP);
		else if(!(REG_P1 & KEY_DOWN))
			Walk(DOWN);
		else if(action != WATER && action != PICKUP)
			action = STAND;
		
		// Check action button (A)
		if(!(REG_P1 & KEY_A) && !(action == WATER || action == PICKUP))
		{
			action = WATER;
			animStep = 0;
			animPause = 10;
		}
	}

	bool Actioning()
	{
		return action == WATER;
	}

	// Returns co-ordinate on 16x16 grid of where the player is watering
	coord WateringLoc()
	{
		switch(direc)
		{
			case UP:
				return coord((loc.x + 8) / 16, (loc.y - 0) / 16);
			case DOWN:
				return coord((loc.x + 8) / 16, (loc.y + 28) / 16);
			case LEFT:
				return coord((loc.x - 8) / 16, (loc.y + 20) / 16);
			case RIGHT:
				return coord((loc.x + 28) / 16, (loc.y + 20) / 16);
			default:
				return coord(0, 0);
		}
	}

	// Deletes where the character last was by redrawing tiles over those spots
	void Erase()
	{
		for(int i = -1; i < 3; i++)
			for(int j = -1; j < 3; j++)
				DrawSprite(_groundSprite, 16, 16, (LastXPos() + i) * 16, (LastYPos() + j) * 16);
	}

	void Draw()
	{
		// Check if character is performing certain tasks in directions that need the image to be translated in some way
		if(action == WATER && (direc == LEFT || direc == RIGHT))
		{
			if(direc == LEFT)
				DrawSprite(CurrentSprite(), 24, 22, loc.Plus(-8, 0));
			else if(direc == RIGHT)
				DrawSprite(CurrentSprite(), 24, 22, loc);
		}
		else
		{
			// If the player is holding a turnip currently draw one just above the player
			if(action == PICKUP && animStep == 1)
				DrawSprite(_turnipHeldSprite, 13, 12, loc.Plus((direc == UP ? 0 : 1), -11));
			DrawSprite(CurrentSprite(), 16, 22, loc);
		}
	}

	uint16_t * CurrentSprite()
	{
		switch(direc)
		{
			case LEFT:
				switch(action)
				{
					case STAND:
						return _standLeftSprite;
					case WALK:
						switch(animStep)
						{
							case 0:
								return _walkLeft1Sprite;
							case 1:
								return _standLeftSprite;
							case 2:
								return _walkLeft2Sprite;
							case 3:
								return _standLeftSprite;
						}
					case WATER:
						switch(animStep)
						{
							case 0:
								return _waterLeft1Sprite;
							case 1:
								return _waterLeft2Sprite;
						}
					case PICKUP:
						switch(animStep)
						{
							case 0:
								return _pickLeft1Sprite;
							case 1:
								return _pickLeft2Sprite;
						}
				}
			case RIGHT:
				switch(action)
				{
					case STAND:
						return _standRightSprite;
					case WALK:
						switch(animStep)
						{
							case 0:
								return _walkRight1Sprite;
							case 1:
								return _standRightSprite;
							case 2:
								return _walkRight2Sprite;
							case 3:
								return _standRightSprite;
						}
					case WATER:
						switch(animStep)
						{
							case 0:
								return _waterRight1Sprite;
							case 1:
								return _waterRight2Sprite;
						}
					case PICKUP:
						switch(animStep)
						{
							case 0:
								return _pickRight1Sprite;
							case 1:
								return _pickRight2Sprite;
						}
				}
			case UP:
				switch(action)
				{
					case STAND:
						return _standUpSprite;
					case WALK:
						switch(animStep)
						{
							case 0:
								return _walkUp1Sprite;
							case 1:
								return _standUpSprite;
							case 2:
								return _walkUp2Sprite;
							case 3:
								return _standUpSprite;
						}
					case WATER:
						switch(animStep)
						{
							case 0:
								return _waterUp1Sprite;
							case 1:
								return _waterUp2Sprite;
						}
					case PICKUP:
						switch(animStep)
						{
							case 0:
								return _pickUp1Sprite;
							case 1:
								return _pickUp2Sprite;
						}
				}
			case DOWN:
				switch(action)
				{
					case STAND:
						return _standDownSprite;
					case WALK:
						switch(animStep)
						{
							case 0:
								return _walkDown1Sprite;
							case 1:
								return _standDownSprite;
							case 2:
								return _walkDown2Sprite;
							case 3:
								return _standDownSprite;
						}
					case WATER:
						switch(animStep)
						{
							case 0:
								return _waterDown1Sprite;
							case 1:
								return _waterDown2Sprite;
						}
					case PICKUP:
						switch(animStep)
						{
							case 0:
								return _pickDown1Sprite;
							case 1:
								return _pickDown2Sprite;
						}
				}
			default:
				return _standDownSprite;
		}
	}
};

// Class for the waterable crops
class Crop
{
private:
	enum CropState { SEED, SPROUT, TURNIP };
	CropState state;
	bool watered;
	coord loc;
	int nextStep;
	uint16_t * CurrentSprite()
	{
		switch(state)
		{
			case SEED:
				if(!watered)
					return _seedSprite;
				else
					return _wSeedSprite;
			case SPROUT:
				if(!watered)
					return _sproutSprite;
				else
					return _wSproutSprite;
			case TURNIP:
				return _turnipSprite;
			default:
				return _seedSprite;
		}
	}
public:
	Crop()
	{
		loc = coord(0,0);
		state = SEED;
		watered = false;
	}
	
	Crop(int x, int y)
	{ loc = coord(x, y); }
	
	bool Is(coord isLoc)
	{ return loc.Is(isLoc); }
	
	bool Action()
	{
		// Water / pick up the crop
		if(state == TURNIP)
		{
			state = SEED;
			watered = false;
			return true;
		}
		else
		{
			if(!watered)
			{
				nextStep = 60;
				watered = true;
			}
		}
		return false;
	}
	
	void Update()
	{
		// If the crop is watered then count down until it steps until the next phase
		if(watered)
		{
			nextStep--;
			if(nextStep <= 0)
			{
				if(state == SEED)
					state = SPROUT;
				else if(state == SPROUT)
					state = TURNIP;
				
				watered = false;
			}
		}
	}
	
	void Draw()
	{
		DrawSprite(CurrentSprite(), 16, 16, loc.Times(16));
	}
};

int main()
{
	REG_DISPCNT = MODE4 | BG2_ENABLE;
	
	Character me = Character();
	
	Crop crops[9];
	
	// Initialise crops
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			crops[i * 3 + j] = Crop(6 + i, 3 + j);
	
	// Initialise palette
	for(int i = 0; i < PALETTE_SIZE; i++)
		SetPaletteBG(i+1, _paletteMap[i]);
	
	FlipBuffers();
	// Draw tiles throughout whole screen
	for(int i = 0; i < 15; i++)
		for(int j = 0; j < 10; j++)
			DrawSprite(_groundSprite, 16, 16, i * 16, j * 16);
	FlipBuffers();
	// Draw tiles throughout whole screen on other buffer
	for(int i = 0; i < 15; i++)
		for(int j = 0; j < 10; j++)
			DrawSprite(_groundSprite, 16, 16, i * 16, j * 16);
	
	while (true)
	{
		FlipBuffers();
		
		me.Erase();
		me.Update();
		
		for(int i = 0; i < 9; i++)
		{
			crops[i].Update();
			crops[i].Draw();
		}
		
		// If the player is doing an action iterate through crops to see if any of them match the location the player
		// is watering and if it does then the crop is the player's target and if so then perform an action on it
		if(me.Actioning())
			for(int i = 0; i < 9; i++)
				if(crops[i].Is(me.WateringLoc()))
					if(crops[i].Action())
						me.PickUp();
		
		me.Draw();
		
		WaitVSync();
	}

	return 0;
}












