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

#if !defined(TileReflectionFilter_H)
#define TileReflectionFilter_H

#include "IImageFilter.h"


namespace HaoRan_ImageFilter{

class TileReflectionFilter : public IImageFilter{

private:

	struct POINT_FLOAT
    {
        double   x ;
        double   y ;
    };

    // angle ==> radian
    double AngleToRadian (int nAngle) {return LIB_PI * nAngle / 180.0;}

	double   m_sin, m_cos ;
    double   m_scale ;
    double   m_curvature ;
	const static int aasamples = 17;
    POINT_FLOAT   m_aapt[aasamples] ;
  
	
public:

	/**
		Constructor \n
		param -45 <= nAngle <= 45 \n
		param 2 <= nSquareSize <= 200 \n
		param -20 <= nCurvature <= 20
	*/
    TileReflectionFilter (int nSquareSize, int nCurvature, int nAngle=45)
    {
        nAngle = FClamp (nAngle, -45, 45) ;
        m_sin = sin (AngleToRadian(nAngle)) ;
        m_cos = cos (AngleToRadian(nAngle)) ;

        nSquareSize = FClamp (nSquareSize, 2, 200) ;
        m_scale = LIB_PI / nSquareSize ;

        nCurvature = FClamp (nCurvature, -20, 20) ;
        if (nCurvature == 0)
            nCurvature = 1 ;
        m_curvature = nCurvature * nCurvature / 10.0 * (abs(nCurvature)/nCurvature) ;

        for (int i=0 ; i < aasamples ; i++)
        {
            double  x = (i * 4) / (double)aasamples,
                    y = i / (double)aasamples ;
            x = x - (int)x ;
            m_aapt[i].x = m_cos * x + m_sin * y ;
            m_aapt[i].y = m_cos * y - m_sin * x ;
        }
    }

	virtual Image process(Image imageIn)
	{
		  int r, g, b;
		  int width = imageIn.getWidth();
		  int height = imageIn.getHeight();
		  double hw = width / 2.0;
          double hh = imageIn.getHeight() / 2.0;
		  for(int x = 0 ; x < width ; x++){
			  for(int y = 0 ; y < height ; y++){
				    int i = x - hw;
					int j = y - hh;
					int b=0, g=0, r=0, a=0 ;
					for (int mm=0 ; mm < aasamples ; mm++)
					{
						double   u = i + m_aapt[mm].x ;
						double   v = j - m_aapt[mm].y ;

						double   s =  m_cos * u + m_sin * v ;
						double   t = -m_sin * u + m_cos * v ;

						s += m_curvature * tan(s * m_scale) ;
						t += m_curvature * tan(t * m_scale) ;
						u = m_cos * s - m_sin * t ;
						v = m_sin * s + m_cos * t ;
            
						int   xSample = (int)(hw + u) ;
						int ySample = (int)(hh + v) ;

						xSample = FClamp (xSample, 0, width -1) ;
						ySample = FClamp (ySample, 0, height-1) ;

						r += imageIn.getRComponent(xSample, ySample);
				        g += imageIn.getGComponent(xSample, ySample);
				        b += imageIn.getBComponent(xSample, ySample);
					}
				   imageIn.setPixelColor(x, y, SAFECOLOR(r/aasamples), SAFECOLOR(g/aasamples), SAFECOLOR(b/aasamples));
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