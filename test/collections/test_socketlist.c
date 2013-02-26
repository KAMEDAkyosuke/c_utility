#include "../../collections/socketlist.h"

#include "../external/unittest/unittest.h"

#include <stdbool.h>

static void test_append();
static void test_delete();
static void test_delete_closed_socket();

static socketlist_t* create_list(int num);

int main(int argc, char** argv)
{
    test_append();    
    test_delete();
    test_delete_closed_socket();
    return 0;
}

static void test_append()
{
    socketlist_t* root = socketlist_append(NULL, 0);
    test(root->next == NULL);
    test(root->socket == 0);
    test(root->is_closed == false);

    socketlist_t* list = socketlist_append(root, 1);
    test(list == root);
    test(list->next->next == NULL);
    test(list->next->socket == 1);
    test(list->next->is_closed == false);

    socketlist_free(root);
    root = NULL;
}

static void test_delete()
{
    {// delete first
        socketlist_t* l = create_list(3);
        socketlist_t* second = l->next;
        l = socketlist_delete(l, l);
        test(second == l);
        socketlist_free(l);
        l = NULL;
    }
    {// delete second
        socketlist_t* l = create_list(3);
        socketlist_t* first = l;
        socketlist_t* third = l->next->next;
        l = socketlist_delete(l, l->next);
        test(first == l);
        test(third == l->next);
        socketlist_free(l);
        l = NULL;
    }
    {// delete last
        socketlist_t* l = create_list(3);
        socketlist_t* first = l;
        socketlist_t* second = l->next;
        l = socketlist_delete(l, l->next->next);
        test(first == l);
        test(second == l->next);
        test(l->next->next == NULL);
        socketlist_free(l);
        l = NULL;
    }
}

static void test_delete_closed_socket()
{
    {// close first
        socketlist_t* l = create_list(3);
        l->is_closed = true;
        socketlist_t* second = l->next;
        l = socketlist_delete_closed_socket(l);
        test(l == second);
        socketlist_free(l);
        l = NULL;
    }

    {// close first, second
        socketlist_t* l = create_list(3);
        l->is_closed = true;
        l->next->is_closed = true;
        socketlist_t* third = l->next->next;
        l = socketlist_delete_closed_socket(l);
        test(l == third);
        socketlist_free(l);
        l = NULL;
    }

    {// close first, third
        socketlist_t* l = create_list(3);
        l->is_closed = true;
        l->next->next->is_closed = true;
        socketlist_t* second = l->next;
        l = socketlist_delete_closed_socket(l);
        test(l == second);
        socketlist_free(l);
        l = NULL;
    }

    {// close second
        socketlist_t* l = create_list(3);
        l->next->is_closed = true;
        socketlist_t* first = l;
        socketlist_t* third = l->next->next;
        l = socketlist_delete_closed_socket(l);
        test(l == first);
        test(l->next == third);
        socketlist_free(l);
        l = NULL;
    }

    {// close second, third
        socketlist_t* l = create_list(3);
        l->next->is_closed = true;
        l->next->next->is_closed = true;
        socketlist_t* first = l;
        l = socketlist_delete_closed_socket(l);
        test(l == first);
        test(l->next == NULL);
        socketlist_free(l);
        l = NULL;
    }

    {// close third
        socketlist_t* l = create_list(3);
        l->next->next->is_closed = true;
        socketlist_t* first = l;
        socketlist_t* second = l->next;
        l = socketlist_delete_closed_socket(l);
        test(l == first);
        test(l->next == second);
        test(l->next->next == NULL);
        socketlist_free(l);
        l = NULL;
    }
}

static socketlist_t* create_list(int num)
{
    if(num < 0){
        return NULL;
    }
    socketlist_t* new_item = NULL;
    for(int i=0; i<num; i++){
        new_item = socketlist_append(new_item, i);
    }
    return new_item;
}
