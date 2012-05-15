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

#if !defined(WaterWaveFilter_H)
#define WaterWaveFilter_H

#include "IImageFilter.h"


namespace HaoRan_ImageFilter{

class WaterWaveFilter : public IImageFilter{
private:
	int width;
	int height;
	vector<short> buf2;
	vector<short> buf1;
	int *temp;
	int *source;

public:

	WaterWaveFilter(){};

	void DropStone(int x /*x坐标*/, int y /*y坐标*/, int stonesize /*波源半径*/, int stoneweight /*波源能量*/)
    {
    	if ((x + stonesize) > width || (y + stonesize) > height || (x - stonesize) < 0 || (y - stonesize) < 0){
           return;
    	}
        for (int posx = x - stonesize; posx < x + stonesize; posx++){
            for (int posy = y - stonesize; posy < y + stonesize; posy++){
                if ((posx - x) * (posx - x) + (posy - y) * (posy - y) <= stonesize * stonesize){
                    buf1[width * posy + posx] = (short)-stoneweight;
                }
            }
        }
    }


    void RippleSpread() {
    	 for (int i=width; i<width*height-width; i++){
		      //波能扩散
		      buf2[i] =(short)(((buf1[i-1]+buf1[i+1]+buf1[i-width]+buf1[i+width])>>1)- buf2[i]);
		      //波能衰减
		      buf2[i] -= buf2[i]>>5;
	     }
	     //交换波能数据缓冲区
	     vector<short> tmp =buf1;
	     buf1 = buf2;
	     buf2 = tmp;
    }
   
   
    /* 渲染你水纹效果 */
    void render() {
    	 int xoff, yoff;
	     int k = width;
	     for (int i=1; i<height-1; i++) {
		      for (int j=0; j<width; j++) {
			       //计算偏移量
			       xoff = buf1[k-1]-buf1[k+1];
			       yoff = buf1[k-width]-buf1[k+width];
			       //判断坐标是否在窗口范围内
			       if ((i+yoff )< 0 || (i+yoff )>= height || (j+xoff )< 0 || (j+xoff )>= width) {
			    	   k++; 
			    	   continue;
			       }
			       //计算出偏移象素和原始象素的内存地址偏移量		       
			       // image.setPixelColour(j, i, clone.getPixelColour(j+xoff, i+yoff));	
			       int pos1, pos2;
	    		   pos1=width*(i+yoff)+ (j+xoff);
	    		   pos2=width*i+ j;    			
	    		   temp[pos2++]=source[pos1++];
			       k++;
		      }
	     }
     }

	virtual Image process(Image imageIn)
	{
		width = imageIn.getWidth();
    	height = imageIn.getHeight();
    	buf2.resize(width*height);
		buf1.resize(width*height);
	    source = imageIn.colorArray;
	    temp = new int[width*height];
	    DropStone(width/2, height/2, max(width, height)/4, max(width, height));
		for(int i = 0 ; i < 170; i++){
			RippleSpread();
			render();
		}	
		imageIn.colorArray = temp;
		imageIn.copyPixelsFromBuffer();
		return imageIn;
	}
};

}// namespace HaoRan
#endif