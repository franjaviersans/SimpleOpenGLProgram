#include "VBOQuad.h"
#include <stdlib.h>

/**
* Default constructor
*/
VBOQuad::VBOQuad()
{

	GLfloat Vertex[] = {//Word				Color				Texture
						-0.5f,-0.5f,0.0f,	1.0f,0.0f,0.0f,		0.0f,0.0f,
						0.5f,-0.5f,0.0f,	0.0f,1.0f,0.0f,		1.0f,0.0f,
						0.5f,0.5f,0.0f,		0.0f,0.0f,1.0f,		1.0f,1.0f,
						-0.5f,0.5f,0.0f,	1.0f,1.0f,0.0f,		0.0f,1.0f}; 

	GLuint Index[] = {0,1,2,3}; 

	glGenBuffers(1, &m_iVBO);
	glGenBuffers(1, &m_iVBOIndex);

	// bind buffer for positions and copy data into buffer
	// GL_ARRAY_BUFFER is the buffer type we use to feed attributes
	glBindBuffer(GL_ARRAY_BUFFER, m_iVBO);
 
		// feed the buffer, and let OpenGL know that we don't plan to
		// change it (STATIC) and that it will be used for drawing (DRAW)
		glBufferData(GL_ARRAY_BUFFER, 32 * sizeof(GL_FLOAT), Vertex, GL_STATIC_DRAW);

		//bind buffer for positions and copy data into buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iVBOIndex);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GL_UNSIGNED_INT), Index, GL_STATIC_DRAW);


	//Generate the VAO
	glGenVertexArrays(1, &m_iVAO);
    glBindVertexArray(m_iVAO );

		// bind buffer for positions and copy data into buffer
		// GL_ARRAY_BUFFER is the buffer type we use to feed attributes
		glBindBuffer(GL_ARRAY_BUFFER, m_iVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iVBOIndex);

		glEnableVertexAttribArray(WORLD_COORD_LOCATION);
		glVertexAttribPointer(WORLD_COORD_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*8, BUFFER_OFFSET(0)); //Vertex
		glEnableVertexAttribArray(WORLD_COORD_LOCATION);
		glVertexAttribPointer(COLOR_COORD_LOCATION, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*8, BUFFER_OFFSET(sizeof(GL_FLOAT)*3)); //Vertex
		glEnableVertexAttribArray(COLOR_COORD_LOCATION);
		glVertexAttribPointer(TEXTURE_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*8, BUFFER_OFFSET(sizeof(GL_FLOAT)*6)); //Text Coord
		
	//Unbind the vertex array	
	glBindVertexArray(0);

	//Disable Buffers and vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

/**
* Default destructor
*/
VBOQuad::~VBOQuad()
{

	glDeleteBuffers(1, &m_iVBO);
	glDeleteBuffers(1, &m_iVBOIndex);
	glDeleteVertexArrays(1, &m_iVAO);
}

/**
* Method to Draw the Quad
*/
void VBOQuad::Draw()
{

	//Bind Buffers
	glBindVertexArray(m_iVAO );

		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);

	//Unbid Buffer
	glBindVertexArray(0);

}
