#include <windows.h>
#include <string>
#include <iostream>

void SetSoundForEvent(const std::wstring& soundFilePath, const std::wstring& event) {
    HKEY hKey;
    std::wstring keyPath = L"AppEvents\\Schemes\\Apps\\.Default\\" + event + L"\\.Current";

    // Abre a chave de registro
    if (RegOpenKeyExW(HKEY_CURRENT_USER, keyPath.c_str(), 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        // Define o novo valor do som
        if (RegSetValueExW(hKey, NULL, 0, REG_SZ, (const BYTE*)soundFilePath.c_str(), (soundFilePath.size() + 1) * sizeof(wchar_t)) == ERROR_SUCCESS) {
            std::wcout << L"Som para o evento " << event.c_str() << L" alterado com sucesso para: " << soundFilePath.c_str() << std::endl;
        }
        else {
            std::wcerr << L"Erro ao definir o valor do registro para " << event.c_str() << L"." << std::endl;
        }
        RegCloseKey(hKey);
    }
    else {
        std::wcerr << L"Erro ao abrir a chave de registro para " << event.c_str() << L"." << std::endl;
    }
}

int wmain() {
    std::wstring deviceConnectSoundFilePath = L"C:\\Users\\Fred\\Documents\\gui.wav";
    std::wstring deviceDisconnectSoundFilePath = L"C:\\Users\\Fred\\Documents\\gui.wav";

    // Define os sons para os eventos de conexão e desconexão de dispositivo
    SetSoundForEvent(deviceConnectSoundFilePath, L"DeviceConnect");
    SetSoundForEvent(deviceDisconnectSoundFilePath, L"DeviceDisconnect");

    return 0;
}
