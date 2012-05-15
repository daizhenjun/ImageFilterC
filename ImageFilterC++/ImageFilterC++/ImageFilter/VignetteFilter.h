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

#if !defined(VignetteFilter_H)
#define VignetteFilter_H

#include "IImageFilter.h"


namespace HaoRan_ImageFilter{

class VignetteFilter : public IImageFilter{
public:
	float Size;

	VignetteFilter() : Size(0.5){};

	virtual Image process(Image imageIn)
	{
		int r, g, b;
        int ratio = imageIn.getWidth() >  imageIn.getHeight() ?  imageIn.getHeight() * 32768 / imageIn.getWidth() : imageIn.getWidth() * 32768 /  imageIn.getHeight();

        // Calculate center, min and max
        int cx = imageIn.getWidth() >> 1;
        int cy = imageIn.getHeight() >> 1;
        int max = cx * cx + cy * cy;
        int min = (int)(max * (1 - Size));
        int diff = max - min;

        for (int x = 0; x < imageIn.getWidth(); x++) {
            for (int y = 0; y < imageIn.getHeight(); y++) {
            	 r = imageIn.getRComponent(x, y);
                 g = imageIn.getGComponent(x, y);
                 b = imageIn.getBComponent(x, y);

                 // Calculate distance to center and adapt aspect ratio
                 int dx = cx - x;
                 int dy = cy - y;
                 if (imageIn.getWidth() > imageIn.getHeight()){
                    dx = (dx * ratio) >> 15;
                 }
                 else{
                    dy = (dy * ratio) >> 15;
                 }
                 int distSq = dx * dx + dy * dy;

                 if (distSq > min){
                    // Calculate vignette
                    int v = ((max - distSq) << 8) / diff;
                    v *= v;

                    // Apply vignette
                    int ri = (r * v) >> 16;
                    int gi = (g * v) >> 16;
                    int bi = (b * v) >> 16;

                    // Check bounds
                    r = SAFECOLOR(ri);
                    g = SAFECOLOR(gi);
                    b = SAFECOLOR(bi);
                 }
         
                 imageIn.setPixelColor(x,y,r,g,b);
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