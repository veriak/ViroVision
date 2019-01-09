/////////////////////////////////////////////////////////////////////////////
// ViroVisionFilters.cpp
//
// Copyright (C) 2012 Veria Kalantary
// veria.kalantary@gmail.com
// https://github.com/veriak
//

//#include "stdafx.h"
#include "ViroVisionFilters.h"

using namespace ViroVisionFilters;

/////////////////////////////////////////////////////////////////////////////
// CViroVisionFilters

CViroVisionFilters::CViroVisionFilters(void)
{
	m_pPreviousSample = NULL;
}

CViroVisionFilters::~CViroVisionFilters(void)
{
	Clear();
}

void CViroVisionFilters::Clear(void)
{
	if (m_pPreviousSample)
	{
		free(m_pPreviousSample);
		m_pPreviousSample = NULL;
	}
}

LRESULT CALLBACK CViroVisionFilters::RedColorFilter(RGBTRIPLE *pRGBBuffer, long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;

	for (int i = 0; i < lPixelsCount; i++)
	{		
		pRGBBuffer->rgbtGreen = pRGBBuffer->rgbtBlue = 0;
		pRGBBuffer++;
	}

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::BlueColorFilter(RGBTRIPLE *pRGBBuffer, long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;

	for (int i = 0; i < lPixelsCount; i++)
	{		
		pRGBBuffer->rgbtRed = pRGBBuffer->rgbtGreen = 0;
		pRGBBuffer++;
	}

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::GreenColorFilter(RGBTRIPLE *pRGBBuffer, long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;

	for (int i = 0; i < lPixelsCount; i++)
	{		
		pRGBBuffer->rgbtRed = pRGBBuffer->rgbtBlue = 0;
		pRGBBuffer++;
	}

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::GrayColorFilter(RGBTRIPLE *pRGBBuffer, long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	int nGray = 0;

	for (int i = 0; i < lPixelsCount; i++)
	{
		nGray = (28 * pRGBBuffer->rgbtRed + 151 * pRGBBuffer->rgbtGreen +
			77 * pRGBBuffer->rgbtBlue) / 256;
		pRGBBuffer->rgbtRed = pRGBBuffer->rgbtGreen = pRGBBuffer->rgbtBlue = nGray;
		pRGBBuffer++;
	}

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::RedColorFilter2(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lLeft, long lTop, long lRight, long lBottom)
{
	LRESULT lResult = 0;

	for (int y = lTop; y < lBottom; y++)
	{
		int ymulw = y * lWidth;

		for (int x = lLeft; x < lRight; x++)
		{
			(pRGBBuffer + ymulw + x)->rgbtGreen = (pRGBBuffer + ymulw + x)->rgbtBlue = 0;
		}
	}

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::GreenColorFilter2(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lLeft, long lTop, long lRight, long lBottom)
{
	LRESULT lResult = 0;

	for (int y = lTop; y < lBottom; y++)
	{
		int ymulw = y * lWidth;

		for (int x = lLeft; x < lRight; x++)
		{
			(pRGBBuffer + ymulw + x)->rgbtRed = (pRGBBuffer + ymulw + x)->rgbtBlue = 0;
		}
	}

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::BlueColorFilter2(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lLeft, long lTop, long lRight, long lBottom)
{
	LRESULT lResult = 0;

	for (int y = lTop; y < lBottom; y++)
	{
		int ymulw = y * lWidth;

		for (int x = lLeft; x < lRight; x++)
		{
			(pRGBBuffer + ymulw + x)->rgbtRed = (pRGBBuffer + ymulw + x)->rgbtGreen = 0;
		}
	}

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::GrayColorFilter2(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lLeft, long lTop, long lRight, long lBottom)
{
	LRESULT lResult = 0;
	int nGray = 0;
	RGBTRIPLE *xy;

	for (int y = lTop; y < lBottom; y++)
	{
		int ymulw = y * lWidth;

		for (int x = lLeft; x < lRight; x++)
		{
			xy = pRGBBuffer + ymulw + x; 
			nGray = (28 * (xy)->rgbtRed + 151 * (xy)->rgbtGreen + 77 * (xy)->rgbtBlue) / 256;
			(xy)->rgbtRed = (xy)->rgbtBlue = (xy)->rgbtBlue = nGray;
		}
	}

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::RedBoxFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lLeft, long lTop, long lRight, long lBottom)
{
	LRESULT lResult = 0;	
	int topmulw = lTop * lWidth;
	int bottommulw = lBottom * lWidth;
	RGBTRIPLE *xy;

	for (int x = lLeft; x < lRight; x++)
	{
		xy = pRGBBuffer + topmulw + x;
		(xy)->rgbtGreen = (xy)->rgbtBlue = 0;
		xy = pRGBBuffer + bottommulw + x;
		(xy)->rgbtGreen = (xy)->rgbtBlue = 0;
	}

	int nBoxWidth = abs(lLeft - lRight);

	for (int y = lTop; y < lBottom; y++)
	{
		int ymulw = y * lWidth;

		xy = pRGBBuffer + ymulw + lLeft;
		(xy)->rgbtGreen = (xy)->rgbtBlue = 0;
		xy = pRGBBuffer + ymulw + lLeft + nBoxWidth;
		(xy)->rgbtGreen = (xy)->rgbtBlue = 0;
	}

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::GreenBoxFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lLeft, long lTop, long lRight, long lBottom)
{
	LRESULT lResult = 0;	
	int topmulw = lTop * lWidth;
	int bottommulw = lBottom * lWidth;
	RGBTRIPLE *xy;

	for (int x = lLeft; x < lRight; x++)
	{
		xy = pRGBBuffer + topmulw + x;
		(xy)->rgbtRed = (xy)->rgbtBlue = 0;
		xy = pRGBBuffer + bottommulw + x;
		(xy)->rgbtRed = (xy)->rgbtBlue = 0;
	}

	int nBoxWidth = abs(lLeft - lRight);

	for (int y = lTop; y < lBottom; y++)
	{
		int ymulw = y * lWidth;

		xy = pRGBBuffer + ymulw + lLeft;
		(xy)->rgbtRed = (xy)->rgbtBlue = 0;
		xy = pRGBBuffer + ymulw + lLeft + nBoxWidth;
		(xy)->rgbtRed = (xy)->rgbtBlue = 0;
	}

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::BlueBoxFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lLeft, long lTop, long lRight, long lBottom)
{
	LRESULT lResult = 0;	
	int topmulw = lTop * lWidth;
	int bottommulw = lBottom * lWidth;
	RGBTRIPLE *xy;

	for (int x = lLeft; x < lRight; x++)
	{
		xy = pRGBBuffer + topmulw + x;
		(xy)->rgbtRed = (xy)->rgbtGreen = 0;
		xy = pRGBBuffer + bottommulw + x;
		(xy)->rgbtRed = (xy)->rgbtGreen = 0;
	}

	int nBoxWidth = abs(lLeft - lRight);

	for (int y = lTop; y < lBottom; y++)
	{
		int ymulw = y * lWidth;

		xy = pRGBBuffer + ymulw + lLeft;
		(xy)->rgbtRed = (xy)->rgbtGreen = 0;
		xy = pRGBBuffer + ymulw + lLeft + nBoxWidth;
		(xy)->rgbtRed = (xy)->rgbtGreen = 0;
	}

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::GrayBoxFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lLeft, long lTop, long lRight, long lBottom)
{
	LRESULT lResult = 0;	
	int nGray = 0;
	int topmulw = lTop * lWidth;
	int bottommulw = lBottom * lWidth;
	RGBTRIPLE *xy;

	for (int x = lLeft; x < lRight; x++)
	{
		xy = pRGBBuffer + topmulw + x;
		nGray = (28 * (xy)->rgbtRed + 151 * (xy)->rgbtGreen + 77 * (xy)->rgbtBlue) / 256;
		(xy)->rgbtRed =	(xy)->rgbtGreen = (xy)->rgbtBlue = nGray;

		xy = pRGBBuffer + bottommulw + x;
		nGray = ((xy)->rgbtRed + 151 * (xy)->rgbtGreen + 77 * (xy)->rgbtBlue) / 256;
		(xy)->rgbtRed =	(xy)->rgbtGreen = (xy)->rgbtBlue = nGray;
	}

	int nBoxWidth = abs(lLeft - lRight);

	for (int y = lTop; y < lBottom; y++)
	{
		int ymulw = y * lWidth;

		xy = pRGBBuffer + ymulw + lLeft;
		nGray = (28 * (xy)->rgbtRed + 151 * (xy)->rgbtGreen + 77 * (xy)->rgbtBlue) / 256;
		(xy)->rgbtRed =	(xy)->rgbtGreen = (xy)->rgbtBlue = nGray;

		xy = pRGBBuffer + ymulw + lLeft + nBoxWidth;
		nGray = (28 * (xy)->rgbtRed + 151 * (xy)->rgbtGreen + 77 * (xy)->rgbtBlue) / 256;
		(xy)->rgbtRed =	(xy)->rgbtGreen = (xy)->rgbtBlue = nGray;
	}

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::WhiteBoxFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lLeft, long lTop, long lRight, long lBottom)
{
	LRESULT lResult = 0;	
	int topmulw = lTop * lWidth;
	int bottommulw = lBottom * lWidth;
	RGBTRIPLE *xy;

	for (int x = lLeft; x < lRight; x++)
	{
		xy = pRGBBuffer + topmulw + x;
		(xy)->rgbtRed = (xy)->rgbtGreen = (xy)->rgbtBlue = 255;
		xy = pRGBBuffer + bottommulw + x;
		(xy)->rgbtRed = (xy)->rgbtGreen = (xy)->rgbtBlue = 255;
	}

	int nBoxWidth = abs(lLeft - lRight);

	for (int y = lTop; y < lBottom; y++)
	{
		int ymulw = y * lWidth;

		xy = pRGBBuffer + ymulw + lLeft;
		(xy)->rgbtRed = (xy)->rgbtGreen = (xy)->rgbtBlue = 255;
		xy = pRGBBuffer + ymulw + lLeft + nBoxWidth;
		(xy)->rgbtRed = (xy)->rgbtGreen = (xy)->rgbtBlue = 255;
	}

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::YellowBoxFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lLeft, long lTop, long lRight, long lBottom)
{
	LRESULT lResult = 0;	
	int topmulw = lTop * lWidth;
	int bottommulw = lBottom * lWidth;
	RGBTRIPLE *xy;

	for (int x = lLeft; x < lRight; x++)
	{
		xy = pRGBBuffer + topmulw + x;
		(xy)->rgbtRed = (xy)->rgbtGreen = 255;
		xy = pRGBBuffer + bottommulw + x;
		(xy)->rgbtRed = (xy)->rgbtGreen = 255;
	}

	int nBoxWidth = abs(lLeft - lRight);

	for (int y = lTop; y < lBottom; y++)
	{
		int ymulw = y * lWidth;

		xy = pRGBBuffer + ymulw + lLeft;
		(xy)->rgbtRed = (xy)->rgbtGreen = 255;
		xy = pRGBBuffer + ymulw + lLeft + nBoxWidth;
		(xy)->rgbtRed = (xy)->rgbtGreen = 255;
	}

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::LaplacianEdgeDetectionFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lWidthMinus2 = lWidth - 2;
	long lHeightMinus1 = lHeight - 1;
	long lHeightMinus2 = lHeight - 2;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	
	
	GrayColorFilter(pRGBBuffer, lWidth, lHeight);	
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 2; y < lHeightMinus2; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y_2mulw = y_1mulw - lWidth;
		int y1mulw = ymulw + lWidth;
		int y2mulw = y1mulw + lWidth;

		for (int x = 2; x < lWidthMinus2; x++)
		{
			int nSum = -1 * (pCOB + y_2mulw + x - 2)->rgbtRed +
				-1 * (pCOB + y_2mulw + x - 1)->rgbtRed +
				-1 * (pCOB + y_2mulw + x)->rgbtRed +
				-1 * (pCOB + y_2mulw + x + 1)->rgbtRed +
				-1 * (pCOB + y_2mulw + x + 2)->rgbtRed +
				-1 * (pCOB + y_1mulw + x - 2)->rgbtRed +
				-1 * (pCOB + y_1mulw + x - 1)->rgbtRed +
				-1 * (pCOB + y_1mulw + x)->rgbtRed +
				-1 * (pCOB + y_1mulw + x + 1)->rgbtRed +
				-1 * (pCOB + y_1mulw + x + 2)->rgbtRed +
				-1 * (pCOB + ymulw + x - 2)->rgbtRed +
				-1 * (pCOB + ymulw + x - 1)->rgbtRed +
				24 * (pCOB + ymulw + x)->rgbtRed +
				-1 * (pCOB + ymulw + x + 1)->rgbtRed +
				-1 * (pCOB + ymulw + x + 2)->rgbtRed +
				-1 * (pCOB + y1mulw + x - 2)->rgbtRed +
				-1 * (pCOB + y1mulw + x - 1)->rgbtRed +
				-1 * (pCOB + y1mulw + x)->rgbtRed +
				-1 * (pCOB + y1mulw + x + 1)->rgbtRed +
				-1 * (pCOB + y1mulw + x + 2)->rgbtRed +
				-1 * (pCOB + y2mulw + x - 2)->rgbtRed +
				-1 * (pCOB + y2mulw + x - 1)->rgbtRed +
				-1 * (pCOB + y2mulw + x)->rgbtRed +
				-1 * (pCOB + y2mulw + x + 1)->rgbtRed +
				-1 * (pCOB + y2mulw + x + 2)->rgbtRed;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = 255 - nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::LaplacianEdgeDetectionFilter3_3(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);	
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1; x++)
		{
			int nSum = -1 * (pCOB + y_1mulw + x)->rgbtRed +
				-1 * (pCOB + ymulw + x - 1)->rgbtRed +
				4 * (pCOB + ymulw + x)->rgbtRed +
				-1 * (pCOB + ymulw + x + 1)->rgbtRed +
				-1 * (pCOB + y1mulw + x)->rgbtRed;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = 255 - nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::SobelEdgeDetectionFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);	
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1; x++)
		{
			int nSum = 0;
			int Gx = 0;
			int Gy = 0;

			Gx = -1 * (pCOB + y_1mulw + x - 1)->rgbtRed +
				(pCOB + y_1mulw + x + 1)->rgbtRed +
				-2 * (pCOB + ymulw + x - 1)->rgbtRed +
				2 * (pCOB + ymulw + x + 1)->rgbtRed +
				-1 * (pCOB + y1mulw + x - 1)->rgbtRed +					
				(pCOB + y1mulw + x + 1)->rgbtRed;

			Gy = (pCOB + y_1mulw + x - 1)->rgbtRed +
				2 * (pCOB + y_1mulw + x)->rgbtRed +
				(pCOB + y_1mulw + x + 1)->rgbtRed +
				-1 * (pCOB + y1mulw + x - 1)->rgbtRed +					
				-2 * (pCOB + y1mulw + x)->rgbtRed +
				-1 * (pCOB + y1mulw + x + 1)->rgbtRed;

			nSum = abs(Gx) + abs(Gy);

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = 255 - nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::PrewittEdgeDetectionFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1; x++)
		{
			int nSum = 0;
			int Gx = 0;
			int Gy = 0;

			Gx = -1 * (pCOB + y_1mulw + x - 1)->rgbtRed +
				(pCOB + y_1mulw + x + 1)->rgbtRed +
				-1 * (pCOB + ymulw + x - 1)->rgbtRed +
				(pCOB + ymulw + x + 1)->rgbtRed +
				-1 * (pCOB + y1mulw + x - 1)->rgbtRed +					
				(pCOB + y1mulw + x + 1)->rgbtRed;

			Gy = (pCOB + y_1mulw + x - 1)->rgbtRed +
				(pCOB + y_1mulw + x)->rgbtRed +
				(pCOB + y_1mulw + x + 1)->rgbtRed +
				-1 * (pCOB + y1mulw + x - 1)->rgbtRed +					
				-1 * (pCOB + y1mulw + x)->rgbtRed +
				-1 * (pCOB + y1mulw + x + 1)->rgbtRed;

			nSum = abs(Gx) + abs(Gy);

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = 255 - nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::PrewittNorthFilter(RGBTRIPLE *pRGBBuffer,
		long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1; x++)
		{
			int nSum = -1 * (pCOB + y_1mulw + x - 1)->rgbtRed +
				-2 * (pCOB + y_1mulw + x)->rgbtRed +
				-1 * (pCOB + y_1mulw + x + 1)->rgbtRed +
				(pCOB + y1mulw + x - 1)->rgbtRed +					
				2 * (pCOB + y1mulw + x)->rgbtRed +
				(pCOB + y1mulw + x + 1)->rgbtRed;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = 255 - nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::PrewittWestFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1; x++)
		{
			int nSum = -1 * (pCOB + y_1mulw + x - 1)->rgbtRed +
				(pCOB + y_1mulw + x + 1)->rgbtRed +
				-2 * (pCOB + ymulw + x - 1)->rgbtRed +
				2 * (pCOB + ymulw + x + 1)->rgbtRed +
				-1 * (pCOB + y1mulw + x - 1)->rgbtRed +					
				(pCOB + y1mulw + x + 1)->rgbtRed;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = 255 - nSum;			
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::PrewittEastFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1; x++)
		{
			int nSum = (pCOB + y_1mulw + x - 1)->rgbtRed +
				-1 * (pCOB + y_1mulw + x + 1)->rgbtRed +
				2 * (pCOB + ymulw + x - 1)->rgbtRed +					
				-2 * (pCOB + ymulw + x + 1)->rgbtRed +
				(pCOB + y1mulw + x - 1)->rgbtRed +					
				-1 * (pCOB + y1mulw + x + 1)->rgbtRed;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = 255 - nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::PrewittSouthFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1; x++)
		{
			int nSum = (pCOB + y_1mulw + x - 1)->rgbtRed +
				2 * (pCOB + y_1mulw + x)->rgbtRed +
				(pCOB + y_1mulw + x + 1)->rgbtRed +
				-1 * (pCOB + y1mulw + x - 1)->rgbtRed +					
				-2 * (pCOB + y1mulw + x)->rgbtRed +
				-1 * (pCOB + y1mulw + x + 1)->rgbtRed;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = 255 - nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::PrewittNortheastFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1; x++)
		{
			int nSum = -1 * (pCOB + y_1mulw + x)->rgbtRed +
				-2 * (pCOB + y_1mulw + x + 1)->rgbtRed +
				(pCOB + ymulw + x - 1)->rgbtRed +					
				-1 * (pCOB + ymulw + x + 1)->rgbtRed +
				2 * (pCOB + y1mulw + x - 1)->rgbtRed +					
				(pCOB + y1mulw + x)->rgbtRed;					

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = 255 - nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::PrewittSoutheastFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1; x++)
		{
			int nSum = 2 * (pCOB + y_1mulw + x - 1)->rgbtRed +
				(pCOB + y_1mulw + x)->rgbtRed +
				(pCOB + ymulw + x - 1)->rgbtRed +
				-1 * (pCOB + ymulw + x + 1)->rgbtRed +
				-1 * (pCOB + y1mulw + x)->rgbtRed +
				-2 * (pCOB + y1mulw + x + 1)->rgbtRed;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = 255 - nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::PrewittSouthwestFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1; x++)
		{
			int nSum = (pCOB + y_1mulw + x)->rgbtRed +
				2 * (pCOB + y_1mulw + x + 1)->rgbtRed +
				-1 * (pCOB + ymulw + x - 1)->rgbtRed +
				(pCOB + ymulw + x + 1)->rgbtRed +
				-2 * (pCOB + y1mulw + x - 1)->rgbtRed +					
				-1 * (pCOB + y1mulw + x)->rgbtRed;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = 255 - nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::PrewittNorthwestFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1; x++)
		{
			int nSum = -2 * (pCOB + y_1mulw + x - 1)->rgbtRed +
				-1 * (pCOB + y_1mulw + x)->rgbtRed +
				-1 * (pCOB + ymulw + x - 1)->rgbtRed +
				(pCOB + ymulw + x + 1)->rgbtRed +					
				(pCOB + y1mulw + x)->rgbtRed +
				2 * (pCOB + y1mulw + x + 1)->rgbtRed;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = 255 - nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::SharpenHighPassFilter5_5(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lWidthMinus2 = lWidth - 2;
	long lHeightMinus1 = lHeight - 1;
	long lHeightMinus2 = lHeight - 2;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 2; y < lHeightMinus2; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y_2mulw = y_1mulw - lWidth;
		int y1mulw = ymulw + lWidth;
		int y2mulw = y1mulw + lWidth;

		for (int x = 2; x < lWidthMinus2; x++)
		{
			int nSum = -1 * (pCOB + y_2mulw + x - 1)->rgbtRed +
				-1 * (pCOB + y_2mulw + x)->rgbtRed +
				-1 * (pCOB + y_2mulw + x + 1)->rgbtRed +
				-1 * (pCOB + y_1mulw + x - 2)->rgbtRed +
				2 * (pCOB + y_1mulw + x - 1)->rgbtRed +
				-4 * (pCOB + y_1mulw + x)->rgbtRed +
				2 * (pCOB + y_1mulw + x + 1)->rgbtRed +
				-1 * (pCOB + y_1mulw + x + 2)->rgbtRed +
				-1 * (pCOB + ymulw + x - 2)->rgbtRed +
				-4 * (pCOB + ymulw + x - 1)->rgbtRed +
				13 * (pCOB + ymulw + x)->rgbtRed +
				-4 * (pCOB + ymulw + x + 1)->rgbtRed +
				-1 * (pCOB + ymulw + x + 2)->rgbtRed +
				-1 * (pCOB + y1mulw + x - 2)->rgbtRed +
				2 * (pCOB + y1mulw + x - 1)->rgbtRed +
				-4 * (pCOB + y1mulw + x)->rgbtRed +
				2 * (pCOB + y1mulw + x + 1)->rgbtRed +
				-1 * (pCOB + y1mulw + x + 2)->rgbtRed +
				-1 * (pCOB + y2mulw + x - 1)->rgbtRed +
				-1 * (pCOB + y2mulw + x)->rgbtRed +
				-1 * (pCOB + y2mulw + x + 1)->rgbtRed;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::SharpenHighPassFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1; x++)
		{
			int nSum = -1 * (pCOB + y_1mulw + x - 1)->rgbtRed +
				-1 * (pCOB + y_1mulw + x)->rgbtRed +
				-1 * (pCOB + y_1mulw + x + 1)->rgbtRed +
				-1 * (pCOB + ymulw + x - 1)->rgbtRed +
				9 * (pCOB + ymulw + x)->rgbtRed +
				-1 * (pCOB + ymulw + x + 1)->rgbtRed +
				-1 * (pCOB + y1mulw + x - 1)->rgbtRed +					
				-1 * (pCOB + y1mulw + x)->rgbtRed +
				-1 * (pCOB + y1mulw + x + 1)->rgbtRed;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::SmoothLowPassFilter5_5(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lWidthMinus2 = lWidth - 2;
	long lHeightMinus1 = lHeight - 1;
	long lHeightMinus2 = lHeight - 2;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 2; y < lHeightMinus2; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y_2mulw = y_1mulw - lWidth;
		int y1mulw = ymulw + lWidth;
		int y2mulw = y1mulw + lWidth;

		for (int x = 2; x < lWidthMinus2; x++)
		{
			int nSum = (pCOB + y_2mulw + x - 2)->rgbtRed +
				(pCOB + y_2mulw + x - 1)->rgbtRed +
				(pCOB + y_2mulw + x)->rgbtRed +
				(pCOB + y_2mulw + x + 1)->rgbtRed +
				(pCOB + y_2mulw + x + 2)->rgbtRed +
				(pCOB + y_1mulw + x - 2)->rgbtRed +
				4 * (pCOB + y_1mulw + x - 1)->rgbtRed +
				4 * (pCOB + y_1mulw + x)->rgbtRed +
				4 * (pCOB + y_1mulw + x + 1)->rgbtRed +
				(pCOB + y_1mulw + x + 2)->rgbtRed +
				(pCOB + ymulw + x - 2)->rgbtRed +
				4 * (pCOB + ymulw + x - 1)->rgbtRed +
				12 * (pCOB + ymulw + x)->rgbtRed +
				4 * (pCOB + ymulw + x + 1)->rgbtRed +
				(pCOB + ymulw + x + 2)->rgbtRed +
				(pCOB + y1mulw + x - 2)->rgbtRed +
				4 * (pCOB + y1mulw + x - 1)->rgbtRed +
				4 * (pCOB + y1mulw + x)->rgbtRed +
				4 * (pCOB + y1mulw + x + 1)->rgbtRed +
				(pCOB + y1mulw + x + 2)->rgbtRed +
				(pCOB + y2mulw + x - 2)->rgbtRed +
				(pCOB + y2mulw + x - 1)->rgbtRed +
				(pCOB + y2mulw + x)->rgbtRed +
				(pCOB + y2mulw + x + 1)->rgbtRed +
				(pCOB + y2mulw + x + 2)->rgbtRed;

			nSum /= 60;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::SmoothLowPassFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1; x++)
		{
			int nSum = (pCOB + y_1mulw + x - 1)->rgbtRed +
				2 * (pCOB + y_1mulw + x)->rgbtRed +
				(pCOB + y_1mulw + x + 1)->rgbtRed +
				2 * (pCOB + ymulw + x - 1)->rgbtRed +
				4 * (pCOB + ymulw + x)->rgbtRed +
				2 * (pCOB + ymulw + x + 1)->rgbtRed +
				(pCOB + y1mulw + x - 1)->rgbtRed +					
				2 * (pCOB + y1mulw + x)->rgbtRed +
				(pCOB + y1mulw + x + 1)->rgbtRed;

			nSum /= 16;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::GaussianFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lWidthMinus2 = lWidth - 2;
	long lWidthMinus3 = lWidth - 3;
	long lHeightMinus1 = lHeight - 1;
	long lHeightMinus2 = lHeight - 2;
	long lHeightMinus3 = lHeight - 3;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 3; y < lHeightMinus3; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y_2mulw = y_1mulw - lWidth;
		int y_3mulw = y_2mulw - lWidth;
		int y1mulw = ymulw + lWidth;
		int y2mulw = y1mulw + lWidth;
		int y3mulw = y2mulw + lWidth;

		for (int x = 3; x < lWidthMinus3; x++)
		{
			int nSum = (pCOB + y_3mulw + x - 3)->rgbtRed +
				(pCOB + y_3mulw + x - 2)->rgbtRed +
				2 * (pCOB + y_3mulw + x - 1)->rgbtRed +
				2 * (pCOB + y_3mulw + x)->rgbtRed +
				2 * (pCOB + y_3mulw + x + 1)->rgbtRed +
				(pCOB + y_3mulw + x + 2)->rgbtRed +
				(pCOB + y_3mulw + x + 3)->rgbtRed +
				(pCOB + y_2mulw + x - 3)->rgbtRed +
				2 * (pCOB + y_2mulw + x - 2)->rgbtRed +
				2 * (pCOB + y_2mulw + x - 1)->rgbtRed +
				4 * (pCOB + y_2mulw + x)->rgbtRed +
				2 * (pCOB + y_2mulw + x + 1)->rgbtRed +
				2 * (pCOB + y_2mulw + x + 2)->rgbtRed +
				(pCOB + y_2mulw + x + 3)->rgbtRed +
				2 * (pCOB + y_1mulw + x - 3)->rgbtRed +
				2 * (pCOB + y_1mulw + x - 2)->rgbtRed +
				4 * (pCOB + y_1mulw + x - 1)->rgbtRed +
				8 * (pCOB + y_1mulw + x)->rgbtRed +
				4 * (pCOB + y_1mulw + x + 1)->rgbtRed +
				2 * (pCOB + y_1mulw + x + 2)->rgbtRed +
				2 * (pCOB + y_1mulw + x + 3)->rgbtRed +
				2 * (pCOB + ymulw + x - 3)->rgbtRed +
				4 * (pCOB + ymulw + x - 2)->rgbtRed +
				8 * (pCOB + ymulw + x - 1)->rgbtRed +
				16 * (pCOB + ymulw + x)->rgbtRed +
				8 * (pCOB + ymulw + x + 1)->rgbtRed +
				4 * (pCOB + ymulw + x + 2)->rgbtRed +
				2 * (pCOB + ymulw + x + 3)->rgbtRed +
				2 * (pCOB + y1mulw + x - 3)->rgbtRed +
				2 * (pCOB + y1mulw + x - 2)->rgbtRed +
				4 * (pCOB + y1mulw + x - 1)->rgbtRed +
				8 * (pCOB + y1mulw + x)->rgbtRed +
				4 * (pCOB + y1mulw + x + 1)->rgbtRed +
				2 * (pCOB + y1mulw + x + 2)->rgbtRed +
				2 * (pCOB + y1mulw + x + 3)->rgbtRed +
				(pCOB + y2mulw + x - 3)->rgbtRed +
				2 * (pCOB + y2mulw + x - 2)->rgbtRed +
				2 * (pCOB + y2mulw + x - 1)->rgbtRed +
				4 * (pCOB + y2mulw + x)->rgbtRed +
				2 * (pCOB + y2mulw + x + 1)->rgbtRed +
				2 * (pCOB + y2mulw + x + 2)->rgbtRed +
				(pCOB + y2mulw + x + 3)->rgbtRed +
				(pCOB + y3mulw + x - 3)->rgbtRed +
				(pCOB + y3mulw + x - 2)->rgbtRed +
				2 * (pCOB + y3mulw + x - 1)->rgbtRed +
				2 * (pCOB + y3mulw + x)->rgbtRed +
				2 * (pCOB + y3mulw + x + 1)->rgbtRed +
				(pCOB + y3mulw + x + 2)->rgbtRed +
				(pCOB + y3mulw + x + 3)->rgbtRed;

			nSum /= 140;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::LineDetectionHorizontalFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1; x++)
		{
			int nSum = -1 * (pCOB + y_1mulw + x - 1)->rgbtRed +
				-1 * (pCOB + y_1mulw + x)->rgbtRed +
				-1 * (pCOB + y_1mulw + x + 1)->rgbtRed +
				2 * (pCOB + ymulw + x - 1)->rgbtRed +
				2 * (pCOB + ymulw + x)->rgbtRed +
				2 * (pCOB + ymulw + x + 1)->rgbtRed +
				-1 * (pCOB + y1mulw + x - 1)->rgbtRed +					
				-1 * (pCOB + y1mulw + x)->rgbtRed +
				-1 * (pCOB + y1mulw + x + 1)->rgbtRed;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::LineDetectionVerticalFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1; x++)
		{
			int nSum = -1 * (pCOB + y_1mulw + x - 1)->rgbtRed +
				2 * (pCOB + y_1mulw + x)->rgbtRed +
				-1 * (pCOB + y_1mulw + x + 1)->rgbtRed +
				-1 * (pCOB + ymulw + x - 1)->rgbtRed +
				2 * (pCOB + ymulw + x)->rgbtRed +
				-1 * (pCOB + ymulw + x + 1)->rgbtRed +
				-1 * (pCOB + y1mulw + x - 1)->rgbtRed +					
				2 * (pCOB + y1mulw + x)->rgbtRed +
				-1 * (pCOB + y1mulw + x + 1)->rgbtRed;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::LineDetectionLeftDiagonalFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1; x++)
		{
			int nSum = 2 * (pCOB + y_1mulw + x - 1)->rgbtRed +
				-1 * (pCOB + y_1mulw + x)->rgbtRed +
				-1 * (pCOB + y_1mulw + x + 1)->rgbtRed +
				-1 * (pCOB + ymulw + x - 1)->rgbtRed +
				2 * (pCOB + ymulw + x)->rgbtRed +
				-1 * (pCOB + ymulw + x + 1)->rgbtRed +
				-1 * (pCOB + y1mulw + x - 1)->rgbtRed +					
				-1 * (pCOB + y1mulw + x)->rgbtRed +
				2 * (pCOB + y1mulw + x + 1)->rgbtRed;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::LineDetectionRightDiagonalFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1; x++)
		{
			int nSum = -1 * (pCOB + y_1mulw + x - 1)->rgbtRed +
				-1 * (pCOB + y_1mulw + x)->rgbtRed +
				2 * (pCOB + y_1mulw + x + 1)->rgbtRed +
				-1 * (pCOB + ymulw + x - 1)->rgbtRed +
				2 * (pCOB + ymulw + x)->rgbtRed +
				-1 * (pCOB + ymulw + x + 1)->rgbtRed +
				2 * (pCOB + y1mulw + x - 1)->rgbtRed +					
				-1 * (pCOB + y1mulw + x)->rgbtRed +
				-1 * (pCOB + y1mulw + x + 1)->rgbtRed;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::PointDetectionFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1; x++)
		{
			int nSum = -1 * (pCOB + y_1mulw + x - 1)->rgbtRed +
				-1 * (pCOB + y_1mulw + x)->rgbtRed +
				-1 * (pCOB + y_1mulw + x + 1)->rgbtRed +
				-1 * (pCOB + ymulw + x - 1)->rgbtRed +
				8 * (pCOB + ymulw + x)->rgbtRed +
				-1 * (pCOB + ymulw + x + 1)->rgbtRed +
				-1 * (pCOB + y1mulw + x - 1)->rgbtRed +					
				-1 * (pCOB + y1mulw + x)->rgbtRed +
				-1 * (pCOB + y1mulw + x + 1)->rgbtRed;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = nSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::WeightedMeanFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lWidthMinus2 = lWidth - 2;
	long lHeightMinus1 = lHeight - 1;
	long lHeightMinus2 = lHeight - 2;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 2; y < lHeightMinus2; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y_2mulw = y_1mulw - lWidth;
		int y1mulw = ymulw + lWidth;
		int y2mulw = y1mulw + lWidth;

		for (int x = 2; x < lWidthMinus2; x++)
		{
			int nSum = (pCOB + y_2mulw + x - 2)->rgbtRed +
				(pCOB + y_2mulw + x - 1)->rgbtRed +
				(pCOB + y_2mulw + x)->rgbtRed +
				(pCOB + y_2mulw + x + 1)->rgbtRed +
				(pCOB + y_2mulw + x + 2)->rgbtRed +
				(pCOB + y_1mulw + x - 2)->rgbtRed +
				2 * (pCOB + y_1mulw + x - 1)->rgbtRed +
				2 * (pCOB + y_1mulw + x)->rgbtRed +
				2 * (pCOB + y_1mulw + x + 1)->rgbtRed +
				(pCOB + y_1mulw + x + 2)->rgbtRed +
				(pCOB + ymulw + x - 2)->rgbtRed +
				2 * (pCOB + ymulw + x - 1)->rgbtRed +
				3 * (pCOB + ymulw + x)->rgbtRed +
				2 * (pCOB + ymulw + x + 1)->rgbtRed +
				(pCOB + ymulw + x + 2)->rgbtRed +
				(pCOB + y1mulw + x - 2)->rgbtRed +
				2 * (pCOB + y1mulw + x - 1)->rgbtRed +
				2 * (pCOB + y1mulw + x)->rgbtRed +
				2 * (pCOB + y1mulw + x + 1)->rgbtRed +
				(pCOB + y1mulw + x + 2)->rgbtRed +
				(pCOB + y2mulw + x - 2)->rgbtRed +
				(pCOB + y2mulw + x - 1)->rgbtRed +
				(pCOB + y2mulw + x)->rgbtRed +
				(pCOB + y2mulw + x + 1)->rgbtRed +
				(pCOB + y2mulw + x + 2)->rgbtRed;

			nSum /= 35;

			if (nSum > 255)
				nSum = 255;

			if (nSum < 0)
				nSum = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = nSum;			
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::MedianFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	int arrWindow[9];
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1 ; x++)
		{
			arrWindow[0] = (pCOB + y_1mulw + x - 1)->rgbtRed;
			arrWindow[1] = (pCOB + y_1mulw + x)->rgbtRed;
			arrWindow[2] = (pCOB + y_1mulw + x + 1)->rgbtRed;
			arrWindow[3] = (pCOB + ymulw + x - 1)->rgbtRed;
			arrWindow[4] = (pCOB + ymulw + x)->rgbtRed;
			arrWindow[5] = (pCOB + ymulw + x + 1)->rgbtRed;
			arrWindow[6] = (pCOB + y1mulw + x - 1)->rgbtRed;
			arrWindow[7] = (pCOB + y1mulw + x)->rgbtRed;
			arrWindow[8] = (pCOB + y1mulw + x + 1)->rgbtRed;

			for (int i = 0; i < 8; i++)
			{
				int i1 = i + 1;

				for (int j = i1; j < 9; j++)
				{
					if (arrWindow[i] > arrWindow[j])
					{
						int temp = arrWindow[i];
						arrWindow[i] = arrWindow[j];
						arrWindow[j] = temp;
					}
				}
			}

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = arrWindow[4];
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::MeanFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1 ; x++)
		{
			int nSum = (pCOB + y_1mulw + x - 1)->rgbtRed +
				(pCOB + y_1mulw + x)->rgbtRed +
				(pCOB + y_1mulw + x + 1)->rgbtRed +
				(pCOB + ymulw + x - 1)->rgbtRed +
				(pCOB + ymulw + x)->rgbtRed +
				(pCOB + ymulw + x + 1)->rgbtRed +
				(pCOB + y1mulw + x - 1)->rgbtRed +
				(pCOB + y1mulw + x)->rgbtRed +
				(pCOB + y1mulw + x + 1)->rgbtRed;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = nSum / 9;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::MinimumFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	int arrWindow[9];
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1 ; x++)
		{
			int nMin = 255;

			arrWindow[0] = (pCOB + y_1mulw + x - 1)->rgbtRed;
			arrWindow[1] = (pCOB + y_1mulw + x)->rgbtRed;
			arrWindow[2] = (pCOB + y_1mulw + x + 1)->rgbtRed;
			arrWindow[3] = (pCOB + ymulw + x - 1)->rgbtRed;
			arrWindow[4] = (pCOB + ymulw + x)->rgbtRed;
			arrWindow[5] = (pCOB + ymulw + x + 1)->rgbtRed;
			arrWindow[6] = (pCOB + y1mulw + x - 1)->rgbtRed;
			arrWindow[7] = (pCOB + y1mulw + x)->rgbtRed;
			arrWindow[8] = (pCOB + y1mulw + x + 1)->rgbtRed;

			for (int i = 0; i < 9; i++)
			{
				if (arrWindow[i] < nMin)
					nMin = arrWindow[i];
			}

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = nMin;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::MaximumFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	int arrWindow[9];
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1 ; x++)
		{
			int nMax = 0;

			arrWindow[0] = (pCOB + y_1mulw + x - 1)->rgbtRed;
			arrWindow[1] = (pCOB + y_1mulw + x)->rgbtRed;
			arrWindow[2] = (pCOB + y_1mulw + x + 1)->rgbtRed;
			arrWindow[3] = (pCOB + ymulw + x - 1)->rgbtRed;
			arrWindow[4] = (pCOB + ymulw + x)->rgbtRed;
			arrWindow[5] = (pCOB + ymulw + x + 1)->rgbtRed;
			arrWindow[6] = (pCOB + y1mulw + x - 1)->rgbtRed;
			arrWindow[7] = (pCOB + y1mulw + x)->rgbtRed;
			arrWindow[8] = (pCOB + y1mulw + x + 1)->rgbtRed;

			for (int i = 0; i < 9; i++)
			{
				if (arrWindow[i] > nMax)
					nMax = arrWindow[i];
			}

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = nMax;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::RangeFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	int arrWindow[9];
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 1; y < lHeightMinus1; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y1mulw = ymulw + lWidth;

		for (int x = 1; x < lWidthMinus1 ; x++)
		{
			int nMin = 255;
			int nMax = 0;

			arrWindow[0] = (pCOB + y_1mulw + x - 1)->rgbtRed;
			arrWindow[1] = (pCOB + y_1mulw + x)->rgbtRed;
			arrWindow[2] = (pCOB + y_1mulw + x + 1)->rgbtRed;
			arrWindow[3] = (pCOB + ymulw + x - 1)->rgbtRed;
			arrWindow[4] = (pCOB + ymulw + x)->rgbtRed;
			arrWindow[5] = (pCOB + ymulw + x + 1)->rgbtRed;
			arrWindow[6] = (pCOB + y1mulw + x - 1)->rgbtRed;
			arrWindow[7] = (pCOB + y1mulw + x)->rgbtRed;
			arrWindow[8] = (pCOB + y1mulw + x + 1)->rgbtRed;

			for (int i = 0; i < 9; i++)
			{
				if (arrWindow[i] < nMin)
					nMin = arrWindow[i];
			}

			for (int i = 0; i < 9; i++)
			{
				if (arrWindow[i] > nMax)
					nMax = arrWindow[i];
			}

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = nMax - nMin;
		}		
	}

	free(pCOB);

	return lResult;
}

long CViroVisionFilters::CalculateMean(RGBTRIPLE *pRGBBuffer, long lWidth, long lHeight)
{
	long lSum = 0;

	for (int y = 0; y < lHeight; y++)
	{
		int ymulw = y * lWidth;

		for (int x = 0; x < lWidth ; x++)
		{
			lSum += (pRGBBuffer + ymulw + x)->rgbtRed;
		}
	}	

	return lSum / (lWidth * lHeight);
}

long CViroVisionFilters::CalculateVariance(RGBTRIPLE *pRGBBuffer, long lWidth, long lHeight)
{
	long lMean = CalculateMean(pRGBBuffer, lWidth, lHeight);
	float lSum = 0;
	float lTemp;

	for (int y = 0; y < lHeight; y++)
	{
		int ymulw = y * lWidth;

		for (int x = 0; x < lWidth ; x++)
		{
			lTemp = (pRGBBuffer + ymulw + x)->rgbtRed - lMean;
			lSum += lTemp * lTemp;
		}
	}	

	return (long) lSum / (lWidth * lHeight);
}

LRESULT CALLBACK CViroVisionFilters::DWMTM_AdaptiveFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight, LPVOID lpFilterParam)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lWidthMinus2 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	long lHeightMinus2 = lHeight - 2;
	float c = *(float *) lpFilterParam;
	int arrWindow[9];
	int nMedian;
	int nMedian_c ;
	int nMedianc;
	long lSum;
	long lTotalCount;
	int gray0, gray1, gray2, gray3, gray4, gray5, gray6, gray7, gray8, gray9, gray10,
		gray11, gray12, gray13, gray14, gray15, gray16, gray17, gray18, gray19, gray20,
		gray21, gray22, gray23, gray24;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 2; y < lHeightMinus2; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y_2mulw = y_1mulw - lWidth;
		int y1mulw = ymulw + lWidth;
		int y2mulw = y1mulw + lWidth;

		for (int x = 2; x < lWidthMinus2; x++)
		{
			arrWindow[0] = (pCOB + y_1mulw + x - 1)->rgbtRed;
			arrWindow[1] = (pCOB + y_1mulw + x)->rgbtRed;
			arrWindow[2] = (pCOB + y_1mulw + x + 1)->rgbtRed;
			arrWindow[3] = (pCOB + ymulw + x - 1)->rgbtRed;
			arrWindow[4] = (pCOB + ymulw + x)->rgbtRed;
			arrWindow[5] = (pCOB + ymulw + x + 1)->rgbtRed;
			arrWindow[6] = (pCOB + y1mulw + x - 1)->rgbtRed;
			arrWindow[7] = (pCOB + y1mulw + x)->rgbtRed;
			arrWindow[8] = (pCOB + y1mulw + x + 1)->rgbtRed;

			for (int i = 0; i < 8; i++)
			{
				int i1 = i + 1;

				for (int j = i1; j < 9; j++)
				{
					if (arrWindow[i] > arrWindow[j])
					{
						int temp = arrWindow[i];
						arrWindow[i] = arrWindow[j];
						arrWindow[j] = temp;
					}
				}
			}

			nMedian = arrWindow[4];
			nMedian_c = nMedian - c;
			nMedianc = nMedian + c;
			lSum = 0;
			lTotalCount = 0;

			gray0 = (pCOB + y_2mulw + x - 2)->rgbtRed;
			if ((gray0 >= nMedian_c) && (gray0 <= nMedianc))
			{
				lSum += gray0;
				lTotalCount++;
			}
			gray1 = (pCOB + y_2mulw + x - 1)->rgbtRed;
			if ((gray1 >= nMedian_c) && (gray1 <= nMedianc))
			{
				lSum += gray1;
				lTotalCount++;
			}
			gray2 = (pCOB + y_2mulw + x)->rgbtRed;
			if ((gray2 >= nMedian_c) && (gray2 <= nMedianc))
			{
				lSum += gray2;
				lTotalCount++;
			}
			gray3 = (pCOB + y_2mulw + x + 1)->rgbtRed;
			if ((gray3 >= nMedian_c) && (gray3 <= nMedianc))
			{
				lSum += gray3;
				lTotalCount++;
			}
			gray4 = (pCOB + y_2mulw + x + 2)->rgbtRed;
			if ((gray4 >= nMedian_c) && (gray4 <= nMedianc))
			{
				lSum += gray4;
				lTotalCount++;
			}
			gray5 = (pCOB + y_1mulw + x - 2)->rgbtRed;
			if ((gray5 >= nMedian_c) && (gray5 <= nMedianc))
			{
				lSum += gray5;
				lTotalCount++;
			}
			gray6 = (pCOB + y_1mulw + x - 1)->rgbtRed;
			if ((gray6 >= nMedian_c) && (gray6 <= nMedianc))
			{
				lSum += gray6;
				lTotalCount++;
			}
			gray7 = (pCOB + y_1mulw + x)->rgbtRed;
			if ((gray7 >= nMedian_c) && (gray7 <= nMedianc))
			{
				lSum += gray7;
				lTotalCount++;
			}
			gray8 = (pCOB + y_1mulw + x + 1)->rgbtRed;
			if ((gray8 >= nMedian_c) && (gray8 <= nMedianc))
			{
				lSum += gray8;
				lTotalCount++;
			}
			gray9 = (pCOB + y_1mulw + x + 2)->rgbtRed;
			if ((gray9 >= nMedian_c) && (gray9 <= nMedianc))
			{
				lSum += gray9;
				lTotalCount++;
			}
			gray10 = (pCOB + ymulw + x - 2)->rgbtRed;
			if ((gray10 >= nMedian_c) && (gray10 <= nMedianc))
			{
				lSum += gray10;
				lTotalCount++;
			}
			gray11 = (pCOB + ymulw + x - 1)->rgbtRed;
			if ((gray11 >= nMedian_c) && (gray11 <= nMedianc))
			{
				lSum += gray11;
				lTotalCount++;
			}
			gray12 = (pCOB + ymulw + x)->rgbtRed;
			if ((gray12 >= nMedian_c) && (gray12 <= nMedianc))
			{
				lSum += gray12;
				lTotalCount++;
			}
			gray13 = (pCOB + ymulw + x + 1)->rgbtRed;
			if ((gray13 >= nMedian_c) && (gray13 <= nMedianc))
			{
				lSum += gray13;
				lTotalCount++;
			}
			gray14 = (pCOB + ymulw + x + 2)->rgbtRed;
			if ((gray14 >= nMedian_c) && (gray14 <= nMedianc))
			{
				lSum += gray14;
				lTotalCount++;
			}
			gray15 = (pCOB + y1mulw + x - 2)->rgbtRed;
			if ((gray15 >= nMedian_c) && (gray15 <= nMedianc))
			{
				lSum += gray15;
				lTotalCount++;
			}
			gray16 = (pCOB + y1mulw + x - 1)->rgbtRed;
			if ((gray16 >= nMedian_c) && (gray16 <= nMedianc))
			{
				lSum += gray16;
				lTotalCount++;
			}
			gray17 = (pCOB + y1mulw + x)->rgbtRed;
			if ((gray17 >= nMedian_c) && (gray17 <= nMedianc))
			{
				lSum += gray17;
				lTotalCount++;
			}
			gray18 = (pCOB + y1mulw + x + 1)->rgbtRed;
			if ((gray18 >= nMedian_c) && (gray18 <= nMedianc))
			{
				lSum += gray18;
				lTotalCount++;
			}
			gray19 = (pCOB + y1mulw + x + 2)->rgbtRed;
			if ((gray19 >= nMedian_c) && (gray19 <= nMedianc))
			{
				lSum += gray19;
				lTotalCount++;
			}
			gray20 = (pCOB + y2mulw + x - 2)->rgbtRed;
			if ((gray20 >= nMedian_c) && (gray20 <= nMedianc))
			{
				lSum += gray20;
				lTotalCount++;
			}
			gray21 = (pCOB + y2mulw + x - 1)->rgbtRed;
			if ((gray21 >= nMedian_c) && (gray21 <= nMedianc))
			{
				lSum += gray21;
				lTotalCount++;
			}
			gray22 = (pCOB + y2mulw + x)->rgbtRed;
			if ((gray22 >= nMedian_c) && (gray22 <= nMedianc))
			{
				lSum += gray22;
				lTotalCount++;
			}
			gray23 = (pCOB + y2mulw + x + 1)->rgbtRed;
			if ((gray23 >= nMedian_c) && (gray23 <= nMedianc))
			{
				lSum += gray23;
				lTotalCount++;
			}
			gray24 = (pCOB + y2mulw + x + 2)->rgbtRed;
			if ((gray24 >= nMedian_c) && (gray24 <= nMedianc))
			{
				lSum += gray24;
				lTotalCount++;
			}

			lSum = (float) lSum / (float) lTotalCount;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = (BYTE) lSum;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::MMSE_AdaptiveFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight, LPVOID lpFilterParam)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	long lWidthMinus1 = lWidth - 1;
	long lWidthMinus2 = lWidth - 1;
	long lHeightMinus1 = lHeight - 1;
	long lHeightMinus2 = lHeight - 2;
	float NVAR = *(float *) lpFilterParam;
	float fVar;
	float fSqrsMean;
	float fMean;
	long lSum;
	long lSqrsSum;
	long lTotalCount;
	int gray0, gray1, gray2, gray3, gray4, gray5, gray6, gray7, gray8, gray9, gray10,
		gray11, gray12, gray13, gray14, gray15, gray16, gray17, gray18, gray19, gray20,
		gray21, gray22, gray23, gray24 ;
	int g;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);

	GrayColorFilter(pRGBBuffer, lWidth, lHeight);
	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);

	for (int y = 2; y < lHeightMinus2; y++)
	{
		int ymulw = y * lWidth;
		int y_1mulw = ymulw - lWidth;
		int y_2mulw = y_1mulw - lWidth;
		int y1mulw = ymulw + lWidth;
		int y2mulw = y1mulw + lWidth;

		for (int x = 2; x < lWidthMinus2; x++)
		{
			lSum = 0;
			lSqrsSum = 0;			

			gray0 = (pCOB + y_2mulw + x - 2)->rgbtRed;
			gray1 = (pCOB + y_2mulw + x - 1)->rgbtRed;
			gray2 = (pCOB + y_2mulw + x)->rgbtRed;
			gray3 = (pCOB + y_2mulw + x + 1)->rgbtRed;
			gray4 = (pCOB + y_2mulw + x + 2)->rgbtRed;
			gray5 = (pCOB + y_1mulw + x - 2)->rgbtRed;
			gray6 = (pCOB + y_1mulw + x - 1)->rgbtRed;
			gray7 = (pCOB + y_1mulw + x)->rgbtRed;
			gray8 = (pCOB + y_1mulw + x + 1)->rgbtRed;
			gray9 = (pCOB + y_1mulw + x + 2)->rgbtRed;
			gray10 = (pCOB + ymulw + x - 2)->rgbtRed;
			gray11 = (pCOB + ymulw + x - 1)->rgbtRed;
			gray12 = (pCOB + ymulw + x)->rgbtRed;
			gray13 = (pCOB + ymulw + x + 1)->rgbtRed;
			gray14 = (pCOB + ymulw + x + 2)->rgbtRed;
			gray15 = (pCOB + y1mulw + x - 2)->rgbtRed;
			gray16 = (pCOB + y1mulw + x - 1)->rgbtRed;
			gray17 = (pCOB + y1mulw + x)->rgbtRed;
			gray18 = (pCOB + y1mulw + x + 1)->rgbtRed;
			gray19 = (pCOB + y1mulw + x + 2)->rgbtRed;
			gray20 = (pCOB + y2mulw + x - 2)->rgbtRed;
			gray21 = (pCOB + y2mulw + x - 1)->rgbtRed;
			gray22 = (pCOB + y2mulw + x)->rgbtRed;
			gray23 = (pCOB + y2mulw + x + 1)->rgbtRed;
			gray24 = (pCOB + y2mulw + x + 2)->rgbtRed;

			lSum = gray0 + gray1 + gray2 + gray3 + gray4 + gray5 + gray6 + gray7 + gray8 + gray9 +
				gray10 + gray11 + gray12 + gray13 + gray14 + gray15 + gray16 + gray17 + gray18 + gray19 +
				gray20 + gray21 + gray22 + gray23 + gray24;

			lSqrsSum = gray0 * gray0 + gray1 * gray1 + gray2 * gray2 + gray3 * gray3 + gray4 * gray4 +
				gray5 * gray5 + gray6 * gray6 + gray7 * gray7 + gray8 * gray8 + gray9 * gray9 +
				gray10 * gray10 + gray11 * gray11 + gray12 * gray12 + gray13 * gray13 + gray14 * gray14 +
				gray15 * gray15 + gray16 * gray16 + gray17 * gray17 + gray18 * gray18 + gray19 * gray19 +
				gray20 * gray20 + gray21 * gray21 + gray22 * gray22 + gray23 * gray23 + gray24 * gray24;

			lTotalCount = 25;

			fSqrsMean = (float) lSqrsSum / (float) lTotalCount;
			fMean = (float) lSum / (float) lTotalCount;
			fVar = fSqrsMean - fMean * fMean;

			if (fVar == 0.0)
				g = (int) (fMean + 0.5);
			else
				g = (int) ((1 - NVAR / fVar) * gray12 + NVAR / fVar * fMean + 0.5);

			if (g > 255)
				g = 255;

			if (g < 0)
				g = 0;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = (BYTE) g;
		}		
	}

	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::LowPassFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight,
	LPVOID lpFilterParam, CViroVisionFilters *_this)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	int nOldValue;
	int nNewValue;
	unsigned int nFilterParam = *(unsigned int *) lpFilterParam;

//	GrayColorFilter(pRGBBuffer, lWidth, lHeight);

	if (_this->m_pPreviousSample == NULL)
	{
		_this->m_pPreviousSample = malloc(lPixelsCount * sizeof(int));
		memset(_this->m_pPreviousSample, 0, lPixelsCount * sizeof(int));
	}

	for (int y = 0; y < lHeight; y++)
	{
		int ymulw = y * lWidth;

		for (int x = 0; x < lWidth ; x++)
		{
			nNewValue = (pRGBBuffer + ymulw + x)->rgbtRed * 256;
			nOldValue = *((int *) _this->m_pPreviousSample + ymulw + x);
			nNewValue = nOldValue - (nOldValue / nFilterParam) + (nNewValue / nFilterParam);

			*((int *) _this->m_pPreviousSample + ymulw + x) = nNewValue;
			nNewValue /= 256;

			(pRGBBuffer + ymulw + x)->rgbtRed =
				(pRGBBuffer + ymulw + x)->rgbtGreen =
				(pRGBBuffer + ymulw + x)->rgbtBlue = nNewValue;
		}
	}	

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::MotionDetectionFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight,
	LPVOID lpFilterParam, CViroVisionFilters *_this)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	unsigned int nFilterParam = *(unsigned int *) lpFilterParam;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);	

	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);	
	MeanFilter(pCOB, lWidth, lHeight);	

	if (_this->m_pPreviousSample)
	{
		for (int y = 0; y < lHeight; y++)
		{
			int ymulw = y * lWidth;

			for (int x = 0; x < lWidth ; x++)
			{
				if (abs((pCOB + ymulw + x)->rgbtRed - *((int *) _this->m_pPreviousSample + ymulw + x) / 256) > 8)
				{
					(pRGBBuffer + ymulw + x)->rgbtGreen =
						(pRGBBuffer + ymulw + x)->rgbtBlue = 0;
				}
			}
		}
	}

	LowPassFilter(pCOB, lWidth, lHeight, lpFilterParam, _this);	
	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::MotionDetectionSolidRectFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight,
	LPVOID lpFilterParam, CViroVisionFilters *_this)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	unsigned int nFilterParam = *(unsigned int *) lpFilterParam;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);

	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);	
	MeanFilter(pCOB, lWidth, lHeight);	

	if (_this->m_pPreviousSample)
	{
		int nRectWidth = 15;
		int nRectxMax = lWidth / nRectWidth;
		int nRectHeight = 15;
		int nRectyMax = lHeight / nRectWidth;
		int nTriggerValue = 150;
		
		for (int nRecty = 0; nRecty < nRectyMax; nRecty++)
		{
			for (int nRectx = 0; nRectx < nRectxMax ; nRectx++)
			{
				int nDifferenceSum = 0;
				int nDifference;
				int nLeft = nRectx * nRectWidth;
				int nTop = nRecty * nRectHeight;
				int nRight = nLeft + nRectWidth;
				int nBottom = nTop + nRectHeight;

				for (long y = nTop; y < nBottom; y++)
				{
					int ymulw = y * lWidth;

					for (int x = nLeft; x < nRight; x++)
					{
						nDifference = abs((pCOB + ymulw + x)->rgbtRed -
							*((int *) _this->m_pPreviousSample + ymulw + x) / 256);

						if (nDifference > 8)
							nDifferenceSum += nDifference;
					}
				}

				if (nDifferenceSum > nTriggerValue)
					RedColorFilter2(pRGBBuffer, lWidth, nLeft, nTop, nRight, nBottom);
			}
		}
	}

	LowPassFilter(pCOB, lWidth, lHeight, lpFilterParam, _this);	
	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::MotionDetectionBoxRectFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight,
	LPVOID lpFilterParam, CViroVisionFilters *_this)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	unsigned int nFilterParam = *(unsigned int *) lpFilterParam;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);

	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);	
	MeanFilter(pCOB, lWidth, lHeight);	

	if (_this->m_pPreviousSample)
	{
		int nRectWidth = 30;
		int nRectxMax = lWidth / nRectWidth;
		int nRectHeight = 30;
		int nRectyMax = lHeight / nRectWidth;
		int nTriggerValue = 600;
		
		for (int nRecty = 0; nRecty < nRectyMax; nRecty++)
		{
			for (int nRectx = 0; nRectx < nRectxMax ; nRectx++)
			{
				int nDifferenceSum = 0;
				int nDifference;
				int nLeft = nRectx * nRectWidth;
				int nTop = nRecty * nRectHeight;
				int nRight = nLeft + nRectWidth;
				int nBottom = nTop + nRectHeight;

				for (long y = nTop; y < nBottom; y++)
				{
					int ymulw = y * lWidth;

					for (int x = nLeft; x < nRight; x++)
					{
						nDifference = abs((pCOB + ymulw + x)->rgbtRed -
							*((int *) _this->m_pPreviousSample + ymulw + x) / 256);

						if (nDifference > 8)
							nDifferenceSum += nDifference;
					}
				}

				if (nDifferenceSum > nTriggerValue)
					YellowBoxFilter(pRGBBuffer, lWidth, nLeft, nTop, nRight, nBottom);
			}
		}
	}

	LowPassFilter(pCOB, lWidth, lHeight, lpFilterParam, _this);	
	free(pCOB);

	return lResult;
}

