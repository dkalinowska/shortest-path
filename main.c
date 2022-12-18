#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define WALL 1
#define PATH 0
#define UNVISITED -1

// Struktura przechowująca informacje o położeniu komórki labiryntu
struct Cell {
  int x;
  int y;
  int distance; // Odległość komórki od punktu startowego
};

// Funkcja wyznaczająca najkrótszą drogę w labiryncie
int findShortestPath(int** maze, int width, int height, struct Cell start, struct Cell end) 
{
    // Inicjalizacja tablicy odwiedzonych komórek
    int** visited = malloc(height * sizeof(int*));
    for (int i = 0; i < height; i++) 
    {
        visited[i] = malloc(width * sizeof(int));
    }
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++) 
        {
        visited[i][j] = UNVISITED; // Oznaczenie każdej komórki jako nieodwiedzonej
        }
    }

    // Inicjalizacja kolejki do przechowywania komórek do odwiedzenia
    struct Cell queue[width * height];
    int front = 0; // Wskaźnik początku kolejki
    int rear = 0; // Wskaźnik końca kolejki
    queue[rear++] = start; // Dodanie punktu startowego do kolejki
    visited[start.y][start.x] = 0; // Oznaczenie punktu startowego jako odwiedzonego i ustawienie odległości na 0

    // Pętla przechodząca labirynt metodą BFS (Breadth-First Search)
    // i szukająca najkrótszej drogi do wybranego punktu
    while (front != rear) 
    { // Dopóki kolejka nie jest pusta
        struct Cell current = queue[front++]; // Pobranie aktualnej komórki z kolejki
        if (current.x == end.x && current.y == end.y) 
        {   // Jeśli znaleziono wybrany punkt
            // Zwolnienie pamięci zajmowanej przez tablicę odwiedzonych komórek
            for (int i = 0; i < height; i++) 
            {
                free(visited[i]);
            }
            free(visited);
            return current.distance; // Zwrócenie odległości od punktu startowego
        }

    // Przejście po wszystkich sąsiadujących z aktualną komórką komórkach
        for (int dx = -1; dx <= 1; dx++) 
        {
            for (int dy = -1; dy <= 1; dy++) 
            {
                // Pomiń aktualną komórkę (dx = dy = 0) oraz sąsiadujące po skosie komórki (abs(dx) = abs(dy) = 1)
                if (dx == 0 && dy == 0 || abs(dx) == abs(dy)) 
                {
                    continue;
                }

                int x = current.x + dx; // Wyliczenie współrzędnej x sąsiadującej komórki
                int y = current.y + dy; // Wyliczenie współrzędnej y sąsiadującej komórki
                
                // Jeśli sąsiadująca komórka znajduje się w granicach labiryntu
                // i jest ścieżką oraz nie była jeszcze odwiedzona, dodaj ją do kolejki
                if (x >= 0 && x < width && y >= 0 && y < height && maze[y][x] == PATH && visited[y][x] == UNVISITED) 
                {
                    struct Cell next;
                    next.x = x;
                    next.y = y;
                    // Ustawienie odległości sąsiadującej komórki jako o jeden większej niż odległość aktualnej komórki
                    next.distance = current.distance + 1;
                    queue[rear++] = next; // Dodanie sąsiadującej komórki do kolejki
                    visited[y][x] = next.distance; // Oznaczenie sąsiadującej komórki jako odwiedzonej
                }
            }
        }
    }
}