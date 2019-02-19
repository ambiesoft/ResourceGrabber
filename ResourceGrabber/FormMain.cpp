#include "stdafx.h"


#include "FormMain.h"
#include "CListViewOpenFilesData.h"

using namespace System;
using namespace System::Text;
using namespace System::IO;
using namespace System::Collections::Generic;

using namespace std;

using namespace Ambiesoft;

namespace ResourceGrabber {

	FormMain::FormMain()
	{
		InitializeComponent();

		lvOpenFiles->Columns->Add("file","file", 200);
		lvOpenFiles->Columns->Add("flags", "flags", 100);
		lvOpenFiles->Columns->Add("handle", "handle", 100);
		

		int intval;
		bool boolval;
		HashIni^ ini = Profile::ReadAll(IniPath);

		Profile::GetInt(SECTION_OPTION, KEY_SELECTEDTAB, 0, intval, ini);
		if (0 <= intval && intval < tabMain->TabCount)
		{
			tabMain->SelectedIndex = intval;
		}

		// Restore ListView Column Width
		AmbLib::LoadListViewColumnWidth(lvOpenFiles, SECTION_OPTION, KEY_LISTVIEW_OPENFILES, ini);

		// Load ComboBox
		cli::array<String^>^ arComboItems;
		Profile::GetStringArray(SECTION_OPTION, KEY_COMBOFILES, arComboItems, ini);
		for each(String^ cmbItem in arComboItems)
			cmbFile->Items->Add(cmbItem);
		String^ cmbCurrentItem;
		Profile::GetString(SECTION_OPTION, KEY_COMBOFILE_CURRENT, "", cmbCurrentItem, ini);
		cmbFile->Text = cmbCurrentItem;

		// Restore location
		AmbLib::LoadFormXYWH(this, SECTION_LOCATION, ini);

		// Restore splitter distance
		Profile::GetInt(SECTION_OPTION, KEY_SPLITTER_DISTANCE, spRoot->SplitterDistance, intval, ini);
		if (intval > 0)
			spRoot->SplitterDistance = intval;
	
		// Restore checkbox
		Profile::GetBool(SECTION_OPTION, KEY_CHECKBOX_ + chkShareRead->Name, false, boolval, ini);
		chkShareRead->Checked = boolval;
		Profile::GetBool(SECTION_OPTION, KEY_CHECKBOX_ + chkShareWrite->Name, false, boolval, ini);
		chkShareWrite->Checked = boolval;
		Profile::GetBool(SECTION_OPTION, KEY_CHECKBOX_ + chkShareDelete->Name, false, boolval, ini);
		chkShareDelete->Checked = boolval;

	}
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

