#version 330

layout(location = 0, index = 0) out vec4 fragColor;

in vec3 pos;
uniform int renderTechnique;

vec4 strahlMax();
vec4 strahlAverage();
vec4 strahlFirstHit();
vec4 mida();
vec4 alphaCompositing();
float color(float x, float y, float z);
float color(vec3 pos);
float color(vec4 pos);
vec3 normalize(vec3 v);
float max(float v1, float v2);
float max(float v1, float v2, float v3);
vec4 calculatInterpolatedColor (float highestValue, float lowestValue, vec4 colorHigh, vec4 colorLow, float opacity);

vec3 normal(vec3 pos);
float length(vec3 v);
vec4 blinnPhongShading(vec3 pos, vec4 diffuseColor);

vec4 colorAlphaCompositingBeetle(float x, float y, float z);
vec4 colorAlphaCompositingLobster(float x, float y, float z);
vec4 colorAlphaCompositingHead(float x, float y, float z);

float gradientValue(vec3 pos, float dx, float dy, float dz);

int calcVisibleLayers();
vec3 sobel(vec3 pos);
vec3 zentralDiffenz(vec3 pos);

uniform sampler3D volume;

uniform sampler3D gradient;

uniform float z;

uniform int alphaProfil;

uniform int percentageOfAlphaLayers = 0;

uniform float mida_gamma;

vec3 centerPos;
vec3 viewDir;

vec4 samplingPoint;
float samplingDistance;
float renderDistance;
vec4 rayDirection;
vec3 volumeSize;
vec3 gradientSize;

uniform mat4x4 cameraMat;

uniform vec3 lightPos;

uniform float ambientPower;
uniform float diffusePower;
uniform float specularPower;

float specularHardness = 10.0;
vec3 specularColor = vec3(1.0);
const vec3 ambientColor = vec3(0.1, 0.1, 0.1);
const float shininess = 16.0;
const float screenGamma = 2.2; // Assume the monitor is calibrated to the sRGB color space

const int GradientCentralDifference = 0;
const int GradientSobel = 1;
const int GradientCPU = 0;
const int GradientGPU = 1;

uniform int GradientModeTarget;
uniform int GradientModeCalc;

void main( void )
{
	volumeSize = textureSize(volume, 0);
	volumeSize = volumeSize / max(volumeSize.x, volumeSize.y, volumeSize.z);

	gradientSize = textureSize(gradient, 0);
	gradientSize = gradientSize / max(gradientSize.x, gradientSize.y, gradientSize.z);

	viewDir = normalize((cameraMat * vec4(1.0, 0.0, 0.0, 1.0)).xyz);

	samplingPoint = cameraMat * vec4(-1.0, pos.x, pos.y, 1.0);
	samplingDistance = 0.001;
	renderDistance = 2.0;
	rayDirection = cameraMat * vec4(1.0, 0.0, 0.0, 1.0);

	fragColor = vec4(1.0, 0.0, 0.0, 1.0);
	if (renderTechnique == 0) {
		fragColor = strahlMax();
	} else if (renderTechnique == 1) {
		fragColor = strahlAverage();
	} else if (renderTechnique == 2) {
		fragColor = strahlFirstHit();
	} else if (renderTechnique == 3 || renderTechnique == 5) {
		fragColor = alphaCompositing();
	} else if (renderTechnique == 4) {
		fragColor = mida();
	} else if (renderTechnique == 9) {
		float colortmp = color(pos.x, pos.y, z);
		fragColor = vec4(colortmp, colortmp, colortmp, 1.0);
	}
}

