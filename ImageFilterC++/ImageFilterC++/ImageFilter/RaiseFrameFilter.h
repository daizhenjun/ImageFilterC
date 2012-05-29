/* 
 * HaoRan ImageFilter Classes v0.3
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

#if !defined(RaiseFrameFilter_H)
#define RaiseFrameFilter_H

#include "IImageFilter.h"


namespace HaoRan_ImageFilter{

class RaiseFrameFilter : public IImageFilter{
	int   _size ;
public:

	RaiseFrameFilter(int size)
    {
        _size = ((size >= 1) ? size : 1) ;
    };

	virtual Image process(Image imageIn)
	{
		int r, g, b, a = 20;
		int width = imageIn.getWidth();
		int height = imageIn.getHeight();
		for(int x = 0 ; x < width ; x++){
			for(int y = 0 ; y < height; y++){
				r = imageIn.getRComponent(x, y);
				g = imageIn.getGComponent(x, y);
				b = imageIn.getBComponent(x, y);
				int cr ;
				if ((x < _size) && (y < height-x) && (y >= x))
					cr = Color::rgb(255,255,65) ; // left
				else if ((y < _size) && (x < width-y) && (x >= y))
					cr = Color::rgb(255,255,120) ; // top
				else if ((x >width-_size) && (y >= width-x) && (y < height+x-width))
					cr = Color::rgb(0,0,65) ; // right
				else if (y >height-_size)
					cr = Color::rgb(0,0,120) ; // bottom
				else
					continue;

				Color color(cr);
				int t = 0xFF - a ;
				imageIn.setPixelColor(x, y, (color.R * a + r * t) / 0xFF, (color.G * a + g * t) / 0xFF, (color.B * a + b * t) / 0xFF);
			}
		}
#ifndef WIN32 //only for apple ios
		imageIn.copyPixelsFromBuffer();
#endif
		return imageIn;
	}
};

}// namespace HaoRan
#endif