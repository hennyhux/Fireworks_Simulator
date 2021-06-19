/*Author: Henry Zhang*/ 
/* header file for list */

/* these are the function pointer signatures needed */

typedef void (* ActionFunction)( void *data);
typedef int (* ComparisonFunction)(void *data1, void *data2);
typedef int (* CriteriaFunction)(void *data);
typedef double (* NumericFunction)(void *data);

/* signatures that the list code provides to the outside world */

/* insert and delete need to be able to change the head pointer so you pass
 * in the address of the head pointer */

/* int returns FALSE when it fails to do the insert */
int insert(void *p2head, void *data, ComparisonFunction goesInFrontOf, 
		int verbose);
void deleteSome(void *p2head, CriteriaFunction mustGo, 
		ActionFunction disposal, int verbose);

/* iterate and sort do not change the nodes, so you pass in the head
 * pointer and not the address of the head pointer */
void iterate(void *head, ActionFunction doThis);

/* sort moves data, not nodes, so head won't change */
void sort(void *head, ComparisonFunction goesInFrontOf);

/* some returns true if at least one item passes the test 
 * returns false if nothing in the list */
int some(void *head, CriteriaFunction someTest);

/* least returns least value of all calls to numeric function 
 * returns NaN if list is empty.  if(x != x) is true when x is NaN */
double least(void *head, NumericFunction compute_this);




