#ifndef list_h
#define list_h

 

#define Type int

 

typedef struct _list List;

 

List* lstCreate(void);

List* lstDestroy(List* list);

int lstPush(List* list, Type info);

int lstQueue(List* list, Type info);

int lstPop(List* list, Type* pinfo);

int lstIsEmpty(List* list);

int lstPointToFirst(List* list);

int lstPointToNext(List* list);

int lstGetCurrent(List* list, Type* pinfo);

int lstPrint( List* list );


#endif /* list_h */