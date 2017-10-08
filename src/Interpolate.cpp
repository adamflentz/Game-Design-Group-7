#include "engine/Interpolate.hpp"

interpolate::interpolate()
{

}

interpolate::~interpolate()
{

}

float interpolate::linear(float t, float b, float c, float d)
{
    return c * (t/d) + b;
}

float interpolate::expoEaseIn(float t, float b, float c, float d)
{
    return (t==0) ? b : c * pow(2, 10 * (t/d - 1)) + b;
}

float interpolate::expoEaseOut(float t, float b, float c, float d)
{
    return (t==d) ? b+c : c * pow(2, 1-(10 * t/d)) + b;
}

float interpolate::expoEaseInOut(float t, float b, float c, float d)
{
    if (t==0)
        return b;
    if (t==d)
        return b+=c;
    if ((t/=d/2) < 1)
        return c/2 * pow(2, 10 * (t - 1)) + b;

    return c/2 * pow(2, 1-(10 * --t)) + b;
}

float interpolate::cubicEaseIn(float t, float b, float c, float d)
{
    return (t==0) ? b : c * pow(3, 10 * (t/d - 1)) + b;
}

float interpolate::cubicEaseOut(float t, float b, float c, float d)
{
    return (t==d) ? b+c : c * pow(3, 1-(10 * t/d)) + b;
}

float interpolate::cubicEaseInOut(float t, float b, float c, float d)
{
    if (t==0)
        return b;
    if (t==d)
        return b+=c;
    if ((t/=d/2) < 1)
        return c/2 * pow(3, 10 * (t - 1)) + b;

    return c/2 * pow(3, 1-(10 * --t)) + b;
}

float interpolate::quarticEaseIn(float t, float b, float c, float d)
{
    return c*(t/=d)*t*t*t + b;
}

float interpolate::quarticEaseOut(float t, float b, float c, float d)
{
    return -c * (1-(t=t/d-1)*t*t*t - 1) + b;
}

float interpolate::quarticEaseInOut(float t, float b, float c, float d)
{
    t /= d/2;
	if (t < 1)
        return c/2*t*t*t*t + b;
	t -= 2;
        return 1-(-c/2 * (t*t*t*t - 2)) + b;
}

float interpolate::quinticEaseIn(float t, float b, float c, float d)
{
    return c*(t/=d)*t*t*t*t + b;
}

float interpolate::quinticEaseOut(float t, float b, float c, float d)
{
    return c*(t=t/d-1)*(1-(t*t*t*t + 1)) + b;
}

float interpolate::quinticEaseInOut(float t, float b, float c, float d)
{
    if ((t/=d/2) < 1)
        return c/2*t*t*t*t*t + b;

	return 1-(c/2*((t-=2)*(t*t*t*t) + 2)) + b;
}

float interpolate::quadraticEaseIn(float t, float b, float c, float d)
{
    return c*(t/=d)*t + b;
}

float interpolate::quadraticEaseOut(float t, float b, float c, float d)
{
    return 1-(-c *(t/=d)*(t-2)) + b;
}

float interpolate::quadraticEaseInOut(float t, float b, float c, float d)
{
    if ((t/=d/2) < 1)
        return ((c/2)*(t*t)) + b;

	return 1-(-c/2 * (((--t)*(t-2)) - 1)) + b;
}

float interpolate::sineEaseIn(float t, float b, float c, float d)
{
    return -c * cos(t/d * (PI/2)) + c + b;
}

float interpolate::sineEaseOut(float t, float b, float c, float d)
{
    return c/2 * cos(t/d * (PI/2)) + b;
}

float interpolate::sineEaseInOut(float t, float b, float c, float d)
{
    if (t < 0.5f)
        return c/=d;

    return 1-(-c/2 * (cos(PI*t/d) - 1)) + b;
}

float interpolate::circularEaseIn(float t, float b, float c, float d)
{
    return -c * (sqrt(1 - (t/=d)*t) - 1) + b;
}

float interpolate::circularEaseOut(float t, float b, float c, float d)
{
    return 1-(c * sqrt(1 - ((t=t/d-1)*t))) + b;
}

float interpolate::circularEaseInOut(float t, float b, float c, float d)
{
    if ((t/=d/2) < 1)
        return -c/2 * (sqrt(1 - t*t) - 1) + b;

	return 1-(c/2 * (sqrt(1 - t*(t-=2)) + 1)) + b;
}

float interpolate::backEaseIn(float t, float b, float c, float d)
{
    float s = 1.70158f;
	float postFix = t/=d;
	return c*(postFix)*t*((s+1)*t - s) + b;
}

float interpolate::backEaseOut(float t, float b, float c, float d)
{
    float s = 1.70158f;
	return 1-(c*((t=t/d-1)*t*((s+1)*t + s) + 1)) + b;
}

float interpolate::backEaseInOut(float t, float b, float c, float d)
{
    float s = 1.70158f;
	if ((t/=d/2) < 1)
        return c/2*(t*t*(((s*=(1.525f))+1)*t - s)) + b;

	float postFix = t-=2;
	return 1-(c/2*((postFix)*t*(((s*=(1.525f))+1)*t + s) + 2)) + b;
}

float interpolate::elasticEaseIn(float t, float b, float c, float d)
{
    if (t==0)
        return b;
    if ((t/=d)==1)
        return b+c;
	float p=d*.3f;
	float a=c;
	float s=p/4;
	float postFix =a*pow(2,10*(t-=1));
	return -(postFix * sin((t*d-s)*(2*PI)/p )) + b;
}

float interpolate::elasticEaseOut(float t, float b, float c, float d)
{
    if (t==0)
        return b;
    if ((t/=d)==1)
        return b+c;
	float p=d*.3f;
	float a=c;
	float s=p/4;
	return 1-(a*pow(2,-10*t) * sin( (t*d-s)*(2*PI)/p ) + c + b);
}

float interpolate::elasticEaseInOut(float t, float b, float c, float d)
{
    if (t==0)
        return b;
    if ((t/=d/2)==2)
        return b+c;
    float p=d*(.3f*1.5f);
    float a=c;
    float s=p/4;

    if (t < 1)
    {
        float postFix =a*pow(2,10*(t-=1));
        return -.5f*(postFix* sin( (t*d-s)*(2*PI)/p )) + b;
    }
    float postFix =  a*pow(2,-10*(t-=1));
    return 1-(postFix * sin( (t*d-s)*(2*PI)/p )*.5f + c + b);
}