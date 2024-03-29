// Sudoku.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include<string>
#include <cstring>
#include <set>
#include <map>
#include <cmath>
#include <stack>
#include <queue>
#include <fstream>

using namespace std;
const int maxn = 1000;
const int sizen = 16;
int shudu[sizen][sizen];//存储数独
bool row[sizen][sizen];//row[i][j]判断i行j是否被填过
bool col[sizen][sizen];//col[i][j]判断i列j是否被填过
bool little_shudu[sizen][sizen];//little_sudu[i][j]判断从左往右开始的第i个小数独中，j是否被填过；
FILE* fp;

void input(int x, int gx, int gy) {
	memset(row, false, sizeof(row));
	memset(col, false, sizeof(col));
	memset(little_shudu, false, sizeof(little_shudu));
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < x; j++) {

			scanf("%d", &shudu[i][j]);
			int temp_i = i / gx;
			int temp_j = j / gy;
			int area = temp_i * gx + temp_j;

			if (shudu[i][j] != 0) {
				int temp = shudu[i][j];
				row[i][temp] = true;
				col[j][temp] = true;
				if (gx != 1 || gy != 1) {
					little_shudu[area][temp] = true;

				}

			}
		}
	}
}
void print(int x) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < x; j++) {
			if (j == x - 1) {


				printf("%d\n", shudu[i][j]);
			}
			else {

				printf("%d ", shudu[i][j]);
			}
		}
	}

	printf("\n");
}
void dfs(int index, int maxscan, int jie, int gx, int gy) {
	if (index >= maxscan) {
		print(jie);
		return;
	}
	int x = index / jie;
	int y = index % jie;
	int temp_i = x / gx;
	int temp_j = y / gy;
	int area = temp_i * gx + temp_j;
	if (shudu[x][y] == 0) {
		for (int i = 1; i <= jie; i++) {
			if (row[x][i] == false && col[y][i] == false && little_shudu[area][i] == false) {
				shudu[x][y] = i;
				row[x][i] = true;
				col[y][i] = true;
				if (gx != 1 || gy != 1)
					little_shudu[area][i] = true;
				dfs(index + 1, maxscan, jie, gx, gy);
				shudu[x][y] = 0;
				row[x][i] = false;
				col[y][i] = false;
				if (gx != 1 || gy != 1)
					little_shudu[area][i] = false;
			}
		}

	}
	else {
		dfs(index + 1, maxscan, jie, gx, gy);
	}
}

int main(int argc, char *argv[]) {
	int pan, size, jie, gx, gy;
	int in, out;
	for (int i = 0; i < argc; i++)
	{
		if (strlen(argv[i]) == 1)
		{
			if (i == 2)
				size = atoi(argv[i]);
			if (i == 4)
				pan = atoi(argv[i]);
		}
		else if (argv[i][0] == '-' && argv[i][1] == 'i') {
			i++;
			in = i;
		}
		else if (argv[i][0] == '-' && argv[i][1] == 'o') {
			i++;
			out = i;
		}
	}
	freopen(argv[in], "r", stdin);
	freopen(argv[out], "w", stdout);
	jie = size;
	if (size == 4) {
		gx = gy = 2;
	}
	else if (size == 6) {
		gx = 2;
		gy = 3;
	}
	else if (size == 8) {
		gx = 4;
		gy = 2;
	}
	else if (size == 9) {
		gx = gy = 3;
	}
	else gx = gy = 1;
	for (int i = 0; i < pan; i++) {
		input(size, gx, gy);

		dfs(0, jie*jie, jie, gx, gy);

	}
	return 0;
}