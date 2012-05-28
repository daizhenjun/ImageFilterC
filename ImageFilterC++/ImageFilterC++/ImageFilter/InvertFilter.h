/* 
 * HaoRan ImageFilter Classes v0.1
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

#if !defined(INVERTFILTER_H)
#define INVERTFILTER_H

#include "IImageFilter.h"


namespace HaoRan_ImageFilter{

class InvertFilter : public IImageFilter{

public:

	InvertFilter(){};

	virtual Image process(Image imageIn)
	{
		  int r, g, b;
		  for(int x = 0 ; x < (imageIn.getWidth() - 1) ; x++){
			  for(int y = 0 ; y < (imageIn.getHeight() - 1) ; y++){
				   r = 255 - imageIn.getRComponent(x, y);
				   g = 255 - imageIn.getGComponent(x, y);
				   b = 255 - imageIn.getBComponent(x, y);
				   imageIn.setPixelColor(x, y, r, g, b);
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