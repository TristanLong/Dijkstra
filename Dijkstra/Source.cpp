#include "iostream"
#include "fstream"
#include "vector"
#include "queue"
using namespace std;

const int MAX = 20;

struct maTrix {
	int maTranKe[MAX][MAX];
	int soDinh;
};

void readFile(maTrix& mtk) {
	ifstream inFile("Text.txt");
	if (!inFile.is_open()) {
		cout << "\nKhong the mo tep";
		return;
	}

	inFile >> mtk.soDinh;
	for (int i = 0; i < mtk.soDinh; i++) {
		for (int j = 0; j < mtk.soDinh; j++) {
			inFile >> mtk.maTranKe[i][j];
		}
	}
	inFile.close();
}

void outputMaTrix(maTrix mtk) {
	cout << "\nMA TRAN KE: " << endl;
	for (int i = 0; i < mtk.soDinh; i++) {
		for (int j = 0; j < mtk.soDinh; j++) {
			cout << mtk.maTranKe[i][j] << "\t";
		}
		cout << endl;
	}
}

void Dijkstra(int dinhBatDau, maTrix graph) {
	const int VO_CUC = 1e9;
	vector<int> khoangCach(graph.soDinh, VO_CUC); // cho mọi đỉnh là vô cực 
	vector<bool> visited(graph.soDinh, false);
	khoangCach[dinhBatDau] = 0;

	// { khoảng cách, đỉnh, chọn nhỏ nhất }
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> hangUuTien;
	hangUuTien.push({ 0, dinhBatDau });

	while (!hangUuTien.empty()) {
		int dinhHienTai = hangUuTien.top().second;
		hangUuTien.pop();

		if (visited[dinhHienTai]) continue; // đỉnh này đã được thăm 
		visited[dinhHienTai] = true;

		for (int dinhKe = 0; dinhKe < graph.soDinh; dinhKe++) {
			int trongSo = graph.maTranKe[dinhHienTai][dinhKe];
			if (trongSo != VO_CUC) {
				if (trongSo != 0 && khoangCach[dinhKe] > khoangCach[dinhHienTai] + trongSo) {
					khoangCach[dinhKe] = khoangCach[dinhHienTai] + trongSo;
					hangUuTien.push({ khoangCach[dinhKe], dinhKe });
				}
			}
		}
	}

	for (int i = 0; i < graph.soDinh; i++) {
		cout << khoangCach[i] << " ";
	}
}

int main() {
	maTrix graph;
	readFile(graph);
	outputMaTrix(graph);

	int dinhBatDau;
	do {
		cout << "\nNhap dinh bat dau: ";
		cin >> dinhBatDau;
	} while (dinhBatDau < 0 || dinhBatDau >= graph.soDinh);

	Dijkstra(dinhBatDau, graph);

	return 0;
}