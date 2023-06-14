
// fRSH5.cpp: определяет поведение классов для приложения.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "fRSH5.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "fRSH5Doc.h"
#include "fRSH5View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CFrModInCndDlg FrModInCndDlg;
CString strta, strNpat;
// CfRSH5App

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
	//_wtof(ta, strta.GetBufferSetLength(10), sizeof(&strNpat),10);
	strta.Format(_T("%lf"), m_dt);

	FrModInCndDlg.GetDlgItem(IDC_EDIT1)->SetWindowTextW((LPCTSTR)strNpat);
	FrModInCndDlg.GetDlgItem(IDC_EDIT2)->SetWindowTextW((LPCTSTR)strta);
	m_rd = 0;

	((CButton*)FrModInCndDlg.GetDlgItem(IDC_RADIO1))->SetCheck(1);
	((CButton*)FrModInCndDlg.GetDlgItem(IDC_RADIO2))->SetCheck(0);

	return TRUE;
}

void CFrModInCndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrModInCndDlg)
	DDX_Text(pDX, IDC_EDIT1, m_Npat);
	DDV_MinMaxInt(pDX, m_Npat, 2, 10000);
	DDX_Text(pDX, IDC_EDIT2, m_dt);
	DDV_MinMaxFloat(pDX, m_dt, 0, 1);
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

void CFrModInCndDlg::OnBnClickedRadio1()
{
	UpdateData(true);
	m_rd = 0;
}

void CFrModInCndDlg::OnBnClickedRadio2()
{
	UpdateData(true);
	m_rd = 1;
}

void CFrModInCndDlg::OnCancel()
{
	m_Npat = 60;
	m_dt = 0.000002;
	m_rd = 0;
	this->EndDialog(IDCANCEL);
}

BEGIN_MESSAGE_MAP(CFrModInCndDlg, CDialogEx)
	//{{AFX_MSG_MAP(CFrModInCndDlg)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnChangeEdit2)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio2)
	ON_BN_CLICKED(IDCANCEL, OnCancel)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CfRSH5App, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CfRSH5App::OnAppAbout)
	// Стандартные команды по работе с файлами документов
	ON_COMMAND(ID_FrMod_InCnd, &CFrModInCndDlg::OnFrMod_InCnd)
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