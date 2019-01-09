/////////////////////////////////////////////////////////////////////////////
// ViroVision.cpp
//
// Copyright (C) 2012 Veria Kalantary
// veria.kalantary@gmail.com
// https://github.com/veriak
//

//#include "stdafx.h"
#include "ViroVision.h"

using namespace ViroVision;

/////////////////////////////////////////////////////////////////////////////
// CSampleGrabberCallback

CSampleGrabberCallback::CSampleGrabberCallback(void)
	: m_hWnd(NULL),
	m_hDC(NULL),
	m_ppSampleBuffer(NULL),
	m_pFilterProc(NULL),
	m_pFilterParam(NULL),
	m_pViroVisionFilters(NULL),
	m_lLeftPos(0),
	m_lTopPos(0),
	m_lWidth(0),
	m_lHeight(0),
	m_pVih(NULL)
{
};

CSampleGrabberCallback::CSampleGrabberCallback(HWND hWnd, LPBYTE *ppSampleBuffer)
	: m_hWnd(hWnd),
	m_ppSampleBuffer(ppSampleBuffer),
	m_pFilterProc(NULL),
	m_pFilterParam(NULL),
	m_pViroVisionFilters(NULL),	
	m_lLeftPos(0),
	m_lTopPos(0),
	m_lWidth(0),
	m_lHeight(0),
	m_pVih(NULL)
{
	m_hDC = ::GetDC(m_hWnd);
};

CSampleGrabberCallback::~CSampleGrabberCallback(void)
{
	if ((m_hWnd != NULL) && (m_hDC != NULL))
	{
		::ReleaseDC(m_hWnd, m_hDC);
		m_hDC = NULL;
	}
};

void CSampleGrabberCallback::SetParams(LRESULT CALLBACK lpFilterProc, long lLeftPos, long lTopPos,
	long lWidth, long lHeight, VIDEOINFOHEADER *pVih,
	LPVOID lpFilterParam, CViroVisionFilters *lpViroVisionFilters)
{
	m_pFilterProc = (LRESULT CALLBACK) lpFilterProc;
	m_pFilterParam = lpFilterParam;
	m_pViroVisionFilters = lpViroVisionFilters;	
	m_lLeftPos = lLeftPos;
	m_lTopPos = lTopPos;
	m_lWidth = lWidth;
	m_lHeight = lHeight;
	m_pVih = pVih;	
}

void CSampleGrabberCallback::FilterSample(double SampleTime, IMediaSample *pSample)
{
	pSample->GetPointer(m_ppSampleBuffer);

	RGBTRIPLE *pRGBBuffer = (RGBTRIPLE *) *m_ppSampleBuffer;
	LRESULT lResult;
	DWORD dwSampleWidth = (DWORD) m_lWidth;
	DWORD dwSampleHeight = (DWORD) m_lHeight;
	DWORD dwFilterParam = (DWORD) m_pFilterParam;
	DWORD dwViroVisionFilters = (DWORD) m_pViroVisionFilters;

	if (m_pViroVisionFilters)
	{
		__asm
		{
			push dwViroVisionFilters
			push dwFilterParam
			push dwSampleHeight
			push dwSampleWidth
			push pRGBBuffer			
			mov eax, this
			call [eax].m_pFilterProc
			mov lResult, eax
		}
	}
	else
	{
		if (dwFilterParam)
		{
			__asm
			{
				push dwFilterParam
				push dwSampleHeight
				push dwSampleWidth
				push pRGBBuffer
				mov eax, this
				call [eax].m_pFilterProc
				mov lResult, eax
			}
		}
		else
		{
			__asm
			{
				push dwSampleHeight
				push dwSampleWidth
				push pRGBBuffer
				mov eax, this
				call [eax].m_pFilterProc
				mov lResult, eax
			}
		}
	}	

	::SetDIBitsToDevice(m_hDC, m_lLeftPos, m_lTopPos, m_lWidth, m_lHeight,
		0, 0, 0, m_lHeight, *m_ppSampleBuffer, (const BITMAPINFO *) &(m_pVih->bmiHeader), DIB_RGB_COLORS);	
}

