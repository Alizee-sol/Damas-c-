#include <iostream>
//Para la función abs()
#include <cmath>
//Para la función tolower()
#include <cctype>

using namespace std;

//Declaración global del array tablero (8*8 casillas)
char tablero[8][8];
char blanco = 'o';
char negro = 'x';
char libre = '-';
char limite = ' ';
char dama_blanca = 'O';
char dama_negra = 'X';
//Contadores de captura
int Captura_blanca, Captura_negra;

bool evaluarGanador();
void mostrarTablero();

void iniciaTablero()
{
    //Reinicio de contadores
    Captura_blanca = 0;
    Captura_negra = 0;

    //Recorrido de filas
    for (int filas = 0; filas < 8; filas++)
    {
        //Recorrido de columnas (elementos)
        for (int ele = 0; ele < 8; ele++)
        {
            //Casillas oscuras (donde si pueden moverse las fichas)
            if ((filas + ele) % 2 != 0) 
            {
                //fichas Negras en las primeras 3 filas
                if (filas < 3) 
                {
                    tablero[filas][ele] = negro;
                }
                //fichas Blancas en las ultimas 3 filas
                else if (filas > 4) 
                {
                    tablero[filas][ele] = blanco;
                }
                //casillas sin usar
                else 
                {
                    tablero[filas][ele] = libre;
                }
            }
            //Si la suma es par, es una casilla "blanca" 
            //(donde no pueden moverse las fichas)
            else 
            {
                tablero[filas][ele] = limite; 
            }
        }
    }
}

void mostrarTablero() 
{  
    //Recorrido de filas para mostrar número en Y
    for (int num = 0; num < 8; num++) 
    {
        cout << num << " "; 
        //Contenido del tablero con espacios
        for (int celda = 0; celda < 8; celda++) 
        {
            cout << " " << tablero[num][celda] << " ";
        }
        cout << endl;
    }
    //Números para identificar celdas en X
    cout << "   0  1  2  3  4  5  6  7" << endl;
    cout << "Puntos de Blanco(o): " << Captura_blanca << " | Negro(x): " << Captura_negra << endl;
}

void evaluarCoronacion(int x, int y, char jugador)
{
    //si la blanca llega a la fila 0, se convierte en dama
    if (jugador == blanco && y == 0) 
    {
        tablero[y][x] = dama_blanca;
        cout << "\nEl jugador BLANCO ha coronado una Dama" << endl;
    }
    //si la negra llega a la fila 7, se convierte en dama
    else if (jugador == negro && y == 7) 
    {
        tablero[y][x] = dama_negra;
        cout << "\nEl jugador NEGRO ha coronado una Dama" << endl;
    }
}

//dirección Y del movimiento es válida según el tipo de ficha
bool evaluarDireccionY(char fichaMoviendose, int difY, int vectorY)
{
    //Si es una Dama, la dirección no importa
    if (fichaMoviendose == dama_blanca || fichaMoviendose == dama_negra) 
    {
        return true; 
    }
    // Si es una ficha normal, si importa)
    if (difY == vectorY || difY == (vectorY * 2))
    {
        return true;
    }

    return false; // Movimiento hacia atrás de una ficha normal
}

bool evaluarGanador()
{
    if(Captura_blanca == 12)
    {
        cout << "\nEl jugador BLANCO ha ganado por capturas" << endl;
        return true;
    }
    else if(Captura_negra == 12)
    {
        cout << "\nEl jugador NEGRO ha ganado por capturas" << endl;
        return true;
    }
    return false; 
}

//verifica si hay un salto disponible
bool tieneSaltoDisponible(int x, int y, char jugador)
{
    //dirección en Y según quien está jugando
    int dirY = (jugador == blanco) ? -1 : 1;
    char oponente = (jugador == blanco) ? negro : blanco;
    //dirección en X
    int saltosX[2] = {-2, 2}; 
    
    for (int i = 0; i < 2; i++) 
    {
        int destX = x + saltosX[i];
        int destY = y + (dirY * 2);
        int enemigoX = x + (saltosX[i] / 2);
        int enemigoY = y + dirY;

        if (destX >= 0 && destX < 8 && destY >= 0 && destY < 8) 
        {
            if (tablero[enemigoY][enemigoX] == oponente && tablero[destY][destX] == libre) 
            {
                return true; 
            }
        }
    }
    return false; 
}

