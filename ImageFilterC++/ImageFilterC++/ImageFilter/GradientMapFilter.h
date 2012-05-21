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

#if !defined(GradientMapFilter_H)
#define GradientMapFilter_H

#include "GradientFilter.h"
#include <vector>


namespace HaoRan_ImageFilter{

class GradientMapFilter : public IImageFilter{
public:
	float BrightnessFactor;
	float ContrastFactor;
	Gradient Map;
	
	GradientMapFilter() : BrightnessFactor(0),ContrastFactor(0) {};
	GradientMapFilter(Gradient gradient) : Map(gradient),  BrightnessFactor(0),ContrastFactor(0) {};

	virtual Image process(Image imageIn)
	{
		Palette palette = Map.CreatePalette(0x100);
	    vector<int> red = palette.Red;
	    vector<int> green = palette.Green;
	    vector<int> blue = palette.Blue;
	    Image bitmap = imageIn.clone();
		bitmap.clearImage(::White);
	    int bfactor = (int) (BrightnessFactor * 255);
	    float cfactor = 1 + ContrastFactor;
	    cfactor *= cfactor;
	    int limit = ((int) (cfactor * 32768)) + 1;
		int size = imageIn.getHeight()*imageIn.getWidth();
		for (int i = 0; i < size; i++)
	    {
	        int r = (imageIn.colorArray[i]& 0x00FF0000) >> 16;
	        int g = (imageIn.colorArray[i]& 0x0000FF00) >> 8;
	        int b = imageIn.colorArray[i]& 0x000000FF;
	        int index = (((r * 0x1b36) + (g * 0x5b8c)) + (b * 0x93e)) >> 15;
	        if (bfactor != 0)
	        {
	            index += bfactor;
	            index = (index > 0xff) ? 0xff : ((index < 0) ? 0 : index);
	        }
	        if (limit != 0x8001)
	        {
	            index -= 0x80;
	            index = (index * limit) >> 15;
	            index += 0x80;
	            index = (index > 0xff) ? 0xff : ((index < 0) ? 0 : index);
	        }
			bitmap.colorArray[i] = (0xff << 24) + (red[index] << 16) + (green[index] << 8) + blue[index];
	    }
#ifndef WIN32 //only for apple ios
		imageIn.copyPixelsFromBuffer();
#endif
	    return bitmap;   	
	}
};

}// namespace HaoRan

#endif