/////////////////////////////////////////////////////////////////////////////
// CViroVisionBase

CViroVisionBase::CViroVisionBase(void)
{
	m_hInstance = NULL;
	m_hWnd = NULL;
	m_lWidth = 0;
	m_lHeight = 0;
	m_lLeftPos = 0;
	m_lTopPos = 0;
	m_lPixelsCount = 0;
	m_pCaptureGraphBuilder = NULL;
	m_pFilterGraph = NULL;	
	m_pVideoWindow = NULL;
	m_pBasicVideo = NULL;
	m_pMediaControl = NULL;
	m_pMediaEvent = NULL;	
	m_pCaptureFilter = NULL;
	m_pRenderFilter = NULL;
	m_pSampleGrabber = NULL;
	m_pSampleGrabberFilter = NULL;
	m_pNullRendererFilter = NULL;
	m_pSampleGrabberCallback = NULL;
	m_pSampleBuffer = NULL;
	m_ptcsErrorMsgBuff = NULL;
	m_dwLastError = 0;

	if (SUCCEEDED(::CoInitializeEx(NULL, COINIT_MULTITHREADED)))
	{
		if (SUCCEEDED(CreateInterfaces()))
		{
		}
	}
}

CViroVisionBase::~CViroVisionBase(void)
{
	Clear();
	::CoUninitialize();
}

void CViroVisionBase::Clear(void)
{	
	ClearBuffer((LPVOID &) m_ptcsErrorMsgBuff);
	CleanUp();
}

void CViroVisionBase::ClearBuffer(LPVOID &lpBuff)
{
	if (lpBuff)
	{
		free(lpBuff);
		lpBuff = NULL;
	}
}

DWORD CViroVisionBase::_GetLastError(void)
{
	return m_dwLastError;
}

void CViroVisionBase::SetWnd(HWND hWnd)
{
	m_hWnd = hWnd;
}

HRESULT CViroVisionBase::CreateInterfaces(void)
{
	HRESULT hr;	

	hr = ::CoCreateInstance(CLSID_CaptureGraphBuilder2 , NULL, CLSCTX_INPROC,
			IID_ICaptureGraphBuilder2, (LPVOID *) &m_pCaptureGraphBuilder);
	if (FAILED(hr))
		return hr;

	hr = ::CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,
			IID_IGraphBuilder, (LPVOID *) &m_pFilterGraph);
	if (FAILED(hr))
		return hr;

	hr = m_pFilterGraph->QueryInterface(IID_IMediaControl, (LPVOID *) &m_pMediaControl);
	if (FAILED(hr))
		return hr;

	hr = m_pFilterGraph->QueryInterface(IID_IVideoWindow, (LPVOID *) &m_pVideoWindow);
	if (FAILED(hr))
		return hr;

	hr = m_pFilterGraph->QueryInterface(IID_IBasicVideo, (LPVOID *) &m_pBasicVideo);
	if (FAILED(hr))
		return hr;

	hr = m_pFilterGraph->QueryInterface(IID_IMediaEventEx, (LPVOID *) &m_pMediaEvent);
	if (FAILED(hr))
		return hr;	

	return hr;
}

