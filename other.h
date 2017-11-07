#pragma once
#include<iostream>
using namespace std;


void print(char* const &s)
{
	cout << s ;
}

int Length(char *str)
{
	int number = 0;
	for (; str[number] != '\0'; number++);
	return number;
}

void GetNext(char* str, int* next)
{
	int len = Length(str);
	next[0] = -1;
	int j = 0, k = -1;
	while (j < len - 1)
	{
		if (k == -1)
		{
			next[j + 1] = 0;
			j++; k = 0;
		}
		else if (str[k] == str[j])
		{
			next[j + 1] = k + 1;
			j++; k++;
		}
		else
		{
			k = next[k];
		}
	}
}

int KMPIndexHelp(char *T, char *P, int pos, int* next)
{
	int i = pos, j = 0;
	int Tlen = Length(T);
	int Plen = Length(P);
	while (i < Tlen&&j < Plen)
	{
		if (j == -1)
		{
			i++; j = 0;
		}
		else if (P[j] == T[i])
		{
			i++; j++;
		}
		else
		{
			j = next[j];
		}
	}
	if (j < Plen)return -1;
	else return i - j;
}

int KMPIndex(char *T, char *P, int pos = 0)
{
	int *next = new int[Length(P)];
	GetNext(P, next);
	int result = KMPIndexHelp(T, P, pos, next);

	delete[]next;
	return result;
}