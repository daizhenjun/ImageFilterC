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
#if !defined(RainBowFilter_H)
#define RainBowFilter_H

#include "ImageBlender.h"
#include "GradientFilter.h"


namespace HaoRan_ImageFilter{

class RainBowFilter : public IImageFilter{
private:
	ImageBlender blender;
	GradientFilter gradientFx;
	
public:
	float gradAngleDegree; 
	bool IsDoubleRainbow;
	
	RainBowFilter(){
	    IsDoubleRainbow = true;
		gradAngleDegree = 40;

		blender.Mixture = 0.25f;
		blender.Mode = ::Additive;//LinearLight;
		   
        vector<int> rainbowColors = Gradient::RainBow().MapColors;
        if (IsDoubleRainbow)
        {
			rainbowColors.erase(rainbowColors.begin() + rainbowColors.size() - 1);//remove red
			vector<int> vi = Gradient::RainBow().MapColors;
			for(vector<int>::iterator it = vi.begin(); it!=vi.end(); it++){    
				rainbowColors.push_back(*it);
			}
        }  
		gradientFx.OriginAngleDegree = gradAngleDegree;
		Gradient gradient(rainbowColors);
		gradientFx.gradient = gradient;
	};

	virtual Image process(Image imageIn)
	{
       Image clone = gradientFx.process(imageIn.clone());
       return blender.Blend(imageIn, clone);
	}
};

}// namespace HaoRan
#endif