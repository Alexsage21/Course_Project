#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>
#include <string.h>
#include <windows.h>

#define DEV_NAME_LEN 20
#define SOCKET_LEN 10
#define FAM_PROC_LEN 10
#define I_I_CORE_LEN 10
#define FOR_GAME_PC_LEN 3
#define RAM_TYPE_LEN 5
#define PCI_EXPRESS_LEN 3

typedef struct computer
{
	int COST;
	char DEV_NAME[DEV_NAME_LEN];
	char SOCKET[SOCKET_LEN];
	char FAM_PROC[FAM_PROC_LEN];
	int C_P_CORES;
	char I_I_CORE[I_I_CORE_LEN];
	char FOR_GAME_PC[FOR_GAME_PC_LEN];
	int RELEASE_YEAR;
	char RAM_TYPE[RAM_TYPE_LEN];
	int BASE_CPU_HZ;
	int TDP;
	char PCI_EXPRESS[PCI_EXPRESS_LEN];
} PC;

PC* memory_relocate(PC* arr, int n);
void print_PCs(PC* arr, int pcv);
void print_PC(PC* arr, int n);
void sort_function(PC* arr, int n, int ch, int zn);
int find_function(PC* arr, int n, int usl, int zn1, char* zn2, char* zn3, char* zn4, int zn5, char* zn6, char* zn7, int zn8, char* zn9, int zn10, int zn11, char* zn12);
int input_file(FILE* f, PC* arr, int count);
int output_file(FILE* f, PC* arr, int n);

