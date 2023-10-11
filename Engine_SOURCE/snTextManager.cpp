#include "snTextManager.h"
#include "snApplication.h"
#include "snFontWrapper.h"

using namespace sn;

extern sn::Application application;

std::map<std::wstring, Text> TextManager::mapText;

void TextManager::Initiailize()
{
}

void TextManager::Update()
{
}

void TextManager::Render()
{
	for (const auto& it : mapText) {
		if (it.second.enable) {
			FontWrapper::DrawFont(it.second.string.c_str(), it.second.leftTop, it.second.rightTop, it.second.size, it.second.color.toInt());
		}
	}
}

void TextManager::InsertText(std::wstring _wstring, Text _text)
{
	/*_text.leftTop -= (float)_text.size;
	_text.rightTop -= (float)_text.size;*/

	mapText.insert(std::make_pair(_wstring, _text));
}
