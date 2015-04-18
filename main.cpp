CONST INT SCREEN_W = 720;
CONST INT SCREEN_H = 480;

int main(int argc, char* args[])
{
  if(//Place the initialize function here)
  {
    std::cout << "SDL cant Init =[ : " << SDL_GetError() << std::endl;
    return -1;
  }
  else
  {
    Play();
  }
  
  //Place the SDL_Close Function here before the return;
  return 0;
}
