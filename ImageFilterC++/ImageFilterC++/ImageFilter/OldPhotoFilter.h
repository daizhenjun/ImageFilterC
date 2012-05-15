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

#if !defined(OldPhotoFilter_H)
#define OldPhotoFilter_H

#include "GaussianBlurFilter.h"
#include "NoiseFilter.h"
#include "VignetteFilter.h"
#include "GradientMapFilter.h"

namespace HaoRan_ImageFilter{

class OldPhotoFilter : public IImageFilter{

private:
	GaussianBlurFilter blurFx;
	NoiseFilter noiseFx;
	VignetteFilter vignetteFx;
	GradientMapFilter gradientFx;

public:
	
	OldPhotoFilter(){
		blurFx.Sigma = 0.3f;		  
		noiseFx.Intensity = 0.03f;		
		vignetteFx.Size = 0.6f;		
    	gradientFx.ContrastFactor = 0.3f;
	};


	virtual Image process(Image imageIn)
	{
		imageIn = noiseFx.process(blurFx.process(imageIn));
    	imageIn = gradientFx.process(imageIn);
    	return vignetteFx.process(imageIn);
	}
};

}// namespace HaoRan
#endif