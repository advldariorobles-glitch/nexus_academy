#ifndef DB_H
#define DB_H

#include <mysql.h>

MYSQL* conectar();

void buscarAlumno(MYSQL* conn);
void mostrarTop5(MYSQL* conn);
void mostrarRiesgo(MYSQL* conn);
void actualizarNota(MYSQL* conn);

#endif