void CViroVisionBase::CleanUp(void)
{
	if (m_pMediaEvent)
		m_pMediaEvent->SetNotifyWindow(NULL, WM_VIROVISION_NOTIFY, 0);

	if (m_pVideoWindow)
	{
		m_pVideoWindow->put_Visible(OAFALSE);
		m_pVideoWindow->put_Owner(NULL);
	}

	if (m_pMediaControl)
		m_pMediaControl->Stop();

	LONG evCode;

	m_pMediaEvent->WaitForCompletion(INFINITE, &evCode);

	m_pFilterGraph->RemoveFilter(m_pNullRendererFilter);
	m_pFilterGraph->RemoveFilter(m_pSampleGrabberFilter);
	m_pFilterGraph->RemoveFilter(m_pCaptureFilter);

	if (m_pSampleGrabberCallback)
	{
		delete m_pSampleGrabberCallback;
		m_pSampleGrabberCallback = NULL;
	}

	if (m_pNullRendererFilter)
	{
		m_pNullRendererFilter->Release();
		m_pNullRendererFilter = NULL;
	}

	if (m_pSampleGrabberFilter)
	{
		m_pSampleGrabberFilter->Release();
		m_pSampleGrabberFilter = NULL;
	}	

	if (m_pCaptureFilter)
	{
		m_pCaptureFilter->Release();
		m_pCaptureFilter = NULL;
	}

	if (m_pRenderFilter)
	{
		m_pRenderFilter->Release();
		m_pRenderFilter = NULL;
	}

	if (m_pMediaEvent)
	{
		m_pMediaEvent->Release();
		m_pMediaEvent = NULL;
	}

	if (m_pBasicVideo)
	{
		m_pBasicVideo->Release();
		m_pBasicVideo = NULL;
	}

	if (m_pVideoWindow)
	{
		m_pVideoWindow->Release();
		m_pVideoWindow = NULL;
	}

	if (m_pMediaControl)
	{
		m_pMediaControl->Release();
		m_pMediaControl = NULL;
	}

	if (m_pFilterGraph)
	{
		m_pFilterGraph->Release();
		m_pFilterGraph = NULL;
	}

	if (m_pCaptureGraphBuilder)
	{
		m_pCaptureGraphBuilder->Release();
		m_pCaptureGraphBuilder = NULL;
	}
}

HRESULT CViroVisionBase::CaptureVideo(HWND hWnd)
{
	HRESULT hr;

	SetWnd(hWnd);

	hr = m_pMediaEvent->SetNotifyWindow((OAHWND) m_hWnd, WM_VIROVISION_NOTIFY, 0);

	hr = m_pCaptureGraphBuilder->SetFiltergraph(m_pFilterGraph);
	if (FAILED(hr))
		return hr;

	hr = FindFirstCaptureDevice(&m_pCaptureFilter);
	if (FAILED(hr))
		return hr;

	hr = m_pFilterGraph->AddFilter(m_pCaptureFilter, L"Video Capture");
	if (FAILED(hr))
	{
		m_pCaptureFilter->Release();
		return hr;
	}

	hr = m_pCaptureGraphBuilder->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,
			m_pCaptureFilter, NULL, NULL);
	if (FAILED(hr))
	{
		m_pCaptureFilter->Release();
		return hr;
	}

	hr = SetupVideoWindow();
	if (FAILED(hr))
		return hr;

	hr = m_pMediaControl->Run();
	if (FAILED(hr))
		return hr;
	  
	return S_OK;
}

HRESULT CViroVisionBase::RenderVideo(HWND hWnd, LPCTSTR lptcsRenderFilePath)
{
	HRESULT hr;

	SetWnd(hWnd);

	hr = m_pMediaEvent->SetNotifyWindow((OAHWND) m_hWnd, WM_VIROVISION_NOTIFY, 0);
	if (FAILED(hr))
		return hr;

	hr = m_pCaptureGraphBuilder->SetFiltergraph(m_pFilterGraph);
	if (FAILED(hr))
		return hr;

	hr = FindFirstCaptureDevice(&m_pCaptureFilter);
	if (FAILED(hr))
		return hr;

	hr = m_pFilterGraph->AddFilter(m_pCaptureFilter, L"Video Capture");
	if (FAILED(hr))
	{
		m_pCaptureFilter->Release();
		return hr;
	}
	
	hr = m_pCaptureGraphBuilder->RenderStream (&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,
			m_pCaptureFilter, NULL, NULL);
	if (FAILED(hr))
	{
		m_pCaptureFilter->Release();
		return hr;
	}

	hr = SetupVideoWindow();
	if (FAILED(hr))
		return hr;

	m_pCaptureGraphBuilder->SetOutputFileName(&MEDIASUBTYPE_Avi, (LPCOLESTR) lptcsRenderFilePath,
			&m_pRenderFilter, NULL);
	if (FAILED(hr))
		return hr;

    m_pCaptureGraphBuilder->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video,
			m_pCaptureFilter, NULL, m_pRenderFilter);
	if (FAILED(hr))
		return hr;

	hr = m_pMediaControl->Run();
	if (FAILED(hr))
		return hr;
	  
	return S_OK;
}

