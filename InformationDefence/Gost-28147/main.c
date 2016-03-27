#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>

#define SHIFT 11
#define INPUT_BUFFER_SIZE 8

#define A 10
#define B 11
#define C 12
#define D 13
#define E 14
#define F 15

const size_t N = 8;

typedef union {
    uint64_t all;
    uint32_t parts[2];
} Data;

typedef union{
    uint32_t all;
    uint8_t blocks[4];
} Blocks8;

uint32_t key[8] = {0, 0, 0, 0, 0, 0, 0, 0};

const uint8_t SBox[8][16] = {{4, A, 9, 2, D, 8, 0, E, 6, B, 1, C, 7, F, 5, 3},
                         {E, B, 4, C, 6, D, F, A, 2, 3, 8, 1, 0, 7, 5, 9},
                         {5, 8, 1, D, A, 3, 4, 2, E, F, C, 7, 6, 0, 9, B},
                         {7, D, A, 1, 0, 8, 9, F, E, 4, 6, C, B, 2, 5, 3},
                         {6, C, 7, 1, 5, F, D, 8, 4, A, 9, E, 0, 3, B, 2},
                         {4, B, A, 0, 7, 2, 1, D, 3, 6, 8, 5, 9, C, F, E},
                         {D, B, 4, 1, 3, F, 5, 9, 0, A, E, 7, 6, 8, 2, C},
                         {1, F, D, 0, 5, 7, A, 4, 9, 2, 3, E, 6, B, 8, C}
                        };

uint64_t step(uint32_t left, uint32_t right, uint32_t key){

    // Сложение субблока с частью ключа по модулю 2^32.
    left = left + key;

    // Табличная замена.
    Blocks8 block;
    block.all = left;

    for(int i = 0; i < 4; ++i){

        // "четырехбитные" блоки
        uint8_t block1 = block.blocks[i] >> 4; // 12345678 -> 00001234
        uint8_t block2 = block.blocks[i] % 16; // 12345678 -> 00005678
        uint8_t s_elem1 = SBox[2 * i][block1];
        uint8_t s_elem2 = SBox[(2 * i) + 1][block2];

        // в старшие разряды первый блок, в младшие -- второй
        block.blocks[i] = (s_elem1 << 4) | s_elem2;
    }

    left = block.all;

    //Циклический сдвиг на 11 бит влево.
    left = (left << SHIFT) | (left >> (32 - SHIFT));

    //Сложение по модулю 2 обработанного левого субблока и правого субблока.
    left = left ^ right;

    return left;
}

uint64_t decrypt(uint64_t block){

    Data d;
    d.all = block;

    uint32_t left = d.parts[1];
    uint32_t right = d.parts[0];

    for(uint8_t i = 0; i < 8; ++i){
        uint32_t tmp = step(left, right, key[i]);
        right = left;
        left = tmp;
    }

    for(uint8_t i = 23; i > 0; --i){
        uint8_t key_index = i % 8;
        uint32_t tmp = step(left, right, key[key_index]);
        right = left;
        left = tmp;
    }

    // Последний шаг
    uint32_t tmp = step(left, right, key[0]);
    right = tmp;

    d.parts[1] = left;
    d.parts[0] = right;

    return d.all;
}

uint64_t encrypt(uint64_t block){

    Data d;
    d.all = block;

    uint32_t left = d.parts[1];
    uint32_t right = d.parts[0];

    for(uint8_t i = 0; i < 24; ++i){
        uint8_t key_index = i % 8;
        uint32_t tmp = step(left, right, key[key_index]);
        right = left;
        left = tmp;
    }

    for(uint8_t i = 7; i > 0; --i){
        uint32_t tmp = step(left, right, key[i]);
        right = left;
        left = tmp;
    }

    // Последний шаг
    uint32_t tmp = step(left, right, key[0]);
    right = tmp;

    //Получаем 64-битный блок из 32-битных субблоков.
    d.parts[1] = left;
    d.parts[0] = right;
    return d.all;
}

typedef union {
    uint64_t all;
    uint8_t str[INPUT_BUFFER_SIZE + 1];
} Printable;

typedef uint64_t (*action)(uint64_t);
void stream(action func){
    Printable data;
    size_t len_read = read(STDIN_FILENO, &data.str, INPUT_BUFFER_SIZE);
    while(len_read == INPUT_BUFFER_SIZE){
        data.all = func(data.all);
        data.str[N] = '\0';

        printf("%s", data.str);
        len_read = read(STDIN_FILENO, &data.str, INPUT_BUFFER_SIZE);
    }
    data.str[len_read] = '\0';
    printf("%s", data.str);
}

void print_help(char* error){
    if(error != NULL){
        printf("Ошибка! %s\n", error);
    }
    printf("Использование: encrypt -e|-d\n");
    printf("Утилита для поточного шифрования по алгоритму GOST 28-147-89.\n");
    printf("Берет поток 64-битных блоков из stdin,\nвозвращает результат на stdoit.\n\nАргументы:\n");
    printf(" -e       шифрует поток.\n");
    printf(" -d       дешифрует поток.\n");
    printf("--help    выводит эту справку и завершается.\n");
}

int main(int argc, char *argv[]) {

    if(argc != 2){
        char *error = "Программа принимает только 1 аргумент";
        print_help(error);
        return -1;
    }

    char *string_key = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    uint32_t *key_ptr = key;
    for(uint8_t i = 0; i < 8; ++i){
        *key_ptr = (uint32_t)(*string_key);
        string_key += sizeof(*key)/ sizeof(*string_key);
        ++key_ptr;
    }

    if(strcmp(argv[1], "-e") == 0){
        stream(encrypt);
        return 0;
    }
    if(strcmp(argv[1], "-d") == 0){
        stream(decrypt);
        return 0;
    }

    if(strcmp(argv[1], "--help") == 0){
        print_help(NULL);
        return 0;
    }

    return -1;
}
