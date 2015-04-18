#include "Globals.h"

void Play()
{
  bool quit = false;
  SDL_Event e;
  while(quit == false)
  {
    while(SDL_PollEvent(&e) !=0 )
    {
      //This is where we repond to events
      if(e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
      {
        quit = true;
      }
      
       //This is where we STOP reponding to events
    }
    //This is where we Draw!!!!
    MattsFunction();
    
  }
}
