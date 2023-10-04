#pragma once
#include "SnowEngine.h"

struct TextColor {
	BYTE r, g, b, a;

	TextColor() : r(0), g(0), b(0), a(255) {} // 기본 생성자
	TextColor(BYTE r, BYTE g, BYTE b, BYTE a = 255) : r(r), g(g), b(b), a(a) {} // 값으로 초기화하는 생성자

	// RGBA 값을 정수 형식으로 변환하는 함수
	unsigned int toInt() const {
		return ((a << 24) | (b << 16) | (g << 8) | r);
	}
};

struct Text{
	std::wstring	string;
	float			leftTop;
	float			rightTop;
	int				size;
	TextColor		color;

	Text(std::wstring _string, float _leftTop, float _rightTop, int _size, TextColor _color)
		: string(_string)
		, leftTop(_leftTop)
		, rightTop(_rightTop)
		, size(_size)
		, color(_color)
	{}
};

class TextManager
{
public:
	static void Initiailize();
	static void Update();
	static void Render();
	static void InsertText(std::wstring _wstring, Text _text) { mapText.insert(std::make_pair(_wstring, _text)); };
	static void DeleteText(std::wstring _wstring) { auto it = mapText.find(_wstring); if (it != mapText.end()) mapText.erase(it); }
	static void ChangeText(std::wstring _wstring, std::wstring _text) { auto it = mapText.find(_wstring); it->second.string = _text; }

private:
	static std::map<std::wstring, Text> mapText;
};

