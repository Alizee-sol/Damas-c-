#include <iostream>
using namespace std;

//Declaracion global del array tablero (8*8 lugares) tipo char
char tablero[8][8];
char blanco = 'o';
char negro = 'x';
char libre = ' ';
//Contadores de captura
int Captura_blanca, Captura_negra;


void iniciaTablero()
{
    //Recorrido de filas
    for (int filas = 0; filas < 8; filas++)
    {
        //Recorrido de columas (elementos)
        for (int ele = 0; ele < 8; ele++)
        {
            //Fichas Negras en las primeras 3 filas
            //Verifica que la casilla sea par
            if (filas < 3 && (filas + ele) % 2 != 0)
            {
                tablero[filas][ele] = negro;
            }
            //Fichas Blancas en las últimas 3 filas
            //Verifica que la casilla sea par
            else if (filas > 4 && (filas + ele) % 2 != 0)
            {
                tablero[filas][ele] = blanco;
            }
            //Espacios vacíos (el resto)
            else 
            {
                tablero[filas][ele] = libre;
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
        cout << "Ingrese posicion de la ficha que va a mover (Fila Columna):" << endl;
        cin >> x >> y;

        if (tablero[x][y] != jugador)
        {
            cout << "\nError: La ficha que elegiste no es tuya." << endl;
            //reinicia el ciclo en caso de error
            continue; 
        }

        cout << "Ingrese posicion de donde la moverá (Fila Columna):" << endl;
        cin >> xs >> ys;

        //La posicion elegida ya tiene una ficha del mismo jugador
        if (tablero[xs][ys] == jugador)
        {
            cout << "\nError: La posicion que elegiste ya tiene una ficha tuya." << endl;
            continue;
        }
        //La posicion elegida esta libre
        else if (tablero[xs][ys] == libre)
        {
            tablero[xs][ys] = jugador;
            tablero[x][y] = libre;
            //Actualiza tablero
            mostrarTablero();
        }
        //La posicion elegida tiene una ficha del jugador contrario
        else if (tablero[xs][ys] != jugador && tablero[xs][ys] != libre)
        {
            //Elimina la ficha del jugador contrario
            tablero[xs][ys] = jugador; 
            tablero[x][y] = libre;
            
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
            opc = 0;
        }
        else
        {
            cout << "Opción desconocida."; 
            opc = 0;
        }
    } 
    cout << "\n Saliendo del juego...";

    return 0;
}
