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

#if !defined(WaveFilter_H)
#define WaveFilter_H

#include "BilinearDistort.h"


namespace HaoRan_ImageFilter{

class WaveFilter : public BilinearDistort{

private:
	double m_phase ;
    double m_amplitude ;
    double m_wave_length ;

public:

	WaveFilter(int nWavelength, int nAmplitude, double fPhase=0)
    {
        m_phase = fPhase ;
        m_wave_length = 2 * ((nWavelength >= 1) ? nWavelength : 1) ;
        m_amplitude = ((nAmplitude >= 1) ? nAmplitude : 1) ;
    };

	virtual void calc_undistorted_coord (int x, int y, double& un_x, double& un_y)
    {
        double width = clone.getWidth();
        double height = clone.getHeight() ;
        double fScaleX = 1.0, fScaleY = 1.0 ;
        if (width < height)
            fScaleX = height / width ;
        else if (width > height)
            fScaleY = width / height ;

        // distances to center, scaled
        double   cen_x = width / 2.0,
                 cen_y = height / 2.0,
                 dx = (x - cen_x) * fScaleX,
                 dy = (y - cen_y) * fScaleY,
                 amnt = m_amplitude * sin (2 * LIB_PI * sqrt (dx*dx + dy*dy) / m_wave_length + m_phase) ;
        un_x = (amnt + dx) / fScaleX + cen_x ;
        un_y = (amnt + dy) / fScaleY + cen_y ;
        un_x = FClamp (un_x, 0.0, width-1.0) ;
        un_y = FClamp (un_y, 0.0, height-1.0) ;
    }
};

}// namespace HaoRan
#endif