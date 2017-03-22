#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "array_helpers.h"
#include "sort.h"

bool array_is_sorted(int *a, unsigned int length) 
{
	bool r=true;
    unsigned int i=0;
	if(length>2)
	{
		while(i<length-1 && r) 
		{
			if(a[i]<= a[i+1])
			{
				i++;
			}
			else 
			{ 
				r=false;
			}
		}
	}
	return r;
}

void swap(int *a, unsigned int i, unsigned int j) 
{
	int r;
	r=a[i];
	a[i]=a[j];
	a[j]=r;
}
///////////////////SELECTION SORT//////////////////////////
struct sorting_stats_auxA
{
	unsigned long int comps;
	unsigned long int swaps;
	unsigned long int minp;
};

struct sorting_stats_auxA min_pos_from(int *a, unsigned int length, unsigned int i) 
{
	struct sorting_stats_auxA aux1; 
	aux1.comps=0; 
	aux1.minp=i;

	unsigned int j=i+1;

	while(j<length) 
	{
		if (a[j]<a[aux1.minp]) 
		{
			aux1.minp=j;
		}
		aux1.comps++;
		j++;
	}
	return aux1;
}

struct sorting_stats selection_sort(int *a, unsigned int length) 
{
	assert(array_is_valid(a,length));

	struct sorting_stats result; 
	result.comps=0; 
	result.swaps=0;

	struct sorting_stats_auxA aux2;
	aux2.comps=0; 
	aux2.swaps=0;
	aux2.minp=0;

	unsigned int i=0;	

	if(length>2)
	{	
		while (i<length) 
		{
			aux2=min_pos_from(a,length,i);
			if(aux2.minp!=i)
			{
				swap(a,i,aux2.minp);
				result.swaps++;
			}
			i++;
			result.comps=result.comps+aux2.comps; 
        }		
		assert(array_is_sorted(a,length));
	}
	return result;	
}
//////////////////////INSERTION SORT//////////////////////////
struct sorting_stats insert(int *a, unsigned int i)
{
    struct sorting_stats result;
    result.swaps = 0;
    result.comps = 0;

	unsigned int j = i;

	while (j > 0 && a[j] < a[j-1])
	{
		swap(a, j-1, j);
		j--;
        result.swaps++;
        result.comps++;
	}
    if (j > 0)
    {
        result.comps++;
    }
    return result;
}

struct sorting_stats insertion_sort(int *a, unsigned int length) 
{
    assert(array_is_valid(a, length));

    struct sorting_stats result;
    result.swaps = 0;
    result.comps = 0;

    struct sorting_stats aux3;
    aux3.swaps = 0;
    aux3.comps = 0;

    for (unsigned int i = 1; i < length; i++)
    {
    	aux3 = insert(a, i);
        result.swaps = result.swaps + aux3.swaps;
        result.comps = result.comps + aux3.comps;
    }
    return result;
}
/////////////////////////QUICKSORT//////////////////////////////
struct sorting_stats_auxB
{
	unsigned long int comps;
	unsigned long int swaps;
	int piv;
};

struct sorting_stats_auxB pivot(int *a,  int left,  int right) 
{ 
	struct sorting_stats_auxB aux4; 
	aux4.comps=0; 
	aux4.swaps=0;
	aux4.piv=left;

	int i=left+1;
	int j=right;

	while(i<=j) 
	{
		if(a[i]<=a[aux4.piv])
		{
			i++;
			aux4.comps=aux4.comps+1;
		}
		else
		{
			if(a[j]>a[aux4.piv])
			{
				j--;
				aux4.comps=aux4.comps+2;
			}
			 else 
			{
				swap(a,(unsigned int)i,(unsigned int)j);
				aux4.swaps++;
				i++;
				j--;
				aux4.comps=aux4.comps+2;
			}
		}
	}
	if(aux4.piv!=j)
	{	
		swap(a,(unsigned int)aux4.piv,(unsigned int)j);
		aux4.swaps++;	
		aux4.piv= j;
	}
	return aux4;
}

struct sorting_stats recursive_quick_sort(int *a, int left, int right) 
{
	struct sorting_stats result,result2,result3;
	result.comps=0;
	result.swaps=0;
	result2.comps=0;
	result2.swaps=0;
	result3.comps=0; 
	result3.swaps=0;

