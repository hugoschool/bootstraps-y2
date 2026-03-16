#pragma once

#include <dlfcn.h>
#include <memory>
#include <string>

template <typename T>
class DLLoader {
    public:
        DLLoader(const std::string libraryName) : _libraryName(libraryName), _handle(nullptr)
        {
        };

        ~DLLoader()
        {
            closeHandle();
        };

        void *openHandle()
        {
            _handle = dlopen(_libraryName.c_str(), RTLD_LAZY);
            // TODO: return error if _handle is null
            return _handle;
        }

        std::unique_ptr<T> getInstance(const std::string functionName = "entrypoint")
        {
            if (_handle == nullptr)
                openHandle();

            T *(*function)() = (T *(*)())dlsym(_handle, functionName.c_str());
            // TODO: return error if function is null
            T *instance = (*function)();
            // TODO: return error if instance is null
            return std::unique_ptr<T>(instance);
        };

        void closeHandle()
        {
            if (_handle == nullptr)
                return;
            dlclose(_handle);
            _handle = nullptr;
        }

    private:
        const std::string _libraryName;
        void *_handle;
};
