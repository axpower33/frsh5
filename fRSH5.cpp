// fRSH5.cpp: определяет поведение классов для приложения.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "fRSH5.h"
#include "MainFrm.h"
#include "stdafx.h"

#include "afxdb.h"
#include "ChildFrm.h"
#include "fRSH5Doc.h"
#include "fRSH5View.h"
#include "fRSH5.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#using <craxddrt20.dll>
#using <mscorlib.dll>
#using <System.dll>
#using <System.Windows.Forms.dll>
#using <CrystalDecisions.CrystalReports.Engine.dll>
#using <CrystalDecisions.Windows.Forms.dll>
#using <System.Data.dll>
#using <System.Xml.dll>
#using <Microsoft.ReportViewer.WinForms.dll>
CComPtr<IWMPPlayer> m_pWMPPlayer;
using namespace System::Data::SqlClient;
using namespace System;
using namespace System::Data;
using namespace System::Windows;
using namespace System::Windows::Forms;
using namespace CrystalDecisions::CrystalReports::Engine;
using namespace System::Data::SqlTypes;
using namespace CrystalDecisions::Windows::Forms;
using namespace Microsoft::Reporting::WinForms;
using namespace CRAXDDRT20;

CFrModInCndDlg FrModInCndDlg;
CString strta, strNpat;
CDisplay_CrystalrptDlg CrystalrptDlg;
CReportDlg pRepDlg1;
CReportDlg2 pRepDlg2;

// CfRSH5App
/////////////////////////////////////////////////////////////////////////////
// CDisplay_CrystalrptDlg dialog
;
IMPLEMENT_DYNAMIC(CReportDlg2, CDialogEx);

BEGIN_MESSAGE_MAP(CReportDlg2, CDialogEx)
	//{{AFX_MSG_MAP(CReportDlg2)

	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_DISPLAY1, OnDisplay1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CReportDlg2::RegisterWindowClass()
{
	WNDCLASS wndcls;
	//AfxMessageBox(_T("Свойства3...."));
	HINSTANCE hInst = GetModuleHandle(NULL);
	if (!(::GetClassInfo(hInst, CACTIVEXREPORTVIEWER2_CLASSNAME, &wndcls)))
	{
		wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc = ::DefWindowProc;
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
		wndcls.hInstance = hInst;
		wndcls.hIcon = NULL;
		wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
		wndcls.lpszMenuName = NULL;
		wndcls.lpszClassName = CACTIVEXREPORTVIEWER2_CLASSNAME;

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}

CReportDlg2::CReportDlg2() noexcept : CDialogEx(IDD_DIALOG2)
{
	RegisterWindowClass();
	////{{AFX_DATA_INIT(CReportDlg2)
	////}}AFX_DATA_INIT
	//// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CReportDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	//DDX_Control(pDX, IDC_ACTIVEXREPORTVIEWER1, mCRView1);

	DDX_Control(pDX, IDC_ACTIVEXREPORTVIEWER1, mCRView1);
}

void CReportDlg2::PreSubclassWindow()
{
	CWnd::PreSubclassWindow();
}
/////////////////////////////////////////////////////////////////////////////
// CReportDlg2 message handlers

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CReportDlg2::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		//dc.DrawIcon(x, y, cxIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CReportDlg2::OnQueryDragIcon()
{
	return (HCURSOR)SM_CXICON;
}


BOOL CReportDlg2::OnInitDialog()
{
	CDialog::OnInitDialog();
	String^ pStr = "Data Source = (LocalDB)\\MSSQLLocalDB; AttachDbFilename = ""C:\\USERS\\AXPOWER\\SOURCE\\REPOS\\FRSH5\\FRSH5\\FRACTALS.MDF""; Integrated Security = True; Connect Timeout = 60";
	SqlConnection^ cn = gcnew SqlConnection(pStr);
	cn->Open();
	String^ SqlString1= "SELECT X,Y,Z FROM FRSP";
	DataSet^ ds = gcnew DataSet();
	SqlDataAdapter^ da = gcnew SqlDataAdapter(SqlString1,cn);
	DataTable^ dt = gcnew DataTable();

	da->Fill(ds);
	dt = ds->Tables[0]; 

	IReportPtr m_pReport;
	IApplicationPtr m_pApp;

	m_pApp.CreateInstance(_T("CrystalRuntime.Application.11.0"), NULL, CLSCTX_INPROC_SERVER);
	CString m_sReportPath=L"C:\\Users\\axpower\\source\\repos\\WindowsFormsApp8\\WindowsFormsApp8\\CrystalReport1.rpt"
	m_pReport = m_pApp->OpenReport((_bstr_t)m_sReportPath);
	mCRView1.put_ReportSource(m_pReport);
	mCRView1.ViewReport();

	//ReportDocument^ pRep = gcnew ReportDocument();
	//CrystalReportViewer^ pReportViewer1 = gcnew CrystalReportViewer();
	//pRep->Load("C:\\Users\\axpower\\source\\repos\\WindowsFormsApp8\\WindowsFormsApp8\\CrystalReport1.rpt");
	//pRep->SetDataSource(dt);

	//mCRView1.put_ReportSource(pRep);
	//mCRView1.ViewReport();

	
	return TRUE;
}
BOOL CReportDlg2::Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle /*=WS_VISIBLE*/)
{
	return CWnd::Create(CACTIVEXREPORTVIEWER2_CLASSNAME, _T(""), dwStyle, rect, pParentWnd, nID);

}

