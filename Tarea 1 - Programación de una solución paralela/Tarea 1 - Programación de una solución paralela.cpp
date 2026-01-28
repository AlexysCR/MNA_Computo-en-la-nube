
#include <iostream>
#include <omp.h>
#include <ctime>    // Necesario para time()
#include <cstdlib>  // Necesario para rand() y srand()

#define N 7500          // Número de elementos en los arreglos
#define chunk 10       // Tamaño del chunk para la distribución estática
#define mostrar 15      // Número de elementos a mostrar en la terminal

void imprimeArreglo(float* d);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";
    float a[N], b[N], c[N];
    int i;

    // Inicializar la semilla para números aleatorios reales
    srand(time(0));

    // Llenado de arreglos con números aleatorios
    for (i = 0; i < N; i++)
    {
        // Genera números aleatorios entre 0 y 99
        a[i] = static_cast<float>(rand() % 100);
        b[i] = static_cast<float>(rand() % 100);
    }

    int pedazos = chunk;

    // Directiva de OpenMP para paralelizar el ciclo for
#pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    // Impresión de resultados
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);

    return 0;
}

void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++)
    {
        std::cout << d[x] << " - ";
    }
    std::cout << std::endl;
}