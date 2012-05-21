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

#if !defined(ColorQuantizeFilter_H)
#define ColorQuantizeFilter_H

#include "IImageFilter.h"

namespace HaoRan_ImageFilter{

class ColorQuantizeFilter : public IImageFilter{
private:
	float levels;

public:
	ColorQuantizeFilter(): levels(5){};

	virtual Image process(Image imageIn)
	{
		int r, g, b;
        for (int x = 0; x < imageIn.getWidth(); x++) {
            for (int y = 0; y < imageIn.getHeight(); y++) {
                 r = imageIn.getRComponent(x, y);
                 g = imageIn.getGComponent(x, y);
                 b = imageIn.getBComponent(x, y);
                 float quanR = (((float) ((int) (r * 0.003921569 * levels))) / levels) * 255;
                 float quanG = (((float) ((int) (g * 0.003921569 * levels))) / levels) * 255;
                 float quanB = (((float) ((int) (b * 0.003921569 * levels))) / levels) * 255;
                 r = (quanR > 255) ? 255 : ((quanR < 0) ? 0 : ((byte) quanR));
                 g = (quanG > 255) ? 255 : ((quanG < 0) ? 0 : ((byte) quanG));
                 b = (quanB > 255) ? 255 : ((quanB < 0) ? 0: ((byte) quanB));
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