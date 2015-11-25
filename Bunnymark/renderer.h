
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
	glBufferData(GL_ARRAY_BUFFER, 12*4, vVertices, GL_STATIC_DRAW);

	// Load the vertex data
	glVertexAttribPointer(0 /* ? */, 3, GL_FLOAT, 0, 0, 0);
	glEnableVertexAttribArray(0);

	glDrawArrays ( GL_TRIANGLE_STRIP, 0, 4 );

	glDisableVertexAttribArray(0);
}
