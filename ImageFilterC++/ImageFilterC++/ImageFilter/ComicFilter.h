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
#if !defined(ComicFilter_H)
#define ComicFilter_H

#include "IImageFilter.h"
#include "GradientFilter.h"
#include "SaturationModifyFilter.h"
#include "ImageBlender.h"
#include "ParamEdgeDetectFilter.h"
#include "GaussianBlurFilter.h"

namespace HaoRan_ImageFilter{

class ComicFilter : public IImageFilter{

private:
	 SaturationModifyFilter saturationFx;
     GaussianBlurFilter blurFx;
     ImageBlender blender;
     ParamEdgeDetectFilter edgeDetectionFx;
     ImageBlender edgeBlender;

public:

	 ComicFilter()
     {
		saturationFx.SaturationFactor = 1.0f;
		blurFx.Sigma = 1.0f;
		blender.Mixture = 1.0f;
		blender.Mode = BlendMode::Lighten;
		edgeDetectionFx.Threshold = 0.25f;
		edgeDetectionFx.DoGrayConversion = true;
		edgeBlender.Mixture = 0.8f;
		edgeBlender.Mode = BlendMode::Lighten;
	 };

	 virtual Image process(Image imageIn)
	 {
		Image saturated = saturationFx.process(imageIn.clone());
		Image blurred = blurFx.process(saturated);
		imageIn = blender.Blend(saturated, blurred);
		Image edge = edgeDetectionFx.process(imageIn.clone());
		imageIn = edgeBlender.Blend(imageIn, edge);

#ifndef WIN32 //only for apple ios
		 imageIn.copyPixelsFromBuffer();
#endif
	     return imageIn;
        //return imageIn;// saturationFx.process(imageIn);
	 }
};

}// namespace HaoRan
#endif