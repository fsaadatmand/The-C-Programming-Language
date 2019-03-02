/*
 * Exercise 8-6. The standard library function calloc(m, size) returns a
 * pointer to n objects of size size, with the storage initialized to zero.
 * Write calloc, by calling malloc or by modifying it.
 * By Faisal Saadatmand
 */
#define NULL   0
#define NALLOC 1024                    /* minimum #units to request */

typedef long Align;                    /* for alignment to long boundary */

union header {                         /* block header: */
	struct {
		union header *ptr;             /* next block if on free list */
		unsigned size;                 /* size of this block */
	} s;
	Align x;                           /* force alignment of blocks */
};

typedef union header Header;

static Header base;                    /* empty list to get started */
static Header *freep = NULL;           /* start of free list */

void *knr_malloc(unsigned);
static Header *morecore(unsigned);
void knr_free(void *);

/* knr_malloc: general-purpose storage allocator */
void *knr_malloc(unsigned nbytes)
{
	Header *p;                         /* pointer to current block */
	Header *prevp;                     /* pointer to previous block */

	unsigned nunits;

	/* round up to allocate in units of sizeof(Header) */
	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
	if ((prevp = freep) == NULL) {     /* no free list yet */
		base.s.ptr = &base;
		freep = prevp = &base;         /* point all to base */
		base.s.size = 0;
	}

	for (p = prevp->s.ptr; ; p = p->s.ptr) {    /* search free linked-list */
		if (p->s.size >= nunits) {     /* big enough */
			if (p->s.size == nunits)   /* exactly */
				prevp->s.ptr = p->s.ptr;
			else {
				p->s.size -= nunits;
				p += p->s.size;        /* allocate at tail-end */
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *) (p + 1);
		}
		if (p == freep)                /* wrapped around free list */
			if ((p = morecore(nunits)) == NULL)            /* request more memory */
				return NULL;           /* none left */
		prevp = p;                     /* save current pointer's address */
	}
}

/* my_calloc: general-purpose storage allocator. Initialize memory to zeros */
void *my_calloc(unsigned m, unsigned size)
{
	unsigned char *p;                  /* char is exactly 1 byte */
	unsigned i;

	if ((p = (unsigned char *) knr_malloc(m * size)) != NULL)
		for (i = 0; i < m * size; i++)
			p[i] &= 0x0u;              /* clear each byte */
	return (void *) p; 
}

/* morecore: ask system for more memory */
static Header *morecore(unsigned nu)
{
	char *cp;                          /* pointer to chunk of memory */
	char *sbrk(int);
	Header *up;

	if (nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) -1)             /* no space at all */
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;
	knr_free((void *)(up + 1));
	return freep;
}

/* knr_free: put block ap in free list */
void knr_free(void *ap)
{
	Header *bp, *p;

	bp = (Header *) ap - 1;            /* point to block header */
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;                     /* free block at start or end of arena */

	if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else
		bp->s.ptr = p->s.ptr;
	if (p + p->s.size == bp) {          /* join to lower nbr */
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else
		p->s.ptr = bp;
	freep = p;
}

#include <stdio.h>	

#define SIZE 20 
#define LENGTH 21

int main(void)
{
	int *array, i;
	char *s;
	
	array = (int *) my_calloc(SIZE, sizeof(int));
	s = (char *) my_calloc(LENGTH, sizeof(char));

	for (i = 0; i < SIZE; i++)
		printf("%i ", array[i]);
	printf("\n");

	for (i = 0; i < LENGTH - 1; i++)
		printf("%i ", s[i]);
	printf("\n");

	knr_free(array);
	knr_free(s);

	return 0;
}
