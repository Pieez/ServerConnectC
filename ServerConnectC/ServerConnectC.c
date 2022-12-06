#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#define SIZE_BUFFER 140

int main()
{
	system("chcp 1251");
	HANDLE hNamedPipe;
	DWORD size_buffer = SIZE_BUFFER;
	LPSTR lpszPipeName = L"\\\\.\\pipe\\MyPipe";
	LPWSTR buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR));
	char message[SIZE_BUFFER];
	BOOL Connected;
	DWORD actual_readen;
	BOOL SuccessRead;

	while (TRUE)
	{
		hNamedPipe = CreateNamedPipe(//создание канала
			lpszPipeName,//Имя канала
			PIPE_ACCESS_DUPLEX,//режим доступа к каналу(односторонний/двусторонний)
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,//режим работы канала: передавать сообщения/читать сообщения/ждать
			PIPE_UNLIMITED_INSTANCES,//количество водящих к каналу, в данном случае неограничено
			SIZE_BUFFER,//объем буфера на чтение (байт)
			SIZE_BUFFER,//объем буфера на запись (байт)
			INFINITE,// максимальное время ожидания сообщения
			NULL);//указатель на структуру безопасности
		Connected = ConnectNamedPipe(hNamedPipe, NULL);
		if (Connected)
		{
			SuccessRead = ReadFile(hNamedPipe, buffer, size_buffer, &actual_readen, NULL);
		}
	}
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
		printf("соединение установлено\n");
		
		

		
		printf("введите сообщение для сервера:\n");
		gets(message);
		LPWSTR buffer = &message;
		WriteFile(hNamedPipe, buffer, size_buffer,
			&actual_written, NULL);
	}
	Sleep(1000);
	CloseHandle(hNamedPipe);
}