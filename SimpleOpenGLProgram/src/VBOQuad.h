#ifndef VBOQuad_H
#define VBOQuad_H

#include "Definitions.h"

/**
* Class FBOQuad.
* Creates a Quad using FBO with the corresponding texture coordinates
*
*           (-0.5,0.5)*------*(0.5,0.5)
*					  |		 |
*					  |      |
*          (-0.5,-0.5)*------*(0.5,-0.5)
*/
class VBOQuad
{
	//Functions

	public:
		///Default constructor
		VBOQuad();

		///Default destructor
		~VBOQuad();

		///Method to Draw the Quad
		void Draw();

		///Method start up Quad rendering
		void StartUp();

		///Method to only Draw the Quad
		void OnlyDraw();

		///Method to stop Quad rendering
		void Stop();


	//Variables

	private:
		GLuint m_iVBO;
		GLuint m_iVBOIndex;
		GLuint m_iVAO;
};


#endif //FBOQuad_H