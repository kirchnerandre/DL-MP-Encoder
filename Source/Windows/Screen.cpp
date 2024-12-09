
#include "Base/Screen.h"


namespace Screen
{
    HWND _window_handle = nullptr;

    namespace
    {
        LRESULT CALLBACK window_procedure(HWND Window, uint32_t Message, WPARAM WParam, LPARAM LParam)
        {
            LRESULT ret_val = 0;

            Screen* screen = reinterpret_cast<Screen*>(GetWindowLongPtr(Window, GWLP_USERDATA));

            switch (Message)
            {
            case WM_CREATE:
            {
                LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(LParam);
                SetWindowLongPtr(Window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
                ret_val = 0;
            }
            break;

            case WM_PAINT:
                if (screen)
                {
                    screen->on_render();
                }
                ret_val = 0;
                break;

            case WM_DESTROY:
                PostQuitMessage(0);
                ret_val = 0;
                break;

            default:
                ret_val = DefWindowProc(Window, Message, WParam, LParam);
            }

            return ret_val;
        }


        bool initialize_window(uint32_t ScreenWidth, uint32_t ScreenHeight, std::string& Title, WNDCLASSEXW WindowClass, Screen* Screen)
        {
            WindowClass.cbSize         = sizeof(WNDCLASSEX);
            WindowClass.style          = CS_HREDRAW | CS_VREDRAW;
            WindowClass.lpfnWndProc    = window_procedure;
            WindowClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
            WindowClass.lpszClassName  = L"ClassName";

            if (!RegisterClassExW(&WindowClass))
            {
                fprintf(stderr, "%d %x\n", GetLastError(), GetLastError());
                fprintf(stderr, "%s:%d:%s: Failed to register class\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            RECT windowRect = { 0, 0, static_cast<LONG>(ScreenWidth), static_cast<LONG>(ScreenHeight) };

            if (!AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE))
            {
                fprintf(stderr, "%s:%d:%s: Failed to adjust window\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            _window_handle = CreateWindow(WindowClass.lpszClassName,
                                          nullptr,
                                          WS_OVERLAPPEDWINDOW,
                                          CW_USEDEFAULT,
                                          CW_USEDEFAULT,
                                          windowRect.right - windowRect.left,
                                          windowRect.bottom - windowRect.top,
                                          nullptr,
                                          nullptr,
                                          WindowClass.hInstance,
                                          Screen);

            if (!_window_handle)
            {
                fprintf(stderr, "%s:%d:%s: Failed to create window\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            ShowWindow(_window_handle, SW_SHOW);

            return true;
        }
    }


    bool Screen::initialize(uint32_t ScreenWidth, uint32_t ScreenHeight, std::string& Title)
    {
        _width                  = ScreenWidth;
        _height                 = ScreenHeight;
        _frame_index            = 0;

        _viewport.TopLeftX      = 0.0f;
        _viewport.TopLeftY      = 0.0f;
        _viewport.Width         = static_cast<float>(ScreenWidth);
        _viewport.Height        = static_cast<float>(ScreenHeight);

        _scissor_rect.top       = 0;
        _scissor_rect.left      = 0;
        _scissor_rect.right     = static_cast<LONG>(ScreenWidth);
        _scissor_rect.bottom    = static_cast<LONG>(ScreenHeight);

        _rtv_descriptor_size = 0;

        if (!initialize_window(ScreenWidth, ScreenHeight, Title, _window_class, this))
        {
            fprintf(stderr, "%s:%d:%s: Failed to initialize window\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (!create_pipeline())
        {
            fprintf(stderr, "%s:%d:%s: Failed to load pipeline\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (!create_root_signature())
        {
            fprintf(stderr, "%s:%d:%s: Failed to create root signature\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (!create_pipeline_state())
        {
            fprintf(stderr, "%s:%d:%s: Failed to create pipeline state\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (!create_vertex_buffer())
        {
            fprintf(stderr, "%s:%d:%s: Failed to create vertex buffer\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (!create_fence())
        {
            fprintf(stderr, "%s:%d:%s: Failed to create fence\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (!create_texture())
        {
            fprintf(stderr, "%s:%d:%s: Failed to create texture\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    bool Screen::display_image(uint8_t* ImageData)
    {
        if (!_image_data)
        {
            _image_data = new uint8_t[_width * _height * _pixel_size]{};
        }

        for (uint32_t y = 0u; y < _height; y++)
        {
            for (uint32_t x = 0u; x < _width; x++)
            {
                uint32_t offset =  (y * _width + x);

                _image_data[_pixel_size * offset + 0] = ImageData[offset];
                _image_data[_pixel_size * offset + 1] = ImageData[offset];
                _image_data[_pixel_size * offset + 2] = ImageData[offset];
                _image_data[_pixel_size * offset + 3] = 0xff;
            }
        }

        if (_command_allocator->Reset() != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to reset command allocator\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (_command_list->Reset(_command_allocator.Get(), _pipeline_state.Get()) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to reset command allocator\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        _command_list->SetGraphicsRootSignature(_root_signature.Get());

        ID3D12DescriptorHeap* descriptor_heaps[] = { _srv_heap.Get() };

        _command_list->SetDescriptorHeaps(_countof(descriptor_heaps), descriptor_heaps);

        _command_list->SetGraphicsRootDescriptorTable(0, _srv_heap->GetGPUDescriptorHandleForHeapStart());
        _command_list->RSSetViewports(1, &_viewport);
        _command_list->RSSetScissorRects(1, &_scissor_rect);

        _command_list->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(_render_targets[_frame_index].Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

        CD3DX12_CPU_DESCRIPTOR_HANDLE rtv_handle(_rtv_heap->GetCPUDescriptorHandleForHeapStart(), _frame_index, _rtv_descriptor_size);

        _command_list->OMSetRenderTargets(1, &rtv_handle, FALSE, nullptr);
        _command_list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        _command_list->IASetVertexBuffers(0, 1, &_vertex_buffer_view);
        _command_list->DrawInstanced(_vetices, 1, 0, 0);

        D3D12_SUBRESOURCE_DATA texture_data{};

        texture_data.pData      = _image_data;
        texture_data.RowPitch   = _width * _pixel_size;
        texture_data.SlicePitch = texture_data.RowPitch * _height;

        UpdateSubresources(_command_list.Get(), _texture.Get(), _texture_upload_heap.Get(), 0, 0, 1, &texture_data);

        _command_list->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(_render_targets[_frame_index].Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

        if (_command_list->Close() != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to close command list\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        MSG msg{};

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage (&msg);
        }

        return true;
    }


    void Screen::deinitialize()
    {
        if (!DestroyWindow(_window_handle))
        {
            fprintf(stderr, "%s:%d:%s: Failed to destroy window\n", __FILE__, __LINE__, __FUNCTION__);
        }

        if (!UnregisterClassA("ClassName", _window_class.hInstance))
        {
            fprintf(stderr, "%s:%d:%s: Failed to unregister class\n", __FILE__, __LINE__, __FUNCTION__);
        }

        if (_image_data)
        {
            delete[] _image_data;
        }

        _image_data = nullptr;
    }


    bool PrivateScreen::create_pipeline()
    {
        uint32_t                                dxgiFactoryFlags = DXGI_CREATE_FACTORY_DEBUG;

        Microsoft::WRL::ComPtr<ID3D12Debug>     debug;
        Microsoft::WRL::ComPtr<IDXGIFactory4>   factory;
        Microsoft::WRL::ComPtr<IDXGIAdapter1>   adapter;
        Microsoft::WRL::ComPtr<IDXGISwapChain1> swap_chain;

        D3D12_COMMAND_QUEUE_DESC                command_queue_descriptor{};
        DXGI_SWAP_CHAIN_DESC1                   swap_chain_descriptor   {};
        D3D12_DESCRIPTOR_HEAP_DESC              rtv_heap_descriptor     {};
        D3D12_DESCRIPTOR_HEAP_DESC              srv_heap_descriptor     {};

        if (D3D12GetDebugInterface(IID_PPV_ARGS(&debug)) < 0)
        {
            fprintf(stderr, "%s:%d:%s: Failed to instantiate debugger\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        debug->EnableDebugLayer();

        if (CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory)) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to create factory\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (!get_hardware_adapter(factory.Get(), &adapter))
        {
            fprintf(stderr, "%s:%d:%s: Failed to find Directx12 compatible device\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&_device)) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to create device\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        command_queue_descriptor.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        command_queue_descriptor.Type  = D3D12_COMMAND_LIST_TYPE_DIRECT;

        if (_device->CreateCommandQueue(&command_queue_descriptor, IID_PPV_ARGS(&_command_queue)) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to create command queue\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        swap_chain_descriptor.BufferCount       = _frame_count;
        swap_chain_descriptor.Width             = _width;
        swap_chain_descriptor.Height            = _height;
        swap_chain_descriptor.Format            = DXGI_FORMAT_R8G8B8A8_UNORM;
        swap_chain_descriptor.BufferUsage       = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_descriptor.SwapEffect        = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        swap_chain_descriptor.SampleDesc.Count  = 1;

        if (factory->CreateSwapChainForHwnd(_command_queue.Get(), _window_handle, &swap_chain_descriptor, nullptr, nullptr, &swap_chain) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to create swap chain\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (factory->MakeWindowAssociation(_window_handle, DXGI_MWA_NO_ALT_ENTER) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to associate\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (swap_chain.As(&_swap_chain) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to command execution\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        _frame_index = _swap_chain->GetCurrentBackBufferIndex();

        rtv_heap_descriptor.NumDescriptors  = _frame_count;
        rtv_heap_descriptor.Type            = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        rtv_heap_descriptor.Flags           = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

        if (_device->CreateDescriptorHeap(&rtv_heap_descriptor, IID_PPV_ARGS(&_rtv_heap)) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to create descriptor heap\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        srv_heap_descriptor.NumDescriptors  = 1;
        srv_heap_descriptor.Type            = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        srv_heap_descriptor.Flags           = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

        if (_device->CreateDescriptorHeap(&srv_heap_descriptor, IID_PPV_ARGS(&_srv_heap)) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to create descriptor heap\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        _rtv_descriptor_size = _device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

        CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(_rtv_heap->GetCPUDescriptorHandleForHeapStart());

        for (uint32_t n = 0; n < _frame_count; n++)
        {
            if (_swap_chain->GetBuffer(n, IID_PPV_ARGS(&_render_targets[n])) != S_OK)
            {
                fprintf(stderr, "%s:%d:%s: Failed to get buffer\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            _device->CreateRenderTargetView(_render_targets[n].Get(), nullptr, rtvHandle);

            rtvHandle.Offset(1, _rtv_descriptor_size);
        }

        if (_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_command_allocator)) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to create command allocator\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    bool PrivateScreen::create_root_signature()
    {
        D3D12_FEATURE_DATA_ROOT_SIGNATURE       feature_data_root_signature{};
        D3D12_STATIC_SAMPLER_DESC               static_sampler_descriptor{};
        CD3DX12_DESCRIPTOR_RANGE1               descriptor_range;
        CD3DX12_ROOT_PARAMETER1                 root_parameter[1];
        CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC   versioned_root_signature_descriptor;
        Microsoft::WRL::ComPtr<ID3DBlob>        signature;
        Microsoft::WRL::ComPtr<ID3DBlob>        error;

        feature_data_root_signature.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_1;

        if (FAILED(_device->CheckFeatureSupport(D3D12_FEATURE_ROOT_SIGNATURE, &feature_data_root_signature, sizeof(feature_data_root_signature))))
        {
            feature_data_root_signature.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_0;
        }

        descriptor_range.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0, 0, D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC);

        root_parameter[0].InitAsDescriptorTable(1, &descriptor_range, D3D12_SHADER_VISIBILITY_PIXEL);

        static_sampler_descriptor.Filter            = D3D12_FILTER_MIN_MAG_MIP_POINT;
        static_sampler_descriptor.AddressU          = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
        static_sampler_descriptor.AddressV          = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
        static_sampler_descriptor.AddressW          = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
        static_sampler_descriptor.MipLODBias        = 0;
        static_sampler_descriptor.MaxAnisotropy     = 0;
        static_sampler_descriptor.ComparisonFunc    = D3D12_COMPARISON_FUNC_NEVER;
        static_sampler_descriptor.BorderColor       = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
        static_sampler_descriptor.MinLOD            = 0.0f;
        static_sampler_descriptor.MaxLOD            = D3D12_FLOAT32_MAX;
        static_sampler_descriptor.ShaderRegister    = 0;
        static_sampler_descriptor.RegisterSpace     = 0;
        static_sampler_descriptor.ShaderVisibility  = D3D12_SHADER_VISIBILITY_PIXEL;

        versioned_root_signature_descriptor.Init_1_1(_countof(root_parameter), root_parameter, 1, &static_sampler_descriptor, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

        if (FAILED(D3DX12SerializeVersionedRootSignature(&versioned_root_signature_descriptor, feature_data_root_signature.HighestVersion, &signature, &error)))
        {
            fprintf(stderr, "%s:%d:%s: Failed to serialize root signature\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (FAILED(_device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&_root_signature))))
        {
            fprintf(stderr, "%s:%d:%s: Failed to create root signature\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    bool PrivateScreen::create_pipeline_state()
    {
        Microsoft::WRL::ComPtr<ID3DBlob> vertex_shader;
        Microsoft::WRL::ComPtr<ID3DBlob> pixel_shader;

        uint32_t compile_flags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

        if (D3DCompileFromFile(L"Source/Windows/shaders.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", compile_flags, 0, &vertex_shader, nullptr) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to compile vertex shader\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (D3DCompileFromFile(L"Source/Windows/shaders.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", compile_flags, 0, &pixel_shader, nullptr) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to compile pixel shader\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
        };

        D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};

        psoDesc.InputLayout                     = { inputElementDescs, _countof(inputElementDescs) };
        psoDesc.pRootSignature                  = _root_signature.Get();
        psoDesc.VS                              = CD3DX12_SHADER_BYTECODE(vertex_shader.Get());
        psoDesc.PS                              = CD3DX12_SHADER_BYTECODE(pixel_shader.Get());
        psoDesc.RasterizerState                 = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
        psoDesc.BlendState                      = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
        psoDesc.DepthStencilState.DepthEnable   = FALSE;
        psoDesc.DepthStencilState.StencilEnable = FALSE;
        psoDesc.SampleMask                      = UINT_MAX;
        psoDesc.PrimitiveTopologyType           = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        psoDesc.NumRenderTargets                = 1;
        psoDesc.RTVFormats[0]                   = DXGI_FORMAT_R8G8B8A8_UNORM;
        psoDesc.SampleDesc.Count                = 1;

        if (_device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&_pipeline_state)) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to create graphics pipeline state\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _command_allocator.Get(), _pipeline_state.Get(), IID_PPV_ARGS(&_command_list)) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to create command list\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    bool PrivateScreen::create_vertex_buffer()
    {
        Vertex vertices[] =
        {
            { { -1.0f,  1.0f, 0.0f }, { 0.0f, 0.0f } }, // A
            { {  1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } }, // C
            { { -1.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } }, // D

            { { -1.0f,  1.0f, 0.0f }, { 0.0f, 0.0f } }, // A
            { {  1.0f,  1.0f, 0.0f }, { 1.0f, 0.0f } }, // B
            { {  1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } }, // C
        };

        const uint32_t vertex_buffer_size = sizeof(vertices);

        if (_device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
                                             D3D12_HEAP_FLAG_NONE,
                                             &CD3DX12_RESOURCE_DESC::Buffer(vertex_buffer_size),
                                             D3D12_RESOURCE_STATE_GENERIC_READ,
                                             nullptr,
                                             IID_PPV_ARGS(&_vertex_buffer)) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to create commited resource\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        uint8_t* vertex_data_begin = nullptr;

        CD3DX12_RANGE read_range(0, 0);

        if (_vertex_buffer->Map(0, &read_range, reinterpret_cast<void**>(&vertex_data_begin)) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to map vertex buffer\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        memcpy(vertex_data_begin, vertices, sizeof(vertices));

        _vertex_buffer->Unmap(0, nullptr);

        _vertex_buffer_view.BufferLocation  = _vertex_buffer->GetGPUVirtualAddress();
        _vertex_buffer_view.StrideInBytes   = sizeof(Vertex);
        _vertex_buffer_view.SizeInBytes     = vertex_buffer_size;

        return true;
    }


    bool PrivateScreen::create_fence()
    {
        if (_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_fence)) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to create fence\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        _fence_value = 1;

        _fence_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);

        if ((_fence_event == nullptr) && (HRESULT_FROM_WIN32(GetLastError()) != S_OK))
        {
            fprintf(stderr, "%s:%d:%s: Failed to create event\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        return true;
    }


    bool PrivateScreen::create_texture()
    {
        D3D12_RESOURCE_DESC texture_descriptor{};

        texture_descriptor.MipLevels            = 1;
        texture_descriptor.Format               = DXGI_FORMAT_R8G8B8A8_UNORM;
        texture_descriptor.Width                = _width;
        texture_descriptor.Height               = _height;
        texture_descriptor.Flags                = D3D12_RESOURCE_FLAG_NONE;
        texture_descriptor.DepthOrArraySize     = 1;
        texture_descriptor.SampleDesc.Count     = 1;
        texture_descriptor.SampleDesc.Quality   = 0;
        texture_descriptor.Dimension            = D3D12_RESOURCE_DIMENSION_TEXTURE2D;

        if (_device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
                                             D3D12_HEAP_FLAG_NONE,
                                             &texture_descriptor,
                                             D3D12_RESOURCE_STATE_COPY_DEST,
                                             nullptr,
                                             IID_PPV_ARGS(&_texture)) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to create committed resource\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        const UINT64 upload_buffer_size = GetRequiredIntermediateSize(_texture.Get(), 0, 1);

        if (_device->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
                                             D3D12_HEAP_FLAG_NONE,
                                             &CD3DX12_RESOURCE_DESC::Buffer(upload_buffer_size),
                                             D3D12_RESOURCE_STATE_GENERIC_READ,
                                             nullptr,
                                             IID_PPV_ARGS(&_texture_upload_heap)) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to create committed resource\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        _command_list->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(_texture.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));

        D3D12_SHADER_RESOURCE_VIEW_DESC shader_resource_view_descriptor{};

        shader_resource_view_descriptor.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        shader_resource_view_descriptor.Format                  = texture_descriptor.Format;
        shader_resource_view_descriptor.ViewDimension           = D3D12_SRV_DIMENSION_TEXTURE2D;
        shader_resource_view_descriptor.Texture2D.MipLevels     = 1;

        _device->CreateShaderResourceView(_texture.Get(), &shader_resource_view_descriptor, _srv_heap->GetCPUDescriptorHandleForHeapStart());

        if (_command_list->Close() != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to close command list\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        ID3D12CommandList* command_lists[] = { _command_list.Get() };

        _command_queue->ExecuteCommandLists(_countof(command_lists), command_lists);

        wait_for_previous_frame();

        return true;
    }


    void PrivateScreen::on_render()
    {
        ID3D12CommandList* command_lists[] = { _command_list.Get() };

        _command_queue->ExecuteCommandLists(_countof(command_lists), command_lists);

        if (_swap_chain->Present(1, 0) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to present swap chain\n", __FILE__, __LINE__, __FUNCTION__);
        }

        wait_for_previous_frame();
    }


    void PrivateScreen::on_destroy()
    {
        wait_for_previous_frame();

        CloseHandle(_fence_event);
    }


    bool PrivateScreen::wait_for_previous_frame()
    {
        const UINT64 fence = _fence_value;

        if (_command_queue->Signal(_fence.Get(), fence) != S_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to signal command list\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        _fence_value++;

        if (_fence->GetCompletedValue() < fence)
        {
            if (_fence->SetEventOnCompletion(fence, _fence_event) != S_OK)
            {
                fprintf(stderr, "%s:%d:%s: Failed to set event on completion\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            if (WaitForSingleObject(_fence_event, INFINITE) != WAIT_OBJECT_0)
            {
                fprintf(stderr, "%s:%d:%s: Failed to wait for event\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }
        }

        _frame_index = _swap_chain->GetCurrentBackBufferIndex();

        return true;
    }


    bool PrivateScreen::get_hardware_adapter(IDXGIFactory1* Factory, IDXGIAdapter1** Adapter)
    {
        bool ret_val = false;

        Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;

        if (adapter.Get() == nullptr)
        {
            for (uint32_t adapterIndex = 0; SUCCEEDED(Factory->EnumAdapters1(adapterIndex, &adapter)); ++adapterIndex)
            {
                DXGI_ADAPTER_DESC1 desc{};

                adapter->GetDesc1(&desc);

                if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
                {
                    continue;
                }

                if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)))
                {
                    *Adapter = adapter.Detach();
                    ret_val = true;
                    break;
                }
            }
        }

        return ret_val;
    }
}
