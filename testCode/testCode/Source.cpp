#include<windows.h>
#include<stdio.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

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
        // 显示菜单
        showMenu();
        // 接收用户输入的选项
        scanf("%d", &op);
        // 根据选项执行相应操作
        switch (op) {
        case 0: {
            // 退出程序
            printf("bye!\n");
            break;
        }
        case 1: {
            // 调用MessageBoxA函数显示消息框
            MessageBoxA(NULL, "I'm MessageBoxA", "I'm MessageBoxA's title", MB_OK);
            break;
        }
        case 2: {
            // 调用MessageBoxW函数显示消息框
            MessageBoxW(NULL, L"I'm MessageBoxW", L"I'm MessageBoxW's title", MB_OK);
            break;
        }
        case 3: {
            // 调用heapCreateAndDestory函数
            // 进行堆的创建和销毁操作
            heapCreateAndDestory();
            break;
        }
        case 4: {
            // 调用writeFileString函数
            // 创建并写入文件
            writeFileString();
            break;
        }
        case 5: {
            // 调用readFileString函数
            // 创建并读取文件内容
            readFileString();
            break;
        }
        case 6: {
            // 调用regCreateAndSetValue函数
            // 创建、设置注册表值并关闭注册表
            regCreateAndSetValue();
            break;
        }
        case 7: {
            // 调用regOpenAndDelValue函数
            // 打开、删除注册表值并关闭注册表
            regOpenAndDelValue();
            break;
        }
        case 8: {
            // 调用recvData函数
            // 接收套接字数据
            recvData();
            break;
        }
        case 9: {
            // 调用sendData函数
            // 发送套接字数据
            sendData();
            break;
        }
        case 10: {
            // 调用headRepeatedRelease函数
            // 执行重复释放头部的操作
            heapRepeatedRelease();
            break;
        }
        case 11: {
            // 调用modifyExProgram函数
            // 修改可执行程序
            modifyExProgram();
            break;
        }
        case 12: {
            // 调用selfReplication函数
            // 执行自我复制操作
            selfReplication();
            break;
        }
        case 13: {
            // 调用modifyStartupRegistry函数
            // 修改启动项注册表
            modifyStartupRegistry();
            break;
        }
        case 14: {
            // 调用openAnotherFolder函数
            // 打开另一个文件夹
            openAnotherFolder();
            break;
        }
        case 15: {
            // 调用memoryOperation函数
            // 进行内存操作
            memoryOperation();
            break;
        }
        }
        // 如果选项为退出选项（0），则退出循环
        if (op == 0) {
            break;
        }
    }

    return 0;
}

void showMenu() {
    printf("--------------------------------请选择一个选项--------------------------------\n");
    printf("--正常操作--:\n");
    printf("1. 弹出消息框A\n");
    printf("2. 弹出消息框W\n");
    printf("3. 创建和销毁堆\n");
    printf("4. 写入文件字符串\n");
    printf("5. 读取文件字符串\n");
    printf("6. 创建并设置注册表值\n");
    printf("7. 打开并删除注册表值\n");
    printf("8. 接收套接字数据\n");
    printf("9. 发送套接字数据\n");
    printf("--恶意操作--:\n");
    printf("10. 重复释放头部\n");
    printf("11. 修改可执行程序\n");
    printf("12. 自我复制\n");
    printf("13. 修改启动项注册表\n");
    printf("14. 打开另一个文件夹\n");
}

void heapCreateAndDestory() {
    printf("按任意键启动 HeapCreate !\n");
    getchar();
    HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, PAGE_SIZE * 10, PAGE_SIZE * 100);

    int* pArr = (int*)HeapAlloc(hHeap, 0, sizeof(int) * 30);
    for (int i = 0; i < 30; ++i) {
        pArr[i] = i + 1;
    }
    printf("成功创建堆!\n");
    for (int i = 0; i < 30; ++i) {
        if (i % 5 == 0)
            printf_s("\n");
        printf("%3d ", pArr[i]);
    }
    printf_s("\n\n");
    printf("按任意键启动 HeapFree !\n");
    getchar();
    HeapFree(hHeap, 0, pArr);
    printf("按任意键启动 HeapDestory !\n");
    getchar();
    HeapDestroy(hHeap);

    printf("成功销毁堆!\n");
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
        printf("句柄无效，无法打开文件\n");
        return;
    }
    printf("成功打开文件！\n");
    printf("请输入一个字符串:");
    scanf("%s", writeString);
    flag = WriteFile(hOpenFile, writeString, strlen(writeString), NULL, NULL);
    if (flag) {
        printf("成功写入文件！\n");
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
        printf("无法打开文件\n");
        return;
    }
    printf("成功打开文件\n");
    fileSize = GetFileSize(hOpenFile, NULL);
    pBuffer = (char*)malloc((fileSize + 1) * sizeof(char));
    flag = ReadFile(hOpenFile, pBuffer, fileSize, NULL, NULL);
    pBuffer[fileSize] = 0;
    if (flag) {
        printf("成功读取字符串:%s!\n", pBuffer);
    }
    else {
        printf("读取字符串失败!\n");
    }
    free(pBuffer);
    CloseHandle(hOpenFile);
}