vec4 blinnPhongShading(vec3 pos, vec4 diffuseColor) {
	//*
	vec3 gradientVec = normal(pos);

	vec3 normal = normalize(gradientVec);
	vec3 lightDir = normalize(lightPos - pos);

	float lambertian = max(dot(lightDir,normal), 0.0);
	float specular = 0.0;

	if(lambertian > 0.0) {

		// this is blinn phong
		vec3 halfDir = normalize(lightDir + viewDir);
		float specAngle = max(dot(halfDir, normal), 0.0);
		specular = pow(specAngle, shininess);

	}
	vec3 colorLinear = ambientColor * ambientPower +
	                   lambertian * diffuseColor.rgb * diffusePower +
	                   specular * specularColor * specularPower;
	// apply gamma correction (assume ambientColor, diffuseColor and specColor
	// have been linearized, i.e. have no gamma correction in them)
	vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0/screenGamma));
	// use the gamma corrected color in the fragment
	vec4 returnColor = vec4(colorGammaCorrected, diffuseColor.a);

	//*/
	/*
	
	diffuseColor = vec4(normalize(diffuseColor.rgb), diffuseColor.a);
	vec3 gradientVec = normal(pos);
	vec3 normal = normalize(gradientVec);
	

	float lightDist = length(lightPos - pos);
	vec3 lightDir = normalize(lightPos - pos);

	lightDist = lightDist * lightDist;
	float NdotL = dot( normal, lightDir );
	float intensity = NdotL > 0.0 ? NdotL : 0.0;

	vec3 diffuse = intensity * diffuseColor.xyz * diffusePower / lightDist;

	vec3 H = normalize( lightDir + viewDir );

	float NdotH = dot( normal, H );
	intensity = pow( ( NdotH > 0 ? NdotH : 0 ), specularHardness );

	vec3 specular = intensity * specularColor * specularPower / lightDist; 

	vec4 returnColor = vec4(ambientPower * diffuseColor.xyz + diffuse + specular, diffuseColor.a);

	//*/
	return returnColor;
}

vec4 mida() {

	float c = 0.0;
  	float colorOfEachPixel = 1.0;
	float highestValue = 0.0;
	float a = 0.0;
	float beta = 0.0;
	float delta = 0.0;
	for (float i = 0; i <= renderDistance; i += samplingDistance) { 
			float opacity = color(samplingPoint);// -1 -> 1
			if (highestValue < opacity) {
				delta = opacity - highestValue;
				beta = 1.0 - delta * (1.0 + mida_gamma);
				c = beta * c + (1.0 - beta * a) * opacity * opacity;
				a = beta * a + (1.0 - beta * a) * opacity;
				highestValue = opacity;
			} else {
				c = c + (1.0 - a) * opacity * opacity;
				a = a + (1.0 - a) * opacity;
			}
			samplingPoint += rayDirection * samplingDistance;
	}
	return vec4(c, c, c, 1.0);
}

vec4 strahlMax() {
	float highestValue = 0.0;
	for (float i = 0; i <= renderDistance; i += samplingDistance) { 
			float color = color(samplingPoint);
			if (highestValue < color) {
				highestValue = color;
			}
			samplingPoint += rayDirection * samplingDistance;
		}
	return vec4(highestValue, highestValue, highestValue, 1.0);
}

vec4 strahlAverage() {
	float totalValues = 0.0;
	float numberOFValues = 0.0;
	for (float i = 0; i <= renderDistance; i += samplingDistance) { 
			float color = color(samplingPoint);
			totalValues += color;
			numberOFValues += 1.0;
			samplingPoint += rayDirection * samplingDistance;
	}
	float averageValue;
	if (numberOFValues != 0.0) {
		averageValue = totalValues/numberOFValues;
	}
	return vec4(averageValue, averageValue, averageValue, 1.0);
}


// Optimization techniques: Early ray termination
vec4 strahlFirstHit() {
	float firstValues = 0.0;
	bool notFound = true;
	for (float i = 0; i <= renderDistance; i += samplingDistance) { 
			float color = color(samplingPoint);// -1 -> 1
			if (color > 0.0) {
				notFound = false;
				firstValues = color;
			}
			samplingPoint += rayDirection * samplingDistance;
	}
	return vec4(firstValues, firstValues, firstValues, 1.0);
}

float color(float x, float y, float z) {
	return color(vec4(x, y, z, 1.0));
}

float color(vec3 v) {
	return color(vec4(v, 1.0));
}

float color(vec4 pos) {
	vec3 propPos = (pos.xyz / volumeSize)/2.0+0.5;
	vec3 texPos = propPos.xyz;
	if(texPos.x >= 0 && texPos.y >= 0 && texPos.z >= 0 && texPos.x <= 1 && texPos.y <= 1 && texPos.z <= 1) {
		return texture(volume, texPos).r;
	} else {
		return 0.0;
	}
}

vec3 normal(vec3 pos) {
	vec3 propPos = (pos / gradientSize)/2.0+0.5;
	vec3 texPos = propPos.xyz;
	if(texPos.x >= 0 && texPos.y >= 0 && texPos.z >= 0 && texPos.x <= 1 && texPos.y <= 1 && texPos.z <= 1) {
		if(GradientModeTarget == GradientGPU) {
			if(GradientModeCalc == GradientSobel) {
				return sobel(pos);
			} else {
				return zentralDiffenz(pos);
			}
		} else {
			return texture(gradient, texPos).rgb;
		}
	} else {
		return vec3(0.0, 0.0, 0.0);
	}

}

