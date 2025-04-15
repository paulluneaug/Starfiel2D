uniform sampler2D texture;
uniform sampler2D Noise;
uniform vec4 NoiseUV;

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
    if(delta == 0)
    {
        HSV.x = 0;
    }
    else if(maxChannel == RGB.x)
    {
        HSV.x = (RGB.y - RGB.z)/delta + 0;
    }
    else if(maxChannel == RGB.y)
    {
        HSV.x = (RGB.z - RGB.x)/delta + 2;
    }
    else if(maxChannel == RGB.z)
    {
        HSV.x = (RGB.x - RGB.y)/delta + 4;
    }
    
    HSV.x = mod(HSV.x, 6); // Dont know why 0 <= Hue <= 6 but it's supossed to be like that I suppose ?
    
    // Value
    HSV.z = maxChannel;

    //Saturation
    if(HSV.z == 0)
    {
        HSV.y = 0;
    }
    else
    {
        HSV.y = delta/HSV.z;
    }
}

void HSVToRGB(in vec3 HSV, out vec3 RGB)
{
    float alpha = HSV.z * (1 - HSV.y);
    float beta = HSV.z * (1 - (HSV.x-floor(HSV.x))*HSV.y);
    float gamma = HSV.z * (1 - (1 - (HSV.x-floor(HSV.x)))*HSV.y);
    
    float Hue = mod(HSV.x, 6);
    
    if(Hue == 0)
    {
        RGB = HSV.zzz;
    }
    else if(Hue < 1)
    {
        RGB = vec3(HSV.z, gamma, alpha);
    }
    else if(Hue < 2)
    {
        RGB = vec3(beta, HSV.z, alpha);
    }
    else if(Hue < 3)
    {
        RGB = vec3(alpha, HSV.z, gamma);
    }
    else if(Hue < 4)
    {
        RGB = vec3(alpha, beta, HSV.z);
    }
    else if(Hue < 5)
    {
        RGB = vec3(gamma, alpha, HSV.z);
    }
    else if(Hue < 6)
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
        gl_FragColor = vec4(0,0,0,0);
        return;
    }
    
    vec2 noiseUV = gl_TexCoord[0].xy;
    remap(noiseUV.x, vec2(0, 1), vec2(NoiseUV.x - NoiseUV.z, NoiseUV.x + NoiseUV.z));
    remap(noiseUV.y, vec2(0, 1), vec2(NoiseUV.y - NoiseUV.w, NoiseUV.y + NoiseUV.w));
    
    vec4 noise = texture2D(Noise, noiseUV);
    
    // HSV Color variation
    vec3 HSVColor;
    RGBToHSV(gl_Color.xyz, HSVColor);
    
    float normalSaturation = 1.2;
    float normalValue = 1.5;
    
    float seaHeight = .15;
    float seaHue = 3.5;
    float seaSaturation = 4;
    float seaValue = 1.5;
    
    float mountainHeight = .8;
    float mountainSaturation = .8f;
    float mountainValue = 1.2f;
    
    float hueShift = .1;
    
    
    if(noise.x < seaHeight)
    {
        HSVColor.x = seaHue + sign(HSVColor.x - seaHue) * hueShift;
        HSVColor.y = seaSaturation*(noise.x*noise.x);
        HSVColor.z = seaValue*(noise.x*noise.x);
    }
    else if(noise.x > mountainHeight)
    {
        HSVColor.x += hueShift;
        HSVColor.y = mountainSaturation*(noise.x*noise.x);
        HSVColor.z = mountainValue*(noise.x*noise.x);
    }
    else
    {
        HSVColor.y = normalSaturation*(noise.x*noise.x);
        HSVColor.z = normalValue*(noise.x*noise.x);
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
    gl_FragColor = vec4(RGBColor.xyz, 1);
}