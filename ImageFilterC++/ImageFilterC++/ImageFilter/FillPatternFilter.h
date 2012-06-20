/* 
 * HaoRan ImageFilter Classes v0.4
 * Copyright (C) 2012 Zhenjun Dai
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation.
 */

#if !defined(FillPatternFilter_H)
#define FillPatternFilter_H

#include "IImageFilter.h"


namespace HaoRan_ImageFilter{

class FillPatternFilter : public IImageFilter{
private:
	Image pattern;
public:

	FillPatternFilter(std::string path)
	{
		pattern = HaoRan_ImageFilter::Image::LoadImage(path);
	};

	virtual Image process(Image imageIn)
	{
		int r, g, b;
		for (int x = 0; x < imageIn.getWidth(); x++)
		{
			for (int y = 0; y < imageIn.getHeight(); y++)
			{
				int xx = x % pattern.getWidth();
				int yy = y % pattern.getHeight();

				r = imageIn.getRComponent(x, y) + pattern.getRComponent(xx, yy);
				g = imageIn.getGComponent(x, y) + pattern.getGComponent(xx, yy);
				b = imageIn.getBComponent(x, y) + pattern.getBComponent(xx, yy);
				imageIn.setPixelColor(x, y, SAFECOLOR(r), SAFECOLOR(g), SAFECOLOR(b));
			}
		}
#ifndef WIN32 //only for apple ios
		imageIn.copyPixelsFromBuffer();
#endif
		pattern.Destroy();
		return imageIn;
	}
};

}// namespace HaoRan
#endif