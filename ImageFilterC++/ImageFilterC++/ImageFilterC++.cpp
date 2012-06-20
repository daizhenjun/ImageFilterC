// ImageFilterC++.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <ctime>

#include <vector>


#include <algorithm>
//#include "Image.h"
//v0.1
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

//v0.2
#include "ImageFilter\LomoFilter.h"
#include "ImageFilter\PaintBorderFilter.h"
#include "ImageFilter\SceneFilter.h"
#include "ImageFilter\ComicFilter.h"
#include "ImageFilter\FilmFilter.h"
#include "ImageFilter\FocusFilter.h"
#include "ImageFilter\CleanGlassFilter.h"

//v3
#include "ImageFilter\ZoomBlurFilter.h"
#include "ImageFilter\ThreeDGridFilter.h"
#include "ImageFilter\ColorToneFilter.h"
#include "ImageFilter\SoftGlowFilter.h"
#include "ImageFilter\TileReflectionFilter.h"
#include "ImageFilter\BlindFilter.h"
#include "ImageFilter\RaiseFrameFilter.h"
#include "ImageFilter\ShiftFilter.h"
#include "ImageFilter\Distort\WaveFilter.h"
#include "ImageFilter\Distort\BulgeFilter.h"
#include "ImageFilter\Distort\TwistFilter.h"
#include "ImageFilter\Distort\RippleFilter.h"
#include "ImageFilter\IllusionFilter.h"
#include "ImageFilter\SupernovaFilter.h"
#include "ImageFilter\LensFlareFilter.h"
#include "ImageFilter\PosterizeFilter.h"
#include "ImageFilter\SharpFilter.h"
#include "ImageFilter\VideoFilter.h"
#include "ImageFilter\FillPatternFilter.h"
#include "ImageFilter\MirrorFilter.h"
#include "ImageFilter\YCBCrLinearFilter.h"
#include "ImageFilter\Textures\TexturerFilter.h"
#include "ImageFilter\Textures\CloudsTexture.h"
#include "ImageFilter\Textures\LabyrinthTexture.h"
#include "ImageFilter\Textures\MarbleTexture.h"
#include "ImageFilter\Textures\TextileTexture.h"
#include "ImageFilter\Textures\WoodTexture.h"
#include "ImageFilter\HslModifyFilter.h"


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
//v0.1
	//vectorFilter.push_back(new InvertFilter);
	//vectorFilter.push_back(new AutoLevelFilter(0.5));
	//vectorFilter.push_back(new RadialDistortionFilter());
	//vectorFilter.push_back(new BannerFilter(20, true));
	//vectorFilter.push_back(new BannerFilter(20, false));
	//vectorFilter.push_back(new BigBrotherFilter());
	//vectorFilter.push_back(new BlackWhiteFilter());
	//vectorFilter.push_back(new BrightContrastFilter());
	//vectorFilter.push_back(new ColorQuantizeFilter());
	//vectorFilter.push_back(new ConvolutionFilter());
	//vectorFilter.push_back(new BrickFilter());
	//vectorFilter.push_back(new BlockPrintFilter());
	//vectorFilter.push_back(new EdgeFilter());
	//vectorFilter.push_back(new FeatherFilter());
	//vectorFilter.push_back(new GaussianBlurFilter());//vectorFilter.push_back(new GradientFilter());vectorFilter.push_back(new GradientMapFilter());vectorFilter.push_back(new HistogramEqualFilter());
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
	//vectorFilter.push_back(new VignetteFilter());
	//vectorFilter.push_back(new VintageFilter());
	//vectorFilter.push_back(new WaterWaveFilter());
	//vectorFilter.push_back(new XRadiationFilter());

//v0.2
	//vectorFilter.push_back(new LomoFilter());
	//vectorFilter.push_back(new PaintBorderFilter(0x00FF00));//green
    //vectorFilter.push_back(new PaintBorderFilter(0x0000FF));//blue
	//vectorFilter.push_back(new PaintBorderFilter(0xFFFF00));//yellow
	//vectorFilter.push_back(new SceneFilter(5.0f, Gradient::Scene()));
	//vectorFilter.push_back(new SceneFilter(5.0f, Gradient::Scene1()));
	//vectorFilter.push_back(new SceneFilter(5.0f, Gradient::Scene2()));
	//vectorFilter.push_back(new SceneFilter(5.0f, Gradient::Scene3()));
    //vectorFilter.push_back(new ComicFilter());
	//vectorFilter.push_back(new FilmFilter(80.0f));
	//vectorFilter.push_back(new FocusFilter());
	//vectorFilter.push_back(new CleanGlassFilter());

