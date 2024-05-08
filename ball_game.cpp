#define OLC_PGE_APPLICATION
#include <iostream>
#include <vector>
#include <algorithm>
#include "olcPixelGameEngine.h"

class BallGame : public olc::PixelGameEngine
{
public:
	BallGame()
	{
		sAppName = "BallGame";
	}


private:

	// player ball object
	float fBallX;
	float fBallY;
	float fBallVelX;
	float fBallVelY;
	bool bBallCaught;
    float fMouseStartX;
    float fMouseStartY;


protected:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		fBallX = ScreenWidth() / 2.0f;
		fBallY = ScreenHeight() / 2.0f;
		fBallVelX = 0.0f;
		fBallVelY = 0.0f;
		bBallCaught = false;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
	 
        // handling ball movement
        if (!bBallCaught)
        {
            // checks colision with walls
            if (fBallX <= 10 || fBallX >= ScreenWidth() - 10)
                fBallVelX = -fBallVelX;
            if (fBallY <= 10 || fBallY >= ScreenHeight() - 10)
                fBallVelY = -fBallVelY;

            // Ball position update
            fBallX += fBallVelX * fElapsedTime;
            fBallY += fBallVelY * fElapsedTime;

            // Ball drop simulation
            fBallVelY += 100.0f * fElapsedTime; // Przyspieszenie grawitacyjne
        }

        // Drawing a ball
        Clear(olc::BLACK);
        FillCircle(fBallX, fBallY, 10, olc::WHITE);

        // Checking whether the user released the ball
        if (GetMouse(0).bReleased && bBallCaught)
        {
            // Calculation of ball speed based on mouse movement
            fBallVelX = (GetMouseX() - fMouseStartX) * 2.0f;
            fBallVelY = (GetMouseY() - fMouseStartY) * 2.0f;
            bBallCaught = false;
        }

        // Checking whether the user clicked the ball
        if (GetMouse(0).bPressed && !bBallCaught)
        {
            // Checking whether the mouse cursor is over the ball
            if (GetMouseX() >= fBallX - 10 && GetMouseX() <= fBallX + 10 &&
                GetMouseY() >= fBallY - 10 && GetMouseY() <= fBallY + 10)
            {
                // Catching the ball by the user
                bBallCaught = true;
                fMouseStartX = GetMouseX();
                fMouseStartY = GetMouseY();
            }
        }

        // If the user is holding the ball, set its position to the position of the mouse cursor
        if (bBallCaught)
        {
            fBallX = GetMouseX();
            fBallY = GetMouseY();
        }

		return true;
	}
};


int main()
{
	BallGame game;
	if (game.Construct(256, 240, 4, 4))
		game.Start();

	return 0;
}