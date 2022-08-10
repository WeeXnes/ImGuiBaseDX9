//
// Created by weexn on 07.08.2022.
//

#include "hooks.h"
#include <stdexcept>
#include <intrin.h>

#include "../../external/minhook/MinHook.h"

#include "../../external/imgui/imgui.h"
#include "../../external/imgui/imgui_impl_win32.h"
#include "../../external/imgui/imgui_impl_dx9.h"


void hooks::Setup(){
    if(MH_Initialize())
        throw std::runtime_error("unable to init hook");

    if(MH_CreateHook(
            VirtualFunction(gui::device, 42),
            &EndScene,
            reinterpret_cast<void**>(&EndSceneOriginal)
    ))throw std::runtime_error("unable to hook EndScene()");

    if(MH_CreateHook(
            VirtualFunction(gui::device, 16),
            &Reset,
            reinterpret_cast<void**>(&ResetOriginal)
    ))throw std::runtime_error("unable to hook Reset()");

    if(MH_EnableHook(MH_ALL_HOOKS))
        throw std::runtime_error("unable to enable hook");

    gui::DestroyDirectX();
}
void hooks::Destroy() noexcept{
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();
}


long __stdcall hooks::EndScene(IDirect3DDevice9* device) noexcept{
    static const auto returnAddress = _ReturnAddress();
    const auto result = EndSceneOriginal(device, device);
    if(_ReturnAddress() == returnAddress)
        return result;
    if(!gui::setup)
        gui::SetupMenu(device);
    if(gui::open)
        gui::Render();
    return result;
}

HRESULT __stdcall hooks::Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) noexcept{

    ImGui_ImplDX9_InvalidateDeviceObjects();
    const auto result = ResetOriginal(device, device, params);
    ImGui_ImplDX9_CreateDeviceObjects();
    return result;
}