int main()
{
	setlocale(LC_ALL, "RUS");
	int n, k, l, v, ch = 0, pcv = 0, zn = 0, ram1 = 0, ram2 = 0, ram3 = 0, ram4 = 0;
	PC* PCs = NULL, * PCss1 = NULL, * PCss2 = NULL, * PCss3 = NULL, * PCss4 = NULL;
	printf("1 - Считать данные из файла\n11 - Отредактировать запись о компьютере вручную\n2 - Ввести/изменить(добавить/убрать) количество компьютеров\n3 - Записать данные в файл\n4 - Сортировка данных\n5 - Поиск данных\n6 - Вывод данных\n7 - Вывести памятку ещё раз\n8 - Сохарить результат на время работы программы\n9 - Загрузить сохранённый результат\n0 - Завершить выполнение программы\n\n");
	do
	{
		printf("Действие?: ");
		scanf("%d", &v);
		//Считывание из файла
		if (v == 1)
		{
			FILE* file;
			char name[30];
			printf("Введите имя файла, из которого будут записываться данные (без расширения): ");
			scanf("%s", &name);
			if (!(file = fopen(strcat(name, ".txt"), "r")))
			{
				printf("Ошибка открытия файла считывания!\n");
			}
			else
			{
				input_file(file, PCs, pcv);
				fclose(file);
			}
		}
		//Ручной ввод характеристик компьютера
		else if (v == 11)
		{
			int n = 0;
			printf("Введите номер компьютера, который вы хотите отредактировать: ", n);
			scanf("%d", &n);
			printf("Введите цену %d-ого процессора(руб.): ", n);
			scanf("%d", &PCs[n - 1].COST);
			printf("Введите имя производителя %d-ого процессора (макс. 19 сим.): ", n);
			scanf("%s", &PCs[n - 1].DEV_NAME);
			printf("Введите сокет %d-ого процессора (макс. 9 сим.): ", n);
			scanf("%s", &PCs[n - 1].SOCKET);
			printf("Введите семейство %d-ого процессора (макс. 10 сим.): ", n);
			scanf("%s", &PCs[n - 1].FAM_PROC);
			printf("Введите количество производительных ядер %d-ого процессора: ", n);
			scanf("%d", &PCs[n - 1].C_P_CORES);
			printf("Введите интегрированное графическое ядро %d-ого процессора (макс 9 сим.): ", n);
			scanf("%s", &PCs[n - 1].I_I_CORE);
			printf("Введите характеристику для игрового компьютера %d-ого процессора(yes/no): ", n);
			scanf("%s", &PCs[n - 1].FOR_GAME_PC);
			printf("Введите год релиза %d-ого процессора: ", n);
			scanf("%d", &PCs[n - 1].RELEASE_YEAR);
			printf("Введите тип оперативной памяти %d-ого процессора (макс 6 сим.): ", n);
			scanf("%s", &PCs[n - 1].RAM_TYPE);
			printf("Введите базовую частоту %d-ого процессора(ГГц): ", n);
			scanf("%d", &PCs[n - 1].BASE_CPU_HZ);
			printf("Введите тепловыделение %d-ого процессора(Вт): ", n);
			scanf("%d", &PCs[n - 1].TDP);
			printf("Введите наличие PCI Express у %d-ого процессора(yes/no): ", n);
			scanf("%s", &PCs[n - 1].PCI_EXPRESS);
		}
		//Ввод количсетва компьютеров
		else if (v == 2)
		{
			int n = 0;
			printf("Сколько процессоров вы хотите добавить?: ");
			scanf("%d", &n);
			pcv = pcv + n;
			PCs = memory_relocate(PCs, pcv);
			for (int i = pcv - n; i < pcv; i++)
			{
				PCs[i].COST = 0;
				strcpy(PCs[i].DEV_NAME, "-");
				strcpy(PCs[i].SOCKET, "-");
				strcpy(PCs[i].FAM_PROC, "-");
				PCs[i].C_P_CORES = 0;
				strcpy(PCs[i].I_I_CORE, "-");
				strcpy(PCs[i].FOR_GAME_PC, "-");
				PCs[i].RELEASE_YEAR = 0;
				strcpy(PCs[i].RAM_TYPE, "-");
				PCs[i].BASE_CPU_HZ = 0;
				PCs[i].TDP = 0;
				strcpy(PCs[i].PCI_EXPRESS, "-");
			}
		}
		//Запись в файл
		else if (v == 3)
		{
			FILE* file2;
			char name2[30];
			printf("Введите имя файла, в который будут записываться данные (без расширения): ");
			scanf("%s", &name2);
			if (!(file2 = fopen(strcat(name2, ".txt"), "w")))
			{
				printf("Ошибка открытия файла записи!\n");
			}
			else
			{
				output_file(file2, PCs, pcv);
				fclose(file2);
			}
		}
		//Сортировка данных
		else if (v == 4)
		{
			printf("Введите значение сортировки (1-12): ");
			scanf("%d", &ch);
			printf("Введите значение сортировки (1-2): ");
			scanf("%d", &zn);
			sort_function(PCs, pcv, ch, zn);
		}
		//Поиск данных
		else if (v == 5)
		{
			int zn1 = 0;
			char zn2[DEV_NAME_LEN+1] = { "" };
			char zn3[SOCKET_LEN+1] = { "" };
			char zn4[FAM_PROC_LEN+1] = { "" };
			int zn5 = 0;
			char zn6[I_I_CORE_LEN+1] = { "" };
			char zn7[FOR_GAME_PC_LEN+1] = { "" };
			int zn8 = 0;
			char zn9[RAM_TYPE_LEN+1] = { "" };
			int zn10 = 0;
			int zn11 = 0;
			char zn12[PCI_EXPRESS_LEN+1] = { "" };
			int zn = 0;
			int usl = 0;
			printf("По каким значениям поиск? (1-12): ");
			scanf("%d", &zn);
			while (zn != 0)
			{
				if (zn == 1)
				{
					printf("Поиск по цене? (руб.): ");
					scanf("%d", &zn1);
				}
				else if (zn == 2)
				{
					printf("Поиск по имени производителя? (макс. 19 сим.): ");
					scanf("%s", &zn2);
				}
				else if (zn == 3)
				{
					printf("Поиск по сокету? (макс. 9 сим.): ");
					scanf("%s", &zn3);
				}
				else if (zn == 4)
				{
					printf("Поиск по семейству процессора? (макс. 10 сим.): ");
					scanf("%s", &zn4);
				}
				else if (zn == 5)
				{
					printf("Поиск по количеству производительных ядер?: ");
					scanf("%d", &zn5);
				}
				else if (zn == 6)
				{
					printf("Поиск по встроенному графическому интерфейсу? (макс. 9 сим.): ");
					scanf("%s", &zn6);
				}
				else if (zn == 7)
				{
					printf("Для игрового компьютера? (yes/no): ");
					scanf("%s", &zn7);
				}
				else if (zn == 8)
				{
					printf("Поиск по году релиза?: ");
					scanf("%d", &zn8);
				}
				else if (zn == 9)
				{
					printf("Поиск по типу оперативной памяти? (макс. 6 сим.): ");
					scanf("%s", &zn9);
				}
				else if (zn == 10)
				{
					printf("Поиск по базавой частоте процессора? (ГГц): ");
					scanf("%d", &zn10);
				}
				else if (zn == 11)
				{
					printf("Поиск по тепловыделению? (Вт): ");
					scanf("%d", &zn11);
				}
				else if (zn == 12)
				{
					printf("Поиск по наличию PCI Express? (yes/no): ");
					scanf("%s", &zn12);
				}
				printf("Начать поиск? (0 - да, 1-12 - ввести следующий критерий поиска): ");
				scanf("%d", &zn);
				usl += 1;
			}
			pcv = find_function(PCs, pcv, usl, zn1, zn2, zn3, zn4, zn5, zn6, zn7, zn8, zn9, zn10, zn11, zn12);
		}
		//Вывод данных
		else if (v == 6)
		{
			print_PCs(PCs, pcv);
		}
		//Памятка
		else if (v == 7)
			printf("1 - Считать данные из файла\n11 - Отредактировать запись о компьютере вручную\n2 - Ввести/изменить(добавить/убрать) количество компьютеров\n3 - Записать данные в файл\n4 - Сортировка данных\n5 - Поиск данных\n6 - Вывод данных\n7 - Вывести памятку ещё раз\n8 - Сохарить результат на время работы программы\n9 - Загрузить сохранённый результат\n0 - Завершить выполнение программы\n\n");
		//Сохранения
		else if (v == 8)
		{
			int sl = 0;
			printf("Куда записать?(1-4): ");
			scanf("%d", &sl);
			if (sl == 1)
			{
				PCss1 = memory_relocate(PCss1, pcv);
				ram1 = pcv;
				for (int i = 0; i < ram1; i++)
				{
					PCss1[i].COST = PCs[i].COST;
					strcpy(PCss1[i].DEV_NAME, PCs[i].DEV_NAME);
					strcpy(PCss1[i].SOCKET, PCs[i].SOCKET);
					strcpy(PCss1[i].FAM_PROC, PCs[i].FAM_PROC);
					PCss1[i].C_P_CORES = PCs[i].C_P_CORES;
					strcpy(PCss1[i].I_I_CORE, PCs[i].I_I_CORE);
					strcpy(PCss1[i].FOR_GAME_PC, PCs[i].FOR_GAME_PC);
					PCss1[i].RELEASE_YEAR = PCs[i].RELEASE_YEAR;
					strcpy(PCss1[i].RAM_TYPE, PCs[i].RAM_TYPE);
					PCss1[i].BASE_CPU_HZ = PCs[i].BASE_CPU_HZ;
					PCss1[i].TDP = PCs[i].TDP;
					strcpy(PCss1[i].PCI_EXPRESS, PCs[i].PCI_EXPRESS);
				}
			}
			else if (sl == 2)
			{
				PCss2 = memory_relocate(PCss2, pcv);
				ram2 = pcv;
				for (int i = 0; i < ram2; i++)
				{
					PCss2[i].COST = PCs[i].COST;
					strcpy(PCss2[i].DEV_NAME, PCs[i].DEV_NAME);
					strcpy(PCss2[i].SOCKET, PCs[i].SOCKET);
					strcpy(PCss2[i].FAM_PROC, PCs[i].FAM_PROC);
					PCss2[i].C_P_CORES = PCs[i].C_P_CORES;
					strcpy(PCss2[i].I_I_CORE, PCs[i].I_I_CORE);
					strcpy(PCss2[i].FOR_GAME_PC, PCs[i].FOR_GAME_PC);
					PCss2[i].RELEASE_YEAR = PCs[i].RELEASE_YEAR;
					strcpy(PCss2[i].RAM_TYPE, PCs[i].RAM_TYPE);
					PCss2[i].BASE_CPU_HZ = PCs[i].BASE_CPU_HZ;
					PCss2[i].TDP = PCs[i].TDP;
					strcpy(PCss2[i].PCI_EXPRESS, PCs[i].PCI_EXPRESS);
				}
			}
			else if (sl == 3)
			{
				PCss3 = memory_relocate(PCss3, pcv);
				ram3 = pcv;
				for (int i = 0; i < ram3; i++)
				{
					PCss3[i].COST = PCs[i].COST;
					strcpy(PCss3[i].DEV_NAME, PCs[i].DEV_NAME);
					strcpy(PCss3[i].SOCKET, PCs[i].SOCKET);
					strcpy(PCss3[i].FAM_PROC, PCs[i].FAM_PROC);
					PCss3[i].C_P_CORES = PCs[i].C_P_CORES;
					strcpy(PCss3[i].I_I_CORE, PCs[i].I_I_CORE);
					strcpy(PCss3[i].FOR_GAME_PC, PCs[i].FOR_GAME_PC);
					PCss3[i].RELEASE_YEAR = PCs[i].RELEASE_YEAR;
					strcpy(PCss3[i].RAM_TYPE, PCs[i].RAM_TYPE);
					PCss3[i].BASE_CPU_HZ = PCs[i].BASE_CPU_HZ;
					PCss3[i].TDP = PCs[i].TDP;
					strcpy(PCss3[i].PCI_EXPRESS, PCs[i].PCI_EXPRESS);
				}
			}
			else if (sl == 4)
			{
				PCss4 = memory_relocate(PCss4, pcv);
				ram4 = pcv;
				for (int i = 0; i < ram4; i++)
				{
					PCss4[i].COST = PCs[i].COST;
					strcpy(PCss4[i].DEV_NAME, PCs[i].DEV_NAME);
					strcpy(PCss4[i].SOCKET, PCs[i].SOCKET);
					strcpy(PCss4[i].FAM_PROC, PCs[i].FAM_PROC);
					PCss4[i].C_P_CORES = PCs[i].C_P_CORES;
					strcpy(PCss4[i].I_I_CORE, PCs[i].I_I_CORE);
					strcpy(PCss4[i].FOR_GAME_PC, PCs[i].FOR_GAME_PC);
					PCss4[i].RELEASE_YEAR = PCs[i].RELEASE_YEAR;
					strcpy(PCss4[i].RAM_TYPE, PCs[i].RAM_TYPE);
					PCss4[i].BASE_CPU_HZ = PCs[i].BASE_CPU_HZ;
					PCss4[i].TDP = PCs[i].TDP;
					strcpy(PCss4[i].PCI_EXPRESS, PCs[i].PCI_EXPRESS);
				}
			}
		}
		else if (v == 9)
		{
			int sl = 0;
			printf("Откуда взять запись?(1-4): ");
			scanf("%d", &sl);
			if (sl == 1)
			{
				PCs = memory_relocate(PCs, ram1);
				pcv = ram1;
				for (int i = 0; i < pcv; i++)
				{
					PCs[i].COST = PCss1[i].COST;
					strcpy(PCs[i].DEV_NAME, PCss1[i].DEV_NAME);
					strcpy(PCs[i].SOCKET, PCss1[i].SOCKET);
					strcpy(PCs[i].FAM_PROC, PCss1[i].FAM_PROC);
					PCs[i].C_P_CORES = PCss1[i].C_P_CORES;
					strcpy(PCs[i].I_I_CORE, PCss1[i].I_I_CORE);
					strcpy(PCs[i].FOR_GAME_PC, PCss1[i].FOR_GAME_PC);
					PCs[i].RELEASE_YEAR = PCss1[i].RELEASE_YEAR;
					strcpy(PCs[i].RAM_TYPE, PCss1[i].RAM_TYPE);
					PCs[i].BASE_CPU_HZ = PCss1[i].BASE_CPU_HZ;
					PCs[i].TDP = PCss1[i].TDP;
					strcpy(PCs[i].PCI_EXPRESS, PCss1[i].PCI_EXPRESS);
				}
			}
			else if (sl == 2)
			{
				PCs = memory_relocate(PCs, ram2);
				pcv = ram2;
				for (int i = 0; i < pcv; i++)
				{
					PCs[i].COST = PCss2[i].COST;
					strcpy(PCs[i].DEV_NAME, PCss2[i].DEV_NAME);
					strcpy(PCs[i].SOCKET, PCss2[i].SOCKET);
					strcpy(PCs[i].FAM_PROC, PCss2[i].FAM_PROC);
					PCs[i].C_P_CORES = PCss2[i].C_P_CORES;
					strcpy(PCs[i].I_I_CORE, PCss2[i].I_I_CORE);
					strcpy(PCs[i].FOR_GAME_PC, PCss2[i].FOR_GAME_PC);
					PCs[i].RELEASE_YEAR = PCss2[i].RELEASE_YEAR;
					strcpy(PCs[i].RAM_TYPE, PCss2[i].RAM_TYPE);
					PCs[i].BASE_CPU_HZ = PCss2[i].BASE_CPU_HZ;
					PCs[i].TDP = PCss2[i].TDP;
					strcpy(PCs[i].PCI_EXPRESS, PCss2[i].PCI_EXPRESS);
				}
			}
			else if (sl == 3)
			{
				PCs = memory_relocate(PCs, ram3);
				pcv = ram3;
				for (int i = 0; i < pcv; i++)
				{
					PCs[i].COST = PCss3[i].COST;
					strcpy(PCs[i].DEV_NAME, PCss3[i].DEV_NAME);
					strcpy(PCs[i].SOCKET, PCss3[i].SOCKET);
					strcpy(PCs[i].FAM_PROC, PCss3[i].FAM_PROC);
					PCs[i].C_P_CORES = PCss3[i].C_P_CORES;
					strcpy(PCs[i].I_I_CORE, PCss3[i].I_I_CORE);
					strcpy(PCs[i].FOR_GAME_PC, PCss3[i].FOR_GAME_PC);
					PCs[i].RELEASE_YEAR = PCss3[i].RELEASE_YEAR;
					strcpy(PCs[i].RAM_TYPE, PCss3[i].RAM_TYPE);
					PCs[i].BASE_CPU_HZ = PCss3[i].BASE_CPU_HZ;
					PCs[i].TDP = PCss3[i].TDP;
					strcpy(PCs[i].PCI_EXPRESS, PCss3[i].PCI_EXPRESS);
				}
			}
			else if (sl == 4)
			{
				PCs = memory_relocate(PCs, ram4);
				pcv = ram4;
				for (int i = 0; i < pcv; i++)
				{
					PCs[i].COST = PCss4[i].COST;
					strcpy(PCs[i].DEV_NAME, PCss4[i].DEV_NAME);
					strcpy(PCs[i].SOCKET, PCss4[i].SOCKET);
					strcpy(PCs[i].FAM_PROC, PCss4[i].FAM_PROC);
					PCs[i].C_P_CORES = PCss4[i].C_P_CORES;
					strcpy(PCs[i].I_I_CORE, PCss4[i].I_I_CORE);
					strcpy(PCs[i].FOR_GAME_PC, PCss4[i].FOR_GAME_PC);
					PCs[i].RELEASE_YEAR = PCss4[i].RELEASE_YEAR;
					strcpy(PCs[i].RAM_TYPE, PCss4[i].RAM_TYPE);
					PCs[i].BASE_CPU_HZ = PCss4[i].BASE_CPU_HZ;
					PCs[i].TDP = PCss4[i].TDP;
					strcpy(PCs[i].PCI_EXPRESS, PCss4[i].PCI_EXPRESS);
				}
			}
		}
	} while (v != 0);
}

