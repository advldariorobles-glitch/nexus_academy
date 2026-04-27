#include <iostream>
#include <mysql.h>
#include <windows.h>

using namespace std;

void buscarAlumno(MYSQL* conn) {
    int id;
    cout << "Ingrese ID: ";
    cin >> id;

    string query = "SELECT nombre, apellido, celular, nota_final FROM estudiantes WHERE id_estudiante = " + to_string(id);

    mysql_query(conn, query.c_str());
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);

    if (row) {
        cout << "Nombre: " << row[0] << " " << row[1] << endl;
        cout << "Celular: " << row[2] << endl;
        cout << "Nota: " << row[3] << endl;
    } else {
        cout << "Alumno no encontrado\n";
    }

    mysql_free_result(res);
}

void top5(MYSQL* conn) {
    mysql_query(conn, "SELECT nombre, apellido, nota_final FROM estudiantes ORDER BY nota_final DESC LIMIT 5");
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;

    cout << "\n--- TOP 5 ---\n";
    while ((row = mysql_fetch_row(res))) {
        cout << row[0] << " " << row[1] << " - " << row[2] << endl;
    }

    mysql_free_result(res);
}

void enRiesgo(MYSQL* conn) {
    mysql_query(conn, "SELECT nombre, apellido, nota_final FROM estudiantes WHERE nota_final < 40");
    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;

    cout << "\n--- EN RIESGO ---\n";
    while ((row = mysql_fetch_row(res))) {
        cout << row[0] << " " << row[1] << " - " << row[2] << endl;
    }

    mysql_free_result(res);
}

void actualizarNota(MYSQL* conn) {
    int id;
    float nota;

    cout << "ID del alumno: ";
    cin >> id;
    cout << "Nueva nota: ";
    cin >> nota;

    string query = "UPDATE estudiantes SET nota_final = " + to_string(nota) +
                   " WHERE id_estudiante = " + to_string(id);

    if (mysql_query(conn, query.c_str()) == 0) {
        cout << "Nota actualizada\n";
    } else {
        cout << "Error: " << mysql_error(conn) << endl;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    MYSQL* conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "1234", "gestion_estudiantes", 3306, NULL, 0)) {
        cout << "Error de conexion: " << mysql_error(conn) << endl;
        return 1;
    }

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
            case 2: top5(conn); break;
            case 3: enRiesgo(conn); break;
            case 4: actualizarNota(conn); break;
        }

    } while (opcion != 5);

    mysql_close(conn);
    return 0;
}