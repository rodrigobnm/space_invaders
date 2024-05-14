/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = 34, y = 12;
int incX = 1, incY = 1;

void printHello(int nextX, int nextY)
{
    screenSetColor(RED, DARKGRAY);
    screenGotoxy(x, y);
    printf("           ");
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("W");
}

void printKey(int ch)
{
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(35, 22);
    printf("Key code :");

    screenGotoxy(34, 23);
    printf("");
    
    if (ch == 27) screenGotoxy(36, 23);
    else screenGotoxy(39, 23);

    printf("%d ", ch);
    while (keyhit())
    {
        printf("%d ", readch());
    }
}

int main() {
    
    // Inicialize variáveis
    size_t maxX = MAXX;
    size_t minX = MINX;
    static int ch = 0;

    // Inicialize o ambiente (tela, teclado, temporizador)
    screenInit(1);
    keyboardInit();
    timerInit(50);

    printHello(x, y);
    screenUpdate();

    while (ch != 10) //enter
    {
        // Handle user input
        if (keyhit()) 
        {
            ch = readch();
            printKey(ch);
            screenUpdate();
        }

        // Update game state (move elements, verify collision, etc)
        if (timerTimeOver() == 1)
        {
            int newX = x + incX;
            if (newX >= (maxX - strlen("W") - 1) || newX <= minX + 1) 
                incX = -incX;
            int newY = y + incY;
            if (newY >= MAXY-1 || newY <= MINY+1) 
                incY = -incY;

            printKey(ch);
            printHello(newX, newY);

            screenUpdate();
        }
    }

    // Limpeza do ambiente (liberação de recursos)
    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
