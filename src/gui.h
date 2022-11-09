#pragma once

//Windows API Includes
#include <Windows.h>
#include <dwmapi.h>
//Direct X 11
#include <d3d11.h>


//IMGUI Includes
#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>


namespace gui
{
	// Menu window size
	constexpr int WIDTH = 900;
	constexpr int HEIGHT = 300;

	inline bool running = true;

	// winapi vars
	inline HWND window = nullptr;
	inline WNDCLASSEXW wc = {};
	inline DXGI_SWAP_CHAIN_DESC sd{};

	// points for window movements
	inline POINTS position = {};

	//Direct X Variables
	inline ID3D11Device* device{ nullptr };
	inline ID3D11DeviceContext* device_context{ nullptr };
	inline IDXGISwapChain* swap_chain{ nullptr };
	inline ID3D11RenderTargetView* render_target_view{ nullptr };
	inline D3D_FEATURE_LEVEL level{};


	// Window creation and destruction
	void CreateHOverlay(const char* windowName, const char* className) noexcept;
	void DestroyHLayout() noexcept;

	//Rendering
	void BeginRender()noexcept;
	void EndRender()noexcept;
	void Render()noexcept;

	// Components to render
	void renderEsp()noexcept;
	void renderMenu(float posX, float posY)noexcept;
	void renderRadar();
	

};

// IMGUI 
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// JE SAIS PAS
LRESULT CALLBACK window_procedure(HWND window, UINT message, WPARAM w_param, LPARAM l_param);