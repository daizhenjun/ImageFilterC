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

#if !defined(ThreeDGridFilter_h)
#define ThreeDGridFilter_h

#include "IImageFilter.h"


namespace HaoRan_ImageFilter{

class ThreeDGridFilter : public IImageFilter{
private:
	int   m_size ;
    int   m_depth ;
public:

	ThreeDGridFilter(int nSize, int nDepth)
    {
        m_size = ((nSize >= 1) ? nSize : 1) ;
        m_depth = nDepth ;
    };

	virtual Image process(Image imageIn)
	{
		  int r, g, b;
		  for(int x = 0 ; x < (imageIn.getWidth() - 1) ; x++){
			  for(int y = 0 ; y < (imageIn.getHeight() - 1) ; y++){
					r = imageIn.getRComponent(x, y);
					g = imageIn.getGComponent(x, y);
					b = imageIn.getBComponent(x, y);

				    int  d = 0 ;
					if (((y-1) % m_size == 0) && (x % m_size) && ((x+1) % m_size))
						d = -m_depth ; // top
					else if (((y+2) % m_size == 0) && (x % m_size) && ((x+1) % m_size))
						d = m_depth ; // bottom
					else if (((x-1) % m_size == 0) && (y % m_size) && ((y+1) % m_size))
						d = m_depth ; // left
					else if (((x+2) % m_size == 0) && (y % m_size) && ((y+1) % m_size))
						d = -m_depth ; // right

				   imageIn.setPixelColor(x, y, SAFECOLOR(r+d),  SAFECOLOR(g+d),  SAFECOLOR(b+d));
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