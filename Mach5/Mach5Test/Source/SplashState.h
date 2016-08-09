/******************************************************************************/
/*!
\file   SplashState.h
\author Matt Casanova 
\par    email: mcasanov\@digipen.edu
\par    class:
\par    Assignment:
\date   2012/12/6

This is a stage for the Mach5 Engine Demo project. A Splash stage is a good 
place to load data and/or resources that you will need for all of your stages.
*/
/******************************************************************************/
#ifndef SPLASHSTAGE_H
#define SPLASHSTAGE_H

#include "M5Stage.h"

class SplashStage : public M5Stage
{
public:
  virtual void Load(void);
  virtual void Init(void);
  virtual void Update(float dt);
  virtual void Shutdown(void);
  virtual void Unload(void);
private:
  int   m_splashTexture;
  float m_changeTimer;
};


#endif /* SPLASHSTAGE_H */