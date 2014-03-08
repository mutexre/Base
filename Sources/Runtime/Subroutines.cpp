#include <Runtime/Runtime.h>

void Rt::stridedCopy(const u1* src, u4 srcStride, u1* dst, u4 dstStride, u4 size, u4 count) {
    for (u4 i = 0; i < count; i++, src += srcStride, dst += dstStride)
        memcpy(dst, src, size);
}

std::string Rt::readFile(const char* path) {
    std::ifstream ifs(path);
    std::stringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}

std::string Rt::readFile(const std::string& path) {
    return readFile(path.c_str());
}

#if defined _WIN32 || defined _WIN64
std::string Rt::readTextResource(const char* type, int id) {
    HMODULE handle = GetModuleHandleA(nullptr);
    HRSRC rc = FindResource(nullptr, MAKEINTRESOURCE(id), type);
    HGLOBAL rcData = LoadResource(handle, rc);
    DWORD data_size = ::SizeofResource(handle, rc);

    std::string result;

    if (data_size != 0) {
        const char* data = (const char*)::LockResource(rcData);
        result.assign(data, data_size);
    }

    return result;
}
#endif
