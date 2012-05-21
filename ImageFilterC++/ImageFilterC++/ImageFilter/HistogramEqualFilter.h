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

#if !defined(HistogramEqualFilter_H)
#define HistogramEqualFilter_H

#include "IImageFilter.h"
#include <vector>


namespace HaoRan_ImageFilter{

class HistogramEqualFilter : public IImageFilter{
public:
	float ContrastIntensity ;

	HistogramEqualFilter():ContrastIntensity(1){};
	
	virtual Image process(Image imageIn)
	{
		int r, g, b;
        int _array[256];
        vector<int> numArray(imageIn.getHeight()*imageIn.getWidth());
        int contrast = (int) (ContrastIntensity * 255);
        int pos = 0;
        for (int x = 0; x < imageIn.getWidth(); x++) {
            for (int y = 0; y < imageIn.getHeight(); y++) {
            	 r = imageIn.getRComponent(x, y);
                 g = imageIn.getGComponent(x, y);
                 b = imageIn.getBComponent(x, y);
                 int index = (r * 0x1b36 + g * 0x5b8c + b * 0x93e) >> 15;
            	 _array[index]++;
                 numArray[pos] = index;
                 pos++;
            }
        }
        for (int i = 1; i < 0x100; i++){
            _array[i] += _array[i - 1];
        }
        for (int i = 0; i < 0x100; i++){
            _array[i] = (_array[i] << 8) / imageIn.getHeight()*imageIn.getWidth();
            _array[i] = ((contrast * _array[i]) >> 8) + (((0xff - contrast) * i) >> 8);
        }
        pos = 0;
        for (int x = 0; x < imageIn.getWidth(); x++) {
            for (int y = 0; y < imageIn.getHeight(); y++) {
            	 r = imageIn.getRComponent(x, y);
                 g = imageIn.getGComponent(x, y);
                 b = imageIn.getBComponent(x, y);
                 if (numArray[pos] != 0){
                     int num = _array[numArray[pos]];
                     r = (r * num) / numArray[pos];
                     g = (g * num) / numArray[pos];
                     b = (b * num) / numArray[pos];
                     r = (r > 0xff) ? ((byte) 0xff) : ((r < 0) ? ((byte) 0) : ((byte) r));
                     g = (g > 0xff) ? ((byte) 0xff) : ((g < 0) ? ((byte) 0) : ((byte) g));
                     b = (b > 0xff) ? ((byte) 0xff) : ((b < 0) ? ((byte) 0) : ((byte) b));
                 }    
                 imageIn.setPixelColor(x,y,r,g,b);
                 pos++;
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