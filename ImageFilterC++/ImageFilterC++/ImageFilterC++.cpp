// ImageFilterC++.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <ctime>

#include <vector>


#include <algorithm>
//#include "Image.h"
#include "ImageFilter\InvertFilter.h"
#include "ImageFilter\AutoLevelFilter.h"
#include "ImageFilter\RadialDistortionFilter.h"
#include "ImageFilter\BannerFilter.h"
#include "ImageFilter\BigBrotherFilter.h"
#include "ImageFilter\BlackWhiteFilter.h"
#include "ImageFilter\ColorQuantizeFilter.h"
#include "ImageFilter\ConvolutionFilter.h"
#include "ImageFilter\BrickFilter.h"
#include "ImageFilter\BlockPrintFilter.h"
#include "ImageFilter\EdgeFilter.h"
#include "ImageFilter\FeatherFilter.h"
#include "ImageFilter\GaussianBlurFilter.h"
#include "ImageFilter\GradientFilter.h"
#include "ImageFilter\HistogramEqualFilter.h"
#include "ImageFilter\LightFilter.h"
#include "ImageFilter\MistFilter.h"
#include "ImageFilter\MonitorFilter.h"
#include "ImageFilter\MosaicFilter.h"
#include "ImageFilter\NeonFilter.h"
#include "ImageFilter\NightVisionFilter.h"
#include "ImageFilter\NoiseFilter.h"
#include "ImageFilter\OilPaintFilter.h"
#include "ImageFilter\OldPhotoFilter.h"
#include "ImageFilter\PixelateFilter.h"
#include "ImageFilter\RainBowFilter.h"
#include "ImageFilter\RectMatrixFilter.h"
#include "ImageFilter\ReflectionFilter.h"
#include "ImageFilter\ReliefFilter.h"
#include "ImageFilter\SaturationModifyFilter.h"
#include "ImageFilter\SepiaFilter.h"
#include "ImageFilter\SmashColorFilter.h"
#include "ImageFilter\ThresholdFilter.h"
#include "ImageFilter\TintFilter.h"
#include "ImageFilter\VignetteFilter.h"
#include "ImageFilter\VintageFilter.h"
#include "ImageFilter\WaterWaveFilter.h"
#include "ImageFilter\XRadiationFilter.h"



using namespace std;
using namespace HaoRan_ImageFilter;

//打印时间
void printDateTime()
{
    time_t curtime = time(0); 
	tm tim =*localtime(&curtime); 
	std::cout<<tim.tm_year <<"-" << (tim.tm_mon + 1)<<"-"<<tim.tm_mday<<" "<<tim.tm_hour<<":"<<tim.tm_min<<":"<<tim.tm_sec<<std::endl; 
}


vector<IImageFilter*> LoadFilterVector(){
	vector<IImageFilter*> vectorFilter;
	//vectorFilter.push_back(new InvertFilter);
	//vectorFilter.push_back(new AutoLevelFilter(0.5));
	//vectorFilter.push_back(new RadialDistortionFilter());
	//vectorFilter.push_back(new BannerFilter(20, true));
	//vectorFilter.push_back(new BannerFilter(20, false));
	//vectorFilter.push_back(new BigBrotherFilter());
	//vectorFilter.push_back(new BlackWhiteFilter());
	//vectorFilter.push_back(new ColorQuantizeFilter());
	//vectorFilter.push_back(new ConvolutionFilter());
	//vectorFilter.push_back(new BrickFilter());
	//vectorFilter.push_back(new BlockPrintFilter());
	//vectorFilter.push_back(new EdgeFilter());
	//vectorFilter.push_back(new FeatherFilter());
	//vectorFilter.push_back(new GaussianBlurFilter());
	//vectorFilter.push_back(new GradientFilter());
	//vectorFilter.push_back(new GradientMapFilter());
	//vectorFilter.push_back(new HistogramEqualFilter());
	//vectorFilter.push_back(new LightFilter());
	//vectorFilter.push_back(new MistFilter());
	//vectorFilter.push_back(new MonitorFilter());
	//vectorFilter.push_back(new MosaicFilter());
	//vectorFilter.push_back(new NeonFilter());
	//vectorFilter.push_back(new NightVisionFilter());
	//vectorFilter.push_back(new NoiseFilter());
	//vectorFilter.push_back(new OilPaintFilter());
	//vectorFilter.push_back(new OldPhotoFilter());
	//vectorFilter.push_back(new PixelateFilter());  
	//vectorFilter.push_back(new RainBowFilter());  
	//vectorFilter.push_back(new RectMatrixFilter());
	//vectorFilter.push_back(new ReflectionFilter(false));
	//vectorFilter.push_back(new ReflectionFilter(true));
	//vectorFilter.push_back(new ReliefFilter());
	//vectorFilter.push_back(new SaturationModifyFilter());
	//vectorFilter.push_back(new SepiaFilter());
	//vectorFilter.push_back(new SmashColorFilter());
	//vectorFilter.push_back(new ThresholdFilter());
	//vectorFilter.push_back(new TintFilter());
	vectorFilter.push_back(new VignetteFilter());
	//vectorFilter.push_back(new VintageFilter());
	//vectorFilter.push_back(new WaterWaveFilter());
	//vectorFilter.push_back(new XRadiationFilter());
	
	return vectorFilter;
}

//加载各种滤镜
vector<IImageFilter*> vectorFilter = LoadFilterVector();

//加载图片
#ifdef WIN32	
Image LoadImage(string imagePath){
	CImage *cimage = new CImage;
	CString filePath((CString)imagePath.c_str());
	HRESULT hresult = cimage->Load(filePath);
	if(cimage->IsNull()){
	   cout<<"文件不存在或有异常";
	   return 0;
	}
	printDateTime();
	Image image(cimage);
	return image;
}
#else
Image LoadImage(NSString imagePath){
	UIImage *image = [UIImage imageNamed:@imagePath];
	CGImage image = image.CGImage;
	printDateTime();
	Image image(cimage);
	return image;
}
#endif

#ifdef WIN32
//保存图片
void SaveImage(Image image, string savePath)
{
	//输出处理后的图片	

	CString outfilePath((CString)savePath.c_str());
	HRESULT hresult = image.destImage->Save(outfilePath);
	if(FAILED(hresult)){
	   cout<<"文件保存失败";
	   return ;
	}
	image.image->Destroy();
	image.Destroy();
	printDateTime();
	string s = "";char* p = (char*)s.c_str();cin>>p;
}
#else
void SaveImage(Image image, NSString savePath) {
	NSString outfilePath = savePath.c_str();
	CGImageRef  destImage =  image.destImage;
	UIImage *finalImage = [UIImage imageWithCGImage:destImage];
	CGImageRelease(destImage);
	image.Destroy();
	printDateTime();
	string s = "";char* p = (char*)s.c_str();cin>>p;
}
#endif


int _tmain(int argc, _TCHAR* argv[])
{
	//加载图片
	Image image = LoadImage("d:\\4.jpg");
	//开始处理图片
	vector<IImageFilter*>::iterator it;
	for(it=vectorFilter.begin(); it!=vectorFilter.end(); it++){    
		image = (*it)->process(image);	
    }
	SaveImage(image, "d:\\15.jpg");
	return 0;
}

