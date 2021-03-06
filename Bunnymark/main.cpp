#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <GLES2/gl2.h>
#include <EGL/egl.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

using namespace std;

float randomFloat()
{
	return (rand() % 10001) / 10000.0f;
}



SDL_Window* window;
SDL_Renderer* renderer;

SDL_Surface *bunny_image;
SDL_Texture *bunny_tex;

void RenderBear(float x, float y, float angle)
{
	SDL_Point center = {13,18};
	SDL_Rect dstrect;

	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = 26;
	dstrect.h = 37;

	SDL_RenderCopyEx (renderer, bunny_tex, NULL, &dstrect, angle, &center, SDL_FLIP_NONE);
}

void init()
{
	//IMG_Init(IMG_INIT_PNG);
	bunny_image = IMG_Load("data/bunny.png");

	if (!bunny_image)
  {
     cout << "IMG_Load: " << IMG_GetError() << endl;
     return;
  }

	bunny_tex = SDL_CreateTextureFromSurface(renderer, bunny_image);



}

//TODO
void deinit()
{
	SDL_DestroyTexture (bunny_tex);
	SDL_FreeSurface (bunny_image);
}




auto amount = 100;

bool key_pressed = false;

GLuint vertexPosObject;


//GLfloat vVerticesData[200000 * ]

#include "renderer.h"
#include "bunnies.h"


int EventHandler(SDL_Event *event) {
  int mod;

  switch(event->type) {
		case SDL_FINGERUP:
    case SDL_MOUSEBUTTONUP:
			key_pressed = false;

			{
				cout << "Bunnies: " << bunnies.size() << endl;
			}
      break;
		case SDL_FINGERDOWN:
    case SDL_MOUSEBUTTONDOWN:
			key_pressed = true;
      break;
  }
  return 0;
}


void poll_events()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		EventHandler(&event);
	};
}


int frames_fps = 60 * 3;
Uint64 LastCounter = 0;

void frame()
{
		static Uint64 PerfCountFrequency = SDL_GetPerformanceFrequency();
		static unsigned frame_count = 0;
		frame_count++;


		if (frame_count % frames_fps == 0)
		{
			LastCounter = SDL_GetPerformanceCounter();
		}
		if (frame_count % frames_fps == 1)
		{
			auto CounterElapsed = SDL_GetPerformanceCounter() - LastCounter;
			auto MSPerFrame = (((1000.0f * CounterElapsed) / (float)PerfCountFrequency));
			cout << "Frame: " << MSPerFrame << "ms" << " FPS: " << (1000.0f/MSPerFrame) << endl;
		}

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //SDL_RenderClear(renderer);
		glDisable(GL_DEPTH_TEST);

		static bool first = true;

		if (first)
		{
			glRenderer.Init();
			glGenBuffers(1, &vertexPosObject);
			DrawBunnies();
			first = false;
		}

		DrawBunniesGL();

	  //SDL_SetRenderDrawColor(renderer, 255, 0, key_pressed ? 255 : 0, 255);
    //SDL_RenderFillRect(renderer, &rect);
		//RenderBear(10.0f, 10.0f, 0.0f);
		//drawGL();


		glRenderer.DrawBatched();

    SDL_RenderPresent(renderer);




		poll_events();
}


int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("test", 0, 0, width, height, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    SDL_GL_SetSwapInterval(1);
		init();

		InitBunnies();

		#ifdef __EMSCRIPTEN__
		  //emscripten_SDL_SetEventHandler(EventHandler, 0);
			SDL_StartTextInput();
			emscripten_set_main_loop(frame, -1, 1);
		#endif

}
