#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
int id;
char marca[20];
int tipo;
float peso;
}eVehiculo;

eVehiculo* new_vehiculo();
eVehiculo* newVehiculoParam(int id, char marca[], int tipo, float peso);

//setters
int SetId(eVehiculo* p, int id);
int SetMarca(eVehiculo* p, char nombre[]);
int SetTipo(eVehiculo* p, int tipo);
float SetPeso(eVehiculo* p, int peso);

int main()
{
    //char buffer[5][20];
    int cant;
    //int indice;
    int tam = 1;
    int flag = 0;
    int flagB = 0;
    //eVehiculo* aux = NULL;
    eVehiculo** lista = (eVehiculo**) malloc(sizeof(eVehiculo*)* tam);

    newVehiculoParam(1, "fiat", 5, 2000);

    //archivo de texto
    FILE* f = fopen("vehiculos.csv", "w");
    if(f == NULL)
    {
        printf("no se pudo abrir el archivo");
        exit(1);
    }

    fprintf(f, "id,nombre,tipo,peso\n");

    for(int i = 0; i < tam; i++)
    {
        if(*(lista + i) != NULL)
        {
          cant = fprintf(f, "%d,%s,%d,%.2f\n",  (*(lista + i))->id,
                                            (*(lista + i))->marca,
                                            (*(lista + i))->tipo,
                                            (*(lista + i))->peso);
            if(cant < 5)
            {
                flag =1;
                break;
            }
        }
    }

    if(flag)
    {
        printf("hubo un problema al guardar\n");
    }
    else
    {
        printf("personas guardadas con exito\n");
    }

    fclose(f);

    //archivo binario
    f = fopen("lista.bin", "wb");
    if(f == NULL)
    {
        printf("no se pudo abrir el archivo");
        exit(1);
    }

    for(int i = 0; i < tam; i++)
    {
        if(*(lista + i) != NULL)
        {
            cant = fwrite(*(lista + i), sizeof(eVehiculo), 1, f);
            if(cant < 1)
            {
                flagB =1;
                break;
            }
        }
    }

    if(flagB)
    {
        printf("hubo un problema al guardar las personas\n");
    }
    else
    {
        printf("personas guardadas con exito\n");
    }

    fclose(f);
    return 0;
}


eVehiculo* new_vehiculo()
{
    eVehiculo* p = (eVehiculo*) malloc(sizeof(eVehiculo));
    if(p != NULL)
    {
        p->id = 0;
        *(p->marca) = '\0';
        p->tipo = 0;
        p->peso = 0.00;
    }
    return p;
}


eVehiculo* newVehiculoParam(int id, char marca[], int tipo, float peso)
{
    eVehiculo* p = new_vehiculo();
    if(p != NULL)
    {
        if(!(SetId(p, id) &&
        SetMarca(p, marca) &&
        SetTipo(p, tipo) &&
        SetPeso(p, peso)))
        {
            free(p);
            p = NULL;
        }
    }

    return p;
}

int SetId(eVehiculo* p, int id)
{
    int todoOk = 0;

    if(p != NULL && id >= 0 && id <= 30000)
    {
        p->id = id;
        todoOk = 1;
    }

    return todoOk;
}

int SetMarca(eVehiculo* p, char marca[])
{
    int todoOk = 0;

    if(p != NULL && marca != NULL && strlen(marca) <= 20)
    {
        strcpy(p->marca, marca);
        todoOk = 1;
    }

    return todoOk;
}

int SetTipo(eVehiculo* p, int tipo)
{
    int todoOk = 0;

    if(p != NULL && tipo >= 0 && tipo <= 30000)
    {
        p->tipo = tipo;
        todoOk = 1;
    }

    return todoOk;
}

float SetPeso(eVehiculo* p, int peso)
{
    int todoOk = 0;

    if(p != NULL && peso >= 0 && peso <= 10000)
    {
        p->peso = peso;
        todoOk = 1;
    }

    return todoOk;
}
