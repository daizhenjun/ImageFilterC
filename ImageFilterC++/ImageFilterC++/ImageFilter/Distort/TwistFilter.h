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

#if !defined(TwistFilter_H)
#define TwistFilter_H

#include "BilinearDistort.h"


namespace HaoRan_ImageFilter{

class TwistFilter : public BilinearDistort{

private:
    double   _twist ;
    double   _size ;
    double   _offsetX ;
    double   _offsetY ;

public:
    /**
        param -45 <= _amount <= 45 \n
        param 1 <= _size <= 200 \n
        param -2 <= _offsetX (_offsetY) <= 2
    */
    TwistFilter (int amount, int size, double offsetX=0, double offsetY=0)
    {
        amount = -amount ;
        _twist = amount * amount * ((amount > 0) ? 1 : -1) ;

        _size = 1.0 / (FClamp(size, 1, 200) / 100.0) ;
        _offsetX = FClamp(offsetX, -2.0, 2.0) ;
        _offsetY = FClamp(offsetY, -2.0, 2.0) ;
    }
private:
    virtual void calc_undistorted_coord (int x, int y, double& un_x, double& un_y)
    {
        double	width = clone.getWidth() / 2.0 ;
        double	height = clone.getHeight() / 2.0 ;
        double	invmaxrad = 1.0 / (width < height ? width : height) ;
        width += _offsetX * width ;
        height += _offsetY * height ;

        double   u = x - width ;
        double   v = y - height ;
        double   r = sqrt(u*u + v*v) ;
        double   theta = atan2(v, u) ;

        double   t = 1 - ((r * _size) * invmaxrad) ;
        t = (t < 0) ? 0 : (t * t * t) ;
        theta += (t * _twist) / 100.0 ;

        un_x = FClamp (width + r * cos(theta), 0.0, clone.getWidth()-1.0) ;
        un_y = FClamp (height + r * sin(theta), 0.0, clone.getHeight()-1.0) ;
    }

};

}// namespace HaoRan
#endif