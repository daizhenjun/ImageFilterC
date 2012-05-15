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

#if !defined(SaturationModifyFilter_H)
#define SaturationModifyFilter_H

#include "IImageFilter.h"


namespace HaoRan_ImageFilter{

class SaturationModifyFilter : public IImageFilter{

public:
	float SaturationFactor;
	SaturationModifyFilter() : SaturationFactor(0.5f){};

	virtual Image process(Image imageIn)
	{
		float saturation = SaturationFactor + 1;
    	float negosaturation = 1 - saturation;
        int r, g, b;
        for (int x = 0; x < imageIn.getWidth(); x++) {
            for (int y = 0; y < imageIn.getHeight(); y++) {
            	 r = imageIn.getRComponent(x, y);
                 g = imageIn.getGComponent(x, y);
                 b = imageIn.getBComponent(x, y);  
                 
                 float nego1 = negosaturation * 0.2126;
                 float ngeo2 = nego1 + saturation;
                 float ngeo3 = negosaturation * 0.7152;
                 float nego4 = ngeo3 + saturation;
                 float nego5 = negosaturation * 0.0722;
                 float nego6 = nego5 + saturation;
                 float rr = ((r * ngeo2) + (g * ngeo3)) + (b * nego5);
                 float gg = ((r * nego1) + (g * nego4)) + (b * nego5);
                 float bb = ((r * nego1) + (g * ngeo3)) + (b * nego6);
                 r = SAFECOLOR(rr);
                 g = SAFECOLOR(gg);
                 b = SAFECOLOR(bb);
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