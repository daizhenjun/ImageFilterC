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
 
#if !defined(NightVisionFilter_H)
#define NightVisionFilter_H

#include "NoiseFilter.h"
#include "VignetteFilter.h"
#include "GradientMapFilter.h"
#include "GradientFilter.h"

#include "ImageBlender.h"

namespace HaoRan_ImageFilter{

class NightVisionFilter : public IImageFilter{

private:
	NoiseFilter noisefx;
    ImageBlender blender;
    VignetteFilter vignetteFx;
    GradientMapFilter gradientFx;

public:
    
	NightVisionFilter(){
	    noisefx.Intensity = 0.15f;
		 
		vignetteFx.Size = 1;
		
		vector<int> colors(2);
	    colors[0] = ::Black;
	    colors[1] = ::Green;
		Gradient gradient(colors);
	    gradientFx.Map = gradient;
	    gradientFx.BrightnessFactor = 0.2f;
	};

	virtual Image process(Image imageIn)
	{
		imageIn = noisefx.process(imageIn);
    	imageIn = gradientFx.process(imageIn);
    	imageIn = vignetteFx.process(imageIn);
     	return imageIn;
	}
};

}// namespace HaoRan
#endif