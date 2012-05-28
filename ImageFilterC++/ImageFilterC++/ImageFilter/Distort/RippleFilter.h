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

#if !defined(RippleFilter_H)
#define RippleFilter_H

#include "BilinearDistort.h"


namespace HaoRan_ImageFilter{

class RippleFilter : public BilinearDistort{

private:
    int   m_wave_length ;
    int   m_amplitude ;
    int   m_sin_type ;

public:
    /**
        Constructor \n
        nWavelength >= 1 \n
        nAmplitude >= 1
    */
    RippleFilter (int nWavelength, int nAmplitude, bool bSinType=true)
    {
        m_wave_length = ((nWavelength >= 1) ? nWavelength : 1) ;
        m_amplitude = ((nAmplitude >= 1) ? nAmplitude : 1) ;
        m_sin_type = (bSinType ? 1 : 0) ;
    }

    virtual void calc_undistorted_coord (int x, int y, double& un_x, double& un_y)
    {
        double   w = clone.getWidth() ;
        un_x = fmod (x + w + shift_amount(y), w) ;
        un_x = FClamp (un_x, 0.0, w-1) ;
        un_y = y ;
    }
    double shift_amount (int nPos) const
    {
        if (m_sin_type)
            return m_amplitude * sin(nPos*2*LIB_PI/m_wave_length) ;
        else
            return floor (m_amplitude * (fabs ((((nPos % m_wave_length) / (double)m_wave_length) * 4) - 2) - 1)) ;
    }
};

}// namespace HaoRan
#endif