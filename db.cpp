#include <iostream>
#include "db.h"

using namespace std;

MYSQL* conectar() {
    MYSQL* conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "1234", "gestion_estudiantes", 3306, NULL, 0);

    if (conn) {
        cout << "Conexion exitosa\n";
    } else {
        cout << "Error de conexion\n";
    }

    return conn;
}

void buscarAlumno(MYSQL* conn) {
    int id;
    cout << "Ingrese ID: ";
    cin >> id;

    string query = "SELECT nombre, apellido, celular, nota_final FROM estudiantes WHERE id_estudiante = " + to_string(id);

    mysql_query(conn, query.c_str());

    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;

    if ((row = mysql_fetch_row(res))) {
        cout << "Nombre: " << row[0] << " " << row[1] << endl;
        cout << "Celular: " << row[2] << endl;
        cout << "Nota: " << row[3] << endl;
    } else {
        cout << "Alumno no encontrado\n";
    }
}

void mostrarTop5(MYSQL* conn) {
    mysql_query(conn, "SELECT nombre, apellido, nota_final FROM estudiantes ORDER BY nota_final DESC LIMIT 5");

    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(res))) {
        cout << row[0] << " " << row[1] << " - Nota: " << row[2] << endl;
    }
}

void mostrarRiesgo(MYSQL* conn) {
    mysql_query(conn, "SELECT nombre, apellido, nota_final FROM estudiantes WHERE nota_final < 40");

    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(res))) {
        cout << row[0] << " " << row[1] << " - Nota: " << row[2] << endl;
    }
}

void actualizarNota(MYSQL* conn) {
    int id;
    float nota;

    cout << "Ingrese ID: ";
    cin >> id;
    cout << "Nueva nota: ";
    cin >> nota;

    string query = "UPDATE estudiantes SET nota_final = " + to_string(nota) + " WHERE id_estudiante = " + to_string(id);

    mysql_query(conn, query.c_str());

    cout << "Nota actualizada\n";
}