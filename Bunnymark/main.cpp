#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

using namespace std;



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






float randomFloat()
{
	return (rand() % 10001) / 10000.0f;
}


auto width = 800;
auto height = 600;

auto gravity = 0.5;//1.5

auto maxX = width;
auto minX = 0;
auto maxY = height;
auto minY = 0;

auto startBunnyCount = 2;
auto isAdding = false;

auto amount = 100;

struct bunny_data
{
	struct
	{
		float x = 0.0f;
		float y = 0.0f;
	} position;

	float speedX = 0.0f;
	float speedY = 0.0f;
	float scale = 1.0f;
	float rotation  = 0.0f;

	void randomize()
	{
		speedX = randomFloat() * 10.0f;
		speedY = randomFloat() * 10.f - 5.0f;
		scale = 0.5f + randomFloat() * 0.5f;
		rotation = randomFloat() - 0.5f;

		//var random = Math2.randomInt(0, container.children.length-2);
	}

	void draw()
	{
		RenderBear(position.x, position.y, rotation);
	}

	void update()
	{
		auto &bunny = *this;
		//so wrong
		bunny.position.x += bunny.speedX;
		bunny.position.y += bunny.speedY;
		bunny.speedY += gravity;

		if (bunny.position.x > maxX)
		{
			bunny.speedX *= -1;
			bunny.position.x = maxX;
		}
		else if (bunny.position.x < minX)
		{
			bunny.speedX *= -1;
			bunny.position.x = minX;
		}

		if (bunny.position.y > maxY)
		{
			bunny.speedY *= -0.85;
			bunny.position.y = maxY;
			//bunny.spin = (randomFloat()-0.5) * 0.2  so crappy
			if (randomFloat() > 0.5)
			{
				bunny.speedY -= randomFloat() * 6;
			}
		}
		else if (bunny.position.y < minY)
		{
			bunny.speedY = 0;
			bunny.position.y = minY;
		}
	}
};


auto bunnies = vector<bunny_data>();


bool key_pressed = false;

void DrawBunnies()
{
	for(auto& bunny : bunnies)
	{
		bunny.update();
		bunny.draw();
	}

	if (!key_pressed)
	return;

	for (auto i = 0; i < amount; i++)
	{
		bunnies.emplace_back();
		bunnies.back().randomize();
	}

}

void InitBunnies()
{
	for (auto i = 0; i < startBunnyCount; i++)
	{
		bunnies.emplace_back();
		bunnies.back().randomize();
	}
}


int EventHandler(SDL_Event *event) {
  int mod;

  switch(event->type) {
    case SDL_MOUSEBUTTONUP:
			key_pressed = false;
      break;
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

void frame()
{
    static int x = 0;
    static int y = 0;
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = 100;
    rect.h = 100;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

		DrawBunnies();
	  //SDL_SetRenderDrawColor(renderer, 255, 0, key_pressed ? 255 : 0, 255);
    //SDL_RenderFillRect(renderer, &rect);
		//RenderBear(10.0f, 10.0f, 0.0f);

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
