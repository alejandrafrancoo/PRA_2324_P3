#ifndef DICT_H
#define DICT_H

#include <string>
#include <stdexcept>

template <typename V>
class Dict {
public:
    // Inserta un par key->value. Lanza excepción si la clave ya existe.
    virtual void insert(std::string key, V value) = 0;

    // Busca el valor asociado a key. Lanza excepción si no se encuentra.
    virtual V search(std::string key) = 0;

    // Elimina el par asociado a key. Devuelve el valor eliminado.
    // Lanza excepción si no se encuentra.
    virtual V remove(std::string key) = 0;

    // Devuelve el número de pares almacenados.
    virtual int entries() = 0;

    // Destructor virtual por seguridad en clases base abstractas.
    virtual ~Dict() {}
};

#endif

