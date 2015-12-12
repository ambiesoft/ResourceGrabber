#include "stdafx.h"
#include "FormMain.h"

namespace ResourceGrabber {

	void FormMain::AddToErrorLog(String^ text, DWORD dwLastError);
	{
		AddToLog(text);
	}

	System::Void FormMain::btnOpenClipboard_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		if(OpenClipboard(this->Hwnd))
		{
			AddToLog(I18N(L"OpenClipbard succeeded"));
		}
		else
		{
			String^ message;

			AddToLog(I18N(L"OpenClipbard failed"));
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
			String^ message;

			AddToLog(I18N(L"CloseClipboard failed"));
		}

	}


}