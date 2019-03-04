/*
 * Exercise 8-7. malloc accepts a size request without checking its
 * plausibility; free believes that the block it is asked to free contains a
 * valid size field. Improve these routines so they take more pains with error
 * checking.
 * By Faisal Saadatmand
 */

#include <stddef.h>                    /* for NULL */
#include <limits.h>                    /* for INT_MAX */

#define NALLOC      1024               /* minimum #units to request */

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

	if (nbytes == 0 || nbytes > INT_MAX)    /* error check */
		return NULL;

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
void *my_calloc(unsigned  n, unsigned size)
{
	unsigned char *p;                  /* char is exactly 1 byte */
	Header *hp;
	unsigned bsize;                    /* actual block size in bytes */
	unsigned i;

	if ((p = (unsigned char *) knr_malloc(n * size)) != NULL) {
		hp = (Header *) p - 1;
		bsize = (hp->s.size - 1) * sizeof(Header);
		for (i = 0; i < bsize - 1; i++)
			p[i] &= 0x0u;              /* clear each byte */
	}
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
	int valid;

	valid = 1;
	if (ap == NULL)                    /* error checking */
		valid = 0;
	else {
		bp = (Header *) ap - 1;        /* point to block header */
		if (bp->s.size <= 1)           /* must be at least 2 units: */
			valid = 0;                 /* 1 for header, 1 for mem block */ 
	}

	if (valid) {
		for (p = freep ; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
			if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
				break;              /* free block at start or end of arena */

		if (bp + bp->s.size == p->s.ptr) {  /* join to upper nbr */
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
}

#include <stdio.h>	

#define SIZE 21                        /* chenge value to test error checking */

int main(void)
{
	char *s;
	
	if ((s = (char *) knr_malloc(SIZE * sizeof(char))) != NULL)
		printf("Valid size\n");
	else
		fprintf(stderr, "Invalid size\n");

	knr_free(s);

	return 0;
}
