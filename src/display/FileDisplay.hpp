#pragma once

#include "Defines.hpp"
#include "Display.hpp"
#include "renderer/Font.hpp"

class FileDisplay : public Display {
	public:
	FileDisplay();
	~FileDisplay();

	private:
	Font font;
};
