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
	
	//デバイスの生成
	void CreateDevice();

	//コマンド周りの生成
	void CreateCommand();

	//スワップチェインの生成
	void CreateSwapChain();

	//ディスクリプタヒープの生成
	void CreateDescriptor();

	//DSVの生成
	void CreateDSV();

	//RTVの生成
	void CreateRTV();

	//Fenceの生成
	void CreateFence();

	//深度バッファの生成
	void CreateDepth();


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

