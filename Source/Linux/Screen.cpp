
#include <GL/glew.h>
#include <stdint.h>
#include <string>

#include "Base/Screen.h"
#include "Base/UtilsPgm.h"


namespace Screen
{
    namespace
    {
        bool build_shader_vertex(uint32_t& ShaderVertex)
        {
            const char* source_shader_vertex =
                "#version 330 core\n"
                "layout (location = 0) in vec4 input_position;\n"
                "layout (location = 1) in vec2 input_texture;\n"
                "out vec2 output_texture;\n"
                "void main()\n"
                "{\n"
                    "gl_Position    = input_position;\n"
                    "output_texture = input_texture;\n"
                "}\n"
                "\0";

            ShaderVertex = glCreateShader(GL_VERTEX_SHADER);

            glShaderSource(ShaderVertex, 1, &source_shader_vertex, NULL);

            glCompileShader(ShaderVertex);

            GLint success = 0;

            glGetShaderiv(ShaderVertex, GL_COMPILE_STATUS, &success);

            if (!success)
            {
                fprintf(stderr, "%s:%d:%s: Failed to compile vertex shader\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            return true;
        }


        bool build_shader_fragment(uint32_t& ShaderFragment)
        {
            const char* source_shader_fragment =
                "#version 330 core\n"
                "out vec4 fragment_color;\n"
                "in  vec2 output_texture;\n"
                "uniform sampler2D sampled_texture;\n"
                "void main()\n"
                "{\n"
                    "fragment_color = texture(sampled_texture, output_texture);\n"
                "}\n"
                "\0";

            ShaderFragment = glCreateShader(GL_FRAGMENT_SHADER);

            glShaderSource(ShaderFragment, 1, &source_shader_fragment, NULL);

            glCompileShader(ShaderFragment);

            GLint success = 0;

            glGetShaderiv(ShaderFragment, GL_COMPILE_STATUS, &success);

            if (!success)
            {
                fprintf(stderr, "%s:%d:%s: Failed to compile fragment shader\n", __FILE__, __LINE__, __FUNCTION__);
                return false;
            }

            return true;
        }


        bool build_program(uint32_t& ShaderProgram)
        {
            bool        ret_val         = true;
            uint32_t    shader_vertex   = 0u;
            uint32_t    shader_fragment = 0u;
            GLint       success         = 0;

            if (!build_shader_vertex(shader_vertex))
            {
                fprintf(stderr, "%s:%d:%s: Failed to build shader\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }

            if (!build_shader_fragment(shader_fragment))
            {
                fprintf(stderr, "%s:%d:%s: Failed to build shader\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }

            ShaderProgram = glCreateProgram();

            glAttachShader(ShaderProgram, shader_vertex);
            glAttachShader(ShaderProgram, shader_fragment);

            glLinkProgram(ShaderProgram);

            glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);

            if (!success)
            {
                fprintf(stderr, "%s:%d:%s: Failed to link shader program\n", __FILE__, __LINE__, __FUNCTION__);
                ret_val = false;
                goto terminate;
            }

        terminate:
            glDeleteShader(shader_vertex);
            glDeleteShader(shader_fragment);

            return ret_val;
        }
    }


    bool Screen::initialize(uint32_t ScreenWidth, uint32_t ScreenHeight, std::string& Title)
    {
        constexpr int32_t major_number = 3;
        constexpr int32_t minor_number = 3;

        _width  = ScreenWidth;
        _height = ScreenHeight;

        uint32_t shader_program = 0u;

        glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,  major_number);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,  minor_number);
        glfwWindowHint(GLFW_OPENGL_PROFILE,         GLFW_OPENGL_CORE_PROFILE);

        _window = glfwCreateWindow(_width, _height, Title.c_str(), NULL, NULL);

        if (!_window)
        {
            fprintf(stderr, "%s:%d:%s: Failed to create window\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        glfwMakeContextCurrent(_window);

        if (glewInit() != GLEW_OK)
        {
            fprintf(stderr, "%s:%d:%s: Failed to initialize GLEW\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        if (!build_program(shader_program))
        {
            fprintf(stderr, "%s:%d:%s: Failed to initialize GLEW\n", __FILE__, __LINE__, __FUNCTION__);
            return false;
        }

        float vertices[] =
        {
            0.5f,  0.5f, 0.0f, 1.0f,   1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f,   1.0f, 0.0f,
           -0.5f, -0.5f, 0.0f, 1.0f,   0.0f, 0.0f,
           -0.5f,  0.5f, 0.0f, 1.0f,   0.0f, 1.0f,
        };

        unsigned int indices[] =
        {
            0, 1, 3,
            1, 2, 3,
        };

        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(4 * sizeof(float)));
        glEnableVertexAttribArray(1);

        unsigned int texture;

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glUseProgram(shader_program);

        return true;
    }


    bool Screen::display_image(uint8_t* ImageData)
    {
        constexpr uint32_t channels = 3u;

        if (!_image_data)
        {
            _image_data = new uint8_t[3 * _width * _height]{};
        }

        for (uint32_t y = 0u; y < _height; y++)
        {
            for (uint32_t x = 0u; x < _width; x++)
            {
                _image_data[channels * (_width * (_height - 1u - y) + x) + 0u] = ImageData[_width * y + x];
                _image_data[channels * (_width * (_height - 1u - y) + x) + 1u] = ImageData[_width * y + x];
                _image_data[channels * (_width * (_height - 1u - y) + x) + 2u] = ImageData[_width * y + x];
            }
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _image_data);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(_window);

        glfwPollEvents();

        return true;
    }


    void Screen::deinitialize()
    {
        if (_image_data)
        {
            delete[] _image_data;
        }

        glDeleteVertexArrays(1, &_object_vertex_array);
        glDeleteBuffers     (1, &_object_vertex_buffer);
        glDeleteBuffers     (1, &_object_element_buffer);

        _image_data = nullptr;

        glfwTerminate();
    }
}