//v0.3
	//vectorFilter.push_back(new ZoomBlurFilter(30));
	//vectorFilter.push_back(new ThreeDGridFilter(16, 100));
	//vectorFilter.push_back(new ColorToneFilter(Color::rgb(254,168,33), 192));	
	//vectorFilter.push_back(new ColorToneFilter(0x00FF00, 192));	//green
	//vectorFilter.push_back(new ColorToneFilter(0x0000FF, 192));	//blue
	//vectorFilter.push_back(new ColorToneFilter(0xFFFF00, 192));	//yellow
	//vectorFilter.push_back(new SoftGlowFilter(10, 0.1, 0.1));	
	//vectorFilter.push_back(new TileReflectionFilter(20, 8));	
	//vectorFilter.push_back(new BlindFilter(true, 50, 50, Color::rgb(255,255,255)));	
	//vectorFilter.push_back(new BlindFilter(false, 40, 80, Color::rgb(0,0,0)));	
	//vectorFilter.push_back(new RaiseFrameFilter(20));	
	//vectorFilter.push_back(new ShiftFilter(10));	
	//vectorFilter.push_back(new WaveFilter(25, 10));	
	//vectorFilter.push_back(new BulgeFilter(-97));	
	//vectorFilter.push_back(new TwistFilter(27, 106));
	//vectorFilter.push_back(new RippleFilter(38, 15, true));
	//vectorFilter.push_back(new IllusionFilter(3));
	//vectorFilter.push_back(new SupernovaFilter(0xFFFF00,20,100));
	//vectorFilter.push_back(new LensFlareFilter());
	//vectorFilter.push_back(new PosterizeFilter(2));
	//vectorFilter.push_back(new GammaFilter(50));
	//vectorFilter.push_back(new SharpFilter());
	//目前累计提供约73种效果

//v0.4
	/*vectorFilter.push_back(new VideoFilter(VideoFilter::VIDEO_STAGGERED));
	vectorFilter.push_back(new VideoFilter(VideoFilter::VIDEO_TRIPED));
	vectorFilter.push_back(new VideoFilter(VideoFilter::VIDEO_3X3));
	vectorFilter.push_back(new VideoFilter(VideoFilter::VIDEO_DOTS));
	vectorFilter.push_back(new TileReflectionFilter(20, 8, 45, 1));	
	vectorFilter.push_back(new TileReflectionFilter(20, 8, 45, 2));	
	vectorFilter.push_back(new FillPatternFilter("d:\\texture1.png"));
	vectorFilter.push_back(new FillPatternFilter("d:\\texture2.png"));
	vectorFilter.push_back(new MirrorFilter(true));
	vectorFilter.push_back(new MirrorFilter(false));
	vectorFilter.push_back(new YCBCrLinearFilter(new YCBCrLinearFilter::Range(-0.3f, 0.3f)));
	vectorFilter.push_back(new YCBCrLinearFilter(new YCBCrLinearFilter::Range(-0.276f, 0.163f), new YCBCrLinearFilter::Range(-0.202f, 0.5f)));
	vectorFilter.push_back(new TexturerFilter(new CloudsTexture(), 0.8, 0.8));
	vectorFilter.push_back(new TexturerFilter(new LabyrinthTexture(), 0.8, 0.8));
	vectorFilter.push_back(new TexturerFilter(new MarbleTexture(), 1.8, 0.8));
	vectorFilter.push_back(new TexturerFilter(new TextileTexture(), 0.8, 0.8));
	vectorFilter.push_back(new TexturerFilter(new WoodTexture(), 0.8, 0.8));*/
	vectorFilter.push_back(new HslModifyFilter(20));
	vectorFilter.push_back(new HslModifyFilter(60));
	vectorFilter.push_back(new HslModifyFilter(80));
	vectorFilter.push_back(new HslModifyFilter(100));
	vectorFilter.push_back(new HslModifyFilter(150));
	vectorFilter.push_back(new HslModifyFilter(200));
	vectorFilter.push_back(new HslModifyFilter(250));
	vectorFilter.push_back(new HslModifyFilter(300));
          
	return vectorFilter;
}

//加载各种滤镜
vector<IImageFilter*> vectorFilter = LoadFilterVector();



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
	//string s = "";char* p = (char*)s.c_str();cin>>p;
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
	//开始处理图片
	int i = 0;
	vector<IImageFilter*>::iterator it;
	char filePath[64];
	for(it=vectorFilter.begin(); it!=vectorFilter.end(); it++){    
		//加载图片
	    Image image = HaoRan_ImageFilter::Image::LoadImage("d:\\source.jpg");
		printDateTime();
		image = (*it)->process(image);	
		sprintf(filePath, "d:\\filter\\%d.jpg", i);  
		string filename(filePath);
#ifndef WIN32 //only for apple ios
		image.copyPixelsFromBuffer();
#endif
    	SaveImage(image, filename);
		i++;
    }

}

