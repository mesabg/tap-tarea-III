/**
 * Ejercicio 1 
 * Integrantes
 *    Ricardo Pereira
 *    Moisés Berenguer
 **/

//-- Dependencies
#include <climits>
#include <iostream>
#include <cstdio>
#include <queue>
#include <utility>

//-- Defines
#define INFINITO INT_MAX
#define NO_VISITADO FALSE
#define VISITADO TRUE

//-- To avoid std:: namespacing
using namespace std;


//-- To make life easier :)
class Robot{
public:
    int x;
    int y;
    char direccion;

    Robot(){}

    Robot(pair<int, int> position, char direccion){
        this->x = position.first;
        this->y = position.second;
        this->direccion = direccion;
    }

    Robot(int x, int y, char direccion){
        this->x = x;
        this->y = y;
        this->direccion = direccion;
    }

    //-- Some functions
    char beforeDireccion(bool where = true){
        if (where){
            //-- Derecha
            switch(direccion){
                case 'N':
                    direccion = 'E';
                    break;
                case 'S':
                    direccion = 'O';
                    break;
                case 'E':
                    direccion = 'S';
                    break;
                case 'O':
                    direccion = 'N';
                    break;
            };
        }else{
            //-- Izquierda
            switch(direccion){
                case 'N':
                    direccion = 'O';
                    break;
                case 'S':
                    direccion = 'E';
                    break;
                case 'E':
                    direccion = 'N';
                    break;
                case 'O':
                    direccion = 'S';
                    break;
            };
        }
        return direccion;
    }


    pair<int, int> beforeMove (char** tablero, int n){
        pair<int, int> position;

        switch(direccion){
            case 'N':
                position.second = y;
                if( x - 1 >= 0 && x - 1 < n){
                    if( tablero[x - 1][y] != '*' && !(tablero[x - 1][y] == 'D' || tablero[x - 1][y] == '.') ){
                        position.first = x;
                        return position;
                    }
                } else {
                    position.first = x;
                    return position;
                }
                position.first = x - 1;
                return position;

            case 'S':
                position.second = y;
                if( x + 1 >= 0 && x + 1 < n){
                    if( tablero[x + 1][y] != '*' && !(tablero[x + 1][y] == 'D' || tablero[x + 1][y] == '.') ){
                        position.first = x;
                        return position;
                    }
                } else {
                    position.first = x;
                    return position;
                }
                position.first = x + 1;
                return position;
            case 'E':
                position.first = x;
                if( y + 1 >= 0 && y + 1 < n){
                    if( tablero[x][y + 1] != '*' && !(tablero[x][y + 1] == 'D' || tablero[x][y + 1] == '.') ){
                        position.second = y;
                        return position;
                    }
                } else {
                    position.second = y;
                    return position;
                }
                position.second = y + 1;
                return position;   
            case 'O':            
                position.first = x;
                if( y - 1 >= 0 && y - 1 < n){
                    if( tablero[x][y - 1] != '*' && !(tablero[x][y - 1] == 'D' || tablero[x][y - 1] == '.') ){
                        position.second = y;
                        return position;
                    }
                } else {
                    position.second = y;
                    return position;
                }
                position.second = y -1;
                return position;
        }
    }
};


int parseDireccion(char direccion){
    switch(direccion){
        case 'N':
            return 0;
        case 'S':
            return 1;
        case 'E':
            return 2;
        case 'O':
            return 3;
    };
}

void printRobot(Robot r){
    cout << "Robot :: " << r.x << " " << r.y << " " << r.direccion << "\n"; 
}


