#include <iostream>
#include <vector>
#include <SDL/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

using namespace std;

float randomFloat()
{
	return 1.0f;
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


auto bunnys = vector<bunny_data>();

SDL_Window* window;
SDL_Renderer* renderer;

bool key_pressed = false;

void init()
{

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
    SDL_SetRenderDrawColor(renderer, 255, 0, key_pressed ? 255 : 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}

int EventHandler(void *userdata, SDL_Event *event) {
  int mod;

  switch(event->type) {
    case SDL_KEYUP:
			key_pressed = false;
      break;
    case SDL_KEYDOWN:
			key_pressed = true;
			std::cout << "KeyDown" << std::endl;
      break;
  }
  return 0;
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("test", 0, 0, width, height, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    SDL_GL_SetSwapInterval(1);
		init();

		#ifdef __EMSCRIPTEN__
		  emscripten_SDL_SetEventHandler(EventHandler, 0);
			SDL_StartTextInput();
			emscripten_set_main_loop(frame, -1, 1);
		#endif

}
