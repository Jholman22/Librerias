
#include "ring_buffer.h"
#include <string.h>
#define capacity (11)
uint8_t ring_buffer[capacity];
uint8_t head_ptr;
uint8_t tail_ptr;
uint8_t is_full;


/**
 * @brief Esta funcion escribe un dato en el buffer circular
 *
 *  @param data: El dato que se va a escribir
 *
 *  @retval Ninguno
 * */

void ring_buffer_write(uint8_t data){

	ring_buffer[head_ptr] = data;
	head_ptr = head_ptr + 1;
	if (head_ptr >= capacity) { // si la cabeza llega al final de la memoria
		  head_ptr = 0;
	}
	if (is_full != 0) { // si se pierden datos viejos
		  tail_ptr = tail_ptr + 1;
	}
	if (tail_ptr >= capacity) { // si la cola llega al final de la memoria
		  tail_ptr = 0;
	}
	if (head_ptr == tail_ptr) { // si la cabeza alcanza la cola
		  is_full = 1;
	}
}

/**
 * @brief Esta funcion lee un dato en el buffer circular
 *
 *  @param data: La direccion donde se va a escribir el dato
 *
 *  @retval 1: Hay datos disponibles; 0, no hay datos
 * */
uint8_t ring_buffer_read(uint8_t *byte){
		  if ((is_full != 0) || (head_ptr != tail_ptr)) {

		  		  *byte = ring_buffer[tail_ptr];
		  		  tail_ptr = tail_ptr + 1; //add: 0x20, val: buffer
		  		  if (tail_ptr >= capacity) {
		  			  tail_ptr = 0;
		  		  }
		  		  is_full = 0;
		  		  return 1; //buffer con datos
		  	  }
		  	 return 0; //buffer vacio
}


/**
 * @brief Esta funcion calcula los datos disponibles en el bufer
 *
 *  @param data: La direccion donde se va a escribir el dato
 *
 *  @retval size: cantidad de datos disponibles
 * */

uint8_t ring_buffer_size(void) {
    uint8_t size = 0;

    // Caso 1: Si el puntero de la cabeza (head_ptr) es mayor o igual al puntero de la cola (tail_ptr),
    // significa que el buffer no ha dado la vuelta. La diferencia directa entre head_ptr y tail_ptr
    // nos da el tamaño del buffer ocupado.
    if (head_ptr >= tail_ptr) {
        size = head_ptr - tail_ptr;
    }
    // Caso 2: Si el puntero de la cola (tail_ptr) es mayor que el puntero de la cabeza (head_ptr),
    // significa que el buffer ha dado la vuelta. Para calcular el tamaño, restamos la diferencia
    // entre tail_ptr y head_ptr de la capacidad total del buffer.
    else {
        size = capacity - (tail_ptr - head_ptr);
    }

    // Devolvemos el tamaño calculado
    return size;


}

void ring_buffer_reset(void) {
    // Reinicia los punteros de la cabeza y la cola al inicio del buffer
    head_ptr = 0;
    tail_ptr = 0;
}

uint8_t ring_buffer_is_full(void) {
    // El buffer está lleno si el próximo valor de head_ptr alcanzará a tail_ptr
    return ((head_ptr + 1) % capacity) == tail_ptr ? 1 : 0;
    //Retorna 1 si el buffer está lleno
    //Retorna 0 si el buffer no está lleno
}

uint8_t ring_buffer_is_empty(void) {
    // El buffer está vacío si head_ptr y tail_ptr son iguales
    return (head_ptr == tail_ptr) ? 1 : 0;
}

uint8_t ring_buffer_compare(uint32_t* cc) {
    uint8_t tamaño = 11;  // Longitud del numero
    uint8_t i = 0;
    uint8_t temp_tail = tail_ptr;  // Copia temporal de tail_ptr para la comparación

    // Comparar los datos del buffer con la palabra
    while (i < tamaño) {
        // Leer el dato del buffer
        char buffer_data = ring_buffer[temp_tail];

        // Comparar el dato con el carácter correspondiente de la palabra
        if (buffer_data != cc[i]) {
            return 0;  // Los datos no coinciden
        }

        // Avanzar en el buffer circular
        temp_tail = (temp_tail + 1) % capacity;
        i++;
    }

    return 1;  // Los datos coinciden con la palabra
}
