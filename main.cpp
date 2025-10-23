//Author: Jack Fontenot
//Assignment Title: Program 5
//Assignment Description: multi algo path finder
//Due Date: 10/26/2025
//Date Created: 10/22/2025
//Date Last Modified: 10/22/2025

#include <iostream>
#include <vector>

using namespace std;

struct edge;

struct point{
    int name;
    int index;
    point* pred;
    vector<edge*> edges;
    char stat = 'U';
    int ic;
    int og;

    point(int name, int x): name(name), index(x){}

    size_t size() {
        return edges.size();
    }
};


struct edge{
    point* s;
    point* d;
    int c;
    int f;
    char type;

    edge(point* s, point* d, int c){
        this->s = s;
        this->d = d;
        this->c = c;
    }

    //gets the adjacent point to a
    point* getO(point* a){
        point* res = s;

        if(a == s){
            res = d;
        }

        return res;
    }

    //checks if edge is outgoing from a
    bool isOut(point* a){
        bool flag = true;

        if(a == d){
            flag = false;
        }

        return flag;
    }
};


struct path {
    vector<edge*> edges;
};

//to check if a point has been created already
bool contains(vector<int>&, int&);

//to find a point when constructing the graph
point* find(vector<vector<point*>>&, int&);

//Edmonds-Karp algo
void EK(vector<vector<point*>>&, vector<edge*>&, point*, point*, int&);

//Breadth-first search
path* bfs(vector<vector<point*>>&, point*);

int main() {
    char ab;
    int n, n1, m;
    int v1, v2, c, sn, tn;
    //int maxF;
    int x = 0;
    point* p1 = nullptr;
    point* p2 = nullptr;
    vector<vector<point*>> g;
    vector<int> nums;
    vector<edge*> edges;
    edge* e = nullptr;
    point* s = nullptr;
    point* t = nullptr;

    cin >> ab;

    if (ab == 'a') {
        cin >> n;
        cin >> m;

        cout << ab << endl;
        cout << n << " " << m << endl;

        for (int i = 0; i < m; i++) {
            cin >> v1;
            cin >> v2;
            cin >> c;
            cout << v1 << " " << v2 << " " << c << endl;

            if (i == 0) {
                nums.push_back(v1);
                nums.push_back(v2);

                p1 = new point(v1, x);
                vector<point*> temp;
                temp.push_back(p1);
                g.push_back(temp);
                x++;

                p2 = new point(v2, x);
                vector<point*> temp1;
                temp1.push_back(p2);
                g.push_back(temp1);
                x++;
            }else {
                if (!contains(nums, v1)) {
                    nums.push_back(v1);
                    p1 = new point(v1, x);
                    vector<point*> temp;
                    temp.push_back(p1);
                    g.push_back(temp);
                    x++;
                }else {
                    p1 = find(g, v1);
                }

                if (!contains(nums, v2)) {
                    nums.push_back(v2);
                    p2 = new point(v2, x);
                    vector<point*> temp;
                    temp.push_back(p2);
                    g.push_back(temp);
                    x++;
                }else {
                    p2 = find(g, v2);
                }
            }

            e = new edge(p1, p2, c);
            p1->edges.push_back(e);
            p2->edges.push_back(e);
            g.at(p1->index).push_back(p2);
            g.at(p2->index).push_back(p1);

            edges.push_back(e);
        }
        cin >> sn;
        cin >> tn;
        cout << sn << " " << tn << endl;
        c = 0;
        EK(g, edges, s, t, c);
    }else if (ab == 'b') {
        cin >> n;
        cin >> n1;
        cin >> m;
        cout << ab << endl;
        cout << n << " " << n1 << " " << m << endl;

        for (int i = 0; i < m; i++) {
            cin >> v1;
            cin >> v2;
            cout << v1 << " " << v2 << endl;

            if (i == 0) {
                nums.push_back(v1);
                nums.push_back(v2);
                p1 = new point(v1, x);
                vector<point*> temp;
                temp.push_back(p1);
                g.push_back(temp);
                x++;
                p2 = new point(v2, x);
                vector<point*> temp1;
                temp1.push_back(p2);
                g.push_back(temp1);
                x++;
            }else {
                if (!contains(nums, v1)) {
                    nums.push_back(v1);
                    p1 = new point(v1, x);
                    vector<point*> temp;
                    temp.push_back(p1);
                    g.push_back(temp);
                    x++;
                }else {
                    p1 = find(g, v1);
                }

                if (!contains(nums, v2)) {
                    nums.push_back(v2);
                    p2 = new point(v2, x);
                    vector<point*> temp;
                    temp.push_back(p2);
                    g.push_back(temp);
                    x++;
                }else {
                    p2 = find(g, v2);
                }
            }
            e = new edge(p1, p2, 0);
            p1->edges.push_back(e);
            p2->edges.push_back(e);
            g.at(p1->index).push_back(p2);
            g.at(p2->index).push_back(p1);
        }
    }

    return 0;
}

