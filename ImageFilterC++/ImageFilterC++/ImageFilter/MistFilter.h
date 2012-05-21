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

#if !defined(MistFilter_H)
#define MistFilter_H

#include "NoiseFilter.h"


namespace HaoRan_ImageFilter{

class MistFilter : public IImageFilter{
public:
	MistFilter(){};

	virtual Image process(Image imageIn)
	{
	   int width = imageIn.getWidth();
       int height = imageIn.getHeight();
       Image clone = imageIn.clone();
       int r = 0, g = 0, b = 0;
       for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
            	  int k = NoiseFilter::getRandomInt(1, 123456);
            	  //ÏñËØ¿é´óÐ¡
            	  int dx = x + k % 8;
            	  int dy = y + k % 8;
            	  if(dx >= width) {
            		  dx = width -1;   				  
            	  }
            	  if(dy >= height) {
            		  dy = height -1;   				  
            	  }
            	  r = clone.getRComponent(dx, dy);
            	  g = clone.getGComponent(dx, dy);
            	  b = clone.getBComponent(dx, dy);
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