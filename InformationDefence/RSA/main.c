
#define DEBUG

#include <stdio.h>
#include <stdint.h>
#include <gmp.h>
#include <unistd.h>
#include <string.h>

#define ENC_BLOCK_TYPE uint16_t
#define DEC_BLOCK_TYPE uint32_t

#ifdef DEBUG
    #define OPEN_EXP "79"
#else
    #define OPEN_EXP "65537"
#endif


typedef struct{
    mpz_t e;
    mpz_t n;
} PublicKey;

typedef struct {
    mpz_t d;
    mpz_t n;
} SecretKey;

void eiler_func(mpz_t p, mpz_t q, mpz_t result){
    mpz_t tmp; mpz_init(tmp);

    mpz_sub_ui(result, p, 1); // p - 1
    mpz_sub_ui(tmp,    q, 1); // q - 1

    mpz_mul(result, result, tmp); //(p - 1) * (q - 1)

    mpz_clear(tmp);

}

void comp_module(mpz_t p, mpz_t q, mpz_t n){
    mpz_mul(n, p, q); // n = pq
}

void key_generation(mpz_t p, mpz_t q,
                    SecretKey *sk,
                    PublicKey *pk)
{
    mpz_t n; mpz_init(n);
    comp_module(p, q, n);

    //Функция Эйлера от модуля
    mpz_t eiler; mpz_init(eiler);
    eiler_func(p, q, eiler);

    //Открытая экспонента
    mpz_t e; mpz_init_set_str(e, OPEN_EXP, 10);

    mpz_t temp; mpz_init(temp);

    mpz_t d; mpz_init_set_ui(d, 3);
//  for(; d<n; d+=2)
    for(; mpz_cmp(n, d) > 0; mpz_add_ui(d, d, 2)){

//      if(d * e % euler == 1)
        mpz_mul(temp, d, e); // d * e

        mpz_mod(temp, temp, eiler); // %eiler

        if(!mpz_cmp_ui(temp, 1)){
            break;
        }
    }
    mpz_init_set(pk->e, e);
    mpz_init_set(pk->n, n);

    mpz_init_set(sk->d, d);
    mpz_init_set(sk->n, n);

    mpz_clear(e);
    mpz_clear(n);
    mpz_clear(d);
    mpz_clear(temp);
}

void encryptme(ENC_BLOCK_TYPE block, PublicKey *pk, mpz_t result){
    mpz_t m; mpz_init_set_ui(m , (uint32_t)block);
    mpz_powm(result, m, pk->e, pk->n);
    mpz_clear(m);
}

void decryptme(mpz_t encr, SecretKey *sk, ENC_BLOCK_TYPE *res){
    mpz_t decrypted; mpz_init(decrypted);
    mpz_powm(decrypted, encr, sk->d, sk->n);
    *res = mpz_get_ui(decrypted);
}


int main(int argc, char *argv[])
{
#ifdef DEBUG
#define BLOCK_TYPE ENC_BLOCK_TYPE
    mpz_t p; mpz_init_set_str(p, "47", 10);
    mpz_t q; mpz_init_set_str(q, "71", 10);

    SecretKey sk;
    PublicKey pk;

    key_generation(p, q, &sk, &pk);

    gmp_printf("Public key: (%Zd, %Zd)\n", pk.e, pk.n);
    gmp_printf("Secret key: (%Zd, %Zd)\n", sk.d, sk.n);

    mpz_t test;
    mpz_init_set_str(test, "111", 10);


    ENC_BLOCK_TYPE test2;
    test2 = (ENC_BLOCK_TYPE)(mpz_get_ui(test));

    printf("\nTested: %u\n", test2);

    encryptme(test2, &pk, test);

    gmp_printf("Encrypted: %Zd\n", test);

    //test2 = mpz_get_ui(test);

    decryptme(test, &sk, &test2);
    printf("Decrypted: %u\n", test2);

    BLOCK_TYPE buff;

    size_t len_read = read(STDIN_FILENO, &buff, sizeof(BLOCK_TYPE));
    mpz_t temp; mpz_init(temp);

    while(len_read == sizeof(BLOCK_TYPE)){

        printf("\n");
        write(1, &buff, len_read);
        char *print = "   ";
        write(1, print, 3);
        encryptme(buff, &pk, temp);
        gmp_printf("  %Zd", temp);
        decryptme(temp, &sk, &buff);
        write(1, &buff, len_read);
        len_read = read(STDIN_FILENO, &buff, sizeof(BLOCK_TYPE));

    }

    printf("\n");
    mpz_clear(temp);
    mpz_clear(p);
    mpz_clear(q);
    return 0;

#else
    if(argc != 2){
        char *error = "Программа принимает только 1 аргумент";
        printf(error);
        return -1;
    }

    mpz_t p; mpz_init_set_str(p, "3557", 10);
    mpz_t q; mpz_init_set_str(q, "2579", 10);

    SecretKey sk;
    PublicKey pk;

    key_generation(p, q, &sk, &pk);

    ENC_BLOCK_TYPE e_buff;
    DEC_BLOCK_TYPE d_buff;

    mpz_t temp; mpz_init(temp);

    if(strcmp(argv[1], "-e") == 0){
        size_t len_read = read(STDIN_FILENO, &e_buff, sizeof(ENC_BLOCK_TYPE));
        while(len_read == sizeof(ENC_BLOCK_TYPE)){
            encryptme(e_buff, &pk, temp);
            d_buff = mpz_get_ui(temp);
            write(1, &d_buff, sizeof(DEC_BLOCK_TYPE));
            len_read = read(STDIN_FILENO, &e_buff, sizeof(ENC_BLOCK_TYPE));
        }
        goto sucsess;
    }
    if(strcmp(argv[1], "-d") == 0){
        size_t len_read = read(STDIN_FILENO, &e_buff, sizeof(DEC_BLOCK_TYPE));
        while(len_read == sizeof(DEC_BLOCK_TYPE)){
            mpz_set_ui(temp, d_buff);
            decryptme(temp, &sk, &e_buff);
            write(1, &e_buff, sizeof(ENC_BLOCK_TYPE));
            len_read = read(STDIN_FILENO, &d_buff, sizeof(DEC_BLOCK_TYPE));
        }
        goto sucsess;
    }
    mpz_clear(temp);
    mpz_clear(p);
    mpz_clear(q);
    return -1;

    sucsess:
    mpz_clear(temp);
    mpz_clear(p);
    mpz_clear(q);
    return 0;

#endif
}
