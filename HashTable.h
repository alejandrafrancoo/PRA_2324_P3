#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "/home/alumno.upv.es.afravic/W/PRA/REPOSITORIOS_LOCALES/PRA_2324_P1/ListLinked.h"   // AJUSTA ESTA RUTA SEGÚN TU PROYECTO

template <typename V>
class HashTable : public Dict<V> {

private:
    int n;     // número de elementos almacenados
    int max;   // número total de cubetas
    ListLinked<TableEntry<V>>* table;  // array dinámico de listas enlazadas

    // Función hash (suma ASCII % max)
    int h(std::string key) {
        int suma = 0;
        for (int i = 0; i < key.size(); i++)
            suma += int(key.at(i));
        return suma % max;
    }

public:

    // Constructor
    HashTable(int size) {
        this->max = size;
        this->n = 0;

        table = new ListLinked<TableEntry<V>>[size];
    }

    // Destructor
    ~HashTable() {
        delete[] table;
    }

    // Capacidad total
    int capacity() {
        return max;
    }

    // Insertar (Dict<V>::insert)
    void insert(std::string key, V value) override {
        int pos = h(key);
        TableEntry<V> entry(key, value);

        // Si ya existe, se actualiza el valor
        if (table[pos].search(entry) != -1) {
            table[pos].update(entry);   // tu ListLinked debe tener update(), si no, borra + inserta
        } else {
            table[pos].append(entry);
            n++;
        }
    }

    // Buscar (Dict<V>::search)
    V search(std::string key) override {
        int pos = h(key);
        TableEntry<V> entry(key);

        int index = table[pos].search(entry);
        if (index == -1)
            throw std::runtime_error("Clave no encontrada");

        return table[pos].get(index).value;
    }

    // Eliminar (Dict<V>::remove)
    void remove(std::string key) override {
        int pos = h(key);
        TableEntry<V> entry(key);

        int index = table[pos].search(entry);
        if (index == -1)
            return;

        table[pos].remove(index);
        n--;
    }

    // Sobrecarga del operador []
    V operator[](std::string key) {
        return search(key);
    }

    // Imprimir tabla hash
    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &ht) {
        for (int i = 0; i < ht.max; i++) {
            out << i << ": ";
            out << ht.table[i] << "\n";
        }
        return out;
    }
};

#endif