void CReportDlg2::OnCrystalDlg2()
{
	pRepDlg2.DoModal();
}

IMPLEMENT_DYNAMIC(CReportDlg, CDialogEx);

BEGIN_MESSAGE_MAP(CReportDlg, CDialogEx)
	//{{AFX_MSG_MAP(CReportDlg)

	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_DISPLAY1, OnDisplay1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CReportDlg::RegisterWindowClass()
{
	WNDCLASS wndcls;
	//AfxMessageBox(_T("Свойства3...."));
	HINSTANCE hInst= GetModuleHandle(NULL);
	if (!(::GetClassInfo(hInst, CACTIVEXREPORTVIEWER1_CLASSNAME, &wndcls)))
	{
		wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc = ::DefWindowProc;
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
		wndcls.hInstance = hInst;
		wndcls.hIcon = NULL;
		wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
		wndcls.lpszMenuName = NULL;
		wndcls.lpszClassName = CACTIVEXREPORTVIEWER1_CLASSNAME;

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}
	
	return TRUE;
}

CReportDlg::CReportDlg() noexcept : CDialogEx(IDD_DIALOG3)
{
	RegisterWindowClass();
	////{{AFX_DATA_INIT(CReportDlg)
	////}}AFX_DATA_INIT
	//// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CReportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	//DDX_Control(pDX, IDC_ACTIVEXREPORTVIEWER1, mCRView1);
	DDX_Control(pDX, IDC_OCX1, pRepDlg2);
}

void CReportDlg::PreSubclassWindow()
{
	CWnd::PreSubclassWindow();
}
/////////////////////////////////////////////////////////////////////////////
// CReportDlg message handlers

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CReportDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		//dc.DrawIcon(x, y, cxIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CReportDlg::OnQueryDragIcon()
{
	return (HCURSOR)SM_CXICON;
}


BOOL CReportDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	//LPUNKNOWN pUnknown = pRepDlg2.GetControlUnknown();
	//HRESULT hr = pUnknown->QueryInterface(__uuidof(IWMPPlayer), (void**)&m_pWMPPlayer);
	//if (SUCCEEDED(hr))
	//{
		CComBSTR strMovie = _T("C:\\Video\\Clips Selena Gomez\\Selena Gomez - Back To You - 1080HD - [ VKlipe.com ].mp4");
	
		pRepDlg2.put_URL(strMovie);
	//}
	return TRUE;
}
BOOL CReportDlg::Create(CWnd* pParentWnd, const RECT& rect, UINT nID, DWORD dwStyle /*=WS_VISIBLE*/)
{
	return CWnd::Create(CACTIVEXREPORTVIEWER1_CLASSNAME, _T(""), dwStyle, rect, pParentWnd, nID);

}

