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

#include <vector>
#include "../IImageFilter.h"
#include "ITextureGenerator.h"

#if !defined(TexturerFilterH)
#define TexturerFilterH

namespace HaoRan_ImageFilter{

/// <summary>
/// Texturer filter
/// </summary>
/// 
/// <remarks>Adjust pixel colors using factors from texture.</remarks>
/// 
class TexturerFilter : public IImageFilter
{
        
private:
	// texture generator
	ITextureGenerator *m_textureGenerator;
    // generated texture
	vector<vector<float>> m_texture;

    // filtering factor
	double m_filterLevel;// = 0.5;
    // preservation factor
    double m_preserveLevel;// = 0.5;

public:

    /// <summary>
    /// Initializes a new instance of the <see cref="Texturer"/> class
    /// </summary>
    /// 
    /// <param name="texture">Generated texture</param>
    /// 
	TexturerFilter(vector<vector<float>> texture )
	{
		m_texture = texture;
	};

    /// <summary>
    /// Initializes a new instance of the <see cref="Texturer"/> class
    /// </summary>
    /// 
    /// <param name="texture">Generated texture</param>
    /// <param name="filterLevel">Filter level value</param>
    /// <param name="preserveLevel">Preserve level value</param>
    /// 
	TexturerFilter(vector<vector<float>> texture , double filterLevel, double preserveLevel )
	{
		m_texture = texture;
		m_filterLevel    = filterLevel;
        m_preserveLevel  = preserveLevel;
	};

    /// <summary>
    /// Initializes a new instance of the <see cref="Texturer"/> class
    /// </summary>
    /// 
    /// <param name="generator">Texture generator</param>
    /// 
	TexturerFilter( ITextureGenerator *generator )
	{
		m_textureGenerator = generator;
	};

    /// <summary>
    /// Initializes a new instance of the <see cref="Texturer"/> class
    /// </summary>
    /// 
    /// <param name="generator">Texture generator</param>
    /// <param name="filterLevel">Filter level value</param>
    /// <param name="preserveLevel">Preserve level value</param>
    /// 
    TexturerFilter(ITextureGenerator *generator, double filterLevel, double preserveLevel)
	{
		m_textureGenerator   = generator;
		m_filterLevel        = filterLevel;
        m_preserveLevel      = preserveLevel;
	}

		
    virtual Image process(Image imageIn) 
    {
        // get source image size
        int width = imageIn.getWidth();
        int height = imageIn.getHeight();

        // processing region's dimension
        int widthToProcess = width;
        int heightToProcess = height;

        // if generator was specified, then generate a texture
        // otherwise use provided texture
        if ( m_textureGenerator != NULL )
        {
            m_texture = m_textureGenerator->Generate( width, height );
        }
        else
        {
            widthToProcess = width;//min( width, m_texture.l.GetLength( 1 ) );
            heightToProcess = height;//min( height, m_texture.GetLength( 0 ) );
        }

        int r, g, b;
         
        // texture
        for ( int y = 0; y < heightToProcess; y++ )
        {
            for ( int x = 0; x < widthToProcess; x++ )
            {
                double t = m_texture[y][x];
                r = imageIn.getRComponent(x, y);
                g = imageIn.getGComponent(x, y);
                b = imageIn.getBComponent(x, y);
                // process each pixel
                   
                r = (byte) min( 255.0f, ( m_preserveLevel * r) + ( m_filterLevel * r) * t );
                g = (byte) min( 255.0f, ( m_preserveLevel * g) + ( m_filterLevel * g) * t );
                b = (byte) min( 255.0f, ( m_preserveLevel * b) + ( m_filterLevel * b) * t );
                imageIn.setPixelColor(x, y, r, g, b);                
            }
        }
        return imageIn;
    }
	
};
}// namespace HaoRan
#endif