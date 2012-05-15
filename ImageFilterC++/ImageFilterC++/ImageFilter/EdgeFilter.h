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


#if !defined(EdgeFilter_H)
#define EdgeFilter_H

#include "IImageFilter.h"
#include "math.h"

namespace HaoRan_ImageFilter{

class EdgeFilter : public IImageFilter{

private:	
   /* int truncate(int a) {
        if (a < 0)
            return 0;
        else if (a > 255)
            return 255;
        else
            return a;
    }*/

    /**
     * Apply the luminance
     * @param r
     * @param g
     * @param b
     * @return
     */
    int ApplyLuminance(int r, int g, int b) {
        return (int) ((0.299 * r) + (0.58 * g) + (0.11 * b));
    }

public:
	EdgeFilter(){};

	virtual Image process(Image imageIn)
	{
        int width = imageIn.getWidth();
        int height = imageIn.getHeight();
        //bool[][] mask = null;
        int grayMatrix[256];

        // Init gray matrix
        for (int i = 0; i <= 255; i++) {
            grayMatrix[i] = (255 << 24) + (i << 16) + (i<< 8) + i;
        }
		//使用vector模拟二维动态数组
		vector<vector<int>> luminance(width);
		for(int x = 0; x < width ; x++) {
			luminance[x].resize(height);
		}
	    for(int y = 0; y < height ; y++) {
            for(int x = 0; x < width ; x++) {
               /* if(mask != null && !mask[x][y]){
                    continue;
                }*/
		        luminance[x][y] = (int) ApplyLuminance(imageIn.getRComponent(x, y), imageIn.getGComponent(x, y), imageIn.getBComponent(x, y));
            }
        }

        int grayX, grayY;
        int magnitude;
        for (int y = 1; y < height-1; y++) {
            for (int x = 1; x < width-1; x++) {
               /* if(mask != null && !mask[x][y]){
                    continue;
                }*/

                grayX = -luminance[x-1][y-1] + luminance[x-1][y-1+2] - 2* luminance[x-1+1][y-1] + 2* luminance[x-1+1][y-1+2] - luminance[x-1+2][y-1]+ luminance[x-1+2][y-1+2];
                grayY = luminance[x-1][y-1] + 2* luminance[x-1][y-1+1] + luminance[x-1][y-1+2] - luminance[x-1+2][y-1] - 2* luminance[x-1+2][y-1+1] - luminance[x-1+2][y-1+2];

                // Magnitudes sum
                magnitude = 255 - SAFECOLOR(abs(grayX) + abs(grayY));
                // Apply the color into a new image
                imageIn.setPixelColor(x, y, grayMatrix[magnitude]);
            }
        }
#ifndef WIN32 //only for apple ios
		clone.copyPixelsFromBuffer();
#endif
        return imageIn;
	}
};

}// namespace HaoRan

#endif