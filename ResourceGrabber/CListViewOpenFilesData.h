#pragma once
ref class CListViewOpenFilesData
{
	HANDLE hFile_;
public:
	CListViewOpenFilesData(HANDLE hFile) : hFile_(hFile){}

	property HANDLE FileHandle
	{
		HANDLE get() { return hFile_; }
		void set(HANDLE h) { hFile_ = h; }
	}
};