PC* memory_relocate(PC* arr, int n)
{
	arr = (PC*)realloc(arr, n * sizeof(PC));
	return arr;
}

void print_PCs(PC* arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("Цена %d-ого процессора: %dруб.\n", i + 1, arr[i].COST);
		printf("Имя производителя %d-ого процессора: %s\n", i + 1, arr[i].DEV_NAME);
		printf("Сокет %d-ого процессора: %s\n", i + 1, arr[i].SOCKET);
		printf("Семейство %d-ого процессора: %s\n", i + 1, arr[i].FAM_PROC);
		printf("Количество производительных ядер %d-ого процессора: %d\n", i + 1, arr[i].C_P_CORES);
		printf("Интегрированное графическое ядро %d-ого процессора: %s\n", i + 1, arr[i].I_I_CORE);
		printf("Характеристика для игрового компьютера %d-ого процессора(yes/no): %s\n", i + 1, arr[i].FOR_GAME_PC);
		printf("Год релиза %d-ого процессора: %dг.\n", i + 1, arr[i].RELEASE_YEAR);
		printf("Тип оперативной памяти %d-ого процессора: %s\n", i + 1, arr[i].RAM_TYPE);
		printf("Базовая частота %d-ого процессора(ГГц): %dГГц\n", i + 1, arr[i].BASE_CPU_HZ);
		printf("Тепловыделение %d-ого процессора(Вт): %dВт\n", i + 1, arr[i].TDP);
		printf("Наличие PCI Express у %d-ого процессора(yes/no): %s\n", i + 1, arr[i].PCI_EXPRESS);
	}
	printf("\n");
	printf("     | %11s | %20s | %10s | %10s | %5s | %10s | %4s | %7s | %6s | %8s | %7s | %3s\n", "COST", "DEV NAME", "SOCKET", "FAM PROC", "CORES", "I CORE", "GAME", "R YEAR", "R TYPE", "CPU HZ", "TDP", "PCI");
	for (int i = 0; i < n; i++)
	{
		printf("№%3d | %7dруб. | %20s | %10s | %10s | %5d | %10s | %4s | %5dг. | %6s | %5dГГц | %5dВт | %3s\n", i + 1, arr[i].COST, arr[i].DEV_NAME, arr[i].SOCKET, arr[i].FAM_PROC, arr[i].C_P_CORES, arr[i].I_I_CORE, arr[i].FOR_GAME_PC, arr[i].RELEASE_YEAR, arr[i].RAM_TYPE, arr[i].BASE_CPU_HZ, arr[i].TDP, arr[i].PCI_EXPRESS);
	}
}