//to check if a point has been created already
bool contains(vector<int>& nums, int& n) {
    bool flag = false;

    for (size_t i = 0; i < nums.size(); i++) {
        if (nums.at(i) == n) {
            flag = true;
        }
    }

    return flag;
}

//to find a point when constructing the graph
point* find(vector<vector<point*>>& g, int& n) {
    point* res = nullptr;

    for(size_t i = 0; i < g.size(); i++){
        if(!g.at(i).empty() && g.at(i).front()->name == n) {
            res = g.at(i).front();
        }
    }

    return res;
}

//Edmonds-Karp algo
void EK(vector<vector<point*>>& g,vector<edge*>&edges,point*s,point* t,int&c){
    bool stop;
    path* p;
    edge* e = nullptr;
    int d;
    int x = 1;
    int maxF = 0;
    cout << "here" << endl;

    for (size_t i = 0; i < edges.size(); i++) {
        edges.at(i)->f = 0;
    }

    stop = false;

    do {
        cout << "1" << endl;
        p = bfs(g, s);

        if (p != nullptr) {
            d = 9000000;
            for (size_t i = 0; i < p->edges.size(); i++) {
                e = p->edges.at(i);
                if (e->f < d) {
                    d = e->f;
                }
            }
            for (size_t i = 0; i < p->edges.size(); i++) {
                if (e->type ==  'f') {
                    e->f += d;
                }else {
                    e->f -= d;
                }
            }
        }else {
            stop = true;
        }

        cout << "Residual Graph after iteration " << x << ":" << endl;


        x++;

        for (size_t i = 0; i < t->size(); i++) {
            maxF += t->edges.at(i)->f;
        }

        cout << "Max Flow: " << maxF << endl;

    }while(!stop);
}

//Breadth-first search
path* bfs(vector<vector<point*>>& g, point* s) {
    cout << "f" << endl;
    vector<vector<point*>> L;
    point* u = nullptr;
    point* v = nullptr;
    edge* e = nullptr;
    vector<point*> l0;
    s->stat = 'E';
    l0.push_back(s);
    path* res = new path();

    int i = 0;

    cout << "here1" << endl;

    while (!L.at(i).empty()) {
        vector<point*> temp;
        L.push_back(temp);
        for (size_t j = 0; j < L.at(i).size(); j++) {

            u = L.at(i).at(j);

            for (size_t k = 0; k < u->size(); k++) {

                e = u->edges.at(k);
                v = e->getO(s);

                if (e->isOut(u) && e->f < e->c) {
                    e->type = 'f';
                    res->edges.push_back(e);
                }else if ((e->isOut(v)) && e->f > 0) {
                    e->type = 'b';
                    res->edges.push_back(e);
                }

                if (v->stat == 'U') {
                    v->stat = 'E';
                    temp.push_back(v);
                }
            }
        }

        i++;
    }

    if (res->edges.size() == 0) {
        delete res;
        res = nullptr;
    }

    cout << "here2" << endl;

    return res;
}