#include <iostream>
#include <vector>
using namespace std;

const short dots = 8;

struct Figure {
    short x, y, fight = 0;

    bool put = false;

    Figure() {

    }

    void set(short x, short y) {
        this->x = x;
        this->y = y;
    }
};


struct Kon {
    short x, y, fight = 0;
    bool draw = false;

    vector<Figure> figuresss;

    Kon() {

    }

    void set(short x, short y) {
        this->x = x;
        this->y = y;
    }
};


short** init() {

    short** A = new short* [dots];

    for (int i = 0; i < dots; i++)
        A[i] = new short[dots];

    for (int i = 0; i < dots; i++)
        for (int j = 0; j < dots; j++)
            cin >> A[i][j];

    return A;
}


bool isOnBoard(short x, short y) {
    return x >= 0 && y >= 0 && x < 8 && y < 8;
}

void findBestKon(Kon**& koni, Figure**& figures, short s) {

    for (short i = 0; i < dots; i++) {
        for (short j = 0; j < dots; j++) {

            short size = 0;
            for (short k = 0; k < koni[i][j].figuresss.size(); k++) {

                Figure check = koni[i][j].figuresss[k];


                if (figures[check.x][check.y].x == check.x && figures[check.x][check.y].y == check.y && !figures[check.x][check.y].put) {
                    size++;
                }
            }


            if (size == s)
                for (short k = 0; k < koni[i][j].figuresss.size(); k++) {
                    Figure check = koni[i][j].figuresss[k];

                    if (figures[check.x][check.y].x == check.x && figures[check.x][check.y].y == check.y && !figures[check.x][check.y].put) {
                        koni[i][j].draw = true;
                        figures[check.x][check.y].put = true;
                    }

                }
        }
    }
}

void check3(short** matrix) {
    Kon** koni = new Kon * [8 * 8];
    Figure** figures = new Figure * [8 * 8];

    for (int i = 0; i < 8; i++)
        koni[i] = new Kon[8];

    for (int i = 0; i < 8; i++)
        figures[i] = new Figure[8];

    bool ch = false;

    for (int i = 0; i < dots; i++) {
        for (int j = 0; j < dots; j++) {

            if (matrix[i][j] != 2) {
                koni[i][j].set(i, j);
                figures[i][j].set(-1, -1);
            }

            else if (matrix[i][j] == 2) {
                figures[i][j].set(i, j);
                koni[i][j].set(-1, -1);
            }

            else {
                koni[i][j].set(-1, -1);
                figures[i][j].set(-1, -1);
            }
        }
    }
    cout << endl;

    for (int i = 0; i < dots; i++) {
        for (int j = 0; j < dots; j++) {

            if (koni[i][j].x == i) {

                short dx[8] = { -2, -2, -1, -1,  1,  1,  2, 2 };
                short dy[8] = { -1,  1, -2,  2, -2,  2, -1, 1 };

                for (short k = 0; k < 8; k++) {
                    short x = koni[i][j].x + dx[k];
                    short y = koni[i][j].y + dy[k];

                    if (isOnBoard(x, y) && matrix[x][y] == 2) {
                        koni[i][j].fight++;
                        koni[i][j].figuresss.push_back(figures[x][y]);
                    }

                }
            }

        }
    }
 

    findBestKon(koni, figures, 8);
    findBestKon(koni, figures, 7);
    findBestKon(koni, figures, 6);
    findBestKon(koni, figures, 5);
    findBestKon(koni, figures, 4);
    findBestKon(koni, figures, 3);
    findBestKon(koni, figures, 2);
    findBestKon(koni, figures, 1);



    for (int i = 0; i < dots; i++) {
        for (int j = 0; j < dots; j++) {
            if (koni[i][j].draw)
                cout << " K ";
            else if (matrix[i][j] == 2)
                cout << " O ";
            else cout << " . ";
        }
        cout << endl;
    }

}



int main()
{
    short** matrix = init();

    check3(matrix);
}




/*
0 0 0 0 0 0 0 0
0 0 0 0 0 0 2 0
0 0 0 0 0 0 0 0
0 0 0 0 2 0 0 0
2 0 0 0 2 0 0 0
0 0 2 0 0 0 0 0
0 2 0 0 0 2 0 0
0 0 0 0 0 0 0 0
*/