void regCreateAndSetValue() {
    // 创建注册表并设置键值
    HKEY hKey = NULL;
    TCHAR Data[254];
    memset(Data, 0, sizeof(Data));
    wcsncpy_s(Data, TEXT("https://github.com/AgentGuo"), 254);

    size_t lRet = RegCreateKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"aaaMykey", 0, NULL, REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS, NULL, &hKey, NULL);
    if (lRet == ERROR_SUCCESS) {
        printf("成功创建注册表!\n");
    }
    else {
        printf("创建注册表失败!\n");
    }
    // 修改注册表键值，没有则创建它
    size_t iLen = wcslen(Data);
    // 设置键值
    lRet = RegSetValueEx(hKey, L"qyf", 0, REG_SZ, (CONST BYTE*) Data, sizeof(TCHAR) * iLen);
    if (lRet == ERROR_SUCCESS) {
        printf("成功为注册表设置键值!\n");
        return;
    }
    else {
        printf("为注册表设置键值失败!\n");
    }
    RegCloseKey(hKey);
}

void regOpenAndDelValue() {
    HKEY hKey = NULL;
    size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"aaaMykey", 0, KEY_ALL_ACCESS, &hKey);
    if (lRet == ERROR_SUCCESS) {
        printf("成功打开注册表!\n");
    }
    else {
        printf("无法打开注册表!\n");
    }
    lRet = RegDeleteValue(hKey, L"qyf");
    if (lRet == ERROR_SUCCESS) {
        printf("成功删除!\n");
    }
    else {
        printf("删除失败!\n");
    }
    RegCloseKey(hKey);
}

void heapRepeatedRelease() {
    printf("按任意键启动 HeapCreate !\n");
    getchar();
    HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, PAGE_SIZE * 10, PAGE_SIZE * 100);

    int* pArr = (int*)HeapAlloc(hHeap, 0, sizeof(int) * 30);
    for (int i = 0; i < 30; ++i) {
        pArr[i] = i + 1;
    }
    printf("成功创建堆!\n");
    for (int i = 0; i < 30; ++i) {
        if (i % 5 == 0)
            printf_s("\n");
        printf("%3d ", pArr[i]);
    }
    printf_s("\n\n");
    printf("按任意键启动第一个 HeapFree !\n");
    getchar();
    HeapFree(hHeap, 0, pArr);
    printf("按任意键启动第二个 HeapFree !\n");
    getchar();
    HeapFree(hHeap, 0, pArr);
    printf("按任意键销毁堆!\n");
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
        printf("打开成功！\n");
    }
    else {
        printf("打开失败！\n");
    }
    RegCloseKey(hKey);
}

void openAnotherFolder() {
    HANDLE hOpenFile = (HANDLE)CreateFile(L".\\testFolder\\a.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL,
        CREATE_ALWAYS, NULL, NULL);
    CloseHandle(hOpenFile);
}

void recvData() {
    //初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //创建套接字
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    //向服务器发起请求
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(1234);
    connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    Sleep(500);
    //接收服务器传回的数据
    char szBuffer[MAXBYTE] = { 0 };
    recv(sock, szBuffer, MAXBYTE, NULL);
    //输出接收到的数据
    printf("Message form server: %s\n", szBuffer);
    //关闭套接字
    closesocket(sock);
    //终止使用 DLL
    WSACleanup();
}

void sendData() {
    //初始化 DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //创建套接字
    SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    //绑定套接字
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;  //使用IPv4地址
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    sockAddr.sin_port = htons(1234);  //端口
    bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    //进入监听状态
    listen(servSock, 20);
    //接收客户端请求
    SOCKADDR clntAddr;
    int nSize = sizeof(SOCKADDR);
    SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
    //向客户端发送数据
    char str[32] = "Hello World!";
    send(clntSock, str, strlen(str) + sizeof(char), NULL);
    //关闭套接字
    closesocket(clntSock);
    closesocket(servSock);
    //终止 DLL 的使用
    WSACleanup();
}

void memoryOperation() {
    getchar();
    char temp[100] = "";
    printf("按任意键复制内存\n");
    getchar();
    memcpy(temp, "hello\n", 6);
    printf("%s", temp);
    printf("按任意键移动内存\n");
    getchar();
    memmove(temp, "world\n", 6);
    printf("%s", temp);
}