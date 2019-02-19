#include "stdafx.h"

#include "FormMain.h"

using namespace System;
using namespace System::Text;
using namespace System::IO;
using namespace System::Collections::Generic;

namespace ResourceGrabber {
	void FormMain::InitializeComponent(void)
	{
		System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FormMain::typeid));
		this->spRoot = (gcnew System::Windows::Forms::SplitContainer());
		this->tabMain = (gcnew System::Windows::Forms::TabControl());
		this->pageClipBoard = (gcnew System::Windows::Forms::TabPage());
		this->btnEmptyClipboard = (gcnew System::Windows::Forms::Button());
		this->btnSetTextOnClipbard = (gcnew System::Windows::Forms::Button());
		this->btnOpenClipboard = (gcnew System::Windows::Forms::Button());
		this->btnCloseClipboard = (gcnew System::Windows::Forms::Button());
		this->pageFile = (gcnew System::Windows::Forms::TabPage());
		this->cmbFile = (gcnew System::Windows::Forms::ComboBox());
		this->lvOpenFiles = (gcnew System::Windows::Forms::ListView());
		this->chkShareDelete = (gcnew System::Windows::Forms::CheckBox());
		this->chkShareWrite = (gcnew System::Windows::Forms::CheckBox());
		this->chkShareRead = (gcnew System::Windows::Forms::CheckBox());
		this->btnCloseHandle = (gcnew System::Windows::Forms::Button());
		this->btnOpenFile = (gcnew System::Windows::Forms::Button());
		this->btnBrowse = (gcnew System::Windows::Forms::Button());
		this->rtxtLog = (gcnew System::Windows::Forms::RichTextBox());
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->spRoot))->BeginInit();
		this->spRoot->Panel1->SuspendLayout();
		this->spRoot->Panel2->SuspendLayout();
		this->spRoot->SuspendLayout();
		this->tabMain->SuspendLayout();
		this->pageClipBoard->SuspendLayout();
		this->pageFile->SuspendLayout();
		this->SuspendLayout();
		// 
		// spRoot
		// 
		resources->ApplyResources(this->spRoot, L"spRoot");
		this->spRoot->Name = L"spRoot";
		// 
		// spRoot.Panel1
		// 
		resources->ApplyResources(this->spRoot->Panel1, L"spRoot.Panel1");
		this->spRoot->Panel1->Controls->Add(this->tabMain);
		// 
		// spRoot.Panel2
		// 
		resources->ApplyResources(this->spRoot->Panel2, L"spRoot.Panel2");
		this->spRoot->Panel2->Controls->Add(this->rtxtLog);
		// 
		// tabMain
		// 
		resources->ApplyResources(this->tabMain, L"tabMain");
		this->tabMain->Controls->Add(this->pageClipBoard);
		this->tabMain->Controls->Add(this->pageFile);
		this->tabMain->Name = L"tabMain";
		this->tabMain->SelectedIndex = 0;
		// 
		// pageClipBoard
		// 
		resources->ApplyResources(this->pageClipBoard, L"pageClipBoard");
		this->pageClipBoard->Controls->Add(this->btnEmptyClipboard);
		this->pageClipBoard->Controls->Add(this->btnSetTextOnClipbard);
		this->pageClipBoard->Controls->Add(this->btnOpenClipboard);
		this->pageClipBoard->Controls->Add(this->btnCloseClipboard);
		this->pageClipBoard->Name = L"pageClipBoard";
		this->pageClipBoard->UseVisualStyleBackColor = true;
		// 
		// btnEmptyClipboard
		// 
		resources->ApplyResources(this->btnEmptyClipboard, L"btnEmptyClipboard");
		this->btnEmptyClipboard->Name = L"btnEmptyClipboard";
		this->btnEmptyClipboard->UseVisualStyleBackColor = true;
		this->btnEmptyClipboard->Click += gcnew System::EventHandler(this, &FormMain::btnEmptyClipboard_Click);
		// 
		// btnSetTextOnClipbard
		// 
		resources->ApplyResources(this->btnSetTextOnClipbard, L"btnSetTextOnClipbard");
		this->btnSetTextOnClipbard->Name = L"btnSetTextOnClipbard";
		this->btnSetTextOnClipbard->UseVisualStyleBackColor = true;
		this->btnSetTextOnClipbard->Click += gcnew System::EventHandler(this, &FormMain::btnSetTextOnClipbard_Click);
		// 
		// btnOpenClipboard
		// 
		resources->ApplyResources(this->btnOpenClipboard, L"btnOpenClipboard");
		this->btnOpenClipboard->Name = L"btnOpenClipboard";
		this->btnOpenClipboard->UseVisualStyleBackColor = true;
		this->btnOpenClipboard->Click += gcnew System::EventHandler(this, &FormMain::btnOpenClipboard_Click);
		// 
		// btnCloseClipboard
		// 
		resources->ApplyResources(this->btnCloseClipboard, L"btnCloseClipboard");
		this->btnCloseClipboard->Name = L"btnCloseClipboard";
		this->btnCloseClipboard->UseVisualStyleBackColor = true;
		this->btnCloseClipboard->Click += gcnew System::EventHandler(this, &FormMain::btnCloseClipboard_Click);
		// 
		// pageFile
		// 
		resources->ApplyResources(this->pageFile, L"pageFile");
		this->pageFile->Controls->Add(this->cmbFile);
		this->pageFile->Controls->Add(this->lvOpenFiles);
		this->pageFile->Controls->Add(this->chkShareDelete);
		this->pageFile->Controls->Add(this->chkShareWrite);
		this->pageFile->Controls->Add(this->chkShareRead);
		this->pageFile->Controls->Add(this->btnCloseHandle);
		this->pageFile->Controls->Add(this->btnOpenFile);
		this->pageFile->Controls->Add(this->btnBrowse);
		this->pageFile->Name = L"pageFile";
		this->pageFile->UseVisualStyleBackColor = true;
		// 
		// cmbFile
		// 
		resources->ApplyResources(this->cmbFile, L"cmbFile");
		this->cmbFile->AllowDrop = true;
		this->cmbFile->FormattingEnabled = true;
		this->cmbFile->Name = L"cmbFile";
		this->cmbFile->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &FormMain::cmbFile_DragDrop);
		this->cmbFile->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &FormMain::cmbFile_DragEnter);
		this->cmbFile->DragOver += gcnew System::Windows::Forms::DragEventHandler(this, &FormMain::cmbFile_DragOver);
		this->cmbFile->DragLeave += gcnew System::EventHandler(this, &FormMain::cmbFile_DragLeave);
		// 
		// lvOpenFiles
		// 
		resources->ApplyResources(this->lvOpenFiles, L"lvOpenFiles");
		this->lvOpenFiles->FullRowSelect = true;
		this->lvOpenFiles->HideSelection = false;
		this->lvOpenFiles->Name = L"lvOpenFiles";
		this->lvOpenFiles->UseCompatibleStateImageBehavior = false;
		this->lvOpenFiles->View = System::Windows::Forms::View::Details;
		this->lvOpenFiles->SelectedIndexChanged += gcnew System::EventHandler(this, &FormMain::lvOpenFiles_SelectedIndexChanged);
		// 
		// chkShareDelete
		// 
		resources->ApplyResources(this->chkShareDelete, L"chkShareDelete");
		this->chkShareDelete->Name = L"chkShareDelete";
		this->chkShareDelete->UseVisualStyleBackColor = true;
		// 
		// chkShareWrite
		// 
		resources->ApplyResources(this->chkShareWrite, L"chkShareWrite");
		this->chkShareWrite->Name = L"chkShareWrite";
		this->chkShareWrite->UseVisualStyleBackColor = true;
		// 
		// chkShareRead
		// 
		resources->ApplyResources(this->chkShareRead, L"chkShareRead");
		this->chkShareRead->Name = L"chkShareRead";
		this->chkShareRead->UseVisualStyleBackColor = true;
		// 
		// btnCloseHandle
		// 
		resources->ApplyResources(this->btnCloseHandle, L"btnCloseHandle");
		this->btnCloseHandle->Name = L"btnCloseHandle";
		this->btnCloseHandle->UseVisualStyleBackColor = true;
		this->btnCloseHandle->Click += gcnew System::EventHandler(this, &FormMain::btnCloseHandle_Click);
		// 
		// btnOpenFile
		// 
		resources->ApplyResources(this->btnOpenFile, L"btnOpenFile");
		this->btnOpenFile->Name = L"btnOpenFile";
		this->btnOpenFile->UseVisualStyleBackColor = true;
		this->btnOpenFile->Click += gcnew System::EventHandler(this, &FormMain::btnOpenFile_Click);
		// 
		// btnBrowse
		// 
		resources->ApplyResources(this->btnBrowse, L"btnBrowse");
		this->btnBrowse->Name = L"btnBrowse";
		this->btnBrowse->UseVisualStyleBackColor = true;
		this->btnBrowse->Click += gcnew System::EventHandler(this, &FormMain::btnBrowse_Click);
		// 
		// rtxtLog
		// 
		resources->ApplyResources(this->rtxtLog, L"rtxtLog");
		this->rtxtLog->Name = L"rtxtLog";
		// 
		// FormMain
		// 
		resources->ApplyResources(this, L"$this");
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->Controls->Add(this->spRoot);
		this->Name = L"FormMain";
		this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FormMain::FormMain_FormClosing);
		this->Load += gcnew System::EventHandler(this, &FormMain::FormMain_Load);
		this->spRoot->Panel1->ResumeLayout(false);
		this->spRoot->Panel2->ResumeLayout(false);
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->spRoot))->EndInit();
		this->spRoot->ResumeLayout(false);
		this->tabMain->ResumeLayout(false);
		this->pageClipBoard->ResumeLayout(false);
		this->pageFile->ResumeLayout(false);
		this->pageFile->PerformLayout();
		this->ResumeLayout(false);

	}


}