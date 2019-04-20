
#include "stdafx.h"

#include "ResourceGrabber.h"

#include "FormMain.h"

namespace ResourceGrabber {

	int Program::main(array<System::String^>^ args)
	{
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);

		Application::Run(gcnew FormMain());

		rsu_->showUnI18Ned();
		return 0;
	}

}