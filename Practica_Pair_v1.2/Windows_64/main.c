#include <stdio.h>
#include <stdlib.h>
#include "ArrayList.h"
#include "Employee.h"

/****************************************************
    Menu:
        1. Parse del archivo data.csv
        2. Listar Empleados
        3. Ordenar por nombre
        4. Agregar un elemento
        5. Elimina un elemento
        6. Listar Empleados (Desde/Hasta)
*****************************************************/


int main()
{
   ArrayList* lista = al_newArrayList();
   Employee* aux;
   Employee* borrar;
   int* ids=(int*) malloc(sizeof(int)*3);
   int id=0;
   int i;

   Employee* e1= employee_new();
   Employee* e2= employee_new();

   e1->id= 2;
   strcpy(e1->name, "Aldana");
   strcpy(e1->lastName, "Salvatierra");
   e1->isEmpty=1;

   e2->id= 5;
   strcpy(e2->name, "Carolina");
   strcpy(e2->lastName, "Ojeda");
   e2->isEmpty=1;

   al_add(lista, e1);
   al_add(lista,e2);

   printf("La cantidad de elementos son: %d\n\n", al_len(lista));

   for(i=0;i<al_len(lista);i++)
   {
       aux=al_get(lista, i);
       employee_print(aux);
   }

   printf("\nSe obtiene el id por employee_Id(): \n\n");

   for(i=0; i<lista->len(lista);i++)
   {
       aux=lista->get(lista,i);
       *(ids+i)=employee_getId(aux);
       printf("El ID del empleado es: %d\n\n",*(ids+i));
   }

   /*printf("Setea los ID de los empleados por employee_setId(): \n\n");

   for(i=0;i<lista->len(lista);i++)
   {
       aux=lista->get(lista,i);
       if(employee_setId(aux,id))
       {
           employee_print(aux);
       }
       else
       {
           printf("No se pudo realizar la operacion");
       }
   }

   printf("\nElimina un empleado con employee_delete(): \n\n");
   employee_delete(lista,e1,1);
   for(i=0;i<lista->len(lista);i++)
   {
       aux=lista->get(lista,i);

       employee_print(aux);
   }*/

    return 0;
}
