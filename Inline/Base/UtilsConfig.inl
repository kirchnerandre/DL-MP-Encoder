
namespace UtilsConfig
{
    template<typename T>
    bool read(T& Key, std::string& Filename)
    {
        bool    ret_val = true;
        FILE*   file    = fopen(Filename.c_str(), "rb");

        if (!file)
        {
            fprintf(stderr, "%s:%d:%s: Failed to open file\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

        if (fread(&Key, 1u, sizeof(T), file) != sizeof(T))
        {
            fprintf(stderr, "%s:%d:%s: Failed to read file\n", __FILE__, __LINE__, __FUNCTION__);
            ret_val = false;
            goto terminate;
        }

    terminate:
        if (file)
        {
            fclose(file);
        }

        return ret_val;
    }
}
