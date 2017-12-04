#include "stdafx.h"
#include "FormMain.h"

#include "../../lsMisc/GetLastErrorString.h"
#include "../../lsMisc/GetOpenFile.h"
#include "../../lsMisc/getStdString.net.h"

using namespace System;
using namespace System::Text;
using namespace System::IO;

using namespace std;

using namespace Ambiesoft;

namespace ResourceGrabber {

	void FormMain::AddToErrorLog(String^ text, DWORD dwLastError)
	{
		StringBuilder sb;
		sb.Append(text);
		sb.Append(L" : GetLastError=");
		sb.Append(dwLastError.ToString());
		wstring lestr = GetLastErrorString(dwLastError);
		sb.Append(L" (");
		sb.Append(gcnew String(lestr.c_str()));
		sb.Append(L")");

		AddToLog(sb.ToString());
	}

	System::Void FormMain::btnOpenClipboard_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		if(OpenClipboard(this->Hwnd))
		{
			AddToLog(I18N(L"OpenClipbard succeeded"));
		}
		else
		{
			DWORD dwLE = GetLastError();
			AddToErrorLog(I18N(L"OpenClipbard failed"), dwLE);
		}
	}

	System::Void FormMain::btnEmptyClipboard_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if(!EmptyClipboard())
		{
			DWORD dwLE = GetLastError();
			AddToErrorLog(I18N(L"EmptyClipboard failed"), dwLE);
			return;
		}
		AddToErrorLog(I18N(L"EmptyClipboard succeeded"), GetLastError());
	}
	System::Void FormMain::btnSetTextOnClipbard_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		LPWSTR pSTR = L"ResourceGrabber";
		if ( !pSTR || pSTR[0]==0 )
		{
			return;
		}

		size_t strsize = lstrlenW(pSTR);
		HGLOBAL h = GlobalAlloc(
			GMEM_MOVEABLE|GMEM_DDESHARE,
			(strsize+1)*sizeof(wchar_t));

		if(h==NULL)
		{
			DWORD dwLE = GetLastError();
			AddToErrorLog(I18N(L"GlobalAlloc failed"), dwLE);
			return;
		}

		BOOL bRet = FALSE;
		LPWSTR p = (LPWSTR)GlobalLock(h);
		if(p==NULL)
		{
			DWORD dwLE = GetLastError();
			AddToErrorLog(I18N(L"GlobalLock failed"), dwLE);
			return;
		}
		lstrcpyW(p, pSTR);

		if(!SetClipboardData(CF_UNICODETEXT,h))
		{
			DWORD dwLE = GetLastError();
			AddToErrorLog(I18N(L"SetClipboardData failed"), dwLE);
			return;
		}

		GlobalUnlock(h);

		AddToErrorLog(I18N(L"SetClipboardData succeeded"), GetLastError());
		return;
	}
	System::Void FormMain::btnCloseClipboard_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if(CloseClipboard())
		{
			AddToLog(I18N(L"CloseClipboard succeeded"));
		}
		else
		{
			DWORD dwLE = GetLastError();
			AddToErrorLog(I18N(L"CloseClipboard failed"), dwLE);
		}

	}

	System::Void FormMain::btnBrowse_Click(System::Object^  sender, System::EventArgs^  e)
	{
		wstring fullpath;
		if(!GetOpenFile(
				 (HWND)this->Handle.ToPointer(),
				 NULL, // LPCTSTR pFilter, 
				 NULL, // LPCTSTR pInitialDir,
				 NULL, // LPCTSTR pTitle,
				 &fullpath,
				 NULL))
		{
			return;
		}

		txtPath->Text = gcnew String(fullpath.c_str());
	}


	System::Void FormMain::btnOpenWithNoShare_Click(System::Object^  sender, System::EventArgs^  e)
	{
		hFile_ = CreateFile(getStdWstring(txtPath->Text).c_str(),
			GENERIC_READ,
			0, // share none
			NULL, //sec
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if(hFile_==INVALID_HANDLE_VALUE)
		{
			DWORD dwLE = GetLastError();
			AddToErrorLog(I18N(L"CreateFile failed"), dwLE);
			return;
		}

		AddToLog(I18N(L"CreateFile succeeded"));
	}

	System::Void FormMain::btnCloseHandle_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if(!CloseHandle(hFile_))
		{
			DWORD dwLE = GetLastError();
			AddToErrorLog(I18N(L"CloseHandle failed"), dwLE);
			return;
		}
		AddToLog(I18N(L"CloseHandle succeeded"));
	}

		
	System::Void FormMain::FormMain_Load(System::Object^  sender, System::EventArgs^  e)
	{
		this->Text = ProductName;

		int intval;
		Profile::GetInt(SECTION_OPTION, KEY_SELECTEDTAB, 0, intval, IniPath);
		if (0 <= intval && intval < tabMain->TabCount)
		{
			tabMain->SelectedIndex = intval;
		}
	}
	System::Void FormMain::FormMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
	{
		bool failed = false;
		failed |= !Profile::WriteInt(SECTION_OPTION, KEY_SELECTEDTAB, tabMain->SelectedIndex, IniPath);

		if (failed)
		{
			CppUtils::Alert(I18N(L"Failed to save ini."));
		}
	}
	String^ FormMain::IniPath::get()
	{
		return Path::Combine(Path::GetDirectoryName(Application::ExecutablePath),
			Application::ProductName + L".ini");
	}

	System::Void FormMain::txtPath_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
	{
		if (e->Data->GetDataPresent(DataFormats::FileDrop, true))
		{
			cli::array<String^>^ ss = (cli::array<String^>^)e->Data->GetData(DataFormats::FileDrop, true);
			for each(String^ s in ss)
			{
				txtPath->Text = s;
				break;
			}
		}
	}
	System::Void FormMain::txtPath_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
	{
		if (e->Data->GetDataPresent(DataFormats::FileDrop, true))
			e->Effect = DragDropEffects::Copy;
	}
	System::Void FormMain::txtPath_DragLeave(System::Object^  sender, System::EventArgs^  e)
	{}
	System::Void FormMain::txtPath_DragOver(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
	{
		if (e->Data->GetDataPresent(DataFormats::FileDrop, true))
			e->Effect = DragDropEffects::Copy;
	}

}