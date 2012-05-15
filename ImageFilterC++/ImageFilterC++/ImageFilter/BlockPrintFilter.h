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

#include "ParamEdgeDetectFilter.h"
#include "ImageBlender.h"

#if !defined(BlockPrintFilter_H)
#define BlockPrintFilter_H

namespace HaoRan_ImageFilter{

class BlockPrintFilter : public IImageFilter{
public:
	BlockPrintFilter(){};
	virtual Image process(Image imageIn)
	{
		ParamEdgeDetectFilter pde;
    	pde.K00 = 1;
    	pde.K01 = 2;
    	pde.K02 = 1;
    	pde.Threshold = 0.25f;
        pde.DoGrayConversion = false;
        ImageBlender ib;
        ib.Mode = ::Multiply;
        return ib.Blend(imageIn.clone(), pde.process(imageIn));
	}
};

}// namespace HaoRan
#endif