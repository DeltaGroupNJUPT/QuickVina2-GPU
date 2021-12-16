#include "kernel2.h"
inline void ele_init_cl(ele_cl* present, std_vector* x, float f_cl, change_cl* d) {
	for (int i = 0; i < 3; i++)present->x_cl.position[i] = x->position[i];
	for (int i = 0; i < 4; i++)present->x_cl.orientation[i] = x->orientation[i];
	for (int i = 0; i < MAX_NUM_OF_LIG_TORSION; i++)present->x_cl.lig_torsion[i] = x->lig_torsion[i];
	for (int i = 0; i < MAX_NUM_OF_FLEX_TORSION; i++)present->x_cl.flex_torsion[i] = x->flex_torsion[i];
	present->energy = f_cl;
	for (int i = 0; i < 3; i++)present->d_cl.position[i] = d->position[i];
	for (int i = 0; i < 3; i++)present->d_cl.orientation[i] = d->orientation[i];
	for (int i = 0; i < MAX_NUM_OF_LIG_TORSION; i++)present->d_cl.lig_torsion[i] = d->lig_torsion[i];
	for (int i = 0; i < MAX_NUM_OF_FLEX_TORSION; i++)present->d_cl.flex_torsion[i] = d->flex_torsion[i];
	present->d_zero = 0;
	present->d_positive = 0;
	const long ONE = 1;
	long bitMask = 0;
	for (int i = 0; i < 3; i++) {
		bitMask = ONE << i;
		if (d->position[i] == 0) present->d_zero |= bitMask;
		else if (d->position[i] > 0) present->d_positive |= bitMask;
	}
	for (int i = 0; i < 3; i++) {
		bitMask = ONE << i;
		if (d->orientation[i] == 0) present->d_zero |= bitMask;
		else if (d->orientation[i] > 0) present->d_positive |= bitMask;
	}
	for (int i = 0; i < MAX_NUM_OF_LIG_TORSION; i++) {
		bitMask = ONE << i;
		if (d->lig_torsion[i] == 0) present->d_zero |= bitMask;
		else if (d->orientation[i] > 0) present->d_positive |= bitMask;
	}
	for (int i = 0; i < MAX_NUM_OF_FLEX_TORSION; i++) {
		bitMask = ONE << i;
		if (d->flex_torsion[i] == 0) present->d_zero |= bitMask;
		else if (d->flex_torsion[i] > 0) present->d_positive |= bitMask;
	}
}
inline void visited_init(visited_cl* visited)
{
	visited->n_variable = 0;
	visited->p = 0;
	visited->full = false;
	visited->index = 0;

}
inline bool add(visited_cl* visited, output_type_cl* conf_v, float f, change_cl* change_v)
{
	visited->tempf = f;
	std_vector* tempx;
	for (int i = 0; i < 3; i++)tempx->position[i] = conf_v->position[i];
	for (int i = 0; i < 3; i++)tempx->orientation[i] = conf_v->orientation[i];
	for (int i = 0; i < MAX_NUM_OF_LIG_TORSION; i++)tempx->lig_torsion[i] = conf_v->lig_torsion[i];
	for (int i = 0; i < MAX_NUM_OF_FLEX_TORSION; i++)tempx->flex_torsion[i] = conf_v->flex_torsion[i];
	ele_cl* e;
	ele_init_cl(e, tempx, f, change_v);
	if (visited->index == 0)
	{
		visited->n_variable = conf_v->lig_torsion_size;
	}
	if (!visited->full)
	{
		visited->list_cl[visited->index] = e;
		visited->index++;
		if (visited->index >= 10 * visited->n_variable)
		{
			visited->full = true;
			visited->p = 0;
		}
	}
	else
	{
		visited->list_cl[visited->p] = e;
		visited->p = (visited->p + 1) % (10 * visited->n_variable);
	}
	return true;
}
bool check(visited_cl* visited, std_vector now_x, float now_f, change_cl* now_d, int neighbor)
{
	bool newXBigger, newYBigger;
	const long ONE = 1;
	long bitMask = 0;
	newYBigger = (now_f - visited->list_cl[neighbor]->energy) > 0;
	//int nowDSize = now_d->lig_torsion_size;
	for (int i = 0; i < 3; i++)
	{
		bitMask = ONE << i;
		if( (visited->list_cl[neighbor]->d_zero & bitMask) ||!(now_d->position[i])){
        }
		else
		{
			const bool nowPositive = now_d->position[i] > 0;

		}
	}
}

