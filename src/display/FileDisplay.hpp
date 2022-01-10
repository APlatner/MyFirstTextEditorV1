#pragma once

#include "Defines.hpp"
#include "Display.hpp"
#include "renderer/Font.hpp"

class FileDisplay : public Display {
	public:
	FileDisplay();
	~FileDisplay();

	void Init();
	void Update();
	void Render();

	private:
	Font font;
	std::string text;
	float fontSize = 16.0f;
	float fontScale = 1.0f;
    float fontMargin = 1.618;
};
