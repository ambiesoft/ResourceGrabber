#pragma once


namespace ResourceGrabber {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	public ref class FormMain : public System::Windows::Forms::Form
	{
		literal String^ SECTION_OPTION = L"Option";
		literal String^ KEY_SELECTEDTAB = L"SelectedTab";
		literal String^ KEY_LISTVIEW_OPENFILES = L"ListViewOpenFiles";
		literal String^ KEY_COMBOFILES = L"ComboFiles";
		literal String^ KEY_COMBOFILE_CURRENT = L"ComboFileCurrent";
		literal String^ KEY_SPLITTER_DISTANCE = L"SplitterDistance";
		literal String^ KEY_CHECKBOX_ = L"CheckBox_";
		literal String^ SECTION_LOCATION = L"Location";
		
	private: System::Windows::Forms::CheckBox^  chkShareRead;
	private: System::Windows::Forms::CheckBox^  chkShareDelete;
	private: System::Windows::Forms::CheckBox^  chkShareWrite;
	private: System::Windows::Forms::ListView^  lvOpenFiles;
	private: System::Windows::Forms::ComboBox^  cmbFile;
	private: System::Windows::Forms::TabPage^  tabAbout;
	private: System::Windows::Forms::LinkLabel^  linkWebpage;
	private: System::Windows::Forms::TextBox^  txtVersion;


		static initonly String^ inipath_;

	public:
		static FormMain() {
			inipath_ = Path::Combine(Path::GetDirectoryName(Application::ExecutablePath),
				Path::GetFileNameWithoutExtension(Application::ExecutablePath) + L".ini");
		}
		FormMain();

	protected:
		~FormMain()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::SplitContainer^  spRoot;
	protected:
	private: System::Windows::Forms::Button^  btnCloseClipboard;
	private: System::Windows::Forms::Button^  btnOpenClipboard;
	private: System::Windows::Forms::RichTextBox^  rtxtLog;
	private: System::Windows::Forms::Button^  btnSetTextOnClipbard;
	private: System::Windows::Forms::TabControl^  tabMain;
	private: System::Windows::Forms::TabPage^  pageClipBoard;
	private: System::Windows::Forms::TabPage^  pageFile;

	private: System::Windows::Forms::Button^  btnEmptyClipboard;

	private: System::Windows::Forms::Button^  btnBrowse;
	private: System::Windows::Forms::Button^  btnOpenFile;

	private: System::Windows::Forms::Button^  btnCloseHandle;



	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void);
#pragma endregion


	private:

		property HWND Hwnd
		{
			HWND get()
			{
				return (HWND)this->Handle.ToPointer();
			}
		}
		property String^ IniPath
		{
			String^ get() {
				return inipath_;
			}
		}
		void AddToLog(String^ text)
		{
			rtxtLog->AppendText(text);
			rtxtLog->AppendText(Environment::NewLine);

			rtxtLog->Select(rtxtLog->TextLength - 1, 0);
			rtxtLog->ScrollToCaret();
		}
		void AddToErrorLog(String^ text)
		{
			AddToLog(text);
		}
		void AddToErrorLog(String^ text, DWORD dwLastError);















	private:
		System::Void btnOpenClipboard_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnSetTextOnClipbard_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnCloseClipboard_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnEmptyClipboard_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnBrowse_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnOpenFile_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnCloseHandle_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void FormMain_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void FormMain_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
		System::Void cmbFile_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
		System::Void cmbFile_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
		System::Void cmbFile_DragLeave(System::Object^  sender, System::EventArgs^  e);
		System::Void cmbFile_DragOver(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
		System::Void lvOpenFiles_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
		System::Void linkWebpage_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e);

		void OnTestClick(System::Object^ sender, System::EventArgs^ e);
};
}