		cmbFile->Text = gcnew String(fullpath.c_str());
	}
	
	String^ toFlagString(DWORD dwShareMode)
	{
		List<String^> rets;
		if (dwShareMode & FILE_SHARE_READ)
			rets.Add("FILE_SHARE_READ");
		if (dwShareMode & FILE_SHARE_WRITE)
			rets.Add("FILE_SHARE_WRITE");
		if (dwShareMode & FILE_SHARE_DELETE)
			rets.Add("FILE_SHARE_DELETE");

		return String::Join(" ", rets.ToArray());
	}
	System::Void FormMain::btnOpenFile_Click(System::Object^  sender, System::EventArgs^  e)
	{
		DWORD dwShareMode = 0;
		if (chkShareRead->Checked)
			dwShareMode |= FILE_SHARE_READ;
		if (chkShareWrite->Checked)
			dwShareMode |= FILE_SHARE_WRITE;
		if (chkShareDelete->Checked)
			dwShareMode |= FILE_SHARE_DELETE;

		HANDLE hFile = CreateFile(getStdWstring(cmbFile->Text).c_str(),
			GENERIC_READ,
			dwShareMode,
			NULL, //sec
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if(hFile ==INVALID_HANDLE_VALUE)
		{
			DWORD dwLE = GetLastError();
			AddToErrorLog(I18N(L"CreateFile failed"), dwLE);
			return;
		}

		// Add to List
		ListViewItem^ item = gcnew ListViewItem(cmbFile->Text);
		ListViewItem::ListViewSubItem^ subItemFlags = gcnew ListViewItem::ListViewSubItem();
		subItemFlags->Name = "flags";
		subItemFlags->Text = toFlagString(dwShareMode);
		item->SubItems->Add(subItemFlags);

		ListViewItem::ListViewSubItem^ subItemHandle = gcnew ListViewItem::ListViewSubItem();
		subItemHandle->Name = "handle";
		subItemHandle->Text = String::Format("{0} (0x{1})", (ULONGLONG)hFile, ((ULONGLONG)hFile).ToString("X"));
		item->SubItems->Add(subItemHandle);

		item->Tag = gcnew CListViewOpenFilesData(hFile);
		lvOpenFiles->Items->Add(item);

		// Add to ComboBox
		String^ saveCurrent = cmbFile->Text;
		cmbFile->Items->Remove(cmbFile->Text);
		cmbFile->Items->Insert(0, saveCurrent);
		// Reset because Remove also removes current item
		cmbFile->Text = saveCurrent;

		AddToLog(I18N(L"CreateFile succeeded"));
	}

	System::Void FormMain::btnCloseHandle_Click(System::Object^  sender, System::EventArgs^  e)
	{
		List<ListViewItem^> itemsToRemove;
		for each(ListViewItem^ lvItem in lvOpenFiles->SelectedItems)
		{
			CListViewOpenFilesData^ itemData = (CListViewOpenFilesData^)lvItem->Tag;
			HANDLE h = itemData->FileHandle;
		
			if (!CloseHandle(h))
			{
				DWORD dwLE = GetLastError();
				AddToErrorLog(I18N(L"CloseHandle failed"), dwLE);
				continue;
			}

			AddToLog(String::Format(I18N(L"CloseHandle({0}) succeeded"), (ULONGLONG)h));
			itemData->FileHandle = 0;

			lvItem->SubItems["handle"]->Text = "";
			itemsToRemove.Add(lvItem);
		}

		for each(ListViewItem^ item in itemsToRemove)
			lvOpenFiles->Items->Remove(item);

	}
	System::Void FormMain::lvOpenFiles_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		btnCloseHandle->Enabled = lvOpenFiles->SelectedItems->Count != 0;
	}
		
	System::Void FormMain::FormMain_Load(System::Object^  sender, System::EventArgs^  e)
	{
		this->Text = String::Format(L"{0} ({1}{2})",
			ProductName, 
			System::Diagnostics::Process::GetCurrentProcess()->Id,
			Environment::Is64BitProcess ? L" x64" : L"");
	}
	System::Void FormMain::FormMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
	{
		bool failed = false;
		HashIni^ ini = Profile::ReadAll(IniPath);
		failed |= !Profile::WriteInt(SECTION_OPTION, KEY_SELECTEDTAB, tabMain->SelectedIndex, ini);
		
		// Save ComboBox
		List<String^> cmbItems;
		for each(String^ cmbItem in cmbFile->Items)
		{
			cmbItems.Add(cmbItem);
		}
		failed |= !Profile::WriteString(SECTION_OPTION, KEY_COMBOFILE_CURRENT, cmbFile->Text, ini);
		failed |= !Profile::WriteStringArray(SECTION_OPTION, KEY_COMBOFILES, cmbItems.ToArray(), ini);

		// Save ListView
		failed |= !AmbLib::SaveListViewColumnWidth(lvOpenFiles, SECTION_OPTION, KEY_LISTVIEW_OPENFILES, ini);

		// Save Location
		failed |= !AmbLib::SaveFormXYWH(this, SECTION_LOCATION, ini);

		// Save Splitter Distance
		Profile::WriteInt(SECTION_OPTION, KEY_SPLITTER_DISTANCE, spRoot->SplitterDistance, ini);

		// Save check box
		Profile::WriteBool(SECTION_OPTION, KEY_CHECKBOX_ + chkShareRead->Name, chkShareRead->Checked, ini);
		Profile::WriteBool(SECTION_OPTION, KEY_CHECKBOX_ + chkShareWrite->Name, chkShareWrite->Checked, ini);
		Profile::WriteBool(SECTION_OPTION, KEY_CHECKBOX_ + chkShareDelete->Name, chkShareDelete->Checked, ini);
		// Write them all
		failed |= !Profile::WriteAll(ini, IniPath);
		if (failed)
		{
			CppUtils::Alert(I18N(L"Failed to save ini."));
		}
	}


	System::Void FormMain::cmbFile_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
	{
		if (e->Data->GetDataPresent(DataFormats::FileDrop, true))
		{
			cli::array<String^>^ ss = (cli::array<String^>^)e->Data->GetData(DataFormats::FileDrop, true);
			for each(String^ s in ss)
			{
				cmbFile->Text = s;
				break;
			}
		}
	}
	System::Void FormMain::cmbFile_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
	{
		if (e->Data->GetDataPresent(DataFormats::FileDrop, true))
			e->Effect = DragDropEffects::Copy;
	}
	System::Void FormMain::cmbFile_DragLeave(System::Object^  sender, System::EventArgs^  e)
	{}
	System::Void FormMain::cmbFile_DragOver(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
	{
		if (e->Data->GetDataPresent(DataFormats::FileDrop, true))
			e->Effect = DragDropEffects::Copy;
	}

}