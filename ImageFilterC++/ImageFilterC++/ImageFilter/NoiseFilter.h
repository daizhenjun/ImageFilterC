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

#if !defined(NoiseFilter_H)
#define NoiseFilter_H

#include "IImageFilter.h"


namespace HaoRan_ImageFilter{

class NoiseFilter : public IImageFilter{
public:
	float Intensity;
	 
    static int getRandomInt(int a, int b) {  
    	int min = min(a, b);    
    	int max = max(a, b);
        return rand()%((b)-(a)) + (a);
    }  

	NoiseFilter() : Intensity(0.2f){};

	virtual Image process(Image imageIn)
	{
		int r, g, b;
        int num = (int)(Intensity * 32768);
        for (int x = 0; x < imageIn.getWidth(); x++) {
            for (int y = 0; y < imageIn.getHeight(); y++) {
                 r = imageIn.getRComponent(x, y);
                 g = imageIn.getGComponent(x, y);
                 b = imageIn.getBComponent(x, y);
                 if (num != 0){
                    int rr = getRandomInt(-255, 0xff) * num;
                    int gg = getRandomInt(-255, 0xff) * num;
                    int bb = getRandomInt(-255, 0xff) * num;
                    int rrr = r + (rr >> 15);
                    int ggg = g + (gg >> 15);
                    int bbb = b + (bb >> 15);
                    r = SAFECOLOR(rrr);
                    g = SAFECOLOR(ggg);
                    b = SAFECOLOR(bbb);
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