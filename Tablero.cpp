#include <iostream>
using namespace std;

//Declaracion global del array tablero (8*8 lugares) tipo char
char tablero[8][8];
char blanco = 'o';
char negro = 'x';
char libre = ' ';
char limite = '-';
//Contadores de captura
int Captura_blanca, Captura_negra;


void iniciaTablero()
{
    // Recorrido de filas
    for (int filas = 0; filas < 8; filas++)
    {
        // Recorrido de columnas (elementos)
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
    cout << "   0  1  2  3  4  5  6  7";
}
//Bool para que retorne true o false
bool evaluarGanador()
{
    if(Captura_blanca == 12)
    {
        cout << "\n¡El jugador BLANCO ha ganado por capturas!" << endl;
        return true;
    }
    else if(Captura_negra == 12)
    {
        cout << "\n¡El jugador NEGRO ha ganado por capturas!" << endl;
        return true;
    }
    //Aún no hay ganador
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
    
    while (win == false) 
    {
        cout << "\n--- Turno del jugador: " << jugador << " ---" << endl;
        cout << "Ingrese posicion de la ficha que va a mover (X [espacio] Y):" << endl;
        cin >> x >> y;

        if (tablero[y][x] != jugador)
        {
            cout << "\nError: La ficha que elegiste no es tuya." << endl;
            //reinicia el ciclo en caso de error
            continue; 
        }

        cout << "Ingrese posicion de donde la moverá (X [espacio] Y):" << endl;
        cin >> xs >> ys;

        //La posicion elegida ya tiene una ficha del mismo jugador
        if (tablero[ys][xs] == jugador)
        {
            cout << "\nError: La posicion que elegiste ya tiene una ficha tuya." << endl;
            continue;
        }
        //La posicion elegida esta libre
        else if (tablero[ys][xs] == libre)
        {
            tablero[ys][xs] = jugador;
            tablero[y][x] = libre;
            //Actualiza tablero
            mostrarTablero();
        }
        //La posicion elegida tiene una ficha del jugador contrario
        else if (tablero[ys][xs] != jugador && tablero[ys][xs] != libre)
        {
            //Elimina la ficha del jugador contrario
            tablero[ys][xs] = jugador; 
            tablero[y][x] = libre;
            
            if (jugador == blanco) 
            {
                Captura_blanca++;
            } 
            else 
            {
                Captura_negra++;
            }
            mostrarTablero();
        }
        //Evalua si alguien ganó con su ultimo movimiento
        win = evaluarGanador();
        if (win == true) {
            break;
        }

        //Pregunta para rendirse
        cout << "\n¿Prefieres rendirte? (s/n)" << endl;
        cin >> res;
        res = tolower(res);
        if (res == 's') 
        {
            win = true;
            cout << "\nEl jugador " << jugador << " se ha rendido." << endl;
            continue;
        } 

        // Cambio de turno (solo si el movimiento fue exitoso)
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
            cout << "\n El juego ha iniciado" << endl;
            iniciaTablero();
            mostrarTablero();
            turno();
            evaluarGanador();
        }
        else if (opc > 2 || opc < 1)
        {
            cout << "Opción desconocida.";
        }
    } 
    cout << "\n Saliendo del juego...";

    return 0;
}
