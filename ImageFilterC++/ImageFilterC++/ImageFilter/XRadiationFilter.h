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

#if !defined(XRadiationFilter_H)
#define XRadiationFilter_H

#include "GradientMapFilter.h"
#include "ImageBlender.h"

namespace HaoRan_ImageFilter{

class XRadiationFilter : public IImageFilter{
private:
	GradientMapFilter gradientMapFx;
    ImageBlender blender;
public:

	XRadiationFilter(){
	    vector<int> colors(2);
	    colors[0] = ::LightCyan;
	    colors[1] = ::Black;
		Gradient gradient(colors);
	    gradientMapFx.Map = gradient;
	    blender.Mode = ::ColorBurn;
	    blender.Mixture = 0.8f;
	};

	virtual Image process(Image imageIn)
	{
		imageIn = gradientMapFx.process(imageIn);
    	imageIn = blender.Blend(imageIn, imageIn);
    	return imageIn;
	}
};

}// namespace HaoRan
#endif

