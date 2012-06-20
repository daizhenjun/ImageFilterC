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
#if !defined(WoodTextureH)
#define WoodTextureH

#include <vector>
#include "PerlinNoise.h"
#include "../NoiseFilter.h"
#include "ITextureGenerator.h"

namespace HaoRan_ImageFilter{

class WoodTexture : public ITextureGenerator{
private:
	int	r;
	double	m_rings;
public:
	 
	WoodTexture()
	{
		WoodTexture(12);
	}

	WoodTexture(double rings)
	{
		m_rings = max( 3, rings );
		Reset();
	};

    /// <summary>
    /// Generate texture
    /// </summary>
    /// 
    /// <param name="width">Texture's width</param>
    /// <param name="height">Texture's height</param>
    /// 
    /// <returns>Two dimensional array of intensities</returns>
    /// 
    /// <remarks>Generates new texture with specified dimension.</remarks>
    /// 
    virtual vector<vector<float>> Generate( int width, int height )
	{
		// Perlin noise function used for texture generation
		PerlinNoise noise( 1.0 / 32, 0.05, 0.5, 8 );
		// randmom number generator
			
		//使用vector模拟二维动态数组
		vector<vector<float>> texture(height);
		for(int x = 0; x < height ; x++) {
			texture[x].resize(width);
		}

		int	w2 = width / 2;
		int	h2 = height / 2;

		for ( int y = 0; y < height; y++ )
		{
			for ( int x = 0; x < width; x++ )
			{
				double xv = (double) ( x - w2 ) / width;
				double yv = (double) ( y - h2 ) / height;

				texture[y][x] = 
					min( 1.0f, (float)
					abs( sin( 
						( sqrt( xv * xv + yv * yv ) + noise.Function2D( x + r, y + r ) )
							* LIB_PI * 2 * m_rings
					) )
					);
			}
		}
		return texture;
	};

    /// <summary>
    /// Reset generator
    /// </summary>
    /// 
    /// <remarks>Regenerates internal random numbers.</remarks>
    /// 
    virtual void Reset( )
	{
		r = NoiseFilter::getRandomInt(1, 5000);
	}

};

}// namespace HaoRan
#endif
