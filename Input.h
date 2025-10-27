#pragma once
#include <Windows.h>
#include <wrl.h>

#define DIRECTINPUT_VERSION 0x0800//DirectInputのバージョン指定
#include <dinput.h>

class Input
{
public://メンバ変数

	//namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

		//初期化
		void Initialize(HINSTANCE hInstance,HWND hwnd);
		//更新
		void Updata();
private:

	//キーボードのデバイス
	ComPtr<IDirectInputDevice8> keyboard;

};

