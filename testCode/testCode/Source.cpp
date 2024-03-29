#include<windows.h>
#include<stdio.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib")  //���� ws2_32.dll

#define PAGE_SIZE    4096

using namespace std;

void heapCreateAndDestory();

void writeFileString();

void readFileString();

void regCreateAndSetValue();

void regOpenAndDelValue();

void showMenu();

void heapRepeatedRelease();

void modifyExProgram();

void selfReplication();

void modifyStartupRegistry();

void openAnotherFolder();

void recvData();

void sendData();

void memoryOperation();


int main() {
    int op = 0;

    while (1) {
        // ��ʾ�˵�
        showMenu();
        // �����û������ѡ��
        scanf("%d", &op);
        // ����ѡ��ִ����Ӧ����
        switch (op) {
        case 0: {
            // �˳�����
            printf("bye!\n");
            break;
        }
        case 1: {
            // ����MessageBoxA������ʾ��Ϣ��
            MessageBoxA(NULL, "I'm MessageBoxA", "I'm MessageBoxA's title", MB_OK);
            break;
        }
        case 2: {
            // ����MessageBoxW������ʾ��Ϣ��
            MessageBoxW(NULL, L"I'm MessageBoxW", L"I'm MessageBoxW's title", MB_OK);
            break;
        }
        case 3: {
            // ����heapCreateAndDestory����
            // ���жѵĴ��������ٲ���
            heapCreateAndDestory();
            break;
        }
        case 4: {
            // ����writeFileString����
            // ������д���ļ�
            writeFileString();
            break;
        }
        case 5: {
            // ����readFileString����
            // ��������ȡ�ļ�����
            readFileString();
            break;
        }
        case 6: {
            // ����regCreateAndSetValue����
            // ����������ע���ֵ���ر�ע���
            regCreateAndSetValue();
            break;
        }
        case 7: {
            // ����regOpenAndDelValue����
            // �򿪡�ɾ��ע���ֵ���ر�ע���
            regOpenAndDelValue();
            break;
        }
        case 8: {
            // ����recvData����
            // �����׽�������
            recvData();
            break;
        }
        case 9: {
            // ����sendData����
            // �����׽�������
            sendData();
            break;
        }
        case 10: {
            // ����headRepeatedRelease����
            // ִ���ظ��ͷ�ͷ���Ĳ���
            heapRepeatedRelease();
            break;
        }
        case 11: {
            // ����modifyExProgram����
            // �޸Ŀ�ִ�г���
            modifyExProgram();
            break;
        }
        case 12: {
            // ����selfReplication����
            // ִ�����Ҹ��Ʋ���
            selfReplication();
            break;
        }
        case 13: {
            // ����modifyStartupRegistry����
            // �޸�������ע���
            modifyStartupRegistry();
            break;
        }
        case 14: {
            // ����openAnotherFolder����
            // ����һ���ļ���
            openAnotherFolder();
            break;
        }
        case 15: {
            // ����memoryOperation����
            // �����ڴ����
            memoryOperation();
            break;
        }
        }
        // ���ѡ��Ϊ�˳�ѡ�0�������˳�ѭ��
        if (op == 0) {
            break;
        }
    }

    return 0;
}

void showMenu() {
    printf("--------------------------------��ѡ��һ��ѡ��--------------------------------\n");
    printf("--��������--:\n");
    printf("1. ������Ϣ��A\n");
    printf("2. ������Ϣ��W\n");
    printf("3. ���������ٶ�\n");
    printf("4. д���ļ��ַ���\n");
    printf("5. ��ȡ�ļ��ַ���\n");
    printf("6. ����������ע���ֵ\n");
    printf("7. �򿪲�ɾ��ע���ֵ\n");
    printf("8. �����׽�������\n");
    printf("9. �����׽�������\n");
    printf("--�������--:\n");
    printf("10. �ظ��ͷ�ͷ��\n");
    printf("11. �޸Ŀ�ִ�г���\n");
    printf("12. ���Ҹ���\n");
    printf("13. �޸�������ע���\n");
    printf("14. ����һ���ļ���\n");
}

