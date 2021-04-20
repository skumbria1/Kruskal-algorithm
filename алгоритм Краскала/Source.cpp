#include <iostream> 
#include <conio.h>
#include <Windows.h>
#include <string>
using namespace std;
const int enter = 13;
const int escape = 27;
const int space = 32;
const int backspace = 8;
const int tab = 9;
const int sleepTime = 1500;

struct edge {
	int length;
	string first, second;
};

struct vpair {
	string vertex;
	int colour;
};
vpair listOfPairs[50];

edge* add(edge* list, int& listlen, edge elem) {
	edge* tmp = new edge[listlen + 1];
	if (list != nullptr) {
		for (int i = 0; i < listlen; i++) {
			tmp[i].first = list[i].first;
			tmp[i].second = list[i].second;
			tmp[i].length = list[i].length;
		}
		delete[] list;
	}
	tmp[listlen].first = elem.first;
	tmp[listlen].second = elem.second;
	tmp[listlen].length = elem.length;
	listlen++;
	list = tmp;
	return list;
}

void bubblesort(edge* list, int listlen) {
	edge tmp;
	for (int i = 0; i < listlen - 1; i++)
	{
		for (int j = 0; j < listlen - i - 1; j++)
		{
			if (list[j].length > list[j + 1].length) {
				tmp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = tmp;
			}
		}
	}
}

int finds(string v){
	for (int i = 0; i < 50; i++) {
		if (v == listOfPairs[i].vertex) {
			return listOfPairs[i].colour;
		}
	}
}

void unions(string v1, string v2) {
	int v1i, v2i;
	v1i = finds(v1);
	v2i = finds(v2);
	if (v1i != v2i) {
		if (listOfPairs[v1i].colour != listOfPairs[v2i].colour) {
			int col = listOfPairs[v2i].colour;
			for (int i = 0; i < 50; i++) {
				if ((listOfPairs[v1i].colour != listOfPairs[i].colour) and (listOfPairs[i].colour != -1) and (listOfPairs[i].colour == col)) {
					listOfPairs[i].colour = listOfPairs[v1i].colour;
				}
			}
		}
	}
}

int main() {
	edge* listOfedges = nullptr;
	int listlen = 0, alllen = 0;
	bool t = 1;
	edge buf;
	char key;
	string buf1, buf2, buf3;
	for (int i = 0; i < 50; i++) {
		listOfPairs[i].vertex = "0";
		listOfPairs[i].colour = -1;
	};
	cout << "press 1 to stop adding, press other buttons to continue" << "\n\n";
	while (t) {
		cin >> buf1 >> buf2 >> buf3;
		if (stoi(buf3) == 0) {
			system("cls");
			cout << "press 1 to stop adding, press other buttons to continue" << "\n\n";
			for (int i = 0; i < listlen; i++) {
				cout << listOfedges[i].first << " " << listOfedges[i].second << " " << listOfedges[i].length << endl;
			}
			continue;
		}
		buf.first = buf1;
		for (int i = 0; i < 50; i++) {
			if (buf.first == listOfPairs[i].vertex) break;
			if (listOfPairs[i].colour == -1) {
				listOfPairs[i].vertex = buf.first;
				listOfPairs[i].colour = i;
				break;
			}
		}
		buf.second = buf2;
		for (int i = 0; i < 50; i++) {
			if (buf.second == listOfPairs[i].vertex) break;
			if (listOfPairs[i].colour == -1) {
				listOfPairs[i].vertex = buf.second;
				listOfPairs[i].colour = i;
				break;
			}
		}
		buf.length = stoi(buf3); //string to int
		listOfedges = add(listOfedges, listlen, buf);
		cin.get();
		switch (key = _getch()) {
		case '1': t = 0; break;
		default: break;
		}
	}
	bubblesort(listOfedges, listlen);
	for (int i = 0; i < listlen; i++) {
		if (finds(listOfedges[i].first) != finds(listOfedges[i].second)) {
			unions(listOfedges[i].first, listOfedges[i].second);
			alllen += listOfedges[i].length;
			cout << listOfedges[i].first << " " << listOfedges[i].second << endl;
		}
	}
	cout << "\n" << alllen << "\n";
	system("pause");
	delete[] listOfedges;
	return 0;
}