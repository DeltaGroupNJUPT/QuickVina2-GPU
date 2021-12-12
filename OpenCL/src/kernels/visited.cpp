#include "kernel2.h"
inline void ele_init_cl(std_vector* x, float f_cl,change_cl *d) {
	ele_cl *present;
	for (int i = 0; i < 3; i++)present->x_cl.position[i]=x->position[i];
	for (int i = 0; i < 4; i++)present->x_cl.orientation[i] = x->orientation[i];
	for (int i = 0; i < MAX_NUM_OF_LIG_TORSION; i++)present->x_cl.lig_torsion[i] = x->lig_torsion[i];
	for (int i = 0; i < MAX_NUM_OF_FLEX_TORSION; i++)present->x_cl.flex_torsion[i] = x->flex_torsion[i];
	present->energy = f_cl;
	for (int i = 0; i < 3; i++)present->d_cl.position[i] = d->position[i];
	for (int i = 0; i < 3; i++)present->d_cl.orientation[i] = d->orientation[i];
	for (int i = 0; i < MAX_NUM_OF_LIG_TORSION; i++)present->d_cl.lig_torsion[i] = d->lig_torsion[i];
	for (int i = 0; i < MAX_NUM_OF_FLEX_TORSION; i++)present->d_cl.flex_torsion[i] = d->flex_torsion[i];
	long d_zero = 0;
	long d_positive = 0;
	const long ONE = 1;
	long bitMask = 0;
	for (int i = 0; i < 3;i++) {
		bitMask = ONE << i;
		if (d->position[i] == 0) d_zero |= bitMask;
		else if (d->position[i] > 0) d_positive |= bitMask;
	}
	for (int i = 0; i < 3; i++) {
		bitMask = ONE << i;
		if (d->orientation[i] == 0) d_zero |= bitMask;
		else if (d->orientation[i] > 0) d_positive |= bitMask;
	}
	for (int i = 0; i < MAX_NUM_OF_LIG_TORSION; i++) {
		bitMask = ONE << i;
		if (d->lig_torsion[i] == 0) d_zero |= bitMask;
		else if (d->orientation[i] > 0) d_positive |= bitMask;
	}
	for (int i = 0; i < MAX_NUM_OF_FLEX_TORSION; i++) {
		bitMask = ONE << i;
		if (d->flex_torsion[i] == 0) d_zero |= bitMask;
		else if (d->flex_torsion[i] > 0) d_positive |= bitMask;
	}
}