void heapCreateAndDestory() {
    printf("����������� HeapCreate !\n");
    getchar();
    HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, PAGE_SIZE * 10, PAGE_SIZE * 100);

    int* pArr = (int*)HeapAlloc(hHeap, 0, sizeof(int) * 30);
    for (int i = 0; i < 30; ++i) {
        pArr[i] = i + 1;
    }
    printf("�ɹ�������!\n");
    for (int i = 0; i < 30; ++i) {
        if (i % 5 == 0)
            printf_s("\n");
        printf("%3d ", pArr[i]);
    }
    printf_s("\n\n");
    printf("����������� HeapFree !\n");
    getchar();
    HeapFree(hHeap, 0, pArr);
    printf("����������� HeapDestory !\n");
    getchar();
    HeapDestroy(hHeap);

    printf("�ɹ����ٶ�!\n");
}

void writeFileString() {
    CHAR* pBuffer;
    int fileSize = 0;
    char writeString[100];
    bool flag;
    HANDLE hOpenFile = (HANDLE)CreateFile(L"a.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
        NULL, NULL);
    if (hOpenFile == INVALID_HANDLE_VALUE) {
        hOpenFile = NULL;
        printf("�����Ч���޷����ļ�\n");
        return;
    }
    printf("�ɹ����ļ���\n");
    printf("������һ���ַ���:");
    scanf("%s", writeString);
    flag = WriteFile(hOpenFile, writeString, strlen(writeString), NULL, NULL);
    if (flag) {
        printf("�ɹ�д���ļ���\n");
    }
    FlushFileBuffers(hOpenFile);
    CloseHandle(hOpenFile);
}

void readFileString() {
    CHAR* pBuffer;
    int fileSize = 0;
    bool flag;
    HANDLE hOpenFile = (HANDLE)CreateFile(L"a.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, NULL);
    if (hOpenFile == INVALID_HANDLE_VALUE) {
        hOpenFile = NULL;
        printf("�޷����ļ�\n");
        return;
    }
    printf("�ɹ����ļ�\n");
    fileSize = GetFileSize(hOpenFile, NULL);
    pBuffer = (char*)malloc((fileSize + 1) * sizeof(char));
    flag = ReadFile(hOpenFile, pBuffer, fileSize, NULL, NULL);
    pBuffer[fileSize] = 0;
    if (flag) {
        printf("�ɹ���ȡ�ַ���:%s!\n", pBuffer);
    }
    else {
        printf("��ȡ�ַ���ʧ��!\n");
    }
    free(pBuffer);
    CloseHandle(hOpenFile);
}

void regCreateAndSetValue() {
    // ����ע������ü�ֵ
    HKEY hKey = NULL;
    TCHAR Data[254];
    memset(Data, 0, sizeof(Data));
    wcsncpy_s(Data, TEXT("https://github.com/AgentGuo"), 254);

    size_t lRet = RegCreateKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"aaaMykey", 0, NULL, REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS, NULL, &hKey, NULL);
    if (lRet == ERROR_SUCCESS) {
        printf("�ɹ�����ע���!\n");
    }
    else {
        printf("����ע���ʧ��!\n");
    }
    // �޸�ע����ֵ��û���򴴽���
    size_t iLen = wcslen(Data);
    // ���ü�ֵ
    lRet = RegSetValueEx(hKey, L"qyf", 0, REG_SZ, (CONST BYTE*) Data, sizeof(TCHAR) * iLen);
    if (lRet == ERROR_SUCCESS) {
        printf("�ɹ�Ϊע������ü�ֵ!\n");
        return;
    }
    else {
        printf("Ϊע������ü�ֵʧ��!\n");
    }
    RegCloseKey(hKey);
}

