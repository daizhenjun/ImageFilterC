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

#if !defined(BlindFilter_H)
#define BlindFilter_H

#include "IImageFilter.h"


namespace HaoRan_ImageFilter{

class BlindFilter : public IImageFilter{

private:
	bool _direct;//horizontal: true,  vertical: false
	int _color;
	int _opacity;
    int _width;
	
public:
	

    BlindFilter(bool direct, int width, int opacity, int blindColor)
    {
        _direct = direct ;
        _width = (width >= 2) ? width : 2;
        _opacity = FClamp (opacity, 1, 100);
		_color = blindColor;
    };


	virtual Image process(Image imageIn)
	{
		  int r, g, b, a;
		  for(int x = 0 ; x < (imageIn.getWidth() - 1) ; x++){
			  for(int y = 0 ; y < (imageIn.getHeight() - 1) ; y++){
				r = imageIn.getRComponent(x, y);
				g = imageIn.getGComponent(x, y);
				b = imageIn.getBComponent(x, y);
				int  nMod = 0 ;
				if (_direct) // horizontal direction
					nMod = y % _width ;
				else if (_direct == false) // vertical direction
					nMod = x % _width ;

				double fDelta = 255.0 * (_opacity/100.0) / (_width-1.0);
				a = FClamp0255(nMod * fDelta) ;
				Color color(_color);
				if (_color == 0xFF)
				{
					imageIn.setPixelColor(x, y, color.R, color.G, color.B);
					continue ;
				}
				if (a == 0)
					continue ;

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