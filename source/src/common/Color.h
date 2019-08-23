#pragma once

#include <math.h>
#include <stdlib.h>
#include <iostream>

namespace raytracing
{
	class Color {

	public:
        Color():r(1),g(1),b(1),a(1) {}
		Color(float r0, float g0, float b0, float a0 = 1):r(r0),g(g0),b(b0),a(a0) {}

		float r;
		float g;
		float b;
		float a;

		static const Color Black;
		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Cyan;
		static const Color Magenta;
		static const Color Gray;

		inline float operator[](int i) const;
		inline float& operator[](int i);
		inline const Color& operator+() const { return *this; }
		inline Color operator-() const { return Color(-r, -g, -b, -a); }

		inline Color& operator+=(const Color &c2);
		inline Color& operator-=(const Color &c2);
		inline Color& operator*=(const Color &c2);
		inline Color& operator*=(const float t);
		inline Color& operator/=(const float t);
	
	};

	inline float Color::operator[](int i) const
	{
		switch (i)
		{
		case 0:
			return r;
		case 1:
			return g;
		case 2:
			return b;
		case 3:
			return a;
		default:
			break;
		}
		throw "invalid index";
	}

	inline float & Color::operator[](int i)
	{
		switch (i)
		{
		case 0:
			return r;
		case 1:
			return g;
		case 2:
			return b;
		case 3:
			return a;
		default:
			break;
		}
		throw "invalid index";
	}

	inline std::istream& operator>>(std::istream &is, Color &c) {
		is >> c.r >> c.g >> c.b >> c.a;
		return is;
	}

	inline std::ostream& operator<<(std::ostream &os, const Color &c) {
		os << c.r << " " << c.g << " " << c.b << " " << c.a;
		return os;
	}

	inline Color operator+(const Color &c1, const Color &c2) {
		return Color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, c1.a + c2.a);
	}

	inline Color operator*(const Color &c1, const Color &c2) {
		return Color(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b, c1.a * c2.a);
	}

	inline Color operator*(float t, const Color &c) {
		return Color(t*c.r, t*c.g, t*c.b, t*c.a);
	}

	inline Color operator/(Color c, float t) {
		return Color(c.r / t, c.g / t, c.b / t, c.a / t);
	}

	inline Color operator*(const Color &c, float t) {
		return Color(t*c.r, t*c.g, t*c.b, t*c.a);
	}

	inline Color& Color::operator+=(const Color &c) {
		r += c.r;
		g += c.g;
		b += c.b;
		a += c.a;
		return *this;
	}

	inline Color& Color::operator*=(const Color &c) {
		r *= c.r;
		g *= c.g;
		b *= c.b;
		a *= c.a;
		return *this;
	}

	inline Color& Color::operator-=(const Color& c) {
		r -= c.r;
		g -= c.g;
		b -= c.b;
		a -= c.a;
		return *this;
	}

	inline Color& Color::operator*=(const float t) {
		r *= t;
		g *= t;
		b *= t;
		a *= t;
		return *this;
	}

	inline Color& Color::operator/=(const float t) {
		float k = 1.0 / t;
		r *= k;
		g *= k;
		b *= k;
		a *= k;
		return *this;
	}

}
