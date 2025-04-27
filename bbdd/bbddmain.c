#include <stdio.h>
#include <string.h>
#include "bbddmain.h"

int abrir_base(BBDD *base, const char *nombre_archivo) {
    int rc = sqlite3_open(nombre_archivo, &(base->db));
    if (rc) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(base->db));
        return rc;
    }
    printf("Base de datos abierta correctamente.\n");

    // Crear tabla de usuarios si no existe
    const char *sql_create = "CREATE TABLE IF NOT EXISTS usuarios ("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                             "usuario TEXT UNIQUE,"
                             "contrasena TEXT);";

    char *errmsg = 0;
    rc = sqlite3_exec(base->db, sql_create, 0, 0, &errmsg);
    if (rc != SQLITE_OK) {
        printf("Error al crear tabla: %s\n", errmsg);
        sqlite3_free(errmsg);
    }

    return rc;
}

void cerrar_base(BBDD *base) {
    sqlite3_close(base->db);
    printf("Base de datos cerrada.\n");
}

int registrar_usuario(BBDD *base, const char *usuario, const char *contrasena) {
    const char *sql_insert = "INSERT INTO usuarios (usuario, contrasena) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(base->db, sql_insert, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        printf("Error al preparar statement: %s\n", sqlite3_errmsg(base->db));
        return rc;
    }

    sqlite3_bind_text(stmt, 1, usuario, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, contrasena, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Error al registrar usuario: %s\n", sqlite3_errmsg(base->db));
    } else {
        printf("Usuario registrado exitosamente.\n");
    }

    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE ? SQLITE_OK : rc;
}

int iniciar_sesion(BBDD *base, const char *usuario, const char *contrasena) {
    const char *sql_select = "SELECT id FROM usuarios WHERE usuario = ? AND contrasena = ?;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(base->db, sql_select, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        printf("Error al preparar consulta: %s\n", sqlite3_errmsg(base->db));
        return rc;
    }

    sqlite3_bind_text(stmt, 1, usuario, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, contrasena, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    int resultado = (rc == SQLITE_ROW);  // Hay resultado = inicio de sesión correcto

    if (resultado) {
        printf("Inicio de sesión exitoso.\n");
    } else {
        printf("Usuario o contraseña incorrectos.\n");
    }

    sqlite3_finalize(stmt);
    return resultado;
}

int existe_usuario(BBDD *bd, const char *nombre_usuario) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM usuarios WHERE usuario = ?;";  // asumiendo que tu tabla se llama 'usuarios'
    int existe = 0;

    if (sqlite3_prepare_v2(bd->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar consulta: %s\n", sqlite3_errmsg(bd->db));
        return 0;  // si falla, asumimos que no existe (podrías manejarlo diferente)
    }

    sqlite3_bind_text(stmt, 1, nombre_usuario, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        existe = (count > 0);
    }

    sqlite3_finalize(stmt);

    return existe;
}