void print_PC(PC* arr, int n)
{
	printf("Цена %d-ого процессора: %dруб.\n", n, arr[n - 1].COST);
	printf("Имя производителя %d-ого процессора: %s\n", n, arr[n - 1].DEV_NAME);
	printf("Сокет %d-ого процессора: %s\n", n, arr[n - 1].SOCKET);
	printf("Семейство %d-ого процессора: %s\n", n, arr[n - 1].FAM_PROC);
	printf("Количество производительных ядер %d-ого процессора: %d\n", n, arr[n - 1].C_P_CORES);
	printf("Интегрированное графическое ядро %d-ого процессора: %s\n", n, arr[n - 1].I_I_CORE);
	printf("Характеристика для игрового компьютера %d-ого процессора(yes/no): %s\n", n, arr[n - 1].FOR_GAME_PC);
	printf("Год релиза %d-ого процессора: %dг.\n", n, arr[n - 1].RELEASE_YEAR);
	printf("Тип оперативной памяти %d-ого процессора: %s\n", n, arr[n - 1].RAM_TYPE);
	printf("Базовая частота %d-ого процессора(ГГц): %dГГц\n", n, arr[n - 1].BASE_CPU_HZ);
	printf("Тепловыделение %d-ого процессора(Вт): %dВт\n", n, arr[n - 1].TDP);
	printf("Наличие PCI Express у %d-ого процессора(yes/no): %s\n", n, arr[n - 1].PCI_EXPRESS);
}

