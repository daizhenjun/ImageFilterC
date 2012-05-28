/* 
 * HaoRan ImageFilter Classes v0.
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

#if !defined(TwistFilter_H)
#define TwistFilter_H

#include "BilinearDistort.h"


namespace HaoRan_ImageFilter{

class TwistFilter : public BilinearDistort{

private:
    double   m_twist ;
    double   m_size ;
    double   m_offset_x ;
    double   m_offset_y ;

public:
    /**
        Constructor \n
        param -45 <= nAmount <= 45 \n
        param 1 <= nSize <= 200 \n
        param -2 <= offset_x (offset_y) <= 2
    */
    TwistFilter (int nAmount, int nSize, double offset_x=0, double offset_y=0)
    {
        nAmount = -nAmount ;
        m_twist = nAmount * nAmount * ((nAmount > 0) ? 1 : -1) ;

        m_size = 1.0 / (FClamp(nSize, 1, 200) / 100.0) ;
        m_offset_x = FClamp(offset_x, -2.0, 2.0) ;
        m_offset_y = FClamp(offset_y, -2.0, 2.0) ;
    }
private:
    virtual void calc_undistorted_coord (int x, int y, double& un_x, double& un_y)
    {
        double   width = clone.getWidth() / 2.0 ;
        double   height = clone.getHeight() / 2.0 ;
        double   invmaxrad = 1.0 / (width < height ? width : height) ;
        width += m_offset_x * width ;
        height += m_offset_y * height ;

        double   u = x - width ;
        double   v = y - height ;
        double   r = sqrt(u*u + v*v) ;
        double   theta = atan2(v, u) ;

        double   t = 1 - ((r * m_size) * invmaxrad) ;
        t = (t < 0) ? 0 : (t * t * t) ;
        theta += (t * m_twist) / 100.0 ;

        un_x = FClamp (width + r * cos(theta), 0.0, clone.getWidth()-1.0) ;
        un_y = FClamp (height + r * sin(theta), 0.0, clone.getHeight()-1.0) ;
    }

};

}// namespace HaoRan
#endif