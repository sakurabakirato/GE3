#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#include "WinApp.h"

//DirectX基盤
class DirectXCommon
{
public:
	//初期化
	void Initialize(WinApp* winApp);
	//描画開始
	void PreDraw();
	//描画終了
	void PostDraw();

private:
	//DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	//DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory> dxgiFactory;

	//WindowsAPI
	WinApp* winApp = nullptr;

};