int input_file(FILE* f, PC* arr, int count)
{
	char* strk[140];
	char* p, * r;
	int i, k = -1;

	while (!feof(f) && k < count)
	{
		fgets(strk, 140, f);
		p = strtok(strk, "'\n'");
		p = strtok(strk, "| ");
		i = -1;
		while (p != NULL)
		{
			i++;
			if (k >= 0)
			{
				if (i == 0)
				{
					r = (int*)malloc(sizeof(int));
					strcpy(r, p);
					r = strtol(r, NULL, 10);
					arr[k].COST = r;
				}
				else if (i == 1)
				{
					strcpy(arr[k].DEV_NAME, p);
				}
				else if (i == 2)
				{
					strcpy(arr[k].SOCKET, p);
				}
				else if (i == 3)
				{
					strcpy(arr[k].FAM_PROC, p);
				}
				else if (i == 4)
				{
					r = (int*)malloc(sizeof(int));
					strcpy(r, p);
					r = strtol(r, NULL, 10);
					arr[k].C_P_CORES = r;
				}
				else if (i == 5)
				{
					strcpy(arr[k].I_I_CORE, p);
				}
				else if (i == 6)
				{
					strcpy(arr[k].FOR_GAME_PC, p);
				}
				else if (i == 7)
				{
					r = (int*)malloc(sizeof(int));
					strcpy(r, p);
					r = strtol(r, NULL, 10);
					arr[k].RELEASE_YEAR = r;
				}
				else if (i == 8)
				{
					strcpy(arr[k].RAM_TYPE, p);
				}
				else if (i == 9)
				{
					r = (int*)malloc(sizeof(int));
					strcpy(r, p);
					r = strtol(r, NULL, 10);
					arr[k].BASE_CPU_HZ = r;
				}
				else if (i == 10)
				{
					r = (int*)malloc(sizeof(int));
					strcpy(r, p);
					r = strtol(r, NULL, 10);
					arr[k].TDP = r;
				}
				else if (i == 11)
				{
					strcpy(arr[k].PCI_EXPRESS, p);
				}
			}
			p = strtok(NULL, "| ");
		}
		k++;
	}
}

