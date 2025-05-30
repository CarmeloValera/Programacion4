#include <stdio.h>
#include <string.h>
#include "bbddmain.h"

// Abrir la base de datos
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

// Cerrar la base de datos
void cerrar_base(BBDD *base) {
    sqlite3_close(base->db);
    printf("Base de datos cerrada.\n");
}

// Registrar un nuevo usuario
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

// Iniciar sesión
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
    int resultado = (rc == SQLITE_ROW);  // Si hay un resultado, el inicio de sesión es correcto

    if (resultado) {
        printf("Inicio de sesión exitoso.\n");
    } else {
        printf("Usuario o contraseña incorrectos.\n");
    }

    sqlite3_finalize(stmt);
    return resultado;
}

// Cambiar el nombre de usuario
int cambiar_nombre_usuario(BBDD *base, const char *usuario_actual, const char *nuevo_nombre) {
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE usuarios SET usuario = ? WHERE usuario = ?;";
    int rc = sqlite3_prepare_v2(base->db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta: %s\n", sqlite3_errmsg(base->db));
        return rc;
    }

    sqlite3_bind_text(stmt, 1, nuevo_nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, usuario_actual, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Error al cambiar el nombre de usuario: %s\n", sqlite3_errmsg(base->db));
    } else {
        printf("Nombre de usuario cambiado con éxito.\n");
    }

    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE ? SQLITE_OK : rc;
}

// Cambiar la contraseña del usuario
int cambiar_contrasena(BBDD *base, const char *usuario, const char *nueva_contrasena) {
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE usuarios SET contrasena = ? WHERE usuario = ?;";
    int rc = sqlite3_prepare_v2(base->db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        printf("Error al preparar la consulta: %s\n", sqlite3_errmsg(base->db));
        return rc;
    }

    sqlite3_bind_text(stmt, 1, nueva_contrasena, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, usuario, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Error al cambiar la contraseña: %s\n", sqlite3_errmsg(base->db));
    } else {
        printf("Contraseña cambiada con éxito.\n");
    }

    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE ? SQLITE_OK : rc;
}

int existe_usuario(BBDD *bd, const char *nombre_usuario) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM usuarios WHERE usuario = ?;";
    int existe = 0;

    if (sqlite3_prepare_v2(bd->db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar consulta: %s\n", sqlite3_errmsg(bd->db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, nombre_usuario, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        existe = (count > 0);
    }

    sqlite3_finalize(stmt);

    return existe;
}