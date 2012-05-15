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

#if !defined(NeonFilter_H)
#define NeonFilter_H

#include "NoiseFilter.h"
#include "GradientFilter.h"

namespace HaoRan_ImageFilter{

class NeonFilter : public IImageFilter{
private:
    int Luminance(int r, int g, int b) {
        return (int) ((0.299 * r) + (0.58 * g) + (0.11 * b));
    }   
public:
	NeonFilter(){};
	virtual Image process(Image imageIn)
	{
		// Image size
        int width = imageIn.getWidth();
        int height = imageIn.getHeight();
        //bool[][] mask = null;
        int grayMatrix[256];

        // Init gray matrix
        int outlineCase = 1;
        double rand =  NoiseFilter::getRandomInt(1, 123456);
        if (rand>0.33 && rand<0.66){
            outlineCase=2;
        }
        else if (rand>0.66){
            outlineCase=3;
        }
        for (int i = 255; i >= 0; i--) {
            int red=i,green=i,blue=i;
            if (i>127)
            {
                switch(outlineCase){
                case 1 :
                    red = 255-i;
                    break;                  
                case 2 :
                    green = 255-i;
                    break;      
                case 3 :
                    blue = 255-i;
                    break;
                }
            }
            grayMatrix[255-i] = Color::rgb(red, green, blue);
        }

       	//使用vector模拟二维动态数组
		vector<vector<int>> luminance(width);
		for(int x = 0; x < width ; x++) {
			luminance[x].resize(height);
		}
        for (int y = 0; y < height ; y++) {
            for (int x = 0; x < width ; x++) {
                /*if(mask != null && !mask[x][y]){
                    continue;
                }*/
                luminance[x][y] = (int) Luminance(imageIn.getRComponent(x, y), imageIn.getGComponent(x, y), imageIn.getBComponent(x, y));
            }
        }


        int grayX, grayY;
        int magnitude;
        for (int y = 1; y < height-1; y++) {
            for (int x = 1; x < width-1; x++) {
               /* if(mask != null && !mask[x][y]){
                    continue;
                }*/

                grayX = - luminance[x-1][y-1] + luminance[x-1][y-1+2] - 2* luminance[x-1+1][y-1] + 2* luminance[x-1+1][y-1+2] - luminance[x-1+2][y-1]+ luminance[x-1+2][y-1+2];
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