int distance(pair<Robot, Robot> fuente, char** tablero, int n){
    //-- Variable structure
    bool ***estado_r1 = new bool**[n], ***estado_r2 = new bool**[n];
    int** movimientos = new int*[n];
    for (int i=0; i<n; i++){
        estado_r1[i] = new bool*[n];
        estado_r2[i] = new bool*[n];
        movimientos[i] = new int[n];

        for (int j=0;j<n;j++){
            estado_r1[i][j] = new bool[4];
            estado_r2[i][j] = new bool[4];

            for (int k=0;k<n;k++)
                estado_r1[i][j][k] = estado_r2[i][j][k] = false;

            movimientos[i][j] = INFINITO;
        }
    }
    //ESTADO_R1 CONTIENE UNA MATRIZ DE VISITADOS SOLO PARA ROBOT 1
    estado_r1[fuente.first.x][fuente.first.y][parseDireccion(fuente.first.direccion)] = true;
    //ESTADO_R2 CONTIENE UNA MATRIZ DE VISITADOS SOLO PARA ROBOT 2
    estado_r2[fuente.second.x][fuente.second.y][parseDireccion(fuente.second.direccion)] = true;
    //MOVIMIENTO 0
    movimientos[fuente.first.x][fuente.first.y] = 0;

    queue< pair<Robot, Robot> > Q;
    Q.push(fuente);

    //-- Process
    while( !Q.empty() ){
        pair<Robot, Robot> actual = Q.front();
        Q.pop();
                                  
        if( tablero[actual.first.x][actual.first.y]== 'D' &&
        tablero[actual.second.x][actual.second.y]== 'D'){
            int mov = movimientos[actual.first.x][actual.first.y];
            delete estado_r1;
            delete estado_r2;
            delete movimientos;
            //Q.deallocate();
            //Q.destroy();
            return mov;
        }              
        
        estado_r1[actual.first.x][actual.first.y][parseDireccion(actual.first.direccion)] = true;
        estado_r2[actual.second.x][actual.second.y][parseDireccion(actual.second.direccion)] = true;

        //cout << "Here\n";

        for( int i = 0; i < 3; i++){

            if (i == 0){
                //-- Movimiento hacia adelante
                //cout << "Adelante\n";
                pair<int, int> r1 = actual.first.beforeMove(tablero, n);
                pair<int, int> r2 = actual.second.beforeMove(tablero, n);

                //cout << "R1 :: " << r1.first << " " << r1.second << endl;
                //cout << "R2 :: " << r2.first << " " << r2.second << endl;

                if( !(r1.first == r2.first && r1.second == r2.second) && !(r1.first == actual.first.x && r1.second == actual.first.y) && !(r2.first == actual.second.x && r2.second == actual.second.y) && !estado_r1[r1.first][r1.second][parseDireccion(actual.first.direccion)] && !estado_r2[r2.first][r2.second][parseDireccion(actual.second.direccion)]){
                    movimientos[r1.first][r1.second] = movimientos[actual.first.x][actual.first.y] + 1;
                    pair<Robot, Robot> adyacente;
                    adyacente.first = Robot(r1, actual.first.direccion);
                    adyacente.second = Robot(r2, actual.second.direccion);
                    Q.push(adyacente);  
                    break;
                    //cout << "AQUI TOY" << endl;
                }
            }else if( i == 1){
                // GIRAR DERECHA 
                pair<int, int> r1; r1.first = actual.first.x; r1.second = actual.first.y;
                pair<int, int> r2; r2.first = actual.second.x; r2.second = actual.second.y;

                if(!estado_r1[r1.first][r1.second][parseDireccion(actual.first.beforeDireccion())] && !estado_r2[r2.first][r2.second][parseDireccion(actual.second.beforeDireccion())]){
                    movimientos[actual.first.x][actual.first.y]++;
                    pair<Robot, Robot> adyacente;
                    adyacente.first = Robot(r1, actual.first.beforeDireccion());
                    adyacente.second = Robot(r2, actual.second.beforeDireccion());
                    Q.push(adyacente); 
                    estado_r1[actual.first.x][actual.first.y][parseDireccion(actual.first.beforeDireccion())] = true;
                    estado_r2[actual.second.x][actual.second.y][parseDireccion(actual.second.beforeDireccion())] = true;   
                }
            }else if( i == 2){
                // GIRAR IZQUIERDA
                pair<int, int> r1; r1.first = actual.first.x; r1.second = actual.first.y;
                pair<int, int> r2; r2.first = actual.second.x; r2.second = actual.second.y;

                if(!estado_r1[r1.first][r1.second][parseDireccion(actual.first.beforeDireccion(false))] && !estado_r2[r2.first][r2.second][parseDireccion(actual.second.beforeDireccion(false))]){
                    movimientos[actual.first.x][actual.first.y]++;
                    pair<Robot, Robot> adyacente;
                    adyacente.first = Robot(r1, actual.first.beforeDireccion(false));
                    adyacente.second = Robot(r2, actual.second.beforeDireccion(false));
                    Q.push(adyacente); 
                    
                    estado_r1[actual.first.x][actual.first.y][parseDireccion(actual.first.beforeDireccion(false))] = true;
                    estado_r2[actual.second.x][actual.second.y][parseDireccion(actual.second.beforeDireccion(false))] = true;  
                }
            }
        }
    }

    return INFINITO;
}


int minimumMovements(pair<Robot, Robot> fuente, char** tablero, int n){
    //-- Create Robots
    //printRobot(fuente.first);
   // printRobot(fuente.second);
    
    int mov = distance(fuente, tablero, n);
    return mov == INFINITO ? -1 : mov;
}

void printM(char** tablero, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << tablero[i][j];
        }
        cout << endl;
    }
}


int main(){
    //-- Declare some variables
    int n;
    char **tablero;
    pair<Robot, Robot> fuente;
    bool one_stored = false;

    //-- Process reading
    scanf("%d", &n);
    while(n != 0){
        tablero = new char*[n];
        for(int i=0; i<n; i++){
            tablero[i] = new char[n];
            //scanf("%s", tablero[i]);
            //printf("%s\n", tablero[i]);

            for(int j=0;j<n;j++){
                cin >> tablero[i][j];
                if(tablero[i][j] != '.' && tablero[i][j] != 'D' && tablero[i][j] != '*')
                    if (!one_stored){
                        fuente.first = Robot(i, j, tablero[i][j]);
                        one_stored = true;
                    }else{
                        fuente.second = Robot(i, j, tablero[i][j]);
                    }
            }

            //getchar();
        }
        //printM(tablero, n);

        //-- Process Statement
        printf("%d\n", minimumMovements(fuente, tablero, n));
        scanf("%d", &n);
        //delete tablero;
    }
}