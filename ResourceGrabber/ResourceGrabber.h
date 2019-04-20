#pragma once

namespace ResourceGrabber {

	using namespace System;

	ref class Program abstract
	{
		static Ambiesoft::ResStringUtil^ rsu_ = gcnew Ambiesoft::ResStringUtil("ResourceGrabber.ResourceGrabberStrings");

		[STAThreadAttribute]
		static int main(array<System::String^>^ args);

	public:

		static String^ GetString(String^ s)
		{
			return rsu_->getString(s);
		}
	};

}