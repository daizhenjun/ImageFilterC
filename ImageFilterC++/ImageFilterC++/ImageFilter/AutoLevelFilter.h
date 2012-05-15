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

#if !defined(AutoLevelFilter_H)
#define AutoLevelFilter_H

#include "IImageFilter.h"
#include "math.h"
#include <vector>

using namespace std;


namespace HaoRan_ImageFilter{

class AutoLevelFilter :  public IImageFilter{
private:
	vector<float> ComputeGamma(vector<int> lo, vector<int> md, vector<int> hi)
	{
	    vector<float> _array(3);
	    for (int i = 0; i < 3; i++){
	        if (lo[i] < md[i] && md[i] < hi[i]) {
	            double gamma = log(/*0.5, */(double) (((float) (md[i] - lo[i])) / ((float) (hi[i] - lo[i]))));
				_array[i] = (gamma > 10.0) ? ((float) 10.0) : ((gamma < 0.1) ? ((float) 0.1) : ((float) gamma));
	        }
	        else{
	            _array[i] = 1;
	        }
	    }
	    return _array;
	}

	vector<int> GetMeanColor(int h[3][256])
	{
	    vector<int> _array(3);
	    for (int i = 0; i < 3; i++) {
	        long sum1 = 0L;
	        long sum2 = 0L;
	        for (int j = 0; j < 256; j++){
	            sum1 += j * h[i][j];
	            sum2 += h[i][j];
	        }
	        _array[i] = (sum2 == 0L) ? 0 : (((float) sum1) / ((float) sum2));
	    }
		_array[0] = (((int) (_array[0] + 0.5f)) & 255);
		_array[1] = (((int) (_array[1] + 0.5f)) & 255);
		_array[2] = (((int) (_array[2] + 0.5f)) & 255);
	    return _array;
	}

	vector<int> GetPercentileColor(int h[3][256], float fraction)
	{
	    vector<int> _array(3);
	    for (int i = 0; i < 3; i++)
	    {
	        long sum1 = 0L;
	        long sum2 = 0L;
	        for (int j = 0; j < 256; j++) {
	            sum2 += h[i][j];
	        }
	        for (int k = 0; k < 256; k++) {
	            sum1 += h[i][k];
	            if (sum1 > (sum2 * fraction)) {
	                _array[i] = k;
	                break;
	            }
	        }
	    }
	    return _array;
	}
    
public:
	float Intensity;
	AutoLevelFilter(float intensity):Intensity(intensity){}

	virtual Image process(Image imageIn) {
		int h[3][256];
	    int _array[3];
	    int rgb[3] = { 255, 255, 255 };
	    int bb[256];
	    int gg[256];
	    int rr[256];
	    int intensity = (int)(Intensity * 255);
	    int intensity_invert = 255 - intensity;
	    for (int x = 0; x < imageIn.getWidth() - 1; x++){ 
			 for (int y = 0; y < imageIn.getHeight() - 1; y++)  {
	   			  h[0][imageIn.getRComponent(x, y)]++;
	  	          h[1][imageIn.getGComponent(x, y)]++;
	  	          h[2][imageIn.getBComponent(x, y)]++;
			 }
	    }
	    vector<int> percentileColor = GetPercentileColor(h, 0.005f);
	    vector<int> meanColor = GetMeanColor(h);
	    vector<int> hi = GetPercentileColor(h, 0.995f);
	    vector<float> gamma = ComputeGamma(percentileColor, meanColor, hi);
	    for (int i = 0; i < 3; i++){
	        for (int j = 0; j < 256; j++){
	            int arr[3];
	            for (int n = 0; n < 3; n++){
	                float percent = j - percentileColor[n];
	                if (percent < 0){
	                    arr[n] = _array[n];
	                }
	                else if ((percent + percentileColor[n]) >= hi[n]){
	                    arr[n] = rgb[n];
	                }
	                else {
	                    double adjust = _array[n] + ((rgb[n] - _array[n]) * pow((double) (percent / ((float) (hi[n] - percentileColor[n]))), (double) gamma[n]));
	                    arr[n] = (adjust > 255.0) ? ((int) 255.0) : ((adjust < 0.0) ? ((int) 0.0) : ((int) adjust));
	                }
	            }
	            rr[j] = arr[0];
	            gg[j] = arr[1];
	            bb[j] = arr[2];
	        }
	    }
	    Image clone = imageIn.clone();
	    int r,g,b;
	    for (int x = 0; x < imageIn.getWidth() - 1; x++){
  			 for (int y = 0; y < imageIn.getHeight() - 1; y++)  {  
  				r = imageIn.getRComponent(x, y);
  				g = imageIn.getGComponent(x, y);
  				b = imageIn.getBComponent(x, y);
		        r = (r * intensity_invert + rr[r] * intensity) >> 8;
		        g = (g * intensity_invert + gg[g] * intensity) >> 8;
		        b = (b * intensity_invert + bb[b] * intensity) >> 8;
		        imageIn.setPixelColor(x, y, r, g, b);
		 	 }
	    }
#ifndef WIN32 //only for apple ios
		imageIn.copyPixelsFromBuffer();
#endif
	    return imageIn;//做直方图模式增强
	}
};

}// namespace HaoRan

#endif