LRESULT CALLBACK CViroVisionFilters::MotionDetectionBoxSurroundedFilter(RGBTRIPLE *pRGBBuffer,
	long lWidth, long lHeight,
	LPVOID lpFilterParam, CViroVisionFilters *_this)
{
	LRESULT lResult = 0;
	long lPixelsCount = lWidth * lHeight;
	unsigned int nFilterParam = *(unsigned int *) lpFilterParam;
	RGBTRIPLE *pCOB = (RGBTRIPLE *) malloc(lPixelsCount * 3);

	memcpy(pCOB, pRGBBuffer, lPixelsCount * 3);	
	MeanFilter(pCOB, lWidth, lHeight);	

	if (_this->m_pPreviousSample)
	{
		int nRectWidth = 30;
		int nRectxMax = lWidth / nRectWidth;
		int nRectHeight = 30;
		int nRectyMax = lHeight / nRectWidth;
		int nTriggerValue = 600;

		int nDetectedRectLeft = lWidth;
		int nDetectedRectTop = lHeight;
		int nDetectedRectRight = 0;
		int nDetectedRectBottom = 0;
		
		for (int nRecty = 0; nRecty < nRectyMax; nRecty++)
		{
			for (int nRectx = 0; nRectx < nRectxMax ; nRectx++)
			{
				int nDifferenceSum = 0;
				int nDifference;
				int nLeft = nRectx * nRectWidth;
				int nTop = nRecty * nRectHeight;
				int nRight = nLeft + nRectWidth;
				int nBottom = nTop + nRectHeight;

				for (long y = nTop; y < nBottom; y++)
				{
					int ymulw = y * lWidth;

					for (int x = nLeft; x < nRight; x++)
					{
						nDifference = abs((pCOB + ymulw + x)->rgbtRed -
							*((int *) _this->m_pPreviousSample + ymulw + x) / 256);

						if (nDifference > 8)
							nDifferenceSum += nDifference;
					}
				}

				if (nDifferenceSum > nTriggerValue)
				{
					if (nDetectedRectLeft > nLeft)
						nDetectedRectLeft = nLeft;
					
					if (nDetectedRectTop > nTop)
						nDetectedRectTop = nTop;
					
					if (nDetectedRectRight < nRight)
						nDetectedRectRight = nRight;
					
					if (nDetectedRectBottom < nBottom)
						nDetectedRectBottom = nBottom;
				}
			}
		}

		YellowBoxFilter(pRGBBuffer, lWidth, nDetectedRectLeft, nDetectedRectTop,
			nDetectedRectRight, nDetectedRectBottom);
	}

	LowPassFilter(pCOB, lWidth, lHeight, lpFilterParam, _this);	
	free(pCOB);

	return lResult;
}