void CReportDlg::OnCrystalDlg1()
{
	pRepDlg1.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDisplay_CrystalrptDlg dialog
IMPLEMENT_DYNAMIC(CDisplay_CrystalrptDlg, CDialogEx);

BEGIN_MESSAGE_MAP(CDisplay_CrystalrptDlg, CDialogEx)
	//{{AFX_MSG_MAP(CDisplay_CrystalrptDlg)
	
ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_DISPLAY1, OnDisplay1)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDisplay_CrystalrptDlg::RegisterWindowClass()
{
	/*WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();
	if (!(::GetClassInfo(hInst, CACTIVEXREPORTVIEWER1_CLASSNAME, &wndcls)))
		wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.cbClsExtra = 0;
	wndcls.hInstance = hInst;
	wndcls.hIcon = NULL;
	wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	(HBRUSH)(COLOR_3DFACE + 1);
	wndcls.lpszMenuName = NULL;
	wndcls.lpszClassName = CACTIVEXREPORTVIEWER1_CLASSNAME;
	if (!AfxRegisterClass(&wndcls)) 
	{
		AfxThrowResourceException();
		return FALSE;*/
	//}
	return TRUE;
}
CDisplay_CrystalrptDlg::CDisplay_CrystalrptDlg() noexcept : CDialogEx(IDD_DIALOG4)
{
	RegisterWindowClass();
	////{{AFX_DATA_INIT(CDisplay_CrystalrptDlg)
	////}}AFX_DATA_INIT
	//// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CDisplay_CrystalrptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, pList);
	DDX_Control(pDX, IDC_LIST2, pList2);
	DDX_Control(pDX, IDC_LIST3, pList3);
	//DDX_Control(pDX, IDC_ACTIVEXREPORTVIEWER1, mCRView1);
}

void CDisplay_CrystalrptDlg::PreSubclassWindow()
{
	CWnd::PreSubclassWindow();
}
/////////////////////////////////////////////////////////////////////////////
// CDisplay_CrystalrptDlg message handlers

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDisplay_CrystalrptDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		//dc.DrawIcon(x, y, cxIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDisplay_CrystalrptDlg::OnQueryDragIcon()
{
	return (HCURSOR)SM_CXICON;
}


BOOL CDisplay_CrystalrptDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	//Open the database
	   String ^ pStr = "Data Source = (LocalDB)\\MSSQLLocalDB; AttachDbFilename = ""C:\\USERS\\AXPOWER\\SOURCE\\REPOS\\FRSH5\\FRSH5\\FRACTALS.MDF""; Integrated Security = True; Connect Timeout = 60";
	   SqlConnection^ cn = gcnew SqlConnection(pStr);
	   cn->Open();
	   String^ SqlString = "SELECT X,Y,Z FROM FRSP";
	   
	   SqlCommand^ c3 = gcnew SqlCommand(SqlString, cn);
	   SqlDataReader^ r3 = c3->ExecuteReader();
	   while (r3->Read())
	   {
		   pList.AddString((CString)r3->GetValue(0)->ToString());
		   pList2.AddString((CString)r3->GetValue(1)->ToString());
		   pList3.AddString((CString)r3->GetValue(2)->ToString());
	   }
	   r3->Close();

	   CRect rect;
	   GetClientRect(&rect);

	   
	   //CACTIVEXREPORTVIEWER1* mCRView1 = (CACTIVEXREPORTVIEWER1*)(GetDlgItem(IDC_ACTIVEXREPORTVIEWER1));
	   //mCRView1->put_ReportSource((LPUNKNOWN)"C:\\Users\\axpower\\source\\repos\\WindowsFormsApp8\\WindowsFormsApp8\\CrystalReport1.rpt");
	
	   return TRUE;
}
BOOL CDisplay_CrystalrptDlg::Create(CWnd* pParentWnd, const RECT& rect,UINT nID,  DWORD dwStyle /*=WS_VISIBLE*/) 
{
	return CWnd::Create(CACTIVEXREPORTVIEWER1_CLASSNAME, _T(""), dwStyle, rect, pParentWnd, nID);

}