// Optimization techniques: Early ray termination
vec4 alphaCompositing() {
	
	float a = 0.0f;
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float threshold = float(percentageOfAlphaLayers+1) / 100.0f;
	//return vec4(threshold, 0.0, 0.0, 1.0);

	vec4 result = vec4(0.0);

	for (float i = 0; i <= renderDistance; i += samplingDistance) {
			float opacity = color(samplingPoint.x, samplingPoint.y, samplingPoint.z);// -1 -> 1
			vec4 color = vec4(0.0, 0.0, 0.0, 0.0);
			if (alphaProfil == 0) {
				// TODO Zusammenfuegen auf nur samplingPoint ohne x, y, z
				color = colorAlphaCompositingBeetle(samplingPoint.x, samplingPoint.y, samplingPoint.z);
			} else if (alphaProfil == 1) {
				color = colorAlphaCompositingLobster(samplingPoint.x, samplingPoint.y, samplingPoint.z);
			} else if (alphaProfil == 2) {
				color = colorAlphaCompositingHead(samplingPoint.x, samplingPoint.y, samplingPoint.z);
			} 

			vec3 normal = normal(samplingPoint.xyz);
			
			if (opacity >= threshold) {
				
				if(renderTechnique == 5)
				{
					color = blinnPhongShading(samplingPoint.xyz, color);
				}
				
				// TODO why  * color.a ????????????????????????
				r = r + (1.0f - a) * color.r * color.a;
				g = g + (1.0f - a) * color.g * color.a;
				b = b + (1.0f - a) * color.b * color.a;
				a = a + (1.0f - a) * color.a;
			}
			samplingPoint += rayDirection * samplingDistance;

			result += vec4(opacity * 0.1, length(normal) * 0.01, 0.0, 0.01);



	}
	return vec4(r, g, b, a);
	//return result;
}

vec4 colorAlphaCompositingBeetle(float x, float y, float z) {
	// all colors from high opacity to low opacity
	vec4 color1 = vec4(0.6, 0, 0, 0.7);
	vec4 color2 = vec4(0.96, 0.95, 0.94, 0.2);
	vec4 color3 = vec4(0.43, 0.25, 0.04, 0.2);
	vec4 color4 = vec4(0.0, 0.0, 0.0, 0.0);
	vec4 color5 = vec4(0.0, 0.0, 0.0, 0.0);
	
	float opacity = color(x, y, z);
	vec4 value;
	float density = opacity;

	if (opacity == 0.0) {
	  value = color5;
	} else if (opacity < 0.07) {
	  value = color4;
	} else if (opacity < 0.3) {//0.2
	  value = color3;
	} else if (opacity < 0.4) {//0.37
	  value = color2;
	} else {
	  value = color1;
	}
	
	return value;
}

vec4 colorAlphaCompositingLobster(float x, float y, float z) {
	// all colors from high opacity to low opacity
	vec4 color1 = vec4(0.96, 1.00, 0.80, 0.3);
	vec4 color2 = vec4(0.47, 0.60, 0.70, 0.2);
	vec4 color3 = vec4(0.31, 0.05, 0.05, 0.3);
	vec4 color4 = vec4(0.00, 0.00, 0.00, 0.0);
	vec4 color5 = vec4(0.00, 0.00, 0.00, 0.0);

	float opacity = color(x, y, z);
	vec4 value;


	float density = opacity;
	 if (opacity == 0.0f) {
	  value = color5;
	} else if (density < 0.04) {
	  value = color4;
	 } else if (density < 0.4) {
	  value = color3;
	 }  else if (density < 0.65) {
	  value = color2;
	 } else {
	  value = color1;
	 }
	return value;
}

vec4 colorAlphaCompositingHead(float x, float y, float z) {
	// all colors from high opacity to low opacity
	vec4 color1 = vec4(0.96, 0.95, 0.94, 0.90);
	vec4 color2 = vec4(1.00, 1.00, 0.00, 0.08);
	//vec4 color2 = vec4(0.80, 0.70, 0.60, 0.08);
	vec4 color3 = vec4(0.00, 0.00, 0.00, 0.00);
	vec4 color4 = vec4(0.0, 0.0, 0.0, 0.0);
	
	float opacity = color(x, y, z);
	vec4 value;

	 if (opacity == 0.0f) {
	  value = color4;
	} else if (opacity < 0.2f) {
	  return color3;
	 } else if (opacity < 0.3) {
	  return color2;
	 } else {
	  return color1;
	 }
	
	return value;
}

