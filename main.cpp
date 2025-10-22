//Author: Jack Fontenot
//Assignment Title: Program 5
//Assignment Description: multi algo path finder
//Due Date: 10/26/2025
//Date Created: 10/22/2025
//Date Last Modified: 10/22/2025

#include <iostream>

using namespace std;

int main() {
    int n, m;
    int v1, v2, w;

    cin >> n;
    cin >> m;

    cout << n << " " << m << endl;

    for (int i = 0; i < m; i++) {
        cin >> v1;
        cin >> v2;
        cin >> w;
        cout << v1 << " " << v2 << " " << w << endl;
    }

    return 0;
}