#include "TexturePacking.h"

bool Rectangle::operator==(const Rectangle &n) //overload operator "==" to judge whether two rectangles have same width and height
{
	if (this->width == n.get_width() && this->height == n.get_height())
		return true;
	else if (this->width == n.get_height() && this->height == n.get_width())
	{
		this->rotate();
		return true;
	}
	else
		return false;
}

void Rectangle::rotate()
{
	int tmp = this->width;
	this->width = this->height;
	this->height = tmp;
}

