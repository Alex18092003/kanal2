#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 140

int main()
{
	system("chcp 1251 > null");
	LPSTR lpstrPipeName = L"\\\\.\\.pipe\\MyPipe"; // имя канала (такое же, как и на севере)
	HANDLE hNamePipe;
	while (TRUE)
	{
		hNamePipe = CreateFile( // открываем канал. по аналогии с открытием файла
			lpstrPipeName,
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL
		);

		//WaitNamedPipe(lpstrPipeName, INFINITE);
		DWORD dwMode = PIPE_READMODE_MESSAGE;

		BOOL isSuccess = SetNamedPipeHandleState(
			hNamePipe,
			&dwMode,
			NULL,
			NULL
		);
		if (!isSuccess)
		{
			printf("сервер не отвечает\n");
		}
		else
		{
			printf("соединение установлено\n");
			DWORD size_buffer = SIZE_BUFFER; // размер буфера для записи
			DWORD actual_written; // сколько на самом деле было записано байт

			char message[SIZE_BUFFER];
			printf("введите сообщение для сервера:\n");
			gets(message);
			LPWSTR buffer = &message; // строковая переменая, значение которой записывается в канал
			WriteFile(hNamePipe, buffer, size_buffer, &actual_written, NULL);

		}
		Sleep(5000);
		CloseHandle(hNamePipe);
	}


}