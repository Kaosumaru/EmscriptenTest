#include <limits>

class VBORenderer
{
public:
	VBORenderer()
	{

	}

	void Init()
	{
		glGenBuffers(1, &_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData)*_maxVertices, nullptr, GL_DYNAMIC_DRAW);


	{
		struct UV
		{
			float x,y;
		};
		glGenBuffers(1, &_VBO2);
		glBindBuffer(GL_ARRAY_BUFFER, _VBO2);

		std::vector<UV> uv_data;
		uv_data.resize(_maxVertices);

		int i = 0;
		for (auto& uv : uv_data)
		{
			switch(i%4)
			{
				case 0:
					uv.x = 1.f;
					uv.y = 0.f;
					break;
				case 1:
					uv.x = 0.f;
					uv.y = 0.f;
					break;
				case 2:
					uv.x = 1.f;
					uv.y = 1.f;
					break;
				case 3:
					uv.x = 0.f;
					uv.y = 1.f;
					break;
			}

			i ++;

		}

		glBufferData(GL_ARRAY_BUFFER, sizeof(UV)*_maxVertices, uv_data.data(), GL_STATIC_DRAW);
	}

	}

	void draw(float x, float y, float scale = 1.0f)
	{
		float hw = 13.0f * scale;
		float hh = 18.5f * scale;


		if (_currentVertice != 0)
		{
			auto &c = vertices[_currentVertice-1];
			nextVertex() = c;
		}

		auto &v0 = nextVertex();
		v0.x = hw + x;
		v0.y = -hh + y;
		v0.z = 0.0f;

		if (_currentVertice != 1)
		{
			nextVertex() = v0;
		}


		auto &v1 = nextVertex();
		v1.x = -hw + x;
		v1.y = -hh + y;
		v1.z = 0.0f;

		auto &v2 = nextVertex();
		v2.x = hw + x;
		v2.y = hh + y;
		v2.z = 0.0f;

		auto &v3 = nextVertex();
		v3.x = -hw + x;
		v3.y = hh + y;
		v3.z = 0.0f;

		if (_currentVertice + 100 >_maxVertices)
			DrawBatched();
		//nextVertex() = v3;
	}

	void DrawBatched()
	{
		//_currentVertice--;
		glBindBuffer(GL_ARRAY_BUFFER, _VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData)* _currentVertice, nullptr, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexData) * _currentVertice, vertices);


		glVertexAttribPointer(0 /* ? */, 3, GL_FLOAT, 0, 0, 0);
		glEnableVertexAttribArray(0);


		glBindBuffer(GL_ARRAY_BUFFER, _VBO2);
		glVertexAttribPointer(1 /* ? */, 2, GL_FLOAT, 0, 0, 0);
		glEnableVertexAttribArray(1);

/*
		for (int i = 0; i < _currentVertice/4; i ++)
		{
			glDrawArrays ( GL_TRIANGLE_STRIP, i*4, 4 );
		}*/
		glDrawArrays ( GL_TRIANGLE_STRIP, 0, _currentVertice );

		//glDrawArrays ( GL_TRIANGLE_STRIP, 0, _currentVertice );

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		_currentVertice = 0;
	}
protected:

	const static int _maxVertices = 20000;
	const static unsigned short int _primitiveRestartIndex = std::numeric_limits<unsigned short int>::max();

	struct VertexData
	{
		float x,y,z;
	};

	VertexData vertices[_maxVertices];
	VertexData &nextVertex() { return vertices[_currentVertice++]; }

	int _currentVertice = 0;

	GLuint _VBO;
	GLuint _VBO2;
} glRenderer;


void drawGL(float x, float y)
{
	float hw = 13.0f;
	float hh = 18.5f;


	GLfloat vVertices[] = {  hw + x,  -hh + y, 0.0f,
	                         -hw+x, -hh + y, 0.0f,
	                          hw+x, hh + y, 0.0f,
													  -hw+x, hh + y, 0.0f };

	// No clientside arrays, so do this in a webgl-friendly manner

	glBindBuffer(GL_ARRAY_BUFFER, vertexPosObject);
	glBufferData(GL_ARRAY_BUFFER, 12*4, vVertices, GL_DYNAMIC_DRAW);

	// Load the vertex data
	glVertexAttribPointer(0 /* ? */, 3, GL_FLOAT, 0, 0, 0);
	glEnableVertexAttribArray(0);

	glDrawArrays ( GL_TRIANGLE_STRIP, 0, 4 );

	glDisableVertexAttribArray(0);
}
