#pragma once

// Сформированные компьютером классы-оболочки IDispatch, созданные при помощи Microsoft Visual C++

// Примечание. Не изменяйте содержимое этого файла. При повторном создании этого класса
// в Microsoft Visual C++ изменения будут перезаписаны.

/////////////////////////////////////////////////////////////////////////////

#include "afxwin.h"

class CACTIVEXREPORTVIEWER1 : public CWnd
{
protected:
	DECLARE_DYNCREATE(CACTIVEXREPORTVIEWER1)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= {0x645fe3fb, 0x6922, 0x4ef3, {0x9e, 0x21, 0x5a, 0x11, 0x76, 0xca, 0x12, 0xba}};
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
enum CRLoadingType
{
	crLoadingNothing = 0,
	crLoadingPages = 1,
	crLoadingTotaller = 2,
	crLoadingQueryInfo = 3,
	crLoadingResourceCab = 4
};

enum CRDrillType
{
	crDrillOnGroup = 0,
	crDrillOnGroupTree = 1,
	crDrillOnGraph = 2,
	crDrillOnMap = 3,
	crDrillOnSubreport = 4
};

enum CRTrackCursor
{
	crDefaultCursor = 0,
	crArrowCursor = 1,
	crCrossCursor = 2,
	crIBeamCursor = 3,
	crNoCursor = 10,
	crWaitCursor = 11,
	crAppStartingCursor = 12,
	crHelpCursor = 13,
	crMagnifyCursor = 99
};

enum CRFieldType
{
	crInt8 = 0,
	crInt16 = 1,
	crInt32 = 2,
	crNumber = 3,
	crCurrency = 4,
	crBoolean = 5,
	crDate = 6,
	crTime = 7,
	crDateTime = 8,
	crString = 9,
	crUnknownFieldType = 255
};

enum CRObjectType
{
	crUnknownFieldDefType = 0,
	crDatabaseFieldType = 1,
	crOLAPDimensionFieldType = 2,
	crOLAPDataFieldType = 3,
	crOLAPCrossTabFieldType = 4,
	crFormulaFieldType = 5,
	crSummaryFieldType = 6,
	crSpecialVarFieldType = 7,
	crGroupNameFieldType = 8,
	crPromptingVarFieldType = 9,
	crText = 100,
	crOLEObject = 101,
	crSubreport = 102,
	crBitmap = 103,
	crBlob = 104,
	crLine = 105,
	crBox = 106,
	crGroupChart = 107,
	crCrosstabChart = 108,
	crDetailChart = 109,
	crCrossTab = 110,
	crGraphic = 111,
	crOOPSubreport = 112,
	crOLAPChart = 113,
	crGroupMap = 114,
	crCrosstabMap = 115,
	crDetailMap = 116,
	crOLAPMap = 117,
	crGroupHeaderSection = 200,
	crGroupFooterSection = 201,
	crDetailSection = 202,
	crReportHeaderSection = 203,
	crReportFooterSection = 204,
	crPageHeaderSection = 205,
	crPageFooterSection = 206
};



// Операции
public:
// ICrystalReportViewer12

// Функции
//

	LPUNKNOWN get_ReportSource()
	{
		LPUNKNOWN result;
		InvokeHelper(0xFA, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, nullptr);
		return result;
	}

