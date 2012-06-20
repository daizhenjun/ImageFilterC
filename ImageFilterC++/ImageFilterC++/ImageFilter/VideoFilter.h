/* 
 * HaoRan ImageFilter Classes v0.4
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

#if !defined(VideoFilter_H)
#define VideoFilter_H

#include "IImageFilter.h"


namespace HaoRan_ImageFilter{

class VideoFilter : public IImageFilter{

public:
	enum VIDEO_TYPE { VIDEO_STAGGERED = 0, VIDEO_TRIPED = 1, VIDEO_3X3 = 2, VIDEO_DOTS = 3 } ;

private:
	VIDEO_TYPE m_VideoType;

public:

	VideoFilter(VIDEO_TYPE nVideoType)
    {
        m_VideoType = nVideoType;

    };

	virtual Image process(Image imageIn)
	{
		static const int   pattern_width[] = {2, 1, 3, 5} ;
        static const int   pattern_height[] = {6, 3, 3, 15} ;
        static const int   video_pattern[4][15 * 5/* max pattern size */] =
        {
            {
                0, 1,
                0, 2,
                1, 2,
                1, 0,
                2, 0,
                2, 1,
            },
            {
                0,
                1,
                2,
            },
            {
                0, 1, 2,
                2, 0, 1,
                1, 2, 0,
            },
            {
                0, 1, 2, 0, 0,
                1, 1, 1, 2, 0,
                0, 1, 2, 2, 2,
                0, 0, 1, 2, 0,
                0, 1, 1, 1, 2,
                2, 0, 1, 2, 2,
                0, 0, 0, 1, 2,
                2, 0, 1, 1, 1,
                2, 2, 0, 1, 2,
                2, 0, 0, 0, 1,
                1, 2, 0, 1, 1,
                2, 2, 2, 0, 1,
                1, 2, 0, 0, 0,
                1, 1, 2, 0, 1,
                1, 2, 2, 2, 0,
            }
        };

		int r, g, b;
        for (int x = 0; x < imageIn.getWidth(); x++)
        {
            for (int y = 0; y < imageIn.getHeight(); y++)
            {
                r = imageIn.getRComponent(x, y);
                g = imageIn.getGComponent(x, y);
                b = imageIn.getBComponent(x, y);

                int nWidth = pattern_width[(int)m_VideoType];
                int nHeight = pattern_height[(int)m_VideoType];
                int index = nWidth * (y % nHeight) + (x % nWidth);

                if (video_pattern[m_VideoType][index] == 0)
                    r = FClamp0255(2 * r);
                if (video_pattern[m_VideoType][index] == 1)
                    g = FClamp0255(2 * g);
                if (video_pattern[m_VideoType][index] == 2)
                    b = FClamp0255(2 * b);

                imageIn.setPixelColor(x, y, r, g, b);
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