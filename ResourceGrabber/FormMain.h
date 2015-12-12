#pragma once


namespace ResourceGrabber {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// FormMain の概要
	///
	/// 警告: このクラスの名前を変更する場合、このクラスが依存するすべての .resx ファイルに関連付けられた
	///          マネージ リソース コンパイラ ツールに対して 'Resource File Name' プロパティを
	///          変更する必要があります。この変更を行わないと、
	///          デザイナと、このフォームに関連付けられたローカライズ済みリソースとが、
	///          正しく相互に利用できなくなります。
	/// </summary>
	public ref class FormMain : public System::Windows::Forms::Form
	{
	public:
		FormMain(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクタ コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
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
	private: System::Windows::Forms::TabPage^  tabPage2;


	private:
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->spRoot = (gcnew System::Windows::Forms::SplitContainer());
			this->btnSetTextOnClipbard = (gcnew System::Windows::Forms::Button());
			this->btnCloseClipboard = (gcnew System::Windows::Forms::Button());
			this->btnOpenClipboard = (gcnew System::Windows::Forms::Button());
			this->rtxtLog = (gcnew System::Windows::Forms::RichTextBox());
			this->tabMain = (gcnew System::Windows::Forms::TabControl());
			this->pageClipBoard = (gcnew System::Windows::Forms::TabPage());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->spRoot->Panel1->SuspendLayout();
			this->spRoot->Panel2->SuspendLayout();
			this->spRoot->SuspendLayout();
			this->tabMain->SuspendLayout();
			this->pageClipBoard->SuspendLayout();
			this->SuspendLayout();
			// 
			// spRoot
			// 
			this->spRoot->Dock = System::Windows::Forms::DockStyle::Fill;
			this->spRoot->Location = System::Drawing::Point(0, 0);
			this->spRoot->Name = L"spRoot";
			this->spRoot->Orientation = System::Windows::Forms::Orientation::Horizontal;
			// 
			// spRoot.Panel1
			// 
			this->spRoot->Panel1->Controls->Add(this->tabMain);
			// 
			// spRoot.Panel2
			// 
			this->spRoot->Panel2->Controls->Add(this->rtxtLog);
			this->spRoot->Size = System::Drawing::Size(732, 513);
			this->spRoot->SplitterDistance = 328;
			this->spRoot->TabIndex = 0;
			// 
			// btnSetTextOnClipbard
			// 
			this->btnSetTextOnClipbard->Location = System::Drawing::Point(8, 35);
			this->btnSetTextOnClipbard->Name = L"btnSetTextOnClipbard";
			this->btnSetTextOnClipbard->Size = System::Drawing::Size(131, 23);
			this->btnSetTextOnClipbard->TabIndex = 2;
			this->btnSetTextOnClipbard->Text = L"Set Text on Clipbard";
			this->btnSetTextOnClipbard->UseVisualStyleBackColor = true;
			this->btnSetTextOnClipbard->Click += gcnew System::EventHandler(this, &FormMain::btnSetTextOnClipbard_Click);
			// 
			// btnCloseClipboard
			// 
			this->btnCloseClipboard->Location = System::Drawing::Point(8, 273);
			this->btnCloseClipboard->Name = L"btnCloseClipboard";
			this->btnCloseClipboard->Size = System::Drawing::Size(131, 23);
			this->btnCloseClipboard->TabIndex = 1;
			this->btnCloseClipboard->Text = L"Close Clipbard";
			this->btnCloseClipboard->UseVisualStyleBackColor = true;
			this->btnCloseClipboard->Click += gcnew System::EventHandler(this, &FormMain::btnCloseClipboard_Click);
			// 
			// btnOpenClipboard
			// 
			this->btnOpenClipboard->Location = System::Drawing::Point(8, 6);
			this->btnOpenClipboard->Name = L"btnOpenClipboard";
			this->btnOpenClipboard->Size = System::Drawing::Size(131, 23);
			this->btnOpenClipboard->TabIndex = 0;
			this->btnOpenClipboard->Text = L"Open Clipbard";
			this->btnOpenClipboard->UseVisualStyleBackColor = true;
			this->btnOpenClipboard->Click += gcnew System::EventHandler(this, &FormMain::btnOpenClipboard_Click);
			// 
			// rtxtLog
			// 
			this->rtxtLog->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rtxtLog->Location = System::Drawing::Point(0, 0);
			this->rtxtLog->Name = L"rtxtLog";
			this->rtxtLog->Size = System::Drawing::Size(732, 181);
			this->rtxtLog->TabIndex = 0;
			this->rtxtLog->Text = L"";
			// 
			// tabMain
			// 
			this->tabMain->Controls->Add(this->pageClipBoard);
			this->tabMain->Controls->Add(this->tabPage2);
			this->tabMain->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabMain->Location = System::Drawing::Point(0, 0);
			this->tabMain->Name = L"tabMain";
			this->tabMain->SelectedIndex = 0;
			this->tabMain->Size = System::Drawing::Size(732, 328);
			this->tabMain->TabIndex = 3;
			// 
			// pageClipBoard
			// 
			this->pageClipBoard->Controls->Add(this->btnSetTextOnClipbard);
			this->pageClipBoard->Controls->Add(this->btnOpenClipboard);
			this->pageClipBoard->Controls->Add(this->btnCloseClipboard);
			this->pageClipBoard->Location = System::Drawing::Point(4, 22);
			this->pageClipBoard->Name = L"pageClipBoard";
			this->pageClipBoard->Padding = System::Windows::Forms::Padding(3);
			this->pageClipBoard->Size = System::Drawing::Size(724, 302);
			this->pageClipBoard->TabIndex = 0;
			this->pageClipBoard->Text = L"Clipboard";
			this->pageClipBoard->UseVisualStyleBackColor = true;
			// 
			// tabPage2
			// 
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(724, 302);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"tabPage2";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// FormMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(732, 513);
			this->Controls->Add(this->spRoot);
			this->Name = L"FormMain";
			this->Text = L"FormMain";
			this->spRoot->Panel1->ResumeLayout(false);
			this->spRoot->Panel2->ResumeLayout(false);
			this->spRoot->ResumeLayout(false);
			this->tabMain->ResumeLayout(false);
			this->pageClipBoard->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion


	private:
		property HWND Hwnd 
		{
			HWND get()
			{
				return (HWND)this->Handle.ToPointer();
			}
		}

		void AddToLog(String^ text)
		{
			rtxtLog->AppendText(text);
			rtxtLog->AppendText(Environment::NewLine);

			rtxtLog->Select(rtxtLog->TextLength-1,0);
			rtxtLog->ScrollToCaret();
		}
		void AddToErrorLog(String^ text)
		{
			AddToLog(text);
		}
		void AddToErrorLog(String^ text, DWORD dwLastError);















	private: System::Void btnOpenClipboard_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnSetTextOnClipbard_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void btnCloseClipboard_Click(System::Object^  sender, System::EventArgs^  e);









};
}