int output_file(FILE* f, PC* arr, int n)
{
	int i = 0;
	fprintf(f, "| %11s | %20s | %10s | %10s | %5s | %10s | %4s | %7s | %6s | %8s | %7s | %3s\n", "COST", "DEV_NAME", "SOCKET", "FAM_PROC", "CORES", "I_CORE", "GAME", "R_YEAR", "R_TYPE", "CPU HZ", "TDP", "PCI");

	while (i < n)
	{
		if (i == 0)
		{
			fprintf(f, "| %7dруб. | %20s | %10s | %10s | %5d | %10s | %4s | %5dг. | %6s | %5dГГц | %5dВт | %3s\n", arr[0].COST, arr[0].DEV_NAME, arr[0].SOCKET, arr[0].FAM_PROC, arr[0].C_P_CORES, arr[0].I_I_CORE, arr[0].FOR_GAME_PC, arr[0].RELEASE_YEAR, arr[0].RAM_TYPE, arr[0].BASE_CPU_HZ, arr[0].TDP, arr[0].PCI_EXPRESS);
		}
		else
			fprintf(f, "\n| %7dруб. | %20s | %10s | %10s | %5d | %10s | %4s | %5dг. | %6s | %5dГГц | %5dВт | %3s", arr[i].COST, arr[i].DEV_NAME, arr[i].SOCKET, arr[i].FAM_PROC, arr[i].C_P_CORES, arr[i].I_I_CORE, arr[i].FOR_GAME_PC, arr[i].RELEASE_YEAR, arr[i].RAM_TYPE, arr[i].BASE_CPU_HZ, arr[i].TDP, arr[i].PCI_EXPRESS);
		i++;
	}
}