vec3 normalize(vec3 v) {
	return v / length(v);
}

float max(float v1, float v2) {
	return v1 > v2 ? v1 : v2;
}

float max(float v1, float v2, float v3) {
	float max = v1;
	if(v2 > max) max = v2;
	if(v3 > max) max = v3;
	return max;
}

float length(vec3 v) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

float gradientValue(vec3 pos, float dx, float dy, float dz) {
	vec3 d = vec3(dx, dy, dz) / textureSize(volume, 0);
	return color(pos + d*2);
}

vec3 sobel(vec3 pos) {
	float x = pos.x;
	float y = pos.y;
	float z = pos.z;
	
	float gradient_x =    4 * gradientValue(pos, 1, 0, 0)
						+ 2 * gradientValue(pos, 1, 1, 0)
						+ 2 * gradientValue(pos, 1, -1, 0)
						+ 2 * gradientValue(pos, 1, 0, 1)
						+ 2 * gradientValue(pos, 1, 0, -1)
						+ gradientValue(pos, 1, 1, 1)
						+ gradientValue(pos, 1, 1, -1)
						+ gradientValue(pos, 1, -1, 1)
						+ gradientValue(pos, 1, -1, -1)
						- 4 * gradientValue(pos, -1, 0, 0)
						- 2 * gradientValue(pos, -1, 1, 0)
						- 2 * gradientValue(pos, -1, -1, 0)
						- 2 * gradientValue(pos, -1, 0, 1)
						- 2 * gradientValue(pos, -1, 0, -1)
						- gradientValue(pos, -1, 1, 1)
						- gradientValue(pos, -1, 1, -1)
						- gradientValue(pos, -1, -1, 1)
						- gradientValue(pos, -1, -1, -1);

	float gradient_y =    4 * gradientValue(pos, 0, 1, 0)
						+ 2 * gradientValue(pos, 1, 1, 0)
						+ 2 * gradientValue(pos, -1, 1, 0)
						+ 2 * gradientValue(pos, 0, 1, 1)
						+ 2 * gradientValue(pos, 0, 1, -1)
						+ gradientValue(pos, 1, 1, 1)
						+ gradientValue(pos, 1, 1, -1)
						+ gradientValue(pos, -1, 1, 1)
						+ gradientValue(pos, -1, 1, -1)
						- 4 * gradientValue(pos, 0, -1, 0)
						- 2 * gradientValue(pos, 1, -1, 0)
						- 2 * gradientValue(pos, -1, -1, 0)
						- 2 * gradientValue(pos, 0, -1, 1)
						- 2 * gradientValue(pos, 0, -1, -1)
						- gradientValue(pos, 1, -1, 1)
						- gradientValue(pos, 1, -1, -1)
						- gradientValue(pos, -1, -1, 1)
						- gradientValue(pos, -1, -1, -1);

	float gradient_z =    4 * gradientValue(pos, 0, 0, 1)
						+ 2 * gradientValue(pos, 1, 0, 1)
						+ 2 * gradientValue(pos, -1, 0, 1)
						+ 2 * gradientValue(pos, 0, 1, 1)
						+ 2 * gradientValue(pos, 0, -1, 1)
						+ gradientValue(pos, 1, 1, 1)
						+ gradientValue(pos, 1, -1, 1)
						+ gradientValue(pos, -1, 1, 1)
						+ gradientValue(pos, -1, -1, 1)
						- 4 * gradientValue(pos, 0, 0, -1)
						- 2 * gradientValue(pos, 1, 0, -1)
						- 2 * gradientValue(pos, -1, 0, -1)
						- 2 * gradientValue(pos, 0, 1, -1)
						- 2 * gradientValue(pos, 0, -1, -1)
						- gradientValue(pos, 1, 1, -1)
						- gradientValue(pos, 1, -1, -1)
						- gradientValue(pos, -1, 1, -1)
						- gradientValue(pos, -1, -1, -1);

	return vec3(gradient_x, gradient_y, gradient_z);
}

vec3 zentralDiffenz(vec3 pos) {
	
	float gradient_x =    gradientValue(pos, 1, 0, 0)
						- gradientValue(pos, -1, 0, 0);

	float gradient_y =    gradientValue(pos, 0, 1, 0)
						- gradientValue(pos, 0, -1, 0);

	float gradient_z =    gradientValue(pos, 0, 0, 1)
						- gradientValue(pos, 0, 0, -1);

	return vec3(gradient_x, gradient_y, gradient_z);
}

