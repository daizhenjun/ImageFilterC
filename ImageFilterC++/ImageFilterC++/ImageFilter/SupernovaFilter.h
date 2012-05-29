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

#if !defined(SupernovaFilter_H)
#define SupernovaFilter_H

#include "IImageFilter.h"


namespace HaoRan_ImageFilter{

class SupernovaFilter : public IImageFilter{

private:
	POINT    _pt ;
    double   _radius ;
    int      _count ;

    std::vector<double>   _spoke ;
    std::vector<int>  _spokecolor ;

    static double get_gauss()
    {
        double   s = 0 ;
        for (int i=0 ; i < 6 ; i++)
            s = s + rand() / (double)(RAND_MAX + 1.0) ;
        return s / 6.0 ;
    }

    static int BoundParam1 (int n)
    {
        return ((n >= 1) ? n : 1) ;
    }

public:

	SupernovaFilter(POINT pt, int cr, int radius, int count) : _spoke(BoundParam1(count)), _spokecolor(BoundParam1(count))
    {
        _pt = pt ;
        _radius = BoundParam1(radius) ;
        _count = BoundParam1(count) ;

        for (int i=0 ; i < _count ; i++)
        {
            _spoke[i] = get_gauss() ;
            _spokecolor[i] = cr ;
        }
    }

	SupernovaFilter(int cr, int radius, int count) : _pt(CPoint(0,0)), _spoke(BoundParam1(count)), _spokecolor(BoundParam1(count))
    {
       _radius = BoundParam1(radius) ;
        _count = BoundParam1(count) ;

        for (int i=0 ; i < _count ; i++)
        {
            _spoke[i] = get_gauss() ;
            _spokecolor[i] = cr ;
        }
    }

	virtual Image process(Image imageIn)
	{
		if((_pt.x + _pt.y) <= 0){
			_pt.x = imageIn.getWidth() /2;
			_pt.y = imageIn.getHeight() /2;
		}
		  for(int x = 0 ; x < (imageIn.getWidth() - 1) ; x++){
			  for(int y = 0 ; y < (imageIn.getHeight() - 1) ; y++){
				std::vector<int> pixel(3);
				pixel[0] = imageIn.getRComponent(x, y);
				pixel[1] =  imageIn.getGComponent(x, y);
				pixel[2] =  imageIn.getBComponent(x, y);
				
				double   u = (x - _pt.x + 0.001) / _radius ;
				double   v = (y - _pt.y + 0.001) / _radius ;

				double   t = (atan2 (u, v) / (2 * LIB_PI) + 0.51) * _count ;
				int      i = (int)floor(t) ;
				t -= i ;
				i %= _count ;

				double   w1 = _spoke[i] * (1-t) + _spoke[(i+1) % _count] * t ;
				w1 = w1 * w1 ;

				double   w = 1.0 / sqrt (u*u + v*v) * 0.9 ;
				double   fRatio = FClamp (w, 0.0, 1.0) ;

				double   ws = FClamp (w1 * w, 0.0, 1.0) ;

				for (int m=0 ; m < 3 ; m++)
				{
					double   spokecol = ((BYTE*)&_spokecolor[i])[m]/255.0 * (1-t) + ((BYTE*)&_spokecolor[(i+1) % _count])[m]/255.0 * t ;

					double   r;
					if (w > 1.0)
						r = FClamp (spokecol * w, 0.0, 1.0);
					else {
						r = pixel[m]/255.0 * (1.0 - fRatio) + spokecol * fRatio ;
					}

					r += ws ;
					pixel[m] = FClamp0255 (r*255) ;
					imageIn.setPixelColor(x, y, pixel[0], pixel[1], pixel[2]);
				}
			}
		  }
#ifndef WIN32 //only for apple ios
		imageIn.copyPixelsFromBuffer();
#endif
		return imageIn;
	}
};

}// namespace HaoRan
#endif