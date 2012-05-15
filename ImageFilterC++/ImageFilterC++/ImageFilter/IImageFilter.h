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

#if !defined(IImageFilter_H)
#define IImageFilter_H

//typedef BYTE UInt8; //BYTE此变量在IOS系统中会变成UInt8;
//typedef CImage UIImage;//CImage此变量在IOS系统中会变成UIImage;
#include "Image.h"
#include "math.h"
#include <vector>


namespace HaoRan_ImageFilter{

class Point
{
public:
	   float X;
	   float Y;
	   Point(){
		   X = 0;
		   Y = 0;
	   }

	   Point(float x, float y){
		   X = x;
		   Y = y;
	   }
};


class IImageFilter{
public:
    virtual Image process(Image image){
		return image;
	}
};

}// namespace HaoRan
#endif
