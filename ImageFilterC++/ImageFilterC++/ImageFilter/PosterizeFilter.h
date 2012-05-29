/* 
 * HaoRan ImageFilter Classes v0.3
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

#if !defined(PosterizeFilter_H)
#define PosterizeFilter_H

#include "IImageFilter.h"


namespace HaoRan_ImageFilter{

class LUTFilter : public IImageFilter
{
    int   m_LUT[256] ;
public:
    /**
        Initialize table \n
        0 <= nLUTIndex <= 0xFF
    */
    virtual int InitLUTtable (int nLUTIndex) =0 ;

private:
    virtual Image process(Image imageIn)
	{
		for (int i=0 ; i <= 0xFF ; i++)
			m_LUT[i] = InitLUTtable (i) ;
		int r, g, b;
		for(int x = 0 ; x < (imageIn.getWidth() - 1) ; x++){
			for(int y = 0 ; y < (imageIn.getHeight() - 1) ; y++){
				r = imageIn.getRComponent(x, y);
				g = imageIn.getGComponent(x, y);
				b = imageIn.getBComponent(x, y);
				
				imageIn.setPixelColor(x, y, SAFECOLOR(m_LUT[r]), SAFECOLOR(m_LUT[g]), SAFECOLOR(m_LUT[b]));
			}
		}
#ifndef WIN32 //only for apple ios
		imageIn.copyPixelsFromBuffer();
#endif
	    return imageIn;
    }
};

class PosterizeFilter : public LUTFilter{

private:
	int   _level ;
    virtual int InitLUTtable (int LUTIndex)
    {
        double  d = 255.0 / (_level - 1.0) ;
        int     n = (int)(LUTIndex / d + 0.5) ; // round
        return FClamp0255 (d * n) ; // round
    }
    
public:
    /**
        Constructor \n
        nLevel >= 2
    */
    PosterizeFilter (int nLevel)
    {
        _level = ((nLevel >= 2) ? nLevel : 2) ;
    }
};


class GammaFilter : public LUTFilter
{
    double   _fInvGamma ;
public:
    /**
        Constructor \n
        nGamma >= 1, 100 means not change
    */
    GammaFilter (int gamma)
    {
        gamma = ((gamma >= 1) ? gamma : 1) ;
        _fInvGamma = 1.0 / (gamma / 100.0) ;
    }
private:
    virtual int InitLUTtable (int nLUTIndex)
    {
        double   fMax = pow (255.0, _fInvGamma) / 255.0 ;
        double   d = pow((double)nLUTIndex, _fInvGamma) ;
        return FClamp0255(d / fMax) ;
    }
};

}// namespace HaoRan
#endif