#version 410

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

uniform mat4 Model;

uniform struct LightInfo {
  vec4 Position; // Light position in eye coords.
  vec3 La;       // Ambient light intensity
  } Light;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;


out vec4 vertexColor;
void main()
{
	vec3 n = normalize( NormalMatrix * VertexNormal);
	vec4 camCoords = ModelViewMatrix * vec4(VertexPosition,1.0f);

	vec3 s = normalize(vec3( Light.Position - camCoords));
	float sDotN = max( dot(s,n),0.0 );

	vertexColor = vec4(vec3(sDotN+0.2f),1.0f);
	gl_Position = MVP*vec4(VertexPosition,1.0f);
}