void CDisplay_CrystalrptDlg::OnCrystalDlg()
{
	CrystalrptDlg.DoModal();
}

//void CDisplay_CrystalrptDlg::OnDisplay1()
//{
//	
//	ACTIVEXREPORTVIEWER1* m_cryscontrol = (ACTIVEXREPORTVIEWER1*)(GetDlgItem(IDC_ACTIVEXREPORTVIEWER1));
//	CString str;
//	str = "";  // where Table1 and Name is a name and a field in your Database
//
//
//	m_cryscontrol->put_ReportSource((LPUNKNOWN)"Report1.rpt");
//	m_cryscontrol->ViewReport();
//
//	m_cryscontrol->UpdateData(FALSE);
//
//}

CFrModInCndDlg::CFrModInCndDlg() noexcept : CDialogEx(IDD_FrModInCnd)
{
	CDialogEx::CDialogEx();
	m_Npat = 60;
	m_dt = 2e-6;
	m_rd = 0;

}
CFrModInCndDlg::~CFrModInCndDlg()
{
	CDialogEx::~CDialogEx();
}

BOOL CFrModInCndDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	_itot_s(m_Npat, strNpat.GetBufferSetLength(4), sizeof(&strNpat), 10);
	strta.Format(_T("%lf"), m_dt);

	FrModInCndDlg.GetDlgItem(IDC_EDIT1)->SetWindowTextW((LPCTSTR)strNpat);
	FrModInCndDlg.GetDlgItem(IDC_EDIT2)->SetWindowTextW((LPCTSTR)strta);

	if (m_rd == 0)
	{
		((CButton*)FrModInCndDlg.GetDlgItem(IDC_RADIO1))->SetCheck(1);
		((CButton*)FrModInCndDlg.GetDlgItem(IDC_RADIO2))->SetCheck(0);
	}
	else
	{  
		((CButton*)FrModInCndDlg.GetDlgItem(IDC_RADIO1))->SetCheck(0);
		((CButton*)FrModInCndDlg.GetDlgItem(IDC_RADIO2))->SetCheck(1);
	}
	return TRUE;
}

void CFrModInCndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrModInCndDlg)
	DDX_Text(pDX, IDC_EDIT1, m_Npat);
	DDV_MinMaxInt(pDX, m_Npat, 2, 10000);
	DDX_Text(pDX, IDC_EDIT2, m_dt);
	DDV_MinMaxFloat(pDX,(const float) m_dt, 0, 1);
	DDX_Radio(pDX, IDC_RADIO1, m_rd);
}

void CFrModInCndDlg::OnFrMod_InCnd()
{
	FrModInCndDlg.DoModal(); 
}

void CFrModInCndDlg::OnChangeEdit1()
{
	CString strNpat;
	FrModInCndDlg.GetDlgItem(IDC_EDIT1)->GetWindowTextW(strNpat);
	int m_Npat = _tstoi(strNpat);

}

void CFrModInCndDlg::OnChangeEdit2()
{
	CString strta;
	FrModInCndDlg.GetDlgItem(IDC_EDIT2)->GetWindowTextW(strta);
	double m_dt = _tstof(strta);
}

//void CFrModInCndDlg::OnBnClickedRadio1()
//{
//	//UpdateData(true);
//	m_rd = 0;
//}
//
//void CFrModInCndDlg::OnBnClickedRadio2()
//{
//    //UpdateData(true);
//	m_rd = 1;
//}

void CFrModInCndDlg::OnCancel()
{
	OnInitDialog();
	EndDialog(IDCANCEL);
}