HRESULT CViroVisionBase::FindFirstCaptureDevice(IBaseFilter **ppSrcFilter)
{
	HRESULT hr = S_OK;
	IBaseFilter *pSrcFilter = NULL;
	IMoniker *pMoniker =NULL;
	ICreateDevEnum *pDevEnum =NULL;
	IEnumMoniker *pClassEnum = NULL;

	if (!ppSrcFilter)
	{
		return E_POINTER;
	}

	hr = ::CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC,
		IID_ICreateDevEnum, (LPVOID *) &pDevEnum);

	if (SUCCEEDED(hr))
	{
		hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pClassEnum, 0);
	}

	if (SUCCEEDED(hr))
	{
		if (pClassEnum == NULL)
			hr = E_FAIL;
	}

	if (SUCCEEDED(hr))
	{
		hr = pClassEnum->Next(1, &pMoniker, NULL);
		if (hr == S_FALSE)
			hr = E_FAIL;
	}

	if (SUCCEEDED(hr))
		hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (LPVOID *) &pSrcFilter);

	if (SUCCEEDED(hr))
	{
		*ppSrcFilter = pSrcFilter;
		pSrcFilter->AddRef();
	}

	if (pSrcFilter)
	{
		pSrcFilter->Release();
		pSrcFilter = NULL;
	}

	if (pMoniker)
	{
		pMoniker->Release();
		pMoniker = NULL;
	}

	if (pClassEnum)
	{
		pClassEnum->Release();
		pClassEnum = NULL;
	}

	if (pDevEnum)
	{
		pDevEnum->Release();
		pDevEnum = NULL;
	}

	return hr;
}

HRESULT CViroVisionBase::SetupVideoWindow(void)
{
    HRESULT hr;

    hr = m_pVideoWindow->put_Owner((OAHWND) m_hWnd);
    if (FAILED(hr))
        return hr;
    
    hr = m_pVideoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
    if (FAILED(hr))
        return hr;

    ResizeVideoWindow();

    hr = m_pVideoWindow->put_Visible(OATRUE);
    if (FAILED(hr))
        return hr;

    return hr;
}


void CViroVisionBase::ResizeVideoWindow(void)
{	
    if (m_pVideoWindow)
    {
        RECT rcClient;
		long lWidth = 0;
		long lHeight = 0;
     
		m_pBasicVideo->GetVideoSize(&lWidth, &lHeight);
		::GetClientRect(m_hWnd, &rcClient);

		long lLeftPos = (rcClient.right - lWidth) / 2;
		long lTopPos = (rcClient.bottom - lHeight) / 2;

		m_pVideoWindow->SetWindowPosition(
			(lLeftPos > 0) ? lLeftPos : 0, (lTopPos > 0) ? lTopPos : 0,	lWidth, lHeight);
    }
}

HRESULT CViroVisionBase::HandleGraphEvent(void)
{
	LONG evCode;
	LONG_PTR evParam1, evParam2;
	HRESULT hr = S_OK;

	if (!m_pMediaEvent)
		return E_POINTER;

	while (SUCCEEDED(m_pMediaEvent->GetEvent(&evCode, &evParam1, &evParam2, 0)))
	{
		hr = m_pMediaEvent->FreeEventParams(evCode, evParam1, evParam2);
	    
		if ((evCode == EC_COMPLETE) || (evCode == EC_USERABORT))
			CleanUp();
	}

	return hr;
}

