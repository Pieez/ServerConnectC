#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 140

int main()
{
	system("chcp 1251");
	HANDLE hNamedPipe;
	DWORD chit_buff = 100;
	char message[100];
	LPWSTR buffer = (CHAR*)calloc(chit_buff,sizeof(CHAR));
	LPSTR lpszPipeName = L"\\\\.\\pipe\\MyPipe";
	BOOL Flag_answer = TRUE;
	DWORD size_buffer = SIZE_BUFFER;
	DWORD actual_written;

	while (TRUE)
	{
		hNamedPipe = CreateFile(//создание канала
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
			Flag_answer = TRUE;
		}
		else
		{
			if (Flag_answer) 
			{
				
				printf("Введите сообщение для сервера\n");
				gets(message);
				
				WriteFile(hNamedPipe, buffer, size_buffer,
					&actual_written, NULL);
				Flag_answer = FALSE;

			}
			if (isSuccess)
			{
				printf("Сервер пишет\n");
				printf(buffer);
				printf("\n");
				Flag_answer = TRUE;
				if (buffer)
					printf("Пусто\n");
			

				
			}
			printf("Соединение установлено\n");
			
			
		}
		Sleep(1000);
		CloseHandle(hNamedPipe);
	}
}