BEGIN_MESSAGE_MAP(CFrModInCndDlg, CDialogEx)
	//{{AFX_MSG_MAP(CFrModInCndDlg)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	//}}AFX_MSG_MAP
	//ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio1)
	//ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio2)
	ON_BN_CLICKED(IDCANCEL, OnCancel)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CfRSH5App, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CfRSH5App::OnAppAbout)
	// Стандартные команды по работе с файлами документов
	ON_COMMAND(ID_FrMod_InCnd, &CFrModInCndDlg::OnFrMod_InCnd)
	ON_COMMAND(IDD_DIALOG4, &CDisplay_CrystalrptDlg::OnCrystalDlg)
	ON_COMMAND(IDD_DIALOG3, &CReportDlg::OnCrystalDlg1)
	ON_COMMAND(IDD_DIALOG2, &CReportDlg2::OnCrystalDlg2)
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Стандартная команда настройки печати
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()

// Создание CfRSH5App

CfRSH5App::CfRSH5App() noexcept
{
	m_bHiColorIcons = TRUE;


	m_nAppLook = 0;
	// поддержка диспетчера перезагрузки
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// Если приложение построено с поддержкой среды Common Language Runtime (/clr):
	//     1) Этот дополнительный параметр требуется для правильной поддержки работы диспетчера перезагрузки.
	//   2) В своем проекте для сборки необходимо добавить ссылку на System.Windows.Forms.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: замените ниже строку идентификатора приложения строкой уникального идентификатора; рекомендуемый
	// формат для строки: ИмяКомпании.ИмяПродукта.СубПродукт.СведенияОВерсии
	SetAppID(_T("fRSH5.AppID.NoVersion"));

	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
}

// Единственный объект CfRSH5App

CfRSH5App theApp;


// Инициализация CfRSH5App
CObList m_templateList;

BOOL CfRSH5App::InitInstance()
{
	// InitCommonControlsEx() требуются для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения.  В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CDisplay_CrystalrptDlg CrystalrptDlg;
	CWinAppEx::InitInstance();
	


	// Инициализация библиотек OLE
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// Для использования элемента управления RichEdit требуется метод AfxInitRichEdit2()
	// AfxInitRichEdit2();

	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующего
	// конкретные процедуры инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры
	// TODO: следует изменить эту строку на что-нибудь подходящее,
	// например на название организации
	SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));
	LoadStdProfileSettings(4);  // Загрузите стандартные параметры INI-файла (включая MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Зарегистрируйте шаблоны документов приложения.  Шаблоны документов
	//  выступают в роли посредника между документами, окнами рамок и представлениями
	CMultiDocTemplate* pDocTemplate;

	pDocTemplate = new CMultiDocTemplate(IDR_fRSH5TYPE,
		RUNTIME_CLASS(CfRSH5Doc),
		RUNTIME_CLASS(CChildFrame), // настраиваемая дочерняя рамка MDI
		RUNTIME_CLASS(CfRSH5View));
	if (!pDocTemplate)
		return FALSE;
	else
		m_templateList.AddHead(pDocTemplate);
	AddDocTemplate(pDocTemplate);

	// создайте главное окно рамки MDI
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// Разрешить использование расширенных символов в горячих клавишах меню
	CMFCToolBar::m_bExtCharTranslation = TRUE;

	// Синтаксический разбор командной строки на стандартные команды оболочки, DDE, открытие файлов
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Команды диспетчеризации, указанные в командной строке.  Значение FALSE будет возвращено, если
	// приложение было запущено с параметром /RegServer, /Register, /Unregserver или /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// Главное окно было инициализировано, поэтому отобразите и обновите его
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	
	return TRUE;
}

