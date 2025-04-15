uniform sampler2D texture;

int iterationNb = 7;

void inverseSquircleEquation(in vec2 position, in vec2 point, in float distanceMin, out bool shouldDraw, out float distancePoint)
{
    vec2 distanceVector = abs(position - point);
    distancePoint = pow(distanceVector.x, iterationNb) + pow(distanceVector.y, iterationNb);
    shouldDraw = pow(distanceMin, iterationNb) < distancePoint;
}

void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    
    float distanceMin = .5;
    float pointDistance;
    bool shouldDraw;
    if(gl_TexCoord[0].x < 0.5 && gl_TexCoord[0].y < 0.5)
    {
        // Up-Left Corner
        inverseSquircleEquation(gl_TexCoord[0].xy, vec2(0,0), distanceMin, shouldDraw, pointDistance);
    }
    else if(gl_TexCoord[0].x > 0.5 && gl_TexCoord[0].y > 0.5)
    {
        // Down-Right Corner
        inverseSquircleEquation(gl_TexCoord[0].xy, vec2(1,1), distanceMin, shouldDraw, pointDistance);
    }
    else if(gl_TexCoord[0].x < 0.5)
    {
        // Down-Left Corner
        inverseSquircleEquation(gl_TexCoord[0].xy, vec2(0,1), distanceMin, shouldDraw, pointDistance);
    }
    else if(gl_TexCoord[0].y < 0.5)
    {
        // Up-Right Corner
        inverseSquircleEquation(gl_TexCoord[0].xy, vec2(1,0), distanceMin, shouldDraw, pointDistance);
    }
    
    if(!shouldDraw)
    {
        gl_FragColor = vec4(0,0,0,0);
    }
    else
    {
        pointDistance = (pow(pointDistance, 1.f/iterationNb) - .5) * 20;
        gl_FragColor = gl_Color * vec4(pointDistance, pointDistance, pointDistance, 1);
    }
}