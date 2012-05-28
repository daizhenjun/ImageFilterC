/* 
 * HaoRan ImageFilter Classes v0.2
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
#if !defined(FocusFilter_H)
#define FocusFilter_H

#include "IImageFilter.h"
#include "GradientFilter.h"
#include "GaussianBlurFilter.h"

namespace HaoRan_ImageFilter{

class FocusFilter : public GaussianBlurFilter{


public:

	/// <summary>
	/// Should be in the range [0, 1].
	/// </summary>
	float Size;
		
	FocusFilter()
	{
		Size = 0.5f;
		Sigma = 25.0f;
	};

	virtual Image process(Image imageIn)
	{
		int ratio = imageIn.getWidth() > imageIn.getHeight() ? imageIn.getHeight() * 32768 / imageIn.getWidth() : imageIn.getWidth() * 32768 / imageIn.getHeight();

        // Calculate center, min and max
        int cx = imageIn.getWidth() >> 1;
        int cy = imageIn.getHeight() >> 1;
        int max = cx * cx + cy * cy;
        int min = (int)(max * (1 - Size));
        int diff = max - min;

        int width = imageIn.getWidth();
        int height = imageIn.getHeight();
        vector<float> imageArray = ConvertImageWithPadding(imageIn, width, height);
        imageArray = ApplyBlur(imageArray, width, height);
        int newwidth = width + Padding * 2;
        for (int i = 0; i < height; i++)
        {
            int num = ((i + 3) * newwidth) + 3;
            for (int j = 0; j < width; j++)
            {
                    // Calculate distance to center and adapt aspect ratio
                int dx = cx - j;
                int dy = cy - i;
                if (imageIn.getWidth() > imageIn.getHeight())
                {
                    dy = (dy * ratio) >> 14;
                }
                else
                {
                    dx = (dx * ratio) >> 14;
                }
                int distSq = dx * dx + dy * dy;

                if (distSq > min)
                {
                    int pos = (num + j) * 3;
                    imageIn.setPixelColor(j, i, (byte)(imageArray[pos] * 255.0f), (byte)(imageArray[pos + 1] * 255.0f), (byte)(imageArray[pos + 2] * 255.0f));
                }
            }
        }

#ifndef WIN32 //only for apple ios
		imageIn.copyPixelsFromBuffer();
#endif
	    return imageIn;
        //return imageIn;// saturationFx.process(imageIn);
	 }
};

}// namespace HaoRan
#endif