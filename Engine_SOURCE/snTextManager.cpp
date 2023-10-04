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
		FontWrapper::DrawFont(it.second.string.c_str(), it.second.leftTop, it.second.rightTop, it.second.size, it.second.color.toInt());
	}
}
