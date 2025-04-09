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
    
    // multiply it by the color
    gl_FragColor = gl_Color * vec4(noise.xyz, 1);
    //gl_FragColor = vec4(gl_TexCoord[0].xy, 0, 1); 
}