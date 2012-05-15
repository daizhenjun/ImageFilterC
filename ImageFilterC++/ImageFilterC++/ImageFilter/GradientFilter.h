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

#if !defined(GradientFilter_H)
#define GradientFilter_H


#include "IImageFilter.h"
#include "math.h"
#include <vector>


enum Colors
{
	Black = 0xff000000,
	White = 0xffffffff,
	Red = 0xffff0000,
	Magenta = 0xffff00ff,
	Blue = 0xff0000ff,
    Cyan = 0xff00ffff,
	Green = 0xff00ff00,
	Yellow = 0xffffff00,
	Ltgray = 0xffcccccc
};



enum TintColors
{
	LightCyan = 0xffebf5e1,
	Sepia = (255 << 24) | (230 << 16) | (179 << 8) | 179
};

namespace HaoRan_ImageFilter{

class Palette
{
public:
    vector<int> Blue;
    vector<int> Green;
    int Length;
    vector<int> Red;
	Palette(){};

    Palette(int length)
    {
        Length = length;
        Red.resize(length);
        Green.resize(length);
        Blue.resize(length);
    }
};

class Color{
public:
	int R;
	int G;
	int B;

	Color(int r, int g, int b) : R(r), G(g), B(b){}

	Color(int rgb){
		R = ((rgb& 0x00FF0000) >> 16);
	    G = ((rgb& 0x0000FF00) >> 8);
		B = ( rgb& 0x000000FF);
	}

	static int rgb(int r, int g, int b){
		return (255 << 24) + (r << 16) + (g << 8) + b;
	}
};


class Gradient
{
private:
    Palette CreateGradient(vector<int> colors, int length)
    {
        /*if (colors.Count < 2)
        {
            return null;
        }*/

        Palette palette(length);
       /* vector<int> red = palette.Red;
        vector<int> green = palette.Green;
        vector<int> blue = palette.Blue;*/
		int num = length / (colors.size() - 1);
        float num1 = 1 / ((float)num);
        int index = 0;
        Color rgb(colors[0]);
        int colorR = rgb.R;
        int colorG = rgb.G;
        int colorB = rgb.B;
        for (int i = 1; i < colors.size(); i++)
        {
			Color rgbs(colors[i]);
            int r = rgbs.R;
            int g = rgbs.G;
            int b = rgbs.B;
	        for (int j = 0; j < num; j++)
            {
                float num2 = j * num1;
                int rr = colorR + ((int)((r - colorR) * num2));
                int gg = colorG + ((int)((g - colorG) * num2));
                int bb = colorB + ((int)((b - colorB) * num2));
                palette.Red[index] = SAFECOLOR(rr);
                palette.Green[index] = SAFECOLOR(gg);
                palette.Blue[index] = SAFECOLOR(bb);
                index++;
            }
            colorR = r;
            colorG = g;
            colorB = b;
        }
        if (index < length)
        {
            palette.Red[index] = palette.Red[index - 1];
            palette.Green[index] = palette.Green[index - 1];
            palette.Blue[index] = palette.Blue[index - 1];
        }
        return palette;
    }

public:
	vector<int> MapColors;

    Gradient()
    {
        vector<int> list(2);
		list[0] = ::Black;
        list[1] = ::White;
        MapColors = list;
    }

    Gradient(vector<int> colors)
    {
        MapColors = colors;
    }


      
    Palette CreatePalette(int length)
    {
        return CreateGradient(MapColors, length);
    }

      

    static Gradient BlackSepia()
    {
        vector<int> colors(2);
        colors[0] = ::Black;
        colors[1] = ::Sepia;
        Gradient gradient(colors);
        return gradient;
    }

    static Gradient WhiteSepia()
    {
        vector<int> colors(2);
        colors[0] = ::White;
        colors[1] = ::Sepia;
		Gradient gradient(colors);
        return gradient;
    }

    static Gradient RainBow()
    {
        vector<int> colors(7);
        colors[0] = ::Red;
        colors[1] = ::Magenta;
        colors[2] = ::Blue;
        colors[3] = ::Cyan;
        colors[4] = ::Green;
        colors[5] = ::Yellow;
        colors[6] = ::Red;
		Gradient gradient(colors);
        return gradient;
    }

    static Gradient Inverse()
    {
        vector<int> colors(2);
        colors[1] = ::White;
        colors[2] = ::Black;
        Gradient gradient(colors);
        return gradient;
    }
};

class GradientFilter : public IImageFilter{
private:
	Palette palette;
       
public:
	Gradient gradient;
    float OriginAngleDegree;
	
	GradientFilter():OriginAngleDegree(0){
	};
	
	void ClearCache()
    {
        //delete palette;
    }

	virtual Image process(Image imageIn)
	{
		int width = imageIn.getWidth();
        int height = imageIn.getHeight();
        double d = OriginAngleDegree * 0.0174532925;
        float cos_value = cos(d);
        float sin_value = sin(d);
        float radio = ((cos_value * width) + (sin_value * height));
        float dcos = cos_value * radio;
        float dsin = sin_value * radio;
        int dist = (int)sqrt((double)((dcos * dcos) + (dsin * dsin)));
        dist = max(max(dist, width), height);

        if (/*(palette == NULL) ||*/ (dist != palette.Length))
        {
            palette = gradient.CreatePalette(dist);
        } 
        for (int i = 0; i < height; i++)
        {
           for (int j = 0; j < width; j++)
            {
                radio =(float)((cos_value * j) + (sin_value * i));
                dcos = cos_value * radio;
                dsin = sin_value * radio;
                dist = (int)sqrt((double)((dcos * dcos) + (dsin * dsin)));
                imageIn.setPixelColor(j, i, palette.Red[dist], palette.Green[dist], palette.Blue[dist]);
            }
        }
#ifndef WIN32 //only for apple ios
		clone.copyPixelsFromBuffer();
#endif
        return imageIn;
	}
};

}// namespace HaoRan
#endif
