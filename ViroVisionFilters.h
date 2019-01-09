/////////////////////////////////////////////////////////////////////////////
// ViroVisionFilters.h
//
// Copyright (C) 2012 Veria Kalantary
// veria.kalantary@gmail.com
// https://github.com/veriak
//

#ifndef VIROVISION_FILTERS_INCLUDED
#define VIROVISION_FILTERS_INCLUDED
#pragma once

#include <windows.h>

namespace ViroVisionFilters
{

class CViroVisionFilters
{
protected:	
	LPVOID m_pPreviousSample;

public:
	CViroVisionFilters(void);
	~CViroVisionFilters(void);

	void CViroVisionFilters::Clear(void);

	static LRESULT CALLBACK RedColorFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK GreenColorFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK BlueColorFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK GrayColorFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);

	static LRESULT CALLBACK RedColorFilter2(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lLeft, long lTop, long lRight, long lBottom);
	static LRESULT CALLBACK GreenColorFilter2(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lLeft, long lTop, long lRight, long lBottom);
	static LRESULT CALLBACK BlueColorFilter2(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lLeft, long lTop, long lRight, long lBottom);
	static LRESULT CALLBACK GrayColorFilter2(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lLeft, long lTop, long lRight, long lBottom);

	static LRESULT CALLBACK RedBoxFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lLeft, long lTop, long lRight, long lBottom);
	static LRESULT CALLBACK GreenBoxFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lLeft, long lTop, long lRight, long lBottom);
	static LRESULT CALLBACK BlueBoxFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lLeft, long lTop, long lRight, long lBottom);
	static LRESULT CALLBACK GrayBoxFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lLeft, long lTop, long lRight, long lBottom);
	static LRESULT CALLBACK WhiteBoxFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lLeft, long lTop, long lRight, long lBottom);
	static LRESULT CALLBACK YellowBoxFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lLeft, long lTop, long lRight, long lBottom);

	static LRESULT CALLBACK LaplacianEdgeDetectionFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK LaplacianEdgeDetectionFilter3_3(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK SobelEdgeDetectionFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);

	static LRESULT CALLBACK PrewittEdgeDetectionFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK PrewittNorthFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK PrewittWestFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK PrewittEastFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK PrewittSouthFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK PrewittNortheastFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK PrewittSoutheastFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK PrewittSouthwestFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK PrewittNorthwestFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);

	static LRESULT CALLBACK SharpenHighPassFilter5_5(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK SharpenHighPassFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK SmoothLowPassFilter5_5(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK SmoothLowPassFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);

	static LRESULT CALLBACK GaussianFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);

	static LRESULT CALLBACK LineDetectionHorizontalFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK LineDetectionVerticalFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK LineDetectionLeftDiagonalFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK LineDetectionRightDiagonalFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);

	static LRESULT CALLBACK PointDetectionFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);

	static LRESULT CALLBACK WeightedMeanFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);

	static LRESULT CALLBACK MedianFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK MeanFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK MinimumFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK MaximumFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);
	static LRESULT CALLBACK RangeFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight);

	static long CalculateMean(RGBTRIPLE *pRGBBuffer, long lWidth, long lHeight);
	static long CalculateVariance(RGBTRIPLE *pRGBBuffer, long lWidth, long lHeight);
	static LRESULT CALLBACK DWMTM_AdaptiveFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight,
		LPVOID lpFilterParam);
	static LRESULT CALLBACK MMSE_AdaptiveFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight,
		LPVOID lpFilterParam);

	static LRESULT CALLBACK LowPassFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight,
		LPVOID lpFilterParam, CViroVisionFilters *_this);
	static LRESULT CALLBACK MotionDetectionFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight,
		LPVOID lpFilterParam, CViroVisionFilters *_this);
	static LRESULT CALLBACK MotionDetectionSolidRectFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight,
		LPVOID lpFilterParam, CViroVisionFilters *_this);
	static LRESULT CALLBACK MotionDetectionBoxRectFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight,
		LPVOID lpFilterParam, CViroVisionFilters *_this);
	static LRESULT CALLBACK MotionDetectionBoxSurroundedFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight,
		LPVOID lpFilterParam, CViroVisionFilters *_this);
};

}

#endif