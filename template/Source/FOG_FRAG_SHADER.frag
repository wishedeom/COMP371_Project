#version 330

uniform struct FogParameters{
vec4 fogColor;
float fogStart;
float fogEnd;
} fogParams;

float getFogFactor(FogParameters params, float fogCoordinate){
	return 1.0-clamp(params.fogEnd-fogCoordinate)/(params.fogEnd - params.fogStart;
}