void turno()
{
    //variable temporal para salir del ciclo
    char res;
    bool win = false;
    //Jugador actual (comienza el blanco = o)
    char jugador = blanco;
    //x, y = Origen // xs, ys = destino
    int x = 0, y = 0, xs = 0, ys = 0;
    bool turnoExtra = false;
    char Dama = (jugador == blanco) ? dama_blanca : dama_negra;
    
    while (win == false) 
    {
        cout << "\n+---+---+ Turno del jugador: " << jugador << " +---+---+" << endl;
        
        if (turnoExtra == false) 
        {
            cout << "Ingrese posicion de la ficha que va a mover (X [espacio] Y):" << endl;
            cin >> x >> y;

            if (tablero[y][x] != jugador && tablero[y][x] != Dama)
            {
                cout << "\nError: La ficha que elegiste no es tuya o la casilla esta vacia." << endl;
                continue; 
            }
        }
        else 
        {
            cout << "SALTO MULTIPLE: Debes continuar comiendo con tu ficha en (" << x << " " << y << ")" << endl;
        }

        cout << "Ingrese posicion de donde la movera (X [espacio] Y):" << endl;
        cin >> xs >> ys;

        if (tablero[ys][xs] == limite || tablero[ys][xs] == jugador) {
            cout << "\nError: Destino invalido." << endl;
            continue;
        }

        //vectores de movimiento
        int difX = xs - x;
        int difY = ys - y;
        int vectorY = (jugador == blanco) ? -1 : 1; 
        char fichaActual = tablero[y][x];

        //Movimiento con distancia de 1
        if (abs(difX) == 1 && evaluarDireccionY(fichaActual, difY, vectorY)) 
        {
            if (turnoExtra == true) {
                cout << "\nError: Estas obligado a hacer el salto multiple, no puedes hacer un movimiento normal." << endl;
                continue;
            }

            if (tablero[ys][xs] == libre) 
            {
                tablero[ys][xs] = jugador;
                tablero[y][x] = libre;
                evaluarCoronacion(xs,ys,jugador);
                mostrarTablero();
                turnoExtra = false; 
            } 
        }
        //Movimiento con distancia de 2
        else if (abs(difX) == 2 && evaluarDireccionY(fichaActual, difY, vectorY)) 
        {
            int enemigoX = x + (difX / 2);
            int enemigoY = y + (difY / 2);

            if (tablero[enemigoY][enemigoX] != libre && tablero[enemigoY][enemigoX] != limite && tablero[enemigoY][enemigoX] != jugador) 
            {
                tablero[ys][xs] = jugador;               
                tablero[y][x] = libre;                   
                tablero[enemigoY][enemigoX] = libre; 

                if (jugador == blanco)
                {
                    Captura_blanca++;
                }
                else 
                {
                    Captura_negra++; 
                }
                evaluarCoronacion(xs,ys,jugador);
                mostrarTablero();

                // Evaluar salto múltiple
                if (tieneSaltoDisponible(xs, ys, jugador)) 
                {
                    turnoExtra = true;
                    x = xs; 
                    y = ys; 
                    continue;
                }
                else 
                {
                    turnoExtra = false; 
                }
            }
            else 
            {
                cout << "\nError: No hay una ficha enemiga para saltar." << endl;
                continue;
            }
        }
        else 
        {
            cout << "\nError: Movimiento diagonal invalido." << endl;
            continue;
        }

        win = evaluarGanador();
        if (win == true) break;

        // Pregunta para rendirse (solo si no estamos a mitad de un salto múltiple)
        if (!turnoExtra) {
            cout << "\n¿Prefieres rendirte? (s/n)" << endl;
            cin >> res;
            res = tolower(res);
            if (res == 's') 
            {
                win = true;
                cout << "\nEl jugador " << jugador << " se ha rendido." << endl;
                continue;
            } 

            // Cambio de turno
            if (jugador == blanco) 
            {
                jugador = negro;
            }
            else 
            {
                jugador = blanco;
            }
        }
    }
}

int main()
{
    int opc = 0;
    while(opc != 2)
    {
        cout << "\n+---+---+---+ JUEGO DE LAS DAMAS +---+---+---+" << endl;
        cout << "1. Comenzar" << endl;
        cout << "2. Salir" << endl;
        cin >> opc;
        if (opc == 1)
        {
            cout << "\n +---+---+ El juego ha iniciado +---+---+" << endl;
            iniciaTablero();
            mostrarTablero();
            turno();
        }
        else if (opc != 2)
        {
            cout << "Opcion desconocida.";
        }
    } 
    cout << "\n Saliendo del juego..." << endl;

    return 0;
}