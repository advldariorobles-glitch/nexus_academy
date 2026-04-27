#include <iostream>
#include "db.h"

using namespace std;

int main() {
    MYSQL* conn = conectar();

    int opcion;

    do {
        cout << "\n--- NEXUS ACADEMY ---\n";
        cout << "1. Buscar alumno\n";
        cout << "2. Top 5\n";
        cout << "3. En riesgo\n";
        cout << "4. Actualizar nota\n";
        cout << "5. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: buscarAlumno(conn); break;
            case 2: mostrarTop5(conn); break;
            case 3: mostrarRiesgo(conn); break;
            case 4: actualizarNota(conn); break;
        }

    } while (opcion != 5);

    mysql_close(conn);
    return 0;
}