int CfRSH5App::ExitInstance()
{
	//TODO: обработайте дополнительные ресурсы, которые могли быть добавлены
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// Обработчики сообщений CfRSH5App


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// Команда приложения для запуска диалога
void CfRSH5App::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// Методы загрузки или сохранения настроек CfRSH5App

void CfRSH5App::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CfRSH5App::LoadCustomState()
{
}

void CfRSH5App::SaveCustomState()
{
}

// Обработчики сообщений CfRSH5App


BOOL CfRSH5App::OnIdle(LONG lCount)
{
	  CWinAppEx::OnIdle( lCount );

	  int i = lCount;
	  
      while( i-- )
	  {
		 POSITION pos = m_templateList.GetHeadPosition();
		 
		 while (pos != NULL)
		 {  CMultiDocTemplate* pTemplate = (CMultiDocTemplate*)m_templateList.GetNext(pos);

			POSITION dPos = pTemplate->GetFirstDocPosition();
			while( dPos != NULL )
			{
				  CDocument* doc = (CDocument*)pTemplate->GetNextDoc(dPos);
				  doc->OnIdle();

				  if( i ) continue;

				  POSITION vPos = doc->GetFirstViewPosition();
				  while( vPos != NULL )
				  {
					  CView* view = (CView*)doc->GetNextView( vPos );
					  view->Invalidate( FALSE );
					  view->UpdateWindow();
				  }
			}
		}
	}
	return TRUE;
}

const CLSID CLSID_Application = { 0xb4741fd0, 0x45a6, 0x11d1, {0xab, 0xec, 0x00, 0xa0, 0xc9, 0x27, 0x4b, 0x91} };
const IID IID_IApplication = { 0x0bac5cf2, 0x44c9, 0x11d1, 0xab, 0xec, 0x00, 0xa0, 0xc9, 0x27, 0x4b, 0x91 };
const CLSID CLSID_ReportObjects = { 0xb4741e60, 0x45a6, 0x11d1, 0xab, 0xec, 0x00, 0xa0, 0xc9, 0x27, 0x4b, 0x91 };
const IID IID_IReportObjects = { 0x0bac59b2, 0x44c9, 0x11d1, 0xab, 0xec, 0x00, 0xa0, 0xc9, 0x27, 0x4b, 0x91 };

void CDisplay_CrystalrptDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{

	CDialogEx::OnShowWindow(bShow, nStatus);
	try {
		//HRESULT hr = S_OK;
		//hr = CoCreateInstance(CLSID_Application, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void**)&theApp);
	
		
		//ReportDataSource^ reportDataSource1 = gcnew ReportDataSource();
		//BindingSource^ dataTable1BindingSource = gcnew BindingSource();
		//ReportViewer^ Rep1 = gcnew ReportViewer();
		//dataTable1BindingSource->DataSource = dt;
		//reportDataSource1->Name = "fgv";
		//reportDataSource1->Value = dataTable1BindingSource;
		//Rep1->Name = "bnm";
		//Rep1->LocalReport->DataSources->Add(reportDataSource1);
		//Rep1->LocalReport->ReportEmbeddedResource = "C:\\Users\\axpower\\source\\repos\\WindowsFormsApp8\\WindowsFormsApp8\\Report1.rdlc";
		//Rep1->RefreshReport();


		//ReportDocument^ pRep = gcnew ReportDocument();
		//CrystalReportViewer^ pReportViewer1 = gcnew CrystalReportViewer();
		//
		//pRep->Load("C:\\Users\\axpower\\source\\repos\\WindowsFormsApp8\\WindowsFormsApp8\\CrystalReport1.rpt");
		//pRep->SetDataSource(dt);
		////pRep->SetParameterValue("pRep1", "Acula");
		////pRep->SetParameterValue("pRep2", "Delfin");
		////mCRView1.put_ReportSource((LPUNKNOWN)"C:\\Users\\axpower\\source\\repos\\WindowsFormsApp8\\WindowsFormsApp8\\CrystalReport1.rpt");
		////mCRView1.ViewReport();
		//pReportViewer1->ReuseParameterValuesOnRefresh = true;
		//pReportViewer1->ReportSource = pRep;
		//pReportViewer1->Refresh();
	}
	catch (const _com_error& e) {
		_bstr_t bstrSource(e.Source());
		_bstr_t bstrDescription(e.Description());
		CString strError;
		strError = L"Привет222";
		AfxMessageBox(strError);
	}
  
}