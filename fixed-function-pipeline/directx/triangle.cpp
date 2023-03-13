#ifndef UNICODE
#define UNICODE
#endif 

#define WIN32_LEAN_AND_MEAN
#include <assert.h>
#include <comdef.h>
#include <windows.h>
#include <d3d9.h>        // D3D interface
#include <dxgi.h>        // DirectX driver interface

struct CUSTOMVERTEX {FLOAT X, Y, Z, RHW; DWORD COLOR;};
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    LPDIRECT3D9 d3d; 
    LPDIRECT3DDEVICE9 device_ptr = NULL;
    LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;

    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Direct3D 11 Hello Triangle",  // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    d3d = Direct3DCreate9(D3D_SDK_VERSION);

    D3DPRESENT_PARAMETERS d3dpp;

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.hDeviceWindow = hwnd;
    d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
    d3dpp.BackBufferWidth = 600;
    d3dpp.BackBufferHeight = 400;

    // create a device class using this information and the info from the d3dpp stuct
    d3d->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hwnd,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &device_ptr);

    CUSTOMVERTEX vertices[] =
    {
        { 300.0f, 62.5f,  0.5f, 1.0f, D3DCOLOR_XRGB(0, 0, 255), },
        { 500.0f, 350.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), },
        { 100.0f, 350.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 0, 0), },
    };

    // create a vertex buffer interface called v_buffer
    device_ptr->CreateVertexBuffer(3 * sizeof(CUSTOMVERTEX),
                                   0,
                                   CUSTOMFVF,
                                   D3DPOOL_MANAGED,
                                   &v_buffer,
                                   NULL);

    VOID* pVoid;    // a void pointer

    // lock v_buffer and load the vertices into it
    v_buffer->Lock(0, 0, (void**)&pVoid, 0);
    memcpy(pVoid, vertices, sizeof(vertices));
    v_buffer->Unlock();

    // Run the message loop.
    MSG msg = {};
    bool should_close = false;
    while (!should_close) 
    {
        /**** handle user input and other window events ****/
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (msg.message == WM_QUIT) 
        { 
            break; 
        }

        // clear the back buffer to black for the new frame 
        device_ptr->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

        device_ptr->BeginScene();

        // select which vertex format we are using
        device_ptr->SetFVF(CUSTOMFVF);

        // select the vertex buffer to display
        device_ptr->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

        // copy the vertex buffer to the back buffer
        device_ptr->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

        device_ptr->EndScene();

        device_ptr->Present(NULL, NULL, NULL, NULL);
    }    

    v_buffer->Release();      // close and release the vertex buffer
    device_ptr->Release();    // close and release the 3D device
    d3d->Release();           // close and release Direct3D

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}