	struct sorting_stats_auxB aux5;
	aux5.comps=0;
	aux5.swaps=0;

	if(right>left)
	{
		aux5=pivot(a,left,right);
		assert(left<=aux5.piv && aux5.piv<=right);
		
		result2=recursive_quick_sort(a,left,((int)aux5.piv)-1);
		result3=recursive_quick_sort(a,((int)aux5.piv)+1,right);	
	}	
	result.comps=aux5.comps+result2.comps+result3.comps;
	result.swaps=aux5.swaps+result2.swaps+result3.swaps;
	return result;
}

struct sorting_stats quick_sort(int *a, unsigned int length) 
{
	struct sorting_stats finalresult; 
	finalresult.comps=0; 
	finalresult.swaps=0;

	assert(array_is_valid(a, length));

	if(length>2)
	{	
		finalresult=recursive_quick_sort(a,0,((int)length)-1);
    	assert(array_is_sorted(a, length));
	}
return finalresult;
}
//////////////////BUBBLE SORT///////////////////////
struct sorting_stats bubble_sort(int *a,unsigned int length) 
{ 
	struct sorting_stats result;
	result.comps=0; 
	result.swaps=0; 

	unsigned int i; 
	unsigned int j; 
	bool swapped=true;

	if(length>2) 
	{ 
		for(i=1;swapped && i<length;i++) 
		{ 
			swapped=false; 
			for (j=0;j<length-i;j++) 
			{ 
				if (a[j]>a[j+1]) 
				{ 
					swap(a,j,j+1); 
					result.swaps++; 
					swapped=true;
					result.comps++;  
				} 
				result.comps++;  
			}  
		} 
	} 
	return result; 
}
/////////////////RANDOM QUICK SORT//////////////////////
struct sorting_stats_auxB rand_pivot(int *a,  int left,  int right) 
{ 
	struct sorting_stats_auxB aux6; 
	aux6.comps=0; 
	aux6.swaps=0;

//	srand(time(NULL));
	aux6.piv=(rand()%(right-left))+left;

	swap(a,left,aux6.piv);
	aux6.piv=left;

	int i=left+1;
	int j=right;

	while(i<=j) 
	{
		if(a[i]<=a[aux6.piv])
		{
			i++;
			aux6.comps=aux6.comps+1;
		}
		else
		{
			if(a[j]>a[aux6.piv])
			{
				j--;
				aux6.comps=aux6.comps+2;
			}
			 else 
			{
				swap(a,(unsigned int)i,(unsigned int)j);
				aux6.swaps++;
				i++;
				j--;
				aux6.comps=aux6.comps+2;
			}
		}
	}
	if(aux6.piv!=j)
	{
		swap(a,(unsigned int)aux6.piv,(unsigned int)j);
		aux6.swaps++;	
		aux6.piv= j;
	}
	return aux6;
}

struct sorting_stats recursive_rand_quick_sort(int *a, int left, int right) 
{
	struct sorting_stats result,result2,result3;
	result2.comps=0;
	result2.swaps=0;
	result3.comps=0; 
	result3.swaps=0;

	struct sorting_stats_auxB aux7;
	aux7.comps=0;
	aux7.swaps=0;

	if(right>left)
	{
		aux7=rand_pivot(a,left,right);
		assert(left<=aux7.piv && aux7.piv<=right);

		result2=recursive_rand_quick_sort(a,left,((int)aux7.piv)-1);
		result3=recursive_rand_quick_sort(a,((int)aux7.piv)+1,right);	
	}	
	result.comps=aux7.comps+result2.comps+result3.comps;
	result.swaps=aux7.swaps+result2.swaps+result3.swaps;
	return result;
}

struct sorting_stats rand_quick_sort(int *a, unsigned int length) 
{
	struct sorting_stats finalresult; 
	finalresult.comps=0; 
	finalresult.swaps=0;

	assert(array_is_valid(a, length));

	if(length>2)
	{	
		finalresult=recursive_rand_quick_sort(a,0,((int)length)-1);
    	assert(array_is_sorted(a, length));
	}
return finalresult;
}
