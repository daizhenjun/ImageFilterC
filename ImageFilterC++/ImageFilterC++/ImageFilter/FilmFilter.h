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
#if !defined(FilmFilter_H)
#define FilmFilter_H

#include "IImageFilter.h"
#include "GradientFilter.h"
#include "SaturationModifyFilter.h"
#include "ImageBlender.h"

namespace HaoRan_ImageFilter{

class FilmFilter : public IImageFilter{

private:
	 GradientFilter gradient;
     SaturationModifyFilter saturationFx;


public:

	 FilmFilter(float angle)
     {
		gradient.gradient = Gradient::Fade();
		gradient.OriginAngleDegree = angle;

		saturationFx.SaturationFactor = -0.6f;
	 };

	 virtual Image process(Image imageIn)
	 {
		Image clone = imageIn.clone();
		imageIn = gradient.process(imageIn);
		ImageBlender blender;
		blender.Mode = BlendMode::Multiply;
		imageIn = saturationFx.process(blender.Blend(clone, imageIn));
      
#ifndef WIN32 //only for apple ios
		 imageIn.copyPixelsFromBuffer();
#endif
	     return imageIn;
        //return imageIn;// saturationFx.process(imageIn);
	 }
};

}// namespace HaoRan
#endif