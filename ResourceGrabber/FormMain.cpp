#include "stdafx.h"
#include "FormMain.h"

#include "../../MyUtility/GetLastErrorString.h"

using namespace System;
using namespace System::Text;

using namespace std;
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
	System::Void FormMain::btnSetTextOnClipbard_Click(System::Object^  sender, System::EventArgs^  e) 
	{

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


}