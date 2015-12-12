// ResourceGrabber.cpp : メイン プロジェクト ファイルです。

#include "stdafx.h"
#include "FormMain.h"

using namespace ResourceGrabber;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// コントロールが作成される前に、Windows XP ビジュアル効果を有効にします
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// メイン ウィンドウを作成して、実行します
	Application::Run(gcnew FormMain());
	return 0;
}
