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
	bool m_direct;//horizontal: true,  vertical: false
	int m_color;
	int m_opacity;
    int m_width;
	
public:
	

    BlindFilter(bool nDirect, int nWidth, int nOpacity, int blind_color)
    {
        m_direct = nDirect ;
        m_width = ((nWidth >= 2) ? nWidth : 2) ;
        m_color = blind_color ;
        m_opacity = FClamp (nOpacity, 1, 100) ;
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
				if (m_direct) // horizontal direction
					nMod = y % m_width ;
				else if (m_direct == false) // vertical direction
					nMod = x % m_width ;

				double fDelta = 255.0 * (m_opacity/100.0) / (m_width-1.0);
				a = FClamp0255(nMod * fDelta) ;
				Color color(m_color);
				if (m_color == 0xFF)
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