/******************************************************************************/
/*!
file    GameStage1.cpp
\author Matt Casanova 
\par    email: mcasanov\@digipen.edu
\par    Class:Game150
\par    Assignment:Simple Game Engine
\date   2012/12/14

This is a stage in the game demo. This shows some basic features of the 
window and engine.
*/
/******************************************************************************/
#include "GameState1.h"


#include "M5App.h"
#include "M5Input.h"
#include "M5StageMgr.h"
#include "M5Vec2.h"
#include "M5Mtx44.h"
#include "M5Gfx.h"

#include "DemoStates.h"
#include <cstdio>



/*Create a struct of my game shared stage data*/
struct GameStage1Data
{
  bool isFullScreen;
  bool isShowCursor;
  float timer;
  char textAsString[10];
};

/*Create a static variable so it can't be used in other files.*/
static GameStage1Data stageData;

#define M5_MAX_TIME 5.f
#define M5_FONT_OFFSET 4.f

/******************************************************************************/
/*!
We have no resources in this demo stage
*/
/******************************************************************************/
void GameState1Load(void)
{
}
/******************************************************************************/
/*!
Just initialize the values here.
*/
/******************************************************************************/
void GameState1Init(void)
{
  /*Initialize stage data*/
  stageData.isFullScreen = false;
  stageData.isShowCursor = true;
  /*give a time greater than 5 seconds so we don't start with an 
  invisible window*/
  stageData.timer = M5_MAX_TIME + 1.f;
}
/******************************************************************************/
/*!
This is the update.  All of the input and game logic is here for this stage.
*/
/******************************************************************************/
void GameState1Update(float dt)
{
  M5Vec2 mouse;
  M5Vec2 topLeft;
  M5Gfx::GetWorldTopLeft(topLeft);
  
  /*For our font size*/
  float yOffSet = M5_FONT_OFFSET;

  sprintf_s(stageData.textAsString, "%f", dt);

  /*Check for input*/
  if(M5Input::IsTriggered(M5_S))
  {
    stageData.isFullScreen = !stageData.isFullScreen;
    M5App::SetFullScreen(stageData.isFullScreen);
  }
  else if(M5Input::IsTriggered(M5_W))
  {
    M5App::ShowWindow(false);
    stageData.timer = 0.f;
  }
  else if(M5Input::IsTriggered(M5_MOUSE_LEFT))
  {
    stageData.isShowCursor = !stageData.isShowCursor;
    M5App::ShowCursor(stageData.isShowCursor);
  }
  else if(M5Input::IsTriggered(M5_N))
  {
    M5StageMgr::SetNextStage(DS_GAME2);
  }

  /*Check for time*/
  if(stageData.timer < M5_MAX_TIME)
  {
    stageData.timer += dt;
    if(stageData.timer > M5_MAX_TIME)
    {
      /*Reset our windows and view port*/
      M5App::ShowWindow(true);
    }
  }

    /*Make sure drawing is in world space*/
  M5Gfx::SetToPerspective();

  /*Get mouse click in screen space*/
  M5Input::GetMouse(mouse);
  /*Convert into world space*/
  M5Gfx::ConvertScreenToWorld(mouse.x, mouse.y);



  /*Start drawing*/
  M5Gfx::StartScene();

  /*Draw my different text starting at the top corner*/
  M5Gfx::SetTextureColor(0xFFFFFFFF);
  topLeft.y -= yOffSet;
  M5Gfx::WriteText("S: Toggle full screen", topLeft.x, topLeft.y);

  M5Gfx::SetTextureColor(0xFF0000FF);
  topLeft.y -= yOffSet;
  M5Gfx::WriteText("W: Toggle showing the window", topLeft.x, topLeft.y);

  M5Gfx::SetTextureColor(0xFF00FFFF);
  topLeft.y -= yOffSet;
  M5Gfx::WriteText("N: Continue", topLeft.x, topLeft.y);

  /*Draw some text at the mouse position*/
  M5Gfx::SetTextureColor(0xFFFF00FF);
  M5Gfx::WriteText("Click: Toggle cursor", mouse.x, mouse.y);

  M5Gfx::SetToOrtho();
  M5Gfx::WriteText(stageData.textAsString, 100, 100);

  /*End drawing*/
  M5Gfx::EndScene();

}
/******************************************************************************/
/*!
I don't have any resources to shutdown.

*/
/******************************************************************************/
void GameState1Shutdown(void)
{

}
/******************************************************************************/
/*!
I don't have any textures to unload, but since I changed the color, I reset 
the to the default.

\param pGameData
A pointer to the shared gameData.
*/
/******************************************************************************/
void GameState1Unload(void)
{
  /*Reset color*/
  M5Gfx::SetTextureColor(0xFFFFFFFF);
}