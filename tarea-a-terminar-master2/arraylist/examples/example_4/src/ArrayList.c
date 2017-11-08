#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/ArrayList.h"

// funciones privadas
int resizeUp(ArrayList* this);
int expand(ArrayList* this,int index);
int contract(ArrayList* this,int index);

#define AL_INCREMENT      10
#define AL_INITIAL_VALUE  10
//___________________

/** \brief Allocate a new arrayList with AL_INITIAL_VALUE elements.
 * \param void
 * \return ArrayList* Return (NULL) if Error [if can't allocate memory]
 *                  - (pointer to new arrayList) if ok
 */
ArrayList* al_newArrayList(void)
{
    ArrayList* this;
    ArrayList* returnAux = NULL;
    void* pElements;


        this = (ArrayList *)malloc(sizeof(ArrayList));

        if(this != NULL)
        {
            pElements = malloc(sizeof(void *)*AL_INITIAL_VALUE );

            if(pElements != NULL)
            {
                this->size=0;
                this->pElements=pElements;
                this->reservedSize=AL_INITIAL_VALUE;
                this->add=al_add;
                this->len=al_len;
                this->set=al_set;
                this->remove=al_remove;
                this->clear=al_clear;
                this->clone=al_clone;
                this->get=al_get;
                this->contains=al_contains;
                this->push=al_push;
                this->indexOf=al_indexOf;
                this->isEmpty=al_isEmpty;
                this->pop=al_pop;
                this->subList=al_subList;
                this->containsAll=al_containsAll;
                this->deleteArrayList = al_deleteArrayList;
                this->sort = al_sort;
                returnAux = this;
            }
            else
            {
                free(this);
            }
        }

    return returnAux;
}


/** \brief  Add an element to arrayList and if is
 *          nessesary resize the array
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (0) if Ok
 *
 */
