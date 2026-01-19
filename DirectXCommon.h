#pragma once
#include "WinApp.h"
#include "StringUtility.h"
#include <cstdint>
#include <array>
#include <string>
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>

#include "externals/imgui/imgui.h"
#include "externals/imgui/imgui_impl_dx12.h"
#include "externals/imgui/imgui_impl_win32.h"
#include <dxcapi.h>
#include "externals/DirectXTex/DirectXTex.h"

struct Vector4
{
	float x;
	float y;
	float z;
	float w;
};

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Vector2
{
	float x;
	float y;
};

struct VertexData
{
	Vector4 position;
	Vector2 texcoord;
};

struct MaterialData
{
	std::string textureFilePath;
};


struct ModelData
{
	std::vector<VertexData> vertices;
	MaterialData material;
};

struct Matrix4x4
{
	float m[4][4];
};

struct Transform
{
	Vector3 scale;
	Vector3 rotate;
	Vector3 translate;
};

struct Matrix4x4;

Matrix4x4 MakeIdentity4x4();

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

	//ビューポート矩形の初期化
	void CreateViewport();

	//シザリング矩形の初期化
	void CreateScissorRect();

	//ImGuiの初期化
	void CreateImGui();

	void CreatePipelineState();

	void CreateIndexResource();

	void CreateRootsignature();

	void CreateInputLayout();

	void CreateblendDesc();

	void CreateRastrizeDesc();

	void CreateGraphicsPipelineStateDesc();

	void CreateVertexResource();

	void CreateMaterialResource();

	void CreateModel();

	void CreateTransformationMatrixResourceSprite();

	void CreateDepthStencilDesc();

	void CreateWvpResource();

	void CreateSrv();

	void CreateVertexBufferViewSprite();

	//描画開始
	void PreDraw();
	//描画終了
	void PostDraw();

	/// <summary>
	/// デスクリプタヒープを生成
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);
	ID3D12Resource* CreateDepthStencilTextureResource(int32_t width, int32_t height);

	/*/// <summary>
	/// SRVの指定番号のCPUデスクリプタハンドルを取得する
	/// </summary>
	D3D12_CPU_DESCRIPTOR_HANDLE GetSRVCPUDescriptorHandle(uint32_t index);*/

	///// <summary>
	///// SRVの指定番号のGPUデスクリプタハンドルを取得する
	///// </summary>
	//D3D12_CPU_DESCRIPTOR_HANDLE GetSRVGPUDescriptorHandle(uint32_t index);

	//getter
	ID3D12Device* GetDevice() const { return device.Get(); }
	ID3D12GraphicsCommandList* GetCommandList() const { return commandList.Get(); }



	//スワップチェーンリソース
	std::array<Microsoft::WRL::ComPtr<ID3D12Resource>, 2> swapChainResources{};

	//シェーダーのコンパイル
	Microsoft::WRL::ComPtr<IDxcBlob> CompileShader(const std::wstring& filePath, const wchar_t* profile);

	/// <summary>
	/// バッファリソースの生成
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInBytes);
	/// <summary>
	/// テクスチャリソースの生成
	/// </summary>
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(const DirectX::TexMetadata& metadata);

	/// <summary>
	/// テクスチャデータの転送
	/// </summary>
	void UploadTextureData(const Microsoft::WRL::ComPtr<ID3D12Resource>& texture, const DirectX::ScratchImage& mipImages);

	/// <summary>
	/// テクスチャファイルの読み込み
	/// </summary>
	/// <param name= "filePath">テクスチャファイルのパス</param>
	/// <returns>画像イメージデータ</returns>
	static DirectX::ScratchImage LoadTexture(const std::string& filePath);

	MaterialData LoadMaterialTemplateFile(const std::string& directoryPath, const std::string& filename);

	ModelData LoadObjFile(const std::string& directoryPath, const std::string& filename);


private:

	HRESULT hr;

	//DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	//DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;

	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList = nullptr;


	ID3D12CommandQueue* commandQueue = nullptr;
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};

	IDXGISwapChain4* swapChain = nullptr;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};

	D3D12_GRAPHICS_PIPELINE_STATE_DESC graphicsPipelineStateDesc{};
	D3D12_DEPTH_STENCIL_DESC depthStencilDesc{};
	ID3D12PipelineState* graphicsPipelineState = nullptr;

	//TransitionBarrierの設定
	D3D12_RESOURCE_BARRIER barrier{};

	//頂点リソース用のヒープの設定
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	//頂点リソースの設定
	D3D12_RESOURCE_DESC vertexResourceDesc{};
	//実際に頂点リソースを作る
	ID3D12Resource* vertexResource = nullptr;

	//WindowsAPI
	WinApp* winApp = nullptr;

	//ディスクリプタヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap = nullptr;

	uint32_t rtvDescriptorSize = 0;
	uint32_t srvDescriptorSize = 0;
	uint32_t dsvDescriptorSize = 0;


	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	//RTVを2つ作るのでディスクリプタを２つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2]{};

	D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle;

	D3D12_VIEWPORT viewport{};

	D3D12_RECT scissorRect{};


	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	HANDLE fenceEvent;
	uint64_t fenceValue = 0;

	//頂点バッファビューを作成する
	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSprite{};

	ID3D12Resource* depthStencilResource;

	//使用するアダプタ用の変数。最初にnullptrを入れておく
	IDXGIAdapter4* useAdapter = nullptr;

	ID3D12Debug1* debugController = nullptr;

	/*/// <summary>
	/// 指定番号のCPUデスクリプタハンドルを取得する
	/// </summary>
	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descripHeap, uint32_t descriptorSize, uint32_t index);

	/// <summary>
	/// 指定番号のGPUデスクリプタハンドルを取得する
	/// </summary>
	static D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(const Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>& descripHeap, uint32_t descriptorSize, uint32_t index);*/

	//dxCompilerを初期化
	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;

	Microsoft::WRL::ComPtr<IDxcBlob> vertexShaderBlob;
	Microsoft::WRL::ComPtr<IDxcBlob> pixelShaderBlob;

	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	ID3D12RootSignature* rootSignature = nullptr;

	D3D12_INPUT_LAYOUT_DESC inputLayOutDesc{};
	D3D12_BLEND_DESC blendDesc{};
	D3D12_RASTERIZER_DESC rastrizeDesc{};

	//DepthStencilStateの設定
	D3D12_DEPTH_STENCIL_DESC depthSteFncilDesc{};

	VertexData* vertexData = nullptr;
	//マテリアルにデータを書き込む
	Vector4* materialData = nullptr;

	ModelData modelData;


	//データを書き込む
	Matrix4x4* transformationMatrixDataSprite = nullptr;

	UINT backBufferIndex;

};

