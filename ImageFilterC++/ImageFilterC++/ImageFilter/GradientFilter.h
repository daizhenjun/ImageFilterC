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
	Black = 0x000000,
	White = 0xffffff,
	Red = 0xff0000,
	Magenta = 0xff00ff,
	Blue = 0x0000ff,
    Cyan = 0x00ffff,
	Green = 0x00ff00,
	Yellow = 0xffff00,
	Ltgray = 0xcccccc
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
        colors[0] = ::White;
        colors[1] = ::Black;
        Gradient gradient(colors);
        return gradient;
    }

	static Gradient Fade()
    {
        vector<int> colors(3);
        colors[0] = ::Black;
        colors[1] = 0xFFEEE8CD;//Cornsilk2  , reference http://www.wescn.com/tool/color_3.html
        colors[2] = ::Black;
		Gradient gradient(colors);
        return gradient;
    }

    static Gradient Scene()
    {
		vector<int> colors(3);
        colors[0] = 0xFFFFD700;//Gold  , reference http://www.wescn.com/tool/color_3.html
        colors[1] = ::White;
		colors[2] = 0xFFFFD700;//Gold  , reference http://www.wescn.com/tool/color_3.html
		Gradient gradient(colors);
        return gradient;
	}

    static Gradient Scene1()
    {
		vector<int> colors(3);
        colors[0] = 0xFF6495ED;//CornflowerBlue  , reference http://www.wescn.com/tool/color_3.html
        colors[1] = ::White;
		colors[2] = 0xFF6495ED;//CornflowerBlue  , reference http://www.wescn.com/tool/color_3.html
		Gradient gradient(colors);
        return gradient;
	}
       
    static Gradient Scene2()
    {
		vector<int> colors(3);
        colors[0] = 0xFF00BFFF;//DeepSkyBlue  , reference http://www.wescn.com/tool/color_3.html
        colors[1] = 0xFFDCDCDC;//Gainsboro
		colors[2] = 0xFF00BFFF;//DeepSkyBlue  , reference http://www.wescn.com/tool/color_3.html
		Gradient gradient(colors);
        return gradient;
	}

    static Gradient Scene3()
    {
		vector<int> colors(3);
        colors[0] = 0xFFFFA500;//Orange  , reference http://www.wescn.com/tool/color_3.html
		colors[1] = ::White;//
		colors[2] = 0xFFFFA500;//Orange  , reference http://www.wescn.com/tool/color_3.html
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
		imageIn.copyPixelsFromBuffer();
#endif
        return imageIn;
	}
};

}// namespace HaoRan
#endif
