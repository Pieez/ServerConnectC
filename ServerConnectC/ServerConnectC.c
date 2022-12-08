#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 140

int main()
{
	system("chcp 1251");
	HANDLE hNamedPipe;
	
	LPSTR lpszPipeName = L"\\\\.\\pipe\\MyPipe";
	

	while (TRUE)
	{
		hNamedPipe = CreateNamedPipe(//создание канала
			lpszPipeName,//Имя канала
			GENERIC_READ | GENERIC_WRITE,
			0, NULL, OPEN_EXISTING, 0, NULL
		);
		
		DWORD dwMode = PIPE_READMODE_MESSAGE;

		BOOL isSuccess = SetNamedPipeHandleState(
			hNamedPipe,
			&dwMode,
			NULL,
			NULL);
		if (!isSuccess)
		{
			printf("Сервер не отвечает\n");
		}
		else
		{
			printf("Соединение установлено\n");
			DWORD size_buffer = SIZE_BUFFER;
			DWORD actual_written;

			char message[SIZE_BUFFER];
			printf("Введите сообщение для сервера\n");
			gets(message);
			LPWSTR buffer = &message;
			WriteFile(hNamedPipe, buffer, size_buffer,
				&actual_written, NULL);
		}
		Sleep(1000);
		CloseHandle(hNamedPipe);
	}
}