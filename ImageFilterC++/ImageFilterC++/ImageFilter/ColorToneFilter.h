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

#if !defined(ColorToneFilter_H)
#define ColorToneFilter_H

#include "IImageFilter.h"


namespace HaoRan_ImageFilter{

class ColorToneFilter : public IImageFilter{

private:
	double   _hue ;
    double   _saturation ;
    double   _lum_tab[256] ;

public:
	 /// @name RGB <--> HLS (Hue, Lightness, Saturation).
    //@{
    /**
        RGB --> HLS \n
        prgb - address of 24bpp or 32bpp pixel.
    */
    static void RGBtoHLS (int rgb, double& H, double& L, double& S)
    {
        Color color(rgb);
        int   n_cmax = max(color.R, max(color.G, color.B));
        int   n_cmin = min(color.R, min(color.G, color.B));

        L = (n_cmax + n_cmin) / 2.0 / 255.0 ;

        if (n_cmax == n_cmin)
        {
            S = H = 0.0 ;
            return ;
        }

        double   r = color.R / 255.0,
                 g = color.G / 255.0,
                 b = color.B / 255.0,
                 cmax = n_cmax / 255.0,
                 cmin = n_cmin / 255.0,
                 delta = cmax - cmin ;

        if (L < 0.5) 
            S = delta / (cmax + cmin) ;
        else
            S = delta / (2.0 - cmax - cmin) ;

        if (color.R == n_cmax)
            H = (g-b) / delta ;
        else if (color.G == n_cmax)
            H = 2.0 + (b-r) / delta ;
        else
            H = 4.0 + (r-g) / delta ;

        H /= 6.0 ;

        if (H < 0.0)
            H += 1.0 ;
    }

	static int DoubleRGB_to_RGB (double r, double g, double b)
    {
		return Color::rgb(SAFECOLOR(r*255), SAFECOLOR(g*255), SAFECOLOR(b*255)) ;
    }

	static double HLS_Value (double n1, double n2, double h)
    {
        if (h > 6.0)
            h -= 6.0 ;
        else if (h < 0.0)
            h += 6.0 ;

        if (h < 1.0)
            return n1 + (n2 - n1) * h ;
        else if (h < 3.0)
            return n2 ;
        else if (h < 4.0)
            return n1 + (n2 - n1) * (4.0 - h) ;
        return n1 ;
    }

    /// HLS --> RGB.
    static int HLStoRGB (double H, double L, double S)
    {
        if ((!(S > 0)) && (!(S < 0))) // == 0
            return DoubleRGB_to_RGB (L, L, L) ;

        double   m1, m2 ;
        if (L > 0.5)
            m2 = L + S - L*S ;
        else
            m2 = L * (1.0 + S) ;
        m1 = 2.0*L - m2 ;

        double   r = HLS_Value (m1, m2, H*6.0 + 2.0) ;
        double   g = HLS_Value (m1, m2, H*6.0) ;
        double   b = HLS_Value (m1, m2, H*6.0 - 2.0) ;
        return DoubleRGB_to_RGB (r,g,b) ;
    }

	
	 /**
        Calculate grayscale value of pixel \n
        prgb - address of 24bpp or 32bpp pixel.
    */
    static int GetGrayscale (int r, int g , int b)
    {
        return (int)((30*r + 59*g + 11*g) / 100) ;
    }

	ColorToneFilter(int tone, int saturation)
    {
        double   l ;
        RGBtoHLS (tone, _hue, l, _saturation) ;

        _saturation = _saturation * (saturation/255.0) * (saturation/255.0) ;
        _saturation = ((_saturation < 1) ? _saturation : 1) ;

        for (int i=0 ; i < 256 ; i++)
        {
            int   cr = Color::rgb(i,i,i) ;
            double    h, ll, s ;
            RGBtoHLS (cr, h, ll, s) ;

            ll = ll * (1 + (128-abs(saturation-128)) / 128.0 / 9.0) ;
            _lum_tab[i] = ((ll < 1) ? ll : 1) ;
        }
    };


	virtual Image process(Image imageIn)
	{
		  int r, g, b;
		  for(int x = 0 ; x < imageIn.getWidth() ; x++){
			  for(int y = 0 ; y < imageIn.getHeight() ; y++){
				   r = imageIn.getRComponent(x, y);
				   g = imageIn.getGComponent(x, y);
				   b = imageIn.getBComponent(x, y);

				   double  l = _lum_tab[GetGrayscale(r, g, b)] ;
				   int   cr =HLStoRGB (_hue, l, _saturation) ;
				   imageIn.setPixelColor(x, y, cr);
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