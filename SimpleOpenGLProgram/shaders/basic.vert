#version 450 core

uniform mat4 mProjection, mModelView;

in vec3 vVertex;
in vec3 vColor;

out vec3 vFinalColor;

void main()
{
	vFinalColor = vColor;
	gl_Position = mProjection * mModelView * vec4(vVertex,1.0f);
}