void sort_function(PC* arr, int n, int ch, int zn)
{
	if (ch == 0)
		printf("Не выбрано значение сортировки!");
	if (zn == 0)
		printf("Не выбран способ сортировки!");
	else if (zn == 1)
	{
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n - i - 1; j++)
			{
				if (ch == 1)
				{
					if (arr[j].COST > arr[j + 1].COST)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 2)
				{
					if (arr[j].DEV_NAME > arr[j + 1].DEV_NAME)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 3)
				{
					if (arr[j].SOCKET > arr[j + 1].SOCKET)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 4)
				{
					if (arr[j].FAM_PROC > arr[j + 1].FAM_PROC)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 5)
				{
					if (arr[j].C_P_CORES > arr[j + 1].C_P_CORES)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 6)
				{
					if (arr[j].I_I_CORE > arr[j + 1].I_I_CORE)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 7)
				{
					if (arr[j].FOR_GAME_PC > arr[j + 1].FOR_GAME_PC)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 8)
				{
					if (arr[j].RELEASE_YEAR > arr[j + 1].RELEASE_YEAR)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 9)
				{
					if (arr[j].RAM_TYPE > arr[j + 1].RAM_TYPE)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 10)
				{
					if (arr[j].BASE_CPU_HZ > arr[j + 1].BASE_CPU_HZ)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 11)
				{
					if (arr[j].TDP > arr[j + 1].TDP)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 12)
				{
					if (arr[j].PCI_EXPRESS > arr[j + 1].PCI_EXPRESS)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
			}
		}
	}
	else if (zn == 2)
	{
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n - i - 1; j++)
			{
				if (ch == 1)
				{
					if (arr[j].COST < arr[j + 1].COST)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 2)
				{
					if (arr[j].DEV_NAME < arr[j + 1].DEV_NAME)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 3)
				{
					if (arr[j].SOCKET < arr[j + 1].SOCKET)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 4)
				{
					if (arr[j].FAM_PROC < arr[j + 1].FAM_PROC)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 5)
				{
					if (arr[j].C_P_CORES < arr[j + 1].C_P_CORES)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 6)
				{
					if (arr[j].I_I_CORE < arr[j + 1].I_I_CORE)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 7)
				{
					if (arr[j].FOR_GAME_PC < arr[j + 1].FOR_GAME_PC)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 8)
				{
					if (arr[j].RELEASE_YEAR < arr[j + 1].RELEASE_YEAR)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 9)
				{
					if (arr[j].RAM_TYPE < arr[j + 1].RAM_TYPE)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 10)
				{
					if (arr[j].BASE_CPU_HZ < arr[j + 1].BASE_CPU_HZ)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 11)
				{
					if (arr[j].TDP < arr[j + 1].TDP)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
				else if (ch == 12)
				{
					if (arr[j].PCI_EXPRESS < arr[j + 1].PCI_EXPRESS)
					{
						PC a = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = a;
					}
				}
			}
		}
	}
}

int find_function(PC* arr, int n, int usl, int zn1, char* zn2, char* zn3, char* zn4, int zn5, char* zn6, char* zn7, int zn8, char* zn9, int zn10, int zn11, char* zn12)
{
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		if ((arr[i].COST == zn1) + (strcmp(arr[i].DEV_NAME, zn2) == 0) + (strcmp(arr[i].SOCKET, zn3) == 0) + (strcmp(arr[i].FAM_PROC, zn4) == 0) + (arr[i].C_P_CORES == zn5) + (strcmp(arr[i].I_I_CORE, zn6) == 0) + (strcmp(arr[i].FOR_GAME_PC, zn7) == 0) + (arr[i].RELEASE_YEAR == zn8) + (strcmp(arr[i].RAM_TYPE, zn9) == 0) + (arr[i].BASE_CPU_HZ == zn10) + (arr[i].TDP == zn11) + (strcmp(arr[i].PCI_EXPRESS, zn12) == 0) == usl)
		{
			arr[k] = arr[i];
			k++;
		}
	}
	return k;
}