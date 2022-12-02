#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 140

int main()
{
	system("chcp 1251 > null");
	LPSTR lpstrPipeName = L"\\\\.\\.pipe\\MyPipe"; // ��� ������ (����� ��, ��� � �� ������)
	HANDLE hNamePipe;
	while (TRUE)
	{
		hNamePipe = CreateFile( // ��������� �����. �� �������� � ��������� �����
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
			printf("������ �� ��������\n");
		}
		else
		{
			printf("���������� �����������\n");
			DWORD size_buffer = SIZE_BUFFER; // ������ ������ ��� ������
			DWORD actual_written; // ������� �� ����� ���� ���� �������� ����

			char message[SIZE_BUFFER];
			printf("������� ��������� ��� �������:\n");
			gets(message);
			LPWSTR buffer = &message; // ��������� ���������, �������� ������� ������������ � �����
			WriteFile(hNamePipe, buffer, size_buffer, &actual_written, NULL);

		}
		Sleep(5000);
		CloseHandle(hNamePipe);
	}


}