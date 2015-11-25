
auto width = 800;
auto height = 600;

auto gravity = 0.5;//1.5

auto maxX = width;
auto minX = 0;
auto maxY = height;
auto minY = 0;

auto startBunnyCount = 2;


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

  void drawGL()
	{
		::drawGL(position.x, position.y);
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

void DrawBunnies()
{
	for(auto& bunny : bunnies)
	{
		bunny.update();
		bunny.draw();
	}

	if (!key_pressed)
	   return;

  if (bunnies.size() > 200000)
    return;

	for (auto i = 0; i < amount; i++)
	{
		bunnies.emplace_back();
		bunnies.back().randomize();
	}

}

void DrawBunniesGL()
{
	for(auto& bunny : bunnies)
	{
		bunny.update();
		bunny.drawGL();
	}

	if (!key_pressed)
	   return;

  if (bunnies.size() > 200000)
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
