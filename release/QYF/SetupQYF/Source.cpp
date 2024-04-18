#include<iostream>
#include<cstdio>
#include<windows.h>
#include<detours.h>
#include<thread>

#pragma comment(lib, "detours.lib")
using namespace std;

int main(int argc, char* argv[]) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    si.cb = sizeof(STARTUPINFO);

    // �ļ���·��
    WCHAR DirPath[MAX_PATH + 1];
    wcscpy_s(DirPath, MAX_PATH, L"D:\\VSProjects\\qyf\\PFDLL\\Debug");    // dll�ļ���

    // �ļ�·��
    char DLLPath[MAX_PATH + 1] = "D:\\VSProjects\\qyf\\PFDLL\\Debug\\PFDLL.dll"; // dll�ĵ�ַ

    // ����·��
    WCHAR EXE[MAX_PATH + 1] = { 0 };
    wcscpy_s(EXE, MAX_PATH, L"D:\\VSProjects\\qyf\\testCode\\Debug\\testCode.exe");


    if (DetourCreateProcessWithDllEx(EXE, NULL, NULL, NULL, TRUE,
        CREATE_DEFAULT_ERROR_MODE | CREATE_SUSPENDED, NULL, DirPath,
        &si, &pi, DLLPath, NULL)) {
        // �ָ��߳�
        ResumeThread(pi.hThread);
        WaitForSingleObject(pi.hProcess, INFINITE);
    }
    else {
        char error[100];
        sprintf(error, "%d", GetLastError());

        // ��ӡ������Ϣ������̨
        std::cout << "�޷��򿪽���: " << error << std::endl;
    }
    return 0;
}
