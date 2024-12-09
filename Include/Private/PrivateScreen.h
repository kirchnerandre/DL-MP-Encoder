
#ifndef _PRIVATE_SCREEN_H_
#define _PRIVATE_SCREEN_H_

#if defined(ENCODER_PLATFORM_LINUX)

 #include <GLFW/glfw3.h>
 #include <stdint.h>

namespace Screen
{
    class PrivateScreen
    {
    public:
        virtual
       ~PrivateScreen(){};

    protected:
        PrivateScreen(){};

        GLFWwindow*                         _window                 = nullptr;
        uint8_t*                            _image_data             = nullptr;
        uint32_t                            _width                  = 0u;
        uint32_t                            _height                 = 0u;
        uint32_t                            _shader_program         = 0u;
        uint32_t                            _object_vertex_array    = 0u;
        uint32_t                            _object_vertex_buffer   = 0u;
        uint32_t                            _object_element_buffer  = 0u;
    };
}

#elif defined(ENCODER_PLATFORM_WINDOWS)

    #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
    #endif

    #include <d3d12.h>
    #include <D3Dcompiler.h>
    #include <d3dx12.h>
    #include <DirectXMath.h>
    #include <dxgi1_6.h>
    #include <shellapi.h>
    #include <string>
    #include <vector>
    #include <wrl.h>
    #include <windows.h>

namespace Screen
{
    class PrivateScreen
    {
    public:
        virtual
       ~PrivateScreen(){};

        void on_render ();
        void on_destroy();

    protected:
        PrivateScreen(){};

        static const uint32_t                               _frame_count            = 2u;
        static const uint32_t                               _pixel_size             = 4u;
        static const uint32_t                               _vetices                = 6u;

        struct Vertex
        {
            DirectX::XMFLOAT3 position;
            DirectX::XMFLOAT2 uv;
        };

        Microsoft::WRL::ComPtr<IDXGISwapChain3>             _swap_chain;
        Microsoft::WRL::ComPtr<ID3D12Device>                _device;
        Microsoft::WRL::ComPtr<ID3D12Resource>              _render_targets[_frame_count];
        Microsoft::WRL::ComPtr<ID3D12CommandAllocator>      _command_allocator;
        Microsoft::WRL::ComPtr<ID3D12CommandQueue>          _command_queue;
        Microsoft::WRL::ComPtr<ID3D12RootSignature>         _root_signature;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>        _rtv_heap;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>        _srv_heap;
        Microsoft::WRL::ComPtr<ID3D12PipelineState>         _pipeline_state;
        Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>   _command_list;
        Microsoft::WRL::ComPtr<ID3D12Resource>              _texture_upload_heap;
        Microsoft::WRL::ComPtr<ID3D12Resource>              _vertex_buffer;
        Microsoft::WRL::ComPtr<ID3D12Resource>              _texture;
        Microsoft::WRL::ComPtr<ID3D12Fence>                 _fence;
        CD3DX12_VIEWPORT                                    _viewport;
        CD3DX12_RECT                                        _scissor_rect;
        D3D12_VERTEX_BUFFER_VIEW                            _vertex_buffer_view;
        HANDLE                                              _fence_event;
        WNDCLASSEXW                                         _window_class           {};
        uint32_t                                            _frame_index            = 0u;
        uint64_t                                            _fence_value            = 0u;
        uint32_t                                            _rtv_descriptor_size    = 0u;
        uint32_t                                            _width                  = 0u;
        uint32_t                                            _height                 = 0u;
        uint8_t*                                            _image_data             = nullptr;

        bool create_pipeline();
        bool create_root_signature();
        bool create_pipeline_state();
        bool create_vertex_buffer();
        bool create_texture ();
        bool create_fence();
        bool wait_for_previous_frame();
        bool get_hardware_adapter(IDXGIFactory1* pFactory, IDXGIAdapter1** ppAdapter);
    };
}

#endif

#endif // _PRIVATE_SCREEN_H_