HRESULT CViroVisionBase::FilterVideo(HWND hWnd, LRESULT CALLBACK lpFilterProc,
	LPVOID lpFilterParam, CViroVisionFilters *lpViroVisionFilters)
{
	HRESULT hr;

	SetWnd(hWnd);

	hr = m_pMediaEvent->SetNotifyWindow((OAHWND) m_hWnd, WM_VIROVISION_NOTIFY, 0);

	hr = m_pCaptureGraphBuilder->SetFiltergraph(m_pFilterGraph);
	if (FAILED(hr))
		return hr;

	hr = FindFirstCaptureDevice(&m_pCaptureFilter);
	if (FAILED(hr))
		return hr;

	hr = m_pFilterGraph->AddFilter(m_pCaptureFilter, L"Video Capture");
	if (FAILED(hr))
	{
		m_pCaptureFilter->Release();
		return hr;
	}	

	hr = ::CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC,
			IID_ISampleGrabber, (LPVOID *) &m_pSampleGrabber);
	if (FAILED(hr))
		return hr;

	hr = m_pSampleGrabber->QueryInterface(IID_IBaseFilter, (LPVOID *) &m_pSampleGrabberFilter);
	if (FAILED(hr))
		return hr;

	hr = m_pFilterGraph->AddFilter(m_pSampleGrabberFilter, L"Sample Grabber");
	if (FAILED(hr))
		return hr;	

	hr = m_pSampleGrabber->SetOneShot(FALSE);
	if (FAILED(hr))
		return hr;

	hr = m_pSampleGrabber->SetBufferSamples(FALSE);
	if (FAILED(hr))
		return hr;

	m_pSampleGrabberCallback = new CSampleGrabberCallback(m_hWnd, &m_pSampleBuffer);

	hr = m_pSampleGrabber->SetCallback(m_pSampleGrabberCallback, 0);
	if (FAILED(hr))
		return hr;

	hr = ::CoCreateInstance(CLSID_NullRenderer, NULL, CLSCTX_INPROC,
		IID_IBaseFilter, (LPVOID *) &m_pNullRendererFilter);
	if (FAILED(hr))
		return hr;

	hr = m_pFilterGraph->AddFilter(m_pNullRendererFilter, L"Null Renderer");
	if (FAILED(hr))
		return hr;						
	
	AM_MEDIA_TYPE mt;

	memset(&mt, 0, sizeof(AM_MEDIA_TYPE));
	mt.majortype = MEDIATYPE_Video;
	mt.subtype = MEDIASUBTYPE_RGB24;
	hr = m_pSampleGrabber->SetMediaType(&mt);
	if (FAILED(hr))
		return hr;
	
	hr = m_pCaptureGraphBuilder->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,
			m_pCaptureFilter, m_pSampleGrabberFilter, m_pNullRendererFilter);
	if (FAILED(hr))
		return hr;
	
	memset(&mt, 0, sizeof(AM_MEDIA_TYPE));
	hr = m_pSampleGrabber->GetConnectedMediaType(&mt);
	if (FAILED(hr))
		return hr;

	if ((mt.formattype == FORMAT_VideoInfo) && (mt.cbFormat >= sizeof(VIDEOINFOHEADER)) &&
		(mt.pbFormat != NULL))
	{
		m_pVih = (VIDEOINFOHEADER *) mt.pbFormat;
	}
	else 
	{
		return VFW_E_INVALIDMEDIATYPE;
	}

	RECT rcClient;	
 	
	::GetClientRect(m_hWnd, &rcClient);

	m_lWidth = m_pVih->bmiHeader.biWidth;
	m_lHeight = m_pVih->bmiHeader.biHeight;
	m_lPixelsCount = m_lWidth * m_lHeight;
	m_lLeftPos = (rcClient.right - m_lWidth) / 2;
	m_lTopPos = (rcClient.bottom - m_lHeight) / 2;

	m_pSampleGrabberCallback->SetParams(lpFilterProc,
		m_lLeftPos, m_lTopPos, m_lWidth, m_lHeight, m_pVih,
		lpFilterParam, lpViroVisionFilters);

	hr = m_pMediaControl->Run();
	if (FAILED(hr))
		return hr;
	  
	return S_OK;
}