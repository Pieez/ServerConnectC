#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <math.h>
#define SIZE_BUFFER 140


double quadro(char*  ) {




}

int main()
{
	system("chcp 1251");

	HANDLE hNamedPipe;
	LPSTR lpszPipeName = L"\\\\.\\pipe\\MyPipe";
	DWORD size_buffer = 100;
	LPWSTR buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR));
	BOOL Flag = TRUE;
	while (TRUE)
	{

		hNamedPipe = CreateNamedPipe(//создание канала
			lpszPipeName,//Имя канала
			PIPE_ACCESS_DUPLEX,//режим доступа к каналу(односторонний/двусторонний)
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,//режим работы канала: передавать сообщения/читать сообщения/ждать
			PIPE_UNLIMITED_INSTANCES,//количество водящих к каналу, в данном случае неограничено
			512,//объем буфера на чтение (байт)
			512,//объем буфера на запись (байт)
			INFINITE,// максимальное время ожидания сообщения
			NULL);//указатель на структуру безопасности


		BOOL Connected = ConnectNamedPipe(hNamedPipe, NULL);
		if (Connected)
		{
			printf("\nКлиент успешно подключился\n");



			DWORD actual_readen;
			BOOL SuccessRead = ReadFile(hNamedPipe, buffer, size_buffer, &actual_readen, NULL);

			if (!SuccessRead)
			{
				printf("\nКлиент пишет: \n");
				printf(buffer);
				printf("\n");

				char message[100];
				printf("\nВведите сообщение для клиента\n");
				gets(message);
				buffer = &message;
				WriteFile(hNamedPipe, buffer, size_buffer, &actual_readen, NULL);
			}
		}
		else
		{
			printf("\nКлиент отключился от сервера\n");
		}
		printf(buffer);
		CloseHandle(hNamedPipe);
	}
}