	void put_ReportSource(LPUNKNOWN newValue)
	{
		static BYTE parms[] = VTS_UNKNOWN;
		InvokeHelper(0xFA, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_DisplayGroupTree()
	{
		BOOL result;
		InvokeHelper(0xFB, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_DisplayGroupTree(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xFB, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_DisplayToolbar()
	{
		BOOL result;
		InvokeHelper(0xFC, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_DisplayToolbar(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xFC, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_EnableGroupTree()
	{
		BOOL result;
		InvokeHelper(0xFD, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnableGroupTree(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xFD, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_EnableNavigationControls()
	{
		BOOL result;
		InvokeHelper(0xFE, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnableNavigationControls(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xFE, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_EnableStopButton()
	{
		BOOL result;
		InvokeHelper(0xFF, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnableStopButton(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0xFF, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_EnablePrintButton()
	{
		BOOL result;
		InvokeHelper(0x100, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnablePrintButton(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x100, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_EnableZoomControl()
	{
		BOOL result;
		InvokeHelper(0x101, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnableZoomControl(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x101, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_EnableCloseButton()
	{
		BOOL result;
		InvokeHelper(0x102, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnableCloseButton(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x102, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_EnableProgressControl()
	{
		BOOL result;
		InvokeHelper(0x103, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnableProgressControl(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x103, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_EnableSearchControl()
	{
		BOOL result;
		InvokeHelper(0x104, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnableSearchControl(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x104, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_EnableRefreshButton()
	{
		BOOL result;
		InvokeHelper(0x105, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnableRefreshButton(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x105, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_EnableDrillDown()
	{
		BOOL result;
		InvokeHelper(0x106, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnableDrillDown(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x106, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_EnableAnimationCtrl()
	{
		BOOL result;
		InvokeHelper(0x107, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnableAnimationCtrl(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x107, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_EnableSelectExpertButton()
	{
		BOOL result;
		InvokeHelper(0x108, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnableSelectExpertButton(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x108, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	void ViewReport()
	{
		InvokeHelper(0x109, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	BOOL get_EnableToolbar()
	{
		BOOL result;
		InvokeHelper(0x154, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnableToolbar(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x154, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_DisplayBorder()
	{
		BOOL result;
		InvokeHelper(0x155, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_DisplayBorder(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x155, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_DisplayTabs()
	{
		BOOL result;
		InvokeHelper(0x156, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_DisplayTabs(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x156, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_DisplayBackgroundEdge()
	{
		BOOL result;
		InvokeHelper(0x157, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_DisplayBackgroundEdge(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x157, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	CString get_SelectionFormula()
	{
		CString result;
		InvokeHelper(0x158, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, nullptr);
		return result;
	}

	void put_SelectionFormula(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x158, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	LPDISPATCH get_TrackCursorInfo()
	{
		LPDISPATCH result;
		InvokeHelper(0x159, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, nullptr);
		return result;
	}

	short get_ActiveViewIndex()
	{
		short result;
		InvokeHelper(0x15A, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}

	short get_ViewCount()
	{
		short result;
		InvokeHelper(0x15B, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, nullptr);
		return result;
	}

	void ActivateView(VARIANT Index)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0x15C, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, &Index);
	}

	void AddView(VARIANT GroupPath)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0x15D, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, &GroupPath);
	}

	void CloseView(VARIANT Index)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0x15E, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, &Index);
	}

	VARIANT GetViewPath(short Index)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0x15F, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Index);
		return result;
	}

	void PrintReport()
	{
		InvokeHelper(0x160, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	void Refresh()
	{
		InvokeHelper(0x161, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	void SearchForText(LPCTSTR Text)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x162, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, Text);
	}

	void ShowFirstPage()
	{
		InvokeHelper(0x163, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	void ShowNextPage()
	{
		InvokeHelper(0x164, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	void ShowPreviousPage()
	{
		InvokeHelper(0x165, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	void ShowLastPage()
	{
		InvokeHelper(0x166, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}

	void ShowNthPage(short PageNumber)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0x167, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, PageNumber);
	}

	void Zoom(short ZoomLevel)
	{
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0x168, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, ZoomLevel);
	}

	long GetCurrentPageNumber()
	{
		long result;
		InvokeHelper(0x169, DISPATCH_METHOD, VT_I4, (void*)&result, nullptr);
		return result;
	}

	void ShowGroup(VARIANT GroupPath)
	{
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0x16A, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, &GroupPath);
	}

	BOOL get_IsBusy()
	{
		BOOL result;
		InvokeHelper(0x16B, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	BOOL get_EnablePopupMenu()
	{
		BOOL result;
		InvokeHelper(0x16C, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnablePopupMenu(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x16C, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_EnableExportButton()
	{
		BOOL result;
		InvokeHelper(0x16D, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnableExportButton(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x16D, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_EnableSearchExpertButton()
	{
		BOOL result;
		InvokeHelper(0x16F, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnableSearchExpertButton(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x16F, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	void SearchByFormula(LPCTSTR formula)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x170, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, formula);
	}

	CString GetViewName(BSTR * pTabName)
	{
		CString result;
		static BYTE parms[] = VTS_PBSTR;
		InvokeHelper(0x171, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, pTabName);
		return result;
	}

	BOOL get_EnableHelpButton()
	{
		BOOL result;
		InvokeHelper(0x172, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnableHelpButton(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x172, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	VARIANT GetGroup()
	{
		VARIANT result;
		InvokeHelper(0x190, DISPATCH_METHOD, VT_VARIANT, (void*)&result, nullptr);
		return result;
	}

	void GetLastPageNumber(long * pageN, BOOL * lastPageKnown)
	{
		static BYTE parms[] = VTS_PI4 VTS_PBOOL;
		InvokeHelper(0x191, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, pageN, lastPageKnown);
	}

	void RefreshEx(BOOL refreshServerData)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x192, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, refreshServerData);
	}

	BOOL get_LaunchHTTPHyperlinksInNewBrowser()
	{
		BOOL result;
		InvokeHelper(0x1F4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_LaunchHTTPHyperlinksInNewBrowser(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x1F4, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_EnableLogonPrompts()
	{
		BOOL result;
		InvokeHelper(0x258, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnableLogonPrompts(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x258, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	unsigned long get_LocaleID()
	{
		unsigned long result;
		InvokeHelper(0x259, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, nullptr);
		return result;
	}

	void put_LocaleID(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4;
		InvokeHelper(0x259, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	BOOL get_EnableInteractiveParameterPrompting()
	{
		BOOL result;
		InvokeHelper(0x25A, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, nullptr);
		return result;
	}

	void put_EnableInteractiveParameterPrompting(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL;
		InvokeHelper(0x25A, DISPATCH_PROPERTYPUT, VT_EMPTY, nullptr, parms, newValue);
	}

	void DownloadResourceCab(LPCTSTR ResourceVersion)
	{
		static BYTE parms[] = VTS_BSTR;
		InvokeHelper(0x10A, DISPATCH_METHOD, VT_EMPTY, nullptr, parms, ResourceVersion);
	}



};
