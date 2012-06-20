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

#if !defined(PerlinNoiseH)
#define PerlinNoiseH

#include "../IImageFilter.h"

namespace HaoRan_ImageFilter
{
	// http://www.student.kuleuven.ac.be/~m0216922/CG/perlinnoise.html
	/// <summary>
	/// Perlin Noise function
	/// </summary>
	/// 
	/// <remarks>The class represents Gaussian function.</remarks>
	/// 
class PerlinNoise
{

private:
	double	m_initFrequency;// = 1.0 / 16;
	double	m_initAmplitude;// = 1.0f;
	double	m_persistance;// = 0.65;
	int	m_octaves;// = 4;

public:

	/// <summary>
	/// Initial frequency
	/// </summary>
	double InitFrequency;

	/// <summary>
	/// Initial aplitude
	/// </summary>
	double InitAplitude;

	/// <summary>
	/// Persistance
	/// </summary>
    double Persistance;
	
	/// <summary>
	/// Octaves
	/// </summary>
    int Octaves;
		

	/// <summary>
	/// Initializes a new instance of the <see cref="PerlinNoise"/> class
	/// </summary>
	/// 
	PerlinNoise( ) { }

	/// <summary>
	/// Initializes a new instance of the <see cref="PerlinNoise"/> class
	/// </summary>
	/// 
	/// <param name="initFrequency">Initial frequency</param>
	/// <param name="initAmplitude">Initial amplitude</param>
	/// <param name="persistance">Persistance</param>
	/// <param name="octaves">Octaves</param>
	/// 
	PerlinNoise( double initFrequency, double initAmplitude, double persistance, int octaves )
	{
		m_initFrequency	= initFrequency;
		m_initAmplitude	= initAmplitude;
		m_persistance	= persistance;
		m_octaves		= octaves;
	}

	/// <summary>
	/// 1-D Perlin noise function
	/// </summary>
	/// 
	/// <param name="x">x value</param>
	/// 
	/// <returns>Returns function's value at point <b>x</b>.</returns>
	/// 
	double Function( double x )
	{
		double	frequency = m_initFrequency;
		double	amplitude = m_initAmplitude;
		double	sum = 0;
			
		// octaves
		for ( int i = 0; i < m_octaves; i++ )
		{
			sum += SmoothedNoise( x * frequency ) * amplitude;

			frequency *= 2;
			amplitude *= m_persistance;
		}
		return sum;
	}

	/// <summary>
	/// 2-D Perlin noise function
	/// </summary>
	/// 
	/// <param name="x">x value</param>
	/// <param name="y">y value</param>
	/// 
	/// <returns>Returns function's value at point <b>(x, y)</b>.</returns>
	/// 
	double Function2D( double x, double y )
	{
		double	frequency = m_initFrequency;
		double	amplitude = m_initAmplitude;
		double	sum = 0;
			
		// octaves
		for ( int i = 0; i < m_octaves; i++ )
		{
			sum += SmoothedNoise( x * frequency, y * frequency ) * amplitude;

			frequency *= 2;
			amplitude *= m_persistance;
		}
		return sum;
	}


	/// <summary>
	/// Ordinary noise function
	/// </summary>
	double Noise( int x )
	{
		int n = ( x << 13 ) ^ x;

		return ( 1.0 - ( ( n * ( n * n * 15731 + 789221 ) + 1376312589 ) & 0x7fffffff ) / 1073741824.0 );
	}
		
	double Noise( int x, int y )
	{
		int n = x + y * 57;
		n = ( n << 13 ) ^ n ;

		return ( 1.0 - ( ( n * ( n * n * 15731 + 789221 ) + 1376312589 ) & 0x7fffffff ) / 1073741824.0 );
	}

private:		
	/// <summary>
	/// Smoothed noise
	/// </summary>
	double SmoothedNoise( double x )
	{
		int		xInt = (int) x;
		double	xFrac = x - xInt;

		return CosineInterpolate( Noise( xInt ) , Noise( xInt + 1 ), xFrac );
	}

	double SmoothedNoise( double x, double y )
	{
		int		xInt = (int) x;
		int		yInt = (int) y;
		double	xFrac = x - xInt;
		double	yFrac = y - yInt;

		// get four noise values
		double	x0y0 = Noise( xInt    , yInt );
		double	x1y0 = Noise( xInt + 1, yInt );
		double	x0y1 = Noise( xInt    , yInt + 1 );
		double	x1y1 = Noise( xInt + 1, yInt + 1) ;

		// x interpolation
		double	v1 = CosineInterpolate( x0y0, x1y0, xFrac );
		double	v2 = CosineInterpolate( x0y1, x1y1, xFrac );
		// y interpolation
		return CosineInterpolate( v1, v2, yFrac );
	}


	/// <summary>
	/// Cosine interpolation
	/// </summary>
	double CosineInterpolate( double x1, double x2, double a )
	{
		double f = ( 1 - cos( a * LIB_PI ) ) * 0.5;

		return x1 * ( 1 - f ) + x2 * f;
	}
	
};

}// namespace HaoRan
#endif
