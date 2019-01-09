/////////////////////////////////////////////////////////////////////////////
// ViroVision.h
//
// Copyright (C) 2012 Veria Kalantary
// veria.kalantary@gmail.com
// https://github.com/veriak
//

#ifndef VIROVISION_INCLUDED
#define VIROVISION_INCLUDED
#pragma once

#include <windows.h>
#include <list>
#include <dshow.h>
#include <stdio.h>
//#include <tchar.h>

#include "ViroVisionFilters.h"

using namespace ViroVisionFilters;

namespace ViroVision
{

#define WM_VIROVISION_NOTIFY				WM_APP + 1

#ifndef __qedit_h__
#define __qedit_h__

interface ISampleGrabberCB : public IUnknown
{
	virtual STDMETHODIMP SampleCB( double SampleTime, IMediaSample *pSample ) = 0;
	virtual STDMETHODIMP BufferCB( double SampleTime, BYTE *pBuffer, long BufferLen ) = 0;
};

static const IID IID_ISampleGrabberCB = { 0x0579154A, 0x2B53, 0x4994, { 0xB0, 0xD0, 0xE7, 0x73, 0x14, 0x8E, 0xFF, 0x85 } };

interface ISampleGrabber : public IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE SetOneShot( BOOL OneShot ) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetMediaType( const AM_MEDIA_TYPE *pType ) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetConnectedMediaType( AM_MEDIA_TYPE *pType ) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetBufferSamples( BOOL BufferThem ) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetCurrentBuffer( long *pBufferSize, long *pBuffer ) = 0;
	virtual HRESULT STDMETHODCALLTYPE GetCurrentSample( IMediaSample **ppSample ) = 0;
	virtual HRESULT STDMETHODCALLTYPE SetCallback( ISampleGrabberCB *pCallback, long WhichMethodToCallback ) = 0;
};

static const IID IID_ISampleGrabber = { 0x6B652FFF, 0x11FE, 0x4fce, { 0x92, 0xAD, 0x02, 0x66, 0xB5, 0xD7, 0xC7, 0x8F } };
static const CLSID CLSID_SampleGrabber = { 0xC1F400A0, 0x3F08, 0x11d3, { 0x9F, 0x0B, 0x00, 0x60, 0x08, 0x03, 0x9E, 0x37 } };
static const CLSID CLSID_NullRenderer = { 0xC1F400A4, 0x3F08, 0x11d3, { 0x9F, 0x0B, 0x00, 0x60, 0x08, 0x03, 0x9E, 0x37 } };
static const CLSID CLSID_VideoEffects1Category = { 0xcc7bfb42, 0xf175, 0x11d1, { 0xa3, 0x92, 0x0, 0xe0, 0x29, 0x1f, 0x39, 0x59 } };
static const CLSID CLSID_VideoEffects2Category = { 0xcc7bfb43, 0xf175, 0x11d1, { 0xa3, 0x92, 0x0, 0xe0, 0x29, 0x1f, 0x39, 0x59 } };
static const CLSID CLSID_AudioEffects1Category = { 0xcc7bfb44, 0xf175, 0x11d1, { 0xa3, 0x92, 0x0, 0xe0, 0x29, 0x1f, 0x39, 0x59 } };
static const CLSID CLSID_AudioEffects2Category = { 0xcc7bfb45, 0xf175, 0x11d1, { 0xa3, 0x92, 0x0, 0xe0, 0x29, 0x1f, 0x39, 0x59 } };

#endif


class CSampleGrabberCallback : public ISampleGrabberCB
{
public:
    STDMETHODIMP_(ULONG) AddRef()
	{
		return 1;
	}

    STDMETHODIMP_(ULONG) Release()
	{
		return 2;
	}

    STDMETHODIMP QueryInterface(REFIID riid, void **ppvObject)
    {
        if (NULL == ppvObject)
			return E_POINTER;

        if (riid == __uuidof(IUnknown))
        {
            *ppvObject = static_cast<IUnknown*>(this);
			AddRef();
             return S_OK;
        }

        if (riid == IID_ISampleGrabberCB)
        {
            *ppvObject = static_cast<ISampleGrabberCB*>(this);
			AddRef();
             return S_OK;
        }

        return E_NOTIMPL;
    }

    STDMETHODIMP SampleCB(double SampleTime, IMediaSample *pSample)
    {
		FilterSample(SampleTime, pSample);
        return S_OK;
    }

    STDMETHODIMP BufferCB(double SampleTime, BYTE *pBuffer, long BufferLen)
    {
        return S_OK;    
    }

public:
	CSampleGrabberCallback(void);
	CSampleGrabberCallback(HWND hWnd, LPBYTE *ppSampleBuffer);
	~CSampleGrabberCallback(void);

protected:
	HWND m_hWnd;
	HDC m_hDC;
	LPBYTE *m_ppSampleBuffer;
	long m_lWidth;
	long m_lHeight;
	long m_lLeftPos;
	long m_lTopPos;
	VIDEOINFOHEADER *m_pVih;
	LRESULT CALLBACK m_pFilterProc;
	LPVOID m_pFilterParam;
	CViroVisionFilters *m_pViroVisionFilters;	

protected:
	void FilterSample(double SampleTime, IMediaSample *pSample);

public:
	void SetParams(LRESULT CALLBACK lpFilterProc, long lLeftPos, long lTopPos,
		long lWidth, long lHeight, VIDEOINFOHEADER *pVih,
		LPVOID lpFilterParam = NULL, CViroVisionFilters *lpViroVisionFilters = NULL);
};

class CViroVisionBase
{
protected:
	HINSTANCE	m_hInstance;
	HWND	m_hWnd;	
	ICaptureGraphBuilder2	*m_pCaptureGraphBuilder;
	IGraphBuilder	*m_pFilterGraph;
	IVideoWindow	*m_pVideoWindow;
	IBasicVideo	*m_pBasicVideo;
	IMediaControl	*m_pMediaControl;
	IMediaEventEx	*m_pMediaEvent;
	IBaseFilter	*m_pCaptureFilter;
	IBaseFilter	*m_pRenderFilter;
	ISampleGrabber	*m_pSampleGrabber;
	IBaseFilter	*m_pSampleGrabberFilter;    
	IBaseFilter	*m_pNullRendererFilter;
	CSampleGrabberCallback	*m_pSampleGrabberCallback;	
	LPTSTR	m_ptcsErrorMsgBuff;
	DWORD	m_dwLastError;	
	
protected:
	void ClearBuffer(LPVOID &lpBuff);
	virtual void CleanUp(void);	

	void SetWnd(HWND hWnd);
	HRESULT CreateInterfaces(void);	
	HRESULT SetupVideoWindow(void);

public:
	LPBYTE m_pSampleBuffer;
	long m_lWidth;
	long m_lHeight;
	long m_lLeftPos;
	long m_lTopPos;
	long m_lPixelsCount;
	VIDEOINFOHEADER *m_pVih;

public:
	CViroVisionBase(void);
	~CViroVisionBase(void);

	virtual void Clear(void);
	DWORD _GetLastError(void);

	HRESULT CaptureVideo(HWND hWnd);
	HRESULT RenderVideo(HWND hWnd, LPCTSTR lptcsRenderFilePath);
	HRESULT FilterVideo(HWND hWnd, LRESULT CALLBACK lpFilterProc,
		LPVOID lpFilterParam = NULL, CViroVisionFilters *lpViroVisionFilters = NULL);
	HRESULT FindFirstCaptureDevice(IBaseFilter **ppSrcFilter);
	void ResizeVideoWindow(void);
	HRESULT HandleGraphEvent(void);
};

}

#endif