void regOpenAndDelValue() {
    HKEY hKey = NULL;
    size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"aaaMykey", 0, KEY_ALL_ACCESS, &hKey);
    if (lRet == ERROR_SUCCESS) {
        printf("�ɹ���ע���!\n");
    }
    else {
        printf("�޷���ע���!\n");
    }
    lRet = RegDeleteValue(hKey, L"qyf");
    if (lRet == ERROR_SUCCESS) {
        printf("�ɹ�ɾ��!\n");
    }
    else {
        printf("ɾ��ʧ��!\n");
    }
    RegCloseKey(hKey);
}

void heapRepeatedRelease() {
    printf("����������� HeapCreate !\n");
    getchar();
    HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, PAGE_SIZE * 10, PAGE_SIZE * 100);

    int* pArr = (int*)HeapAlloc(hHeap, 0, sizeof(int) * 30);
    for (int i = 0; i < 30; ++i) {
        pArr[i] = i + 1;
    }
    printf("�ɹ�������!\n");
    for (int i = 0; i < 30; ++i) {
        if (i % 5 == 0)
            printf_s("\n");
        printf("%3d ", pArr[i]);
    }
    printf_s("\n\n");
    printf("�������������һ�� HeapFree !\n");
    getchar();
    HeapFree(hHeap, 0, pArr);
    printf("������������ڶ��� HeapFree !\n");
    getchar();
    HeapFree(hHeap, 0, pArr);
    printf("����������ٶ�!\n");
    getchar();
    HeapDestroy(hHeap);
}

void modifyExProgram() {
    HANDLE hOpenFile = (HANDLE)CreateFile(L"a.exe", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
        NULL, NULL);
    CloseHandle(hOpenFile);
}

void selfReplication() {
    HANDLE hOpenFile = (HANDLE)CreateFile(L"testCode.exe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL,
        NULL);
    CloseHandle(hOpenFile);
}

void modifyStartupRegistry() {
    HKEY hKey = NULL;
    size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"SOFTWARE\Microsoft\Windows\CurrentVersion\Run", 0,
        KEY_READ, &hKey);
    if (lRet == ERROR_SUCCESS) {
        printf("�򿪳ɹ���\n");
    }
    else {
        printf("��ʧ�ܣ�\n");
    }
    RegCloseKey(hKey);
}

void openAnotherFolder() {
    HANDLE hOpenFile = (HANDLE)CreateFile(L".\\testFolder\\a.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL,
        CREATE_ALWAYS, NULL, NULL);
    CloseHandle(hOpenFile);
}

void recvData() {
    //��ʼ��DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //�����׽���
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    //���������������
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(1234);
    connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    Sleep(500);
    //���շ��������ص�����
    char szBuffer[MAXBYTE] = { 0 };
    recv(sock, szBuffer, MAXBYTE, NULL);
    //������յ�������
    printf("Message form server: %s\n", szBuffer);
    //�ر��׽���
    closesocket(sock);
    //��ֹʹ�� DLL
    WSACleanup();
}

void sendData() {
    //��ʼ�� DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //�����׽���
    SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    //���׽���
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
    sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //�����IP��ַ
    sockAddr.sin_port = htons(1234);  //�˿�
    bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    //�������״̬
    listen(servSock, 20);
    //���տͻ�������
    SOCKADDR clntAddr;
    int nSize = sizeof(SOCKADDR);
    SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
    //��ͻ��˷�������
    char str[32] = "Hello World!";
    send(clntSock, str, strlen(str) + sizeof(char), NULL);
    //�ر��׽���
    closesocket(clntSock);
    closesocket(servSock);
    //��ֹ DLL ��ʹ��
    WSACleanup();
}

void memoryOperation() {
    getchar();
    char temp[100] = "";
    printf("������������ڴ�\n");
    getchar();
    memcpy(temp, "hello\n", 6);
    printf("%s", temp);
    printf("��������ƶ��ڴ�\n");
    getchar();
    memmove(temp, "world\n", 6);
    printf("%s", temp);
}