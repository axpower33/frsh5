#pragma once

// Сформированные компьютером классы-оболочки IDispatch, созданные при помощи Microsoft Visual C++

// Примечание. Не изменяйте содержимое этого файла. При повторном создании этого класса
// в Microsoft Visual C++ изменения будут перезаписаны.

/////////////////////////////////////////////////////////////////////////////

#include "afxwin.h"

class COCX1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(COCX1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= {0x6bf52a52, 0x394a, 0x11d3, {0xb1, 0x53, 0x00, 0xc0, 0x4f, 0x79, 0xfa, 0xa6}};
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = nullptr)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID);
	}

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
				UINT nID, CFile* pPersist = nullptr, BOOL bStorage = FALSE,
				BSTR bstrLicKey = nullptr)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// Атрибуты
public:
enum WMPPlaylistChangeEventType
{
	wmplcUnknown = 0,
	wmplcClear = 1,
	wmplcInfoChange = 2,
	wmplcMove = 3,
	wmplcDelete = 4,
	wmplcInsert = 5,
	wmplcAppend = 6,
	wmplcPrivate = 7,
	wmplcNameChange = 8,
	wmplcMorph = 9,
	wmplcSort = 10,
	wmplcLast = 11
};

enum WMPDeviceStatus
{
	wmpdsUnknown = 0,
	wmpdsPartnershipExists = 1,
	wmpdsPartnershipDeclined = 2,
	wmpdsPartnershipAnother = 3,
	wmpdsManualDevice = 4,
	wmpdsNewDevice = 5,
	wmpdsLast = 6
};

enum WMPSyncState
{
	wmpssUnknown = 0,
	wmpssSynchronizing = 1,
	wmpssStopped = 2,
	wmpssEstimating = 3,
	wmpssLast = 4
};

enum WMPRipState
{
	wmprsUnknown = 0,
	wmprsRipping = 1,
	wmprsStopped = 2
};

enum WMPBurnFormat
{
	wmpbfAudioCD = 0,
	wmpbfDataCD = 1
};

enum WMPBurnState
{
	wmpbsUnknown = 0,
	wmpbsBusy = 1,
	wmpbsReady = 2,
	wmpbsWaitingForDisc = 3,
	wmpbsRefreshStatusPending = 4,
	wmpbsPreparingToBurn = 5,
	wmpbsBurning = 6,
	wmpbsStopped = 7,
	wmpbsErasing = 8,
	wmpbsDownloading = 9
};

enum WMPLibraryType
{
	wmpltUnknown = 0,
	wmpltAll = 1,
	wmpltLocal = 2,
	wmpltRemote = 3,
	wmpltDisc = 4,
	wmpltPortableDevice = 5
};

enum WMPFolderScanState
{
	wmpfssUnknown = 0,
	wmpfssScanning = 1,
	wmpfssUpdating = 2,
	wmpfssStopped = 3
};

enum WMPStringCollectionChangeEventType
{
	wmpsccetUnknown = 0,
	wmpsccetInsert = 1,
	wmpsccetChange = 2,
	wmpsccetDelete = 3,
	wmpsccetClear = 4,
	wmpsccetBeginUpdates = 5,
	wmpsccetEndUpdates = 6
};

enum WMPOpenState
{
	wmposUndefined = 0,
	wmposPlaylistChanging = 1,
	wmposPlaylistLocating = 2,
	wmposPlaylistConnecting = 3,
	wmposPlaylistLoading = 4,
	wmposPlaylistOpening = 5,
	wmposPlaylistOpenNoMedia = 6,
	wmposPlaylistChanged = 7,
	wmposMediaChanging = 8,
	wmposMediaLocating = 9,
	wmposMediaConnecting = 10,
	wmposMediaLoading = 11,
	wmposMediaOpening = 12,
	wmposMediaOpen = 13,
	wmposBeginCodecAcquisition = 14,
	wmposEndCodecAcquisition = 15,
	wmposBeginLicenseAcquisition = 16,
	wmposEndLicenseAcquisition = 17,
	wmposBeginIndividualization = 18,
	wmposEndIndividualization = 19,
	wmposMediaWaiting = 20,
	wmposOpeningUnknownURL = 21
};

enum WMPPlayState
{
	wmppsUndefined = 0,
	wmppsStopped = 1,
	wmppsPaused = 2,
	wmppsPlaying = 3,
	wmppsScanForward = 4,
	wmppsScanReverse = 5,
	wmppsBuffering = 6,
	wmppsWaiting = 7,
	wmppsMediaEnded = 8,
	wmppsTransitioning = 9,
	wmppsReady = 10,
	wmppsReconnecting = 11,
	wmppsLast = 12
};

enum WMPSubscriptionDownloadState
{
	wmpsdlsDownloading = 0,
	wmpsdlsPaused = 1,
	wmpsdlsProcessing = 2,
	wmpsdlsCompleted = 3,
	wmpsdlsCancelled = 4
};

enum WMP_WRITENAMESEX_TYPE
{
	WMP_WRITENAMES_TYPE_CD_BY_TOC = 0,
	WMP_WRITENAMES_TYPE_CD_BY_CONTENT_ID = 1,
	WMP_WRITENAMES_TYPE_CD_BY_MDQCD = 2,
	WMP_WRITENAMES_TYPE_DVD_BY_DVDID = 3
};



// Операции
public:
// IWMPPlayer4

// Функции
//

	void close()
	{
		InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	CString get_URL()
	{
		CString result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}

	void put_URL(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	long get_openState()
	{
		long result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	long get_playState()
	{
		long result;
		InvokeHelper(0xA, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, nullptr);
		return result;
	}

	LPDISPATCH get_controls()
	{
		LPDISPATCH result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	LPDISPATCH get_settings()
	{
		LPDISPATCH result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	LPDISPATCH get_currentMedia()
	{
		LPDISPATCH result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	void put_currentMedia(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	LPDISPATCH get_mediaCollection()
	{
		LPDISPATCH result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	LPDISPATCH get_playlistCollection()
	{
		LPDISPATCH result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	CString get_versionInfo()
	{
		CString result;
		InvokeHelper(0xB, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}

	void launchURL(LPCTSTR bstrURL)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0xC, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, bstrURL);
	}

	LPDISPATCH get_network()
	{
		LPDISPATCH result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	LPDISPATCH get_currentPlaylist()
	{
		LPDISPATCH result;
		InvokeHelper(0xD, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	void put_currentPlaylist(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH;
		InvokeHelper(0xD, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	LPDISPATCH get_cdromCollection()
	{
		LPDISPATCH result;
		InvokeHelper(0xE, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	LPDISPATCH get_closedCaption()
	{
		LPDISPATCH result;
		InvokeHelper(0xF, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	BOOL get_isOnline()
	{
		BOOL result;
		InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	LPDISPATCH get_Error()
	{
		LPDISPATCH result;
		InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	CString get_status()
	{
		CString result;
		InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}

	LPDISPATCH get_dvd()
	{
		LPDISPATCH result;
		InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	LPDISPATCH newPlaylist(LPCTSTR bstrName, LPCTSTR bstrURL)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, bstrName, bstrURL);
		return result;
	}

	LPDISPATCH newMedia(LPCTSTR bstrURL)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x2A, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, bstrURL);
		return result;
	}

	BOOL get_enabled()
	{
		BOOL result;
		InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_enabled(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_fullScreen()
	{
		BOOL result;
		InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_fullScreen(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_enableContextMenu()
	{
		BOOL result;
		InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_enableContextMenu(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	void put_uiMode(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	CString get_uiMode()
	{
		CString result;
		InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}

	BOOL get_stretchToFit()
	{
		BOOL result;
		InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_stretchToFit(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_windowlessVideo()
	{
		BOOL result;
		InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_windowlessVideo(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_isRemote()
	{
		BOOL result;
		InvokeHelper(0x1A, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	LPDISPATCH get_playerApplication()
	{
		LPDISPATCH result;
		InvokeHelper(0x1B, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	void openPlayer(LPCTSTR bstrURL)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x1C, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, bstrURL);
	}



};
