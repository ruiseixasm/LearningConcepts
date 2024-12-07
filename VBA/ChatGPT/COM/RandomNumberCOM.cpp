#include <windows.h>
#include <objbase.h>
#include <random>
#include <thread>
#include <chrono>

extern "C" HRESULT __stdcall DllRegisterServer() {
    // Register the COM server (implement as needed, typically involves registry writes)
    return S_OK; // Return S_OK to indicate success
}

extern "C" HRESULT __stdcall DllUnregisterServer() {
    // Unregister the COM server (clean up registry entries)
    return S_OK; // Return S_OK to indicate success
}

// Define GUIDs for the COM object
// Use a GUID generator tool to replace these placeholders
const CLSID CLSID_RandomNumberGenerator = { /* Insert CLSID GUID */ };
const IID IID_IRandomNumberGenerator = { /* Insert IID GUID */ };

// Define the IRandomNumberGenerator interface
interface IRandomNumberGenerator : public IUnknown {
    virtual HRESULT STDMETHODCALLTYPE GetRandomNumber(int* number) = 0;
    virtual HRESULT STDMETHODCALLTYPE GenerateRandomNumber() = 0;
};

// Implementation of the RandomNumberGenerator class
class RandomNumberGenerator : public IRandomNumberGenerator {
    LONG refCount;
    int lastRandomNumber;

public:
    RandomNumberGenerator() : refCount(1), lastRandomNumber(0) {}

    // IUnknown methods
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) {
        if (riid == IID_IUnknown || riid == IID_IRandomNumberGenerator) {
            *ppvObject = static_cast<IRandomNumberGenerator*>(this);
            AddRef();
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    ULONG STDMETHODCALLTYPE AddRef() { return InterlockedIncrement(&refCount); }
    ULONG STDMETHODCALLTYPE Release() {
        LONG count = InterlockedDecrement(&refCount);
        if (count == 0) {
            delete this;
        }
        return count;
    }

    // IRandomNumberGenerator methods
    HRESULT STDMETHODCALLTYPE GetRandomNumber(int* number) {
        *number = lastRandomNumber;
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE GenerateRandomNumber() {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        lastRandomNumber = rand() % 100; // Random number between 0 and 99
        return S_OK;
    }
};

// Factory function to create the RandomNumberGenerator object
class RandomNumberGeneratorFactory : public IClassFactory {
public:
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject) {
        if (riid == IID_IUnknown || riid == IID_IClassFactory) {
            *ppvObject = static_cast<IClassFactory*>(this);
            return S_OK;
        }
        *ppvObject = nullptr;
        return E_NOINTERFACE;
    }
    ULONG STDMETHODCALLTYPE AddRef() { return 1; }
    ULONG STDMETHODCALLTYPE Release() { return 1; }

    HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject) {
        if (pUnkOuter != nullptr) {
            return CLASS_E_NOAGGREGATION;
        }

        RandomNumberGenerator* generator = new RandomNumberGenerator();
        return generator->QueryInterface(riid, ppvObject);
    }

    HRESULT STDMETHODCALLTYPE LockServer(BOOL) { return S_OK; }
};

// DLL Entry Point
extern "C" BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

// Exported functions
extern "C" HRESULT STDMETHODCALLTYPE DllGetClassObject(REFCLSID clsid, REFIID riid, void** ppv) {
    if (clsid == CLSID_RandomNumberGenerator) {
        static RandomNumberGeneratorFactory factory;
        return factory.QueryInterface(riid, ppv);
    }
    *ppv = nullptr;
    return CLASS_E_CLASSNOTAVAILABLE;
}

extern "C" HRESULT STDMETHODCALLTYPE DllCanUnloadNow() {
    return S_OK;
}
