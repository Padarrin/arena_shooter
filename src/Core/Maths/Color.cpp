#include "Color.h"

namespace gce {


Color Color::Clear = Color(0, 0, 0, 0);
Color Color::Black = Color(0, 0, 0, 255);
Color Color::White = Color(255, 255, 255, 255);
Color Color::Red = Color(187, 44, 19, 255);
Color Color::Green = Color(22, 137, 24, 255);
Color Color::Blue = Color(0, 0, 255, 255);
Color Color::Yellow = Color(234, 191, 55, 255);
Color Color::Magenta = Color(255, 0, 255, 255);
Color Color::Cyan = Color(39, 173, 217, 255);
Color Color::Purple = Color(157, 69, 210, 255);
Color Color::Brown = Color(116, 67, 4, 255);
Color Color::LightPurple = Color(198, 49, 244, 255);

void Color::Set(Color newColor)
{
	r = newColor.r;
	g = newColor.g;
	b = newColor.b;
	a = newColor.a;
}

void Color::Set(uint8 newR, uint8 newG, uint8 newB, uint8 newA)
{
	r = newR;
	g = newG;
	b = newB;
	a = newA;
}

void Color::Transparent()
{
	a = 0;
}

void Color::Opaque()
{
	a = 255;
}


}