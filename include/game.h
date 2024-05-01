#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>

#define ANCHO 800
#define ALTO 800
#define FPS 60
#define TPS 7 // ajusta la dificultad con esto
#define TAM_CELDA 38
#define ANCHO_CELDA 19
#define ALTO_CELDA 19
#define RAIZ_2 1.41421356237
#define TAM_MAX ANCHO_CELDA * ALTO_CELDA

const char TITULO[] = "Serpiente";
const Color COLOR_FONDO = {87, 138, 52, 255};
const Color COLOR_TABLERO_1 = {170, 215, 81, 255};
const Color COLOR_TABLERO_2 = {162, 209, 73, 255};
const Color COLOR_SERPIENTE = {63, 108, 222, 255};
const Color COLOR_MANZANA = {231, 71, 29, 255};
const Color OSCURO = {0, 0, 0, 100};

unsigned frames_transcurridos;
bool juego_terminado;
bool empezado;

typedef struct Nodo Nodo;

struct Nodo {
    int x, y;
    Nodo* siguiente;
};

Nodo* serpiente;
int manzana_x, manzana_y, dx, dy, tamano;

void ColocarManzana() {
    while (1) {
        int rx = rand() % ANCHO_CELDA;
        int ry = rand() % ALTO_CELDA;

        Nodo* actual = serpiente;
        while (actual) {
            if (actual->x == rx && actual->y == ry) {
                break;
            }
            actual = actual->siguiente;
        }

        if (!actual) {
            manzana_x = rx;
            manzana_y = ry;
            break;
        }
    }
}

void Reiniciar() {
    frames_transcurridos = 0;
    juego_terminado = 0;
    tamano = 0;

    dx = 1;
    dy = 0;

    // ooc: ¿qué demonios?
    serpiente = (Nodo*)malloc(sizeof(Nodo));
    serpiente->x = 7;
    serpiente->y = 9;
    serpiente->siguiente = (Nodo*)malloc(sizeof(Nodo));
    serpiente->siguiente->x = 6;
    serpiente->siguiente->y = 9;
    serpiente->siguiente->siguiente = (Nodo*)malloc(sizeof(Nodo));
    serpiente->siguiente->siguiente->x = 5;
    serpiente->siguiente->siguiente->y = 9;
    serpiente->siguiente->siguiente->siguiente = NULL;

    ColocarManzana();
}

int main() {

    srand((unsigned)time(NULL));

    assert(!GetWindowHandle());

    SetTargetFPS(60);
    InitWindow(ANCHO, ALTO, TITULO);

    Reiniciar();

    while (!WindowShouldClose()) {
        if (juego_terminado) {
            sleep(1);
            Reiniciar();
            continue;
        }

        BeginDrawing();
        ClearBackground(COLOR_FONDO);

        for (int i = 0; i < ALTO_CELDA; i++) {
            for (int j = 0; j < ANCHO_CELDA; j++) {
                DrawRectangle(
                    (j + 1) * TAM_CELDA,
                    (i + 1) * TAM_CELDA,
                    TAM_CELDA,
                    TAM_CELDA,
                    i * ANCHO_CELDA + j & 1 ? 
                        COLOR_TABLERO_2 :
                        COLOR_TABLERO_1
                );
            }
        }

        {
            Nodo* actual = serpiente;
            while (actual) {
                DrawRectangle(
                    (actual->x + 1) * TAM_CELDA,
                    (actual->y + 1) * TAM_CELDA,
                    TAM_CELDA,
                    TAM_CELDA,
                    COLOR_SERPIENTE
                );
                actual = actual->siguiente;
            }
        }

        DrawRectangle(
            (manzana_x + 1) * TAM_CELDA,
            (manzana_y + 1) * TAM_CELDA,
            TAM_CELDA,
            TAM_CELDA,
            COLOR_MANZANA
        );

        if (!empezado) {
            DrawRectangle(0, 0, ANCHO, ALTO, OSCURO);

            Vector2 v1 = {
                ANCHO / 2 - RAIZ_2 * TAM_CELDA,
                ALTO / 2 - RAIZ_2 * TAM_CELDA
            };
            Vector2 v2 = {
                ANCHO / 2 - RAIZ_2 * TAM_CELDA,
                ALTO / 2 + RAIZ_2 * TAM_CELDA
            };
            Vector2 v3 = {
                ANCHO / 2 + RAIZ_2 * TAM_CELDA,
                ALTO / 2
            };

            DrawTriangle(v1, v2, v3, WHITE);
        }

        EndDrawing();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            empezado = 1;
        }

        if (!empezado) {
            continue;
        }

        bool arriba    = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP),
             abajo  = IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN),
             izquierda  = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT),
             derecha = IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT);

        if (frames_transcurridos % (FPS / TPS) == 0) {

            if (arriba && (dx == -1 || dx == 1)) {
                dx = 0;
                dy = -1;
            }
            else if (abajo && (dx == -1 || dx == 1)) {
                dx = 0;
                dy = 1;
            }
            else if (izquierda && (dy == -1 || dy == 1)) {
                dy = 0;
                dx = -1;
            }
            else if (derecha && (dy == -1 || dy == 1)) {
                dy = 0;
                dx = 1;
            }

            {
                Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
                nuevoNodo->x = serpiente->x + dx;
                nuevoNodo->y = serpiente->y + dy;
                nuevoNodo->siguiente = serpiente;
                serpiente = nuevoNodo;
            }

            tamano++;
            if (serpiente->x == manzana_x && serpiente->y == manzana_y) {
                ColocarManzana();
            } else {
                Nodo* actual = serpiente;
                Nodo* previo = NULL;
                while (actual->siguiente) {
                    previo = actual;
                    actual = actual->siguiente;
                }
                previo->siguiente = NULL;
                tamano--;
            }

            // victoria épica (no obtienes nada)
            if (tamano == ANCHO_CELDA * ALTO_CELDA) {
                juego_terminado = 1;
            }

            if (serpiente->x < 0 || serpiente->y < 0 || 
                serpiente->x >= ANCHO_CELDA || serpiente->y >= ALTO_CELDA) {
                juego_terminado = 1;
            }

            {
                Nodo* actual = serpiente->siguiente;
                while (actual) {
                    if (actual->x == serpiente->x && actual->y == serpiente->y) {
                        juego_terminado = 1;
                        break;
                    }
                    actual = actual->siguiente;
                }
            }
        }

        frames_transcurridos++;
    }

    assert(GetWindowHandle());
    CloseWindow();
}