int al_add(ArrayList* this, void* pElement)
{
    int returnAux = -1;
    int auxiliar = 1;
    int bandera = 1;
    int posicion;

        if(this != NULL && pElement != NULL)
        {
            if(this->reservedSize == this->size)
            {
                auxiliar = resizeUp(this);

                if(auxiliar != 0)
                {
                    bandera = 0;
                }
            }
            if(bandera == 1)
            {
                posicion = this->size;
                this->pElements[posicion] = pElement;
                this->size++;
                returnAux = 0;
            }
        }
    return returnAux;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Ok
 *
 */
int al_deleteArrayList(ArrayList* this)
{
    int returnAux = -1;

        if(this != NULL)
        {
            free(this);
            returnAux = 0;
        }

    return returnAux;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return length of array or (-1) if Error [pList is NULL pointer]
 *
 */
int al_len(ArrayList* this)
{
    int returnAux;

        if(this != NULL)
        {
            returnAux = this->size;
        }
        else
        {
            returnAux = -1;
        }


    return returnAux;
}


/** \brief  Get an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return void* Return (NULL) if Error [pList is NULL pointer or invalid index] - (Pointer to element) if Ok
 *
 */
void* al_get(ArrayList* this, int index)
{
    void* returnAux = NULL;

        if(this != NULL)
        {
            if(this->size > index && index >= 0) ///devolveria el puntero de ArrayList
            {
                returnAux = this->pElements[index];
            }
        }

    return returnAux;
}


/** \brief  Find if pList contains at least one element pElement
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer]
 *                  - ( 0) if Ok but not found a element
 *                  - ( 1) if this list contains at least one element pElement
 *
 */
int al_contains(ArrayList* this, void* pElement)///se usa como comparacion (pElement)
{
    int returnAux = -1;
    int i;
    int bandera = 0;

    if(this != NULL && pElement != NULL)
    {
        for(i=0; i<this->al_len(this)   ;i++)/// this->size
        {
            if(pElement == this->pElements[i])
            {
                returnAux = 1;
                bandera = 1;
                break;
            }
        }
        if(bandera != 1)
        {
            returnAux = 0;
        }
    }


    return returnAux;
}


/** \brief  Set a element in pList at index position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 *
 */
int al_set(ArrayList* this, int index,void* pElement)/// agrega un elemento en la lista en una posicion especifica, lo pisa
{
    int returnAux = -1;

        if(this != NULL && pElement != NULL)
        {
            if(index >= 0 && index < this->size)
            {
                this->pElements[index] = pElement;
                returnAux = 0;
            }
            if(this->size == index)
            {
                al_add(this,pElement);
            }
        }

    return returnAux;
}


/** \brief  Remove an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_remove(ArrayList* this,int index) ///elimina a un solo elemento en una posicion especifica
{
    int returnAux = -1;

        if(this != NULL)
        {
            if(index >= 0 && index < this->size)
            {
                free(this->pElements[index]);
                this->size--;
                returnAux = 0;
            }
        }

    return returnAux;
}



/** \brief Removes all of the elements from this list
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer]
 *                  - ( 0) if Ok
 */
int al_clear(ArrayList* this)
{
    int returnAux = -1;
    int i;

        if(this != NULL)
        {
            for(i=0; i<=this->len(this) ;i++)
            {
                free(*(this->pElements+i));
            }
            this->size = 0;
            returnAux = 0;

        }

    return returnAux;
}



/** \brief Returns an array containing all of the elements in this list in proper sequence
 * \param pList ArrayList* Pointer to arrayList
 * \return ArrayList* Return  (NULL) if Error [pList is NULL pointer]
 *                          - (New array) if Ok
 */
ArrayList* al_clone(ArrayList* this) ///clona todo el arraylist
{
    ArrayList* returnAux = NULL;
    int i;

        if(this != NULL)
        {
            returnAux = al_newArrayList();

            if(returnAux != NULL)
            {
                for(i=0;i<this->size;i++)
                {
                    al_add(returnAux,al_get(this,i));
                }
            }
        }

    return returnAux;
}




/** \brief Inserts the element at the specified position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_push(ArrayList* this, int index, void* pElement) ///inserta un elemento en X posicion, si esta ocupada mueve los elementos para dar espacio e insertar el elemento
{
    int returnAux = -1;

        if(this != NULL && pElement != NULL)
        {
            if(index >= 0 && index < this->size)
            {
                expand(this,index);
                al_set(this,index,pElement);
                this->size++;
                returnAux = 0;
            }
            if(index == this->size)
            {
                al_add(this,pElement);
                returnAux = 0;
            }
        }

    return returnAux;
}



/** \brief Returns the index of the first occurrence of the specified element
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (index to element) if Ok
 */
int al_indexOf(ArrayList* this, void* pElement) ///compara los elementos
{
    int returnAux = -1;
    int i;

        if(this != NULL && pElement != NULL)
        {
            for(i=0;i<this->size;i++)
            {
                if(*(this->pElements+i) == pElement) ///si el elemento coincide con el elemento guardado en el
                                                    ///arraylist devolvera la posicion en la que esta guardada en el AL
                {
                    returnAux = i;
                    break;
                }
            }
        }

    return returnAux;
}



/** \brief Returns true if this list contains no elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Not Empty - (1) if is Empty
 */
int al_isEmpty(ArrayList* this) ///se encarga de verificar que no halla elementos cargados
{
    int returnAux = -1;

        if(this != NULL)
        {
            if(this->size == 0)
            {
                returnAux = 1;
            }
            else
            {
                returnAux = 0;
            }
        }

    return returnAux;
}




/** \brief Remove the item at the given position in the list, and return it.
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid index]
 *                  - ( element pointer) if Ok
 */
void* al_pop(ArrayList* this,int index) ///devuelve un elemento que se pide para trabajar con el o para modificarlo, no para mostrarlo
{
    void* returnAux = NULL;///el puntero a void guarda y devuelve una direccion de memoria sin ningun tipo

        if(this != NULL)
        {
            if(index >= 0 && index < this->size)
            {
                returnAux = *(this->pElements+index);
                contract(this,index); ///usa el contract para que mueva los elementos uno por uno hacia la izquierda
            }
        }

    return returnAux;
}


/** \brief Returns a new arrayList with a portion of pList between the specified
 *         fromIndex, inclusive, and toIndex, exclusive.
 * \param pList ArrayList* Pointer to arrayList
 * \param from int Initial index of the element (inclusive)
 * \param to int Final index of the element (exclusive)
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid 'from' or invalid 'to']
 *                  - ( pointer to new array) if Ok
 */
ArrayList* al_subList(ArrayList* this,int from,int to) ///hace lo mismo que el clon pero te devuelve una pequeña lista con la cantidad de elementos que vos pidas
{
    ArrayList* returnAux = NULL;
     int i;

     if(this != NULL)
     {
         if((from >= 0 && from <= to)&&(to <= this->size && to >= from)) ///empìeza siempre desde 0 hasta la posicion deseada-
         {                                                              ///desde el final hasta la cant.elem.(que no se pase de la cant. de elementos que tenemos)
             returnAux = al_newArrayList();                             /// y el final sea mayor o igual hasta el final

             if(returnAux != NULL)
             {
                 for(i=from; i<=to ;i++)
                 {
                     al_add(returnAux,al_get(this,i));
                 }
             }
         }
     }

    return returnAux ;
}





/** \brief Returns true if pList list contains all of the elements of pList2
 * \param pList ArrayList* Pointer to arrayList
 * \param pList2 ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList or pList2 are NULL pointer]
 *                  - (0) if Not contains All - (1) if is contains All
 */
int al_containsAll(ArrayList* this,ArrayList* this2) ///compara las dos listas para saber si contienen la misma cantidad de elementos
{
    int returnAux = -1;
    int bandera = 0;
    int cont = 0;
    int i,j;

    if(this != NULL && this2 != NULL)
    {
        for(i=0;i<this2->size;i++)
        {
            for(j=0;j<this->size;j++)
            {
                if(*(this2->pElements+i) == *(this->pElements+j))
                {
                    bandera = 1;
                    cont++;
                    break;
                }
            }
        }
        if(bandera == 1 && cont == this2->size)
        {
            returnAux = 1;
        }
        else
        {
          returnAux = 0;
        }

    }

    return returnAux;
}

/** \brief Sorts objects of list, use compare pFunc -
 * \param pList ArrayList* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param order int  [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [pList or pFunc are NULL pointer]
 *                  - (0) if ok
 */
int al_sort(ArrayList* this, int (*pFunc)(void* ,void*), int order)/// hace un ordenamiento simple a partir de otra funcion
{
    int returnAux = -1;
    void* auxiliar = NULL;
    int i,j;

        if(this != NULL && pFunc != NULL)
        {
            if(order == 1)
            {
                for(i=0;i<this->size-1;i++)
                {
                    for(j=i+1;j<this->size;j++)
                    {
                        if(pFunc(*(this->pElements+i),*(this->pElements+j))>0)
                        {
                            auxiliar = *(this->pElements+i);
                            *(this->pElements+i) = *(this->pElements+j);
                            *(this->pElements+j) = auxiliar;
                        }
                    }
                }
            }
            if(order == 0)
            {
                for(i=0;i<this->size-1;i++)
                {
                    for(j=i+1;j<this->size;j++)
                    {
                        if(pFunc(*(this->pElements+i),*(this->pElements+j))<0)
                        {
                            auxiliar = *(this->pElements+i);
                            *(this->pElements+i) = *(this->pElements+j);
                            *(this->pElements+j) = auxiliar;
                        }
                    }
                }
            }
        }

    return returnAux;
}


/** \brief Increment the number of elements in pList in AL_INCREMENT elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer or if can't allocate memory]
 *                  - (0) if ok
 */
int resizeUp(ArrayList* this)
{
    int returnAux = -1;
    void* auxiliar;

        if(this != NULL)
        {
            auxiliar = realloc(this->pElements,(sizeof(void*)*(this->reservedSize+AL_INCREMENT)));

                if(auxiliar != NULL)
                {
                    this->pElements = auxiliar;
                    this->reservedSize += AL_INCREMENT;
                    returnAux = 0;
                }
        }

    return returnAux;
}

/** \brief  Expand an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int expand(ArrayList* this,int index) ///el this es el ArrayList
{
    int returnAux = -1;
    int bandera = 0;
    int i;

        if(this != NULL)
        {
           if(index >= 0 && index <= this->size)
           {
                if(this->size == this->reservedSize)
                {
                    if(resizeUp(this) == -1)
                    {
                        bandera = 1;
                    }
                }
                if(bandera == 0)
                {
                    for(i=this->size ; i>=index ; i--) ///empieza en el ultimo lugar y recorre desde adelante para atras para que no pise los datos y los elimine
                    {
                    }
                    returnAux = 0;
                        *(this->pElements+i-1) = *(this->pElements+i); /// this->pElements[i-1]= this->pElements[i
                }
           }
        }

    return returnAux;
}

/** \brief  Contract an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int contract(ArrayList* this,int index)
{
    int returnAux = -1;
    int i;

        if(this != NULL)
        {
           if(index >= 0 && index <= this->size)
           {
                for(i=index ; i<this->size ; i++)
                {
                    *(this->pElements+i) = *(this->pElements+i+1);
                }
                returnAux = 0;
           }
        }

    return returnAux;
}
/** \brief Increment the number of elements in pList in AL_INCREMENT elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer or if can't allocate memory]
 *                  - (0) if ok
 */
int resizeDown(ArrayList* this) ///
{
    int returnAux = -1;
    void* auxiliar;

        if(this != NULL)
        {
            auxiliar = realloc(this->pElements,(sizeof(void*)*(this->reservedSize-(this->size+AL_INCREMENT))));
                                                                            ///siempre que esta cuenta te de negativo, hay que agregar espacio
                if(auxiliar != NULL)
                {
                    this->pElements = auxiliar;
                    this->reservedSize -= AL_INCREMENT;
                    returnAux = 0;
                }
        }

    return returnAux;
}
