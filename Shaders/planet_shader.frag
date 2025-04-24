uniform sampler2D texture;
uniform vec4 NoiseUV;

#define PI 3.1415926535

void Smoothstep(in float w, out float returnValue)
{
    w = clamp(w, 0.0, 1.0);
    returnValue = w * w * (3.0 - 2.0 * w);
}

void Interpolate(in float a0, in float a1, in float w, out float returnValue)
{
    float smoothValue;
    Smoothstep(w, smoothValue);

    returnValue = a0 + (a1 - a0) * smoothValue;
}

float rand(vec2 co)
{    
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void RandomGradient2D(in float ix, in float iy, out vec2 gradient)
{ 
    float random = rand(vec2(ix, iy)) * 2 * PI;
    gradient = vec2(cos(random), sin(random));
}

void DotGridGradient2D(in float ix, in float iy, in float x, in float y, out float dotGridGradient)
{
    vec2 randomVec;
    RandomGradient2D(ix, iy, randomVec);
    
    // Compute the distance vector
    float dx = x - ix;
    float dy = y - iy;
 
    // Compute the dot-product
    dotGridGradient = dx * randomVec.x + dy * randomVec.y;
}


void PerlinNoise2D (in vec2 position, in float startNoiseScale, in int harmonics, in float falloff, out float noiseValue)
{
    float normalizingFactor = 0.0;
    float noiseScale = startNoiseScale;
    float layerWeigth = 1.0f;

    float unNormalizedNoiseValue = 0.0;
    
    for (int i = 0; i < harmonics; i++)
    {        
        float x = position.x / noiseScale;
        float y = position.y / noiseScale;
    
        // Determine grid cell coordinates
        float x0 = floor(x);
        float x1 = x0 + 1.0;
        float y0 = floor(y);
        float y1 = y0 + 1.0;
 
        // Determine interpolation weights
        // Could also use higher order polynomial/s-curve here
        float sx = x - x0;
        float sy = y - y0;

        float n0, n1, n2, n3, ix0, ix1, layerValue;
 
        // Interpolate between grid point gradients
        DotGridGradient2D(x0, y0, x, y, n0);
        DotGridGradient2D(x1, y0, x, y, n1);
        Interpolate(n0, n1, sx, ix0);


        DotGridGradient2D(x0, y1, x, y, n2);
        DotGridGradient2D(x1, y1, x, y, n3);//Ici le problème
        Interpolate(n2, n3, sx, ix1);

        Interpolate(ix0, ix1, sy, layerValue);
    
        layerValue = (layerValue + 1) / 2.0;

        
        unNormalizedNoiseValue += layerValue * layerWeigth;


        noiseScale /= 2.0;
        normalizingFactor += layerWeigth;

        layerWeigth *= falloff;
    }
    
    noiseValue = unNormalizedNoiseValue / normalizingFactor;
}


void remap(inout float value, in vec2 start, in vec2 end)
{
    value -= start.x;
    value /= start.y-start.x;
    value *= end.y-end.x;
    value += end.x;
}


// Link to Doc for color translation : https://mattlockyer.github.io/iat455/documents/rgb-hsv.pdf
void RGBToHSV(in vec3 RGB, out vec3 HSV)
{
    // Get information from source color
    float maxChannel = max(max(RGB.x, RGB.y), RGB.z);
    float minChannel = min(min(RGB.x, RGB.y), RGB.z);
    float delta = maxChannel - minChannel;
    
    // Hue
    if(delta == 0.0)
    {
        HSV.x = 0.0;
    }
    else if(maxChannel == RGB.x)
    {
        HSV.x = (RGB.y - RGB.z)/delta + 0.0;
    }
    else if(maxChannel == RGB.y)
    {
        HSV.x = (RGB.z - RGB.x)/delta + 2.0;
    }
    else if(maxChannel == RGB.z)
    {
        HSV.x = (RGB.x - RGB.y)/delta + 4.0;
    }
    
    HSV.x = mod(HSV.x, 6.0); // Dont know why 0 <= Hue <= 6 but it's supossed to be like that I suppose ?
    
    // Value
    HSV.z = maxChannel;

    //Saturation
    if(HSV.z == 0.0)
    {
        HSV.y = 0.0;
    }
    else
    {
        HSV.y = delta/HSV.z;
    }
}

void HSVToRGB(in vec3 HSV, out vec3 RGB)
{
    float alpha = HSV.z * (1.0 - HSV.y);
    float beta = HSV.z * (1.0 - (HSV.x-floor(HSV.x))*HSV.y);
    float gamma = HSV.z * (1.0 - (1.0 - (HSV.x-floor(HSV.x)))*HSV.y);
    
    float Hue = mod(HSV.x, 6.0);
    
    if(Hue == 0.0)
    {
        RGB = HSV.zzz;
    }
    else if(Hue < 1.0)
    {
        RGB = vec3(HSV.z, gamma, alpha);
    }
    else if(Hue < 2.0)
    {
        RGB = vec3(beta, HSV.z, alpha);
    }
    else if(Hue < 3.0)
    {
        RGB = vec3(alpha, HSV.z, gamma);
    }
    else if(Hue < 4.0)
    {
        RGB = vec3(alpha, beta, HSV.z);
    }
    else if(Hue < 5.0)
    {
        RGB = vec3(gamma, alpha, HSV.z);
    }
    else if(Hue < 6.0)
    {
        RGB = vec3(HSV.z, alpha, beta);
    }
}

void main()
{
    float x = gl_TexCoord[0].x - 0.5;
    float y = gl_TexCoord[0].y - 0.5;
    if(x*x + y*y > .25f)
    {
        gl_FragColor = vec4(0.0,0.0,0.0,0.0);
        return;
    }
    

    vec2 noiseUV = gl_TexCoord[0].xy;
    remap(noiseUV.x, vec2(0.0, 1.0), vec2(NoiseUV.x - NoiseUV.z, NoiseUV.x + NoiseUV.z));
    remap(noiseUV.y, vec2(0.0, 1.0), vec2(NoiseUV.y - NoiseUV.w, NoiseUV.y + NoiseUV.w));
    
    float noiseValue = 0.0;
    
    //vec4 noise = texture2D(Noise, noiseUV);
    //noiseValue = noise.x;
    PerlinNoise2D( noiseUV * 128 * 2048, 1024, 5, 0.5, noiseValue);

    noiseValue += 0.2;
    
    // HSV Color variation
    vec3 HSVColor;
    RGBToHSV(gl_Color.xyz, HSVColor);
    
    float normalSaturation = 1.2;
    float normalValue = 1.5;
    
    float seaHeight = .15;
    float seaHue = 3.5;
    float seaSaturation = 4.0;
    float seaValue = 1.5;
    
    float mountainHeight = .8;
    float mountainSaturation = .8f;
    float mountainValue = 1.2f;
    
    float hueShift = .1;
    
    
    if(noiseValue < seaHeight)
    {
        HSVColor.x = seaHue + sign(HSVColor.x - seaHue) * hueShift;
        HSVColor.y = seaSaturation * (noiseValue * noiseValue);
        HSVColor.z = seaValue * (noiseValue * noiseValue);
    }
    else if(noiseValue > mountainHeight)
    {
        HSVColor.x += hueShift;
        HSVColor.y = mountainSaturation * (noiseValue * noiseValue);
        HSVColor.z = mountainValue * (noiseValue * noiseValue);
    }
    else
    {
        HSVColor.y = normalSaturation * (noiseValue * noiseValue);
        HSVColor.z = normalValue * (noiseValue * noiseValue);
    }
    
    vec3 RGBColor;
    HSVToRGB(HSVColor, RGBColor);

    
    // RGB - HSV Conversion Test
    // vec3 HSVTest, RGBTest;
    // RGBToHSV(gl_Color.xyz, HSVTest);
    // HSVToRGB(HSVTest, RGBTest);
    
    // multiply it by the color
    //gl_FragColor = gl_Color * vec4(noise.xyz, 1);
    //gl_FragColor = vec4(gl_TexCoord[0].xy, 0, 1); 
    gl_FragColor = vec4(RGBColor.xyz, 1.0);
    // gl_FragColor = vec4(noiseUV.x, noiseUV.y,noiseValue , 1.0);
    // gl_FragColor = vec4(noiseValue, noiseValue,noiseValue , 1.0);
}