/* File: tables.c */

/*
 * Copyright (c) 1997 Ben Harrison, James E. Wilson, Robert A. Koeneke
 *
 * This software may be copied and distributed for educational, research,
 * and not for profit purposes provided that this copyright and statement
 * are included in all such copies.  Other copyrights may also apply.
 *
 * UnAngband (c) 2001-6 Andrew Doull. Modifications to the Angband 2.9.1
 * source code are released under the Gnu Public License. See www.fsf.org
 * for current GPL license details. Addition permission granted to
 * incorporate modifications in all Angband variants as defined in the
 * Angband variants FAQ. See rec.games.roguelike.angband for FAQ.
 */

#include "angband.h"




/*
 * Global array for looping through the "keypad directions".
 */
const s16b ddd[9] =
{ 2, 8, 6, 4, 3, 1, 9, 7, 5 };

/*
 * Global arrays for converting "keypad direction" into "offsets".
 */
const s16b ddx[10] =
{ 0, -1, 0, 1, -1, 0, 1, -1, 0, 1 };

const s16b ddy[10] =
{ 0, 1, 1, 1, 0, 0, 0, -1, -1, -1 };

/*
 * Global arrays for optimizing "ddx[ddd[i]]" and "ddy[ddd[i]]".
 */
const s16b ddx_ddd[9] =
{ 0, 0, 1, -1, 1, -1, 1, -1, 0 };

const s16b ddy_ddd[9] =
{ 1, -1, 0, 0, 1, 1, -1, -1, 0 };


/*
 * Given a central direction at position [dir #][0], return a series 
 * of directions radiating out on both sides from the central direction 
 * all the way back to its rear.
 * 
 * Side directions come in pairs; for example, directions '1' and '3' 
 * flank direction '2'.  The code should know which side to consider 
 * first.  If the left, it must add 10 to the central direction to 
 * access the second part of the table.
 */ 
const byte side_dirs[20][8] = 
{
	{ 0, 0, 0, 0, 0, 0, 0, 0 },	/* bias right */
	{ 1, 4, 2, 7, 3, 8, 6, 9 },
	{ 2, 1, 3, 4, 6, 7, 9, 8 },
	{ 3, 2, 6, 1, 9, 4, 8, 7 },
	{ 4, 7, 1, 8, 2, 9, 3, 6 },
	{ 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 6, 3, 9, 2, 8, 1, 7, 4 },
	{ 7, 8, 4, 9, 1, 6, 2, 3 },
	{ 8, 9, 7, 6, 4, 3, 1, 2 },
	{ 9, 6, 8, 3, 7, 2, 4, 1 },

	{ 0, 0, 0, 0, 0, 0, 0, 0 },	/* bias left */
	{ 1, 2, 4, 3, 7, 6, 8, 9 },
	{ 2, 3, 1, 6, 4, 9, 7, 8 },
	{ 3, 6, 2, 9, 1, 8, 4, 7 },
	{ 4, 1, 7, 2, 8, 3, 9, 6 },
	{ 5, 5, 5, 5, 5, 5, 5, 5 },
	{ 6, 9, 3, 8, 2, 7, 1, 4 },
	{ 7, 4, 8, 1, 9, 2, 6, 3 },
	{ 8, 7, 9, 4, 6, 1, 3, 2 },
	{ 9, 8, 6, 7, 3, 4, 2, 1 } 
};


/*
 * Global array for converting numbers to uppercase hecidecimal digit
 * This array can also be used to convert a number to an octal digit
 */
const char hexsym[16] =
{
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};


/*
 * Stat Table -- One less than number of spells at level 50
 */
const byte adj_mag_study[] =
{
	6	/* 3 */,
	8	/* 4 */,
	10	/* 5 */,
	12	/* 6 */,
	14	/* 7 */,
	16	/* 8 */,
	18	/* 9 */,
	20	/* 10 */,
	24	/* 11 */,
	28	/* 12 */,
	32	/* 13 */,
	36	/* 14 */,
	40	/* 15 */,
	44	/* 16 */,
	48	/* 17 */,
	52	/* 18/00-18/09 */,
	56	/* 18/10-18/19 */,
	60	/* 18/20-18/29 */,
	64	/* 18/30-18/39 */,
	68	/* 18/40-18/49 */,
	72	/* 18/50-18/59 */,
	76	/* 18/60-18/69 */,
	80	/* 18/70-18/79 */,
	84	/* 18/80-18/89 */,
	88	/* 18/90-18/99 */,
	91	/* 18/100-18/109 */,
	94	/* 18/110-18/119 */,
	97	/* 18/120-18/129 */,
	100	/* 18/130-18/139 */,
	103	/* 18/140-18/149 */,
	106	/* 18/150-18/159 */,
	109	/* 18/160-18/169 */,
	112	/* 18/170-18/179 */,
	113	/* 18/180-18/189 */,
	116	/* 18/190-18/199 */,
	119	/* 18/200-18/209 */,
	122	/* 18/210-18/219 */,
	125	/* 18/220+ */
};


/*
 * Stat Table -- one (or 4 for mages) less than the amount of mana at level 50
 */
const s16b adj_mag_mana[] =
{
	0	/* 3 */,
	5	/* 4 */,
	10	/* 5 */,
	15	/* 6 */,
	20	/* 7 */,
	25	/* 8 */,
	30	/* 9 */,
	35	/* 10 */,
	40	/* 11 */,
	45	/* 12 */,
	50	/* 13 */,
	55	/* 14 */,
	60	/* 15 */,
	65	/* 16 */,
	70	/* 17 */,
	75	/* 18/00-18/09 */,
	80	/* 18/10-18/19 */,
	85	/* 18/20-18/29 */,
	90	/* 18/30-18/39 */,
	95	/* 18/40-18/49 */,
	100	/* 18/50-18/59 */,
	110	/* 18/60-18/69 */,
	120	/* 18/70-18/79 */,
	130	/* 18/80-18/89 */,
	140	/* 18/90-18/99 */,
	160	/* 18/100-18/109 */,
	180	/* 18/110-18/119 */,
	200	/* 18/120-18/129 */,
	220	/* 18/130-18/139 */,
	240	/* 18/140-18/149 */,
	260	/* 18/150-18/159 */,
	280	/* 18/160-18/169 */,
	300	/* 18/170-18/179 */,
	320	/* 18/180-18/189 */,
	340	/* 18/190-18/199 */,
	360	/* 18/200-18/209 */,
	380	/* 18/210-18/219 */,
	400	/* 18/220+ */
};


/*
 * Stat Table (spell stat) -- Minimum failure rate (percentage)
 */
const byte adj_mag_fail_min[] =
{
	99	/* 3 */,
	99	/* 4 */,
	99	/* 5 */,
	99	/* 6 */,
	99	/* 7 */,
	50	/* 8 */,
	30	/* 9 */,
	20	/* 10 */,
	15	/* 11 */,
	12	/* 12 */,
	11	/* 13 */,
	10	/* 14 */,
	9	/* 15 */,
	8	/* 16 */,
	7	/* 17 */,
	6	/* 18/00-18/09 */,
	6	/* 18/10-18/19 */,
	5	/* 18/20-18/29 */,
	5	/* 18/30-18/39 */,
	5	/* 18/40-18/49 */,
	4	/* 18/50-18/59 */,
	4	/* 18/60-18/69 */,
	4	/* 18/70-18/79 */,
	4	/* 18/80-18/89 */,
	3	/* 18/90-18/99 */,
	3	/* 18/100-18/109 */,
	2	/* 18/110-18/119 */,
	2	/* 18/120-18/129 */,
	2	/* 18/130-18/139 */,
	2	/* 18/140-18/149 */,
	1	/* 18/150-18/159 */,
	1	/* 18/160-18/169 */,
	1	/* 18/170-18/179 */,
	1	/* 18/180-18/189 */,
	1	/* 18/190-18/199 */,
	0	/* 18/200-18/209 */,
	0	/* 18/210-18/219 */,
	0	/* 18/220+ */
};


/*
 * Stat Table (spell stat) -- Rate fail
 */
const byte adj_mag_fail_rate[] =
{
	0	/* 3 */,
	0	/* 4 */,
	0	/* 5 */,
	0	/* 6 */,
	0	/* 7 */,
	1	/* 8 */,
	1	/* 9 */,
	1	/* 10 */,
	1	/* 11 */,
	1	/* 12 */,
	1	/* 13 */,
	1	/* 14 */,
	2	/* 15 */,
	2	/* 16 */,
	2	/* 17 */,
	3	/* 18/00-18/09 */,
	3	/* 18/10-18/19 */,
	3	/* 18/20-18/29 */,
	3	/* 18/30-18/39 */,
	3	/* 18/40-18/49 */,
	4	/* 18/50-18/59 */,
	4	/* 18/60-18/69 */,
	5	/* 18/70-18/79 */,
	6	/* 18/80-18/89 */,
	7	/* 18/90-18/99 */,
	8	/* 18/100-18/109 */,
	9	/* 18/110-18/119 */,
	10	/* 18/120-18/129 */,
	11	/* 18/130-18/139 */,
	12	/* 18/140-18/149 */,
	13	/* 18/150-18/159 */,
	14	/* 18/160-18/169 */,
	15	/* 18/170-18/179 */,
	16	/* 18/180-18/189 */,
	17	/* 18/190-18/199 */,
	18	/* 18/200-18/209 */,
	19	/* 18/210-18/219 */,
	20	/* 18/220+ */
};


/*
 * Stat Table (CHR) -- payment percentages
 */
const byte adj_chr_gold[] =
{
	130	/* 3 */,
	125	/* 4 */,
	122	/* 5 */,
	120	/* 6 */,
	118	/* 7 */,
	116	/* 8 */,
	114	/* 9 */,
	112	/* 10 */,
	110	/* 11 */,
	108	/* 12 */,
	106	/* 13 */,
	104	/* 14 */,
	103	/* 15 */,
	102	/* 16 */,
	101	/* 17 */,
	100	/* 18/00-18/09 */,
	99	/* 18/10-18/19 */,
	98	/* 18/20-18/29 */,
	97	/* 18/30-18/39 */,
	96	/* 18/40-18/49 */,
	95	/* 18/50-18/59 */,
	94	/* 18/60-18/69 */,
	93	/* 18/70-18/79 */,
	92	/* 18/80-18/89 */,
	91	/* 18/90-18/99 */,
	90	/* 18/100-18/109 */,
	89	/* 18/110-18/119 */,
	88	/* 18/120-18/129 */,
	87	/* 18/130-18/139 */,
	86	/* 18/140-18/149 */,
	85	/* 18/150-18/159 */,
	84	/* 18/160-18/169 */,
	83	/* 18/170-18/179 */,
	82	/* 18/180-18/189 */,
	81	/* 18/190-18/199 */,
	80	/* 18/200-18/209 */,
	80	/* 18/210-18/219 */,
	80	/* 18/220+ */
};


/*
 * Stat Table (CHR) -- chance of restocking an item out of stock
 */
const byte adj_chr_stock[] =
{
	230	/* 3 */,
	220	/* 4 */,
	215	/* 5 */,
	210	/* 6 */,
	205	/* 7 */,
	200	/* 8 */,
	195	/* 9 */,
	190	/* 10 */,
	185	/* 11 */,
	180	/* 12 */,
	175	/* 13 */,
	160	/* 14 */,
	155	/* 15 */,
	140	/* 16 */,
	135	/* 17 */,
	130	/* 18/00-18/09 */,
	120	/* 18/10-18/19 */,
	110	/* 18/20-18/29 */,
	100	/* 18/30-18/39 */,
	90	/* 18/40-18/49 */,
	80	/* 18/50-18/59 */,
	70	/* 18/60-18/69 */,
	65	/* 18/70-18/79 */,
	60	/* 18/80-18/89 */,
	55	/* 18/90-18/99 */,
	50	/* 18/100-18/109 */,
	45	/* 18/110-18/119 */,
	42	/* 18/120-18/129 */,
	40	/* 18/130-18/139 */,
	38	/* 18/140-18/149 */,
	36	/* 18/150-18/159 */,
	34	/* 18/160-18/169 */,
	32	/* 18/170-18/179 */,
	30	/* 18/180-18/189 */,
	28	/* 18/190-18/199 */,
	26	/* 18/200-18/209 */,
	25	/* 18/210-18/219 */,
	24	/* 18/220+ */
};


/*
 * Stat Table (INT) -- Magic devices
 */
const byte adj_int_dev[] =
{
	0	/* 3 */,
	0	/* 4 */,
	0	/* 5 */,
	0	/* 6 */,
	0	/* 7 */,
	1	/* 8 */,
	1	/* 9 */,
	1	/* 10 */,
	1	/* 11 */,
	1	/* 12 */,
	1	/* 13 */,
	1	/* 14 */,
	2	/* 15 */,
	2	/* 16 */,
	2	/* 17 */,
	3	/* 18/00-18/09 */,
	3	/* 18/10-18/19 */,
	4	/* 18/20-18/29 */,
	4	/* 18/30-18/39 */,
	5	/* 18/40-18/49 */,
	5	/* 18/50-18/59 */,
	6	/* 18/60-18/69 */,
	6	/* 18/70-18/79 */,
	7	/* 18/80-18/89 */,
	7	/* 18/90-18/99 */,
	8	/* 18/100-18/109 */,
	9	/* 18/110-18/119 */,
	10	/* 18/120-18/129 */,
	11	/* 18/130-18/139 */,
	12	/* 18/140-18/149 */,
	13	/* 18/150-18/159 */,
	14	/* 18/160-18/169 */,
	15	/* 18/170-18/179 */,
	16	/* 18/180-18/189 */,
	17	/* 18/190-18/199 */,
	18	/* 18/200-18/209 */,
	19	/* 18/210-18/219 */,
	20	/* 18/220+ */
};


/*
 * Stat Table (WIS) -- Saving throw
 */
const byte adj_wis_sav[] =
{
	0	/* 3 */,
	0	/* 4 */,
	0	/* 5 */,
	0	/* 6 */,
	0	/* 7 */,
	1	/* 8 */,
	1	/* 9 */,
	1	/* 10 */,
	1	/* 11 */,
	1	/* 12 */,
	1	/* 13 */,
	1	/* 14 */,
	2	/* 15 */,
	2	/* 16 */,
	2	/* 17 */,
	3	/* 18/00-18/09 */,
	3	/* 18/10-18/19 */,
	3	/* 18/20-18/29 */,
	3	/* 18/30-18/39 */,
	3	/* 18/40-18/49 */,
	4	/* 18/50-18/59 */,
	4	/* 18/60-18/69 */,
	5	/* 18/70-18/79 */,
	5	/* 18/80-18/89 */,
	6	/* 18/90-18/99 */,
	7	/* 18/100-18/109 */,
	8	/* 18/110-18/119 */,
	9	/* 18/120-18/129 */,
	10	/* 18/130-18/139 */,
	11	/* 18/140-18/149 */,
	12	/* 18/150-18/159 */,
	13	/* 18/160-18/169 */,
	14	/* 18/170-18/179 */,
	15	/* 18/180-18/189 */,
	16	/* 18/190-18/199 */,
	17	/* 18/200-18/209 */,
	18	/* 18/210-18/219 */,
	19	/* 18/220+ */
};


/*
 * Stat Table (DEX) -- disarming
 */
const byte adj_dex_dis[] =
{
	0	/* 3 */,
	0	/* 4 */,
	0	/* 5 */,
	0	/* 6 */,
	0	/* 7 */,
	0	/* 8 */,
	0	/* 9 */,
	0	/* 10 */,
	0	/* 11 */,
	0	/* 12 */,
	1	/* 13 */,
	1	/* 14 */,
	1	/* 15 */,
	2	/* 16 */,
	2	/* 17 */,
	4	/* 18/00-18/09 */,
	4	/* 18/10-18/19 */,
	4	/* 18/20-18/29 */,
	4	/* 18/30-18/39 */,
	5	/* 18/40-18/49 */,
	5	/* 18/50-18/59 */,
	5	/* 18/60-18/69 */,
	6	/* 18/70-18/79 */,
	6	/* 18/80-18/89 */,
	7	/* 18/90-18/99 */,
	8	/* 18/100-18/109 */,
	8	/* 18/110-18/119 */,
	8	/* 18/120-18/129 */,
	8	/* 18/130-18/139 */,
	8	/* 18/140-18/149 */,
	9	/* 18/150-18/159 */,
	9	/* 18/160-18/169 */,
	9	/* 18/170-18/179 */,
	9	/* 18/180-18/189 */,
	9	/* 18/190-18/199 */,
	10	/* 18/200-18/209 */,
	10	/* 18/210-18/219 */,
	10	/* 18/220+ */
};


/*
 * Stat Table (INT) -- disarming
 */
const byte adj_int_dis[] =
{
	0	/* 3 */,
	0	/* 4 */,
	0	/* 5 */,
	0	/* 6 */,
	0	/* 7 */,
	1	/* 8 */,
	1	/* 9 */,
	1	/* 10 */,
	1	/* 11 */,
	1	/* 12 */,
	1	/* 13 */,
	1	/* 14 */,
	2	/* 15 */,
	2	/* 16 */,
	2	/* 17 */,
	3	/* 18/00-18/09 */,
	3	/* 18/10-18/19 */,
	3	/* 18/20-18/29 */,
	4	/* 18/30-18/39 */,
	4	/* 18/40-18/49 */,
	5	/* 18/50-18/59 */,
	6	/* 18/60-18/69 */,
	7	/* 18/70-18/79 */,
	8	/* 18/80-18/89 */,
	9	/* 18/90-18/99 */,
	10	/* 18/100-18/109 */,
	10	/* 18/110-18/119 */,
	11	/* 18/120-18/129 */,
	12	/* 18/130-18/139 */,
	13	/* 18/140-18/149 */,
	14	/* 18/150-18/159 */,
	15	/* 18/160-18/169 */,
	16	/* 18/170-18/179 */,
	17	/* 18/180-18/189 */,
	18	/* 18/190-18/199 */,
	19	/* 18/200-18/209 */,
	19	/* 18/210-18/219 */,
	19	/* 18/220+ */
};


/*
 * Stat Table (DEX) -- bonus to ac (plus 128)
 */
const byte adj_dex_ta[] =
{
	128 + -4	/* 3 */,
	128 + -3	/* 4 */,
	128 + -2	/* 5 */,
	128 + -1	/* 6 */,
	128 + 0	/* 7 */,
	128 + 0	/* 8 */,
	128 + 0	/* 9 */,
	128 + 0	/* 10 */,
	128 + 0	/* 11 */,
	128 + 0	/* 12 */,
	128 + 0	/* 13 */,
	128 + 0	/* 14 */,
	128 + 1	/* 15 */,
	128 + 1	/* 16 */,
	128 + 1	/* 17 */,
	128 + 2	/* 18/00-18/09 */,
	128 + 2	/* 18/10-18/19 */,
	128 + 2	/* 18/20-18/29 */,
	128 + 2	/* 18/30-18/39 */,
	128 + 2	/* 18/40-18/49 */,
	128 + 3	/* 18/50-18/59 */,
	128 + 3	/* 18/60-18/69 */,
	128 + 3	/* 18/70-18/79 */,
	128 + 4	/* 18/80-18/89 */,
	128 + 5	/* 18/90-18/99 */,
	128 + 6	/* 18/100-18/109 */,
	128 + 7	/* 18/110-18/119 */,
	128 + 8	/* 18/120-18/129 */,
	128 + 9	/* 18/130-18/139 */,
	128 + 9	/* 18/140-18/149 */,
	128 + 10	/* 18/150-18/159 */,
	128 + 11	/* 18/160-18/169 */,
	128 + 12	/* 18/170-18/179 */,
	128 + 13	/* 18/180-18/189 */,
	128 + 14	/* 18/190-18/199 */,
	128 + 15	/* 18/200-18/209 */,
	128 + 15	/* 18/210-18/219 */,
	128 + 15	/* 18/220+ */
};


/*
 * Stat Table (STR) -- bonus to dam (plus 128)
 */
const byte adj_str_td[] =
{
	128 + -2	/* 3 */,
	128 + -2	/* 4 */,
	128 + -1	/* 5 */,
	128 + -1	/* 6 */,
	128 + 0	/* 7 */,
	128 + 0	/* 8 */,
	128 + 0	/* 9 */,
	128 + 0	/* 10 */,
	128 + 0	/* 11 */,
	128 + 0	/* 12 */,
	128 + 0	/* 13 */,
	128 + 0	/* 14 */,
	128 + 0	/* 15 */,
	128 + 1	/* 16 */,
	128 + 2	/* 17 */,
	128 + 2	/* 18/00-18/09 */,
	128 + 2	/* 18/10-18/19 */,
	128 + 3	/* 18/20-18/29 */,
	128 + 3	/* 18/30-18/39 */,
	128 + 3	/* 18/40-18/49 */,
	128 + 3	/* 18/50-18/59 */,
	128 + 3	/* 18/60-18/69 */,
	128 + 4	/* 18/70-18/79 */,
	128 + 5	/* 18/80-18/89 */,
	128 + 5	/* 18/90-18/99 */,
	128 + 6	/* 18/100-18/109 */,
	128 + 7	/* 18/110-18/119 */,
	128 + 8	/* 18/120-18/129 */,
	128 + 9	/* 18/130-18/139 */,
	128 + 10	/* 18/140-18/149 */,
	128 + 11	/* 18/150-18/159 */,
	128 + 12	/* 18/160-18/169 */,
	128 + 13	/* 18/170-18/179 */,
	128 + 14	/* 18/180-18/189 */,
	128 + 15	/* 18/190-18/199 */,
	128 + 16	/* 18/200-18/209 */,
	128 + 18	/* 18/210-18/219 */,
	128 + 20	/* 18/220+ */
};


/*
 * Stat Table (DEX) -- bonus to hit (plus 128)
 */
const byte adj_dex_th[] =
{
	128 + -3	/* 3 */,
	128 + -2	/* 4 */,
	128 + -2	/* 5 */,
	128 + -1	/* 6 */,
	128 + -1	/* 7 */,
	128 + 0	/* 8 */,
	128 + 0	/* 9 */,
	128 + 0	/* 10 */,
	128 + 0	/* 11 */,
	128 + 0	/* 12 */,
	128 + 0	/* 13 */,
	128 + 0	/* 14 */,
	128 + 0	/* 15 */,
	128 + 1	/* 16 */,
	128 + 2	/* 17 */,
	128 + 3	/* 18/00-18/09 */,
	128 + 3	/* 18/10-18/19 */,
	128 + 3	/* 18/20-18/29 */,
	128 + 3	/* 18/30-18/39 */,
	128 + 3	/* 18/40-18/49 */,
	128 + 4	/* 18/50-18/59 */,
	128 + 4	/* 18/60-18/69 */,
	128 + 4	/* 18/70-18/79 */,
	128 + 4	/* 18/80-18/89 */,
	128 + 5	/* 18/90-18/99 */,
	128 + 6	/* 18/100-18/109 */,
	128 + 7	/* 18/110-18/119 */,
	128 + 8	/* 18/120-18/129 */,
	128 + 9	/* 18/130-18/139 */,
	128 + 9	/* 18/140-18/149 */,
	128 + 10	/* 18/150-18/159 */,
	128 + 11	/* 18/160-18/169 */,
	128 + 12	/* 18/170-18/179 */,
	128 + 13	/* 18/180-18/189 */,
	128 + 14	/* 18/190-18/199 */,
	128 + 15	/* 18/200-18/209 */,
	128 + 15	/* 18/210-18/219 */,
	128 + 15	/* 18/220+ */
};


/*
 * Stat Table (STR) -- bonus to hit (plus 128)
 */
const byte adj_str_th[] =
{
	128 + -3	/* 3 */,
	128 + -2	/* 4 */,
	128 + -1	/* 5 */,
	128 + -1	/* 6 */,
	128 + 0	/* 7 */,
	128 + 0	/* 8 */,
	128 + 0	/* 9 */,
	128 + 0	/* 10 */,
	128 + 0	/* 11 */,
	128 + 0	/* 12 */,
	128 + 0	/* 13 */,
	128 + 0	/* 14 */,
	128 + 0	/* 15 */,
	128 + 0	/* 16 */,
	128 + 0	/* 17 */,
	128 + 1	/* 18/00-18/09 */,
	128 + 1	/* 18/10-18/19 */,
	128 + 1	/* 18/20-18/29 */,
	128 + 1	/* 18/30-18/39 */,
	128 + 1	/* 18/40-18/49 */,
	128 + 1	/* 18/50-18/59 */,
	128 + 1	/* 18/60-18/69 */,
	128 + 2	/* 18/70-18/79 */,
	128 + 3	/* 18/80-18/89 */,
	128 + 4	/* 18/90-18/99 */,
	128 + 5	/* 18/100-18/109 */,
	128 + 6	/* 18/110-18/119 */,
	128 + 7	/* 18/120-18/129 */,
	128 + 8	/* 18/130-18/139 */,
	128 + 9	/* 18/140-18/149 */,
	128 + 10	/* 18/150-18/159 */,
	128 + 11	/* 18/160-18/169 */,
	128 + 12	/* 18/170-18/179 */,
	128 + 13	/* 18/180-18/189 */,
	128 + 14	/* 18/190-18/199 */,
	128 + 15	/* 18/200-18/209 */,
	128 + 15	/* 18/210-18/219 */,
	128 + 15	/* 18/220+ */
};


/*
 * Stat Table (STR) -- weight limit in deca-pounds
 */
const byte adj_str_wgt[] =
{
	5	/* 3 */,
	6	/* 4 */,
	7	/* 5 */,
	8	/* 6 */,
	9	/* 7 */,
	10	/* 8 */,
	11	/* 9 */,
	12	/* 10 */,
	13	/* 11 */,
	14	/* 12 */,
	15	/* 13 */,
	16	/* 14 */,
	17	/* 15 */,
	18	/* 16 */,
	19	/* 17 */,
	20	/* 18/00-18/09 */,
	22	/* 18/10-18/19 */,
	24	/* 18/20-18/29 */,
	26	/* 18/30-18/39 */,
	28	/* 18/40-18/49 */,
	30	/* 18/50-18/59 */,
	30	/* 18/60-18/69 */,
	30	/* 18/70-18/79 */,
	30	/* 18/80-18/89 */,
	30	/* 18/90-18/99 */,
	30	/* 18/100-18/109 */,
	30	/* 18/110-18/119 */,
	30	/* 18/120-18/129 */,
	30	/* 18/130-18/139 */,
	30	/* 18/140-18/149 */,
	30	/* 18/150-18/159 */,
	30	/* 18/160-18/169 */,
	30	/* 18/170-18/179 */,
	30	/* 18/180-18/189 */,
	30	/* 18/190-18/199 */,
	30	/* 18/200-18/209 */,
	30	/* 18/210-18/219 */,
	30	/* 18/220+ */
};


/*
 * Stat Table (STR) -- weapon weight limit in pounds
 */
const byte adj_str_hold[] =
{
	4	/* 3 */,
	5	/* 4 */,
	6	/* 5 */,
	7	/* 6 */,
	8	/* 7 */,
	10	/* 8 */,
	12	/* 9 */,
	14	/* 10 */,
	16	/* 11 */,
	18	/* 12 */,
	20	/* 13 */,
	22	/* 14 */,
	24	/* 15 */,
	26	/* 16 */,
	28	/* 17 */,
	30	/* 18/00-18/09 */,
	30	/* 18/10-18/19 */,
	35	/* 18/20-18/29 */,
	40	/* 18/30-18/39 */,
	45	/* 18/40-18/49 */,
	50	/* 18/50-18/59 */,
	55	/* 18/60-18/69 */,
	60	/* 18/70-18/79 */,
	65	/* 18/80-18/89 */,
	70	/* 18/90-18/99 */,
	80	/* 18/100-18/109 */,
	80	/* 18/110-18/119 */,
	80	/* 18/120-18/129 */,
	80	/* 18/130-18/139 */,
	80	/* 18/140-18/149 */,
	90	/* 18/150-18/159 */,
	90	/* 18/160-18/169 */,
	90	/* 18/170-18/179 */,
	90	/* 18/180-18/189 */,
	90	/* 18/190-18/199 */,
	100	/* 18/200-18/209 */,
	100	/* 18/210-18/219 */,
	100	/* 18/220+ */
};


/*
 * Stat Table (STR) -- digging value
 */
const byte adj_str_dig[] =
{
	0	/* 3 */,
	0	/* 4 */,
	1	/* 5 */,
	2	/* 6 */,
	3	/* 7 */,
	4	/* 8 */,
	4	/* 9 */,
	5	/* 10 */,
	5	/* 11 */,
	6	/* 12 */,
	6	/* 13 */,
	7	/* 14 */,
	7	/* 15 */,
	8	/* 16 */,
	8	/* 17 */,
	9	/* 18/00-18/09 */,
	10	/* 18/10-18/19 */,
	12	/* 18/20-18/29 */,
	15	/* 18/30-18/39 */,
	20	/* 18/40-18/49 */,
	25	/* 18/50-18/59 */,
	30	/* 18/60-18/69 */,
	35	/* 18/70-18/79 */,
	40	/* 18/80-18/89 */,
	45	/* 18/90-18/99 */,
	50	/* 18/100-18/109 */,
	55	/* 18/110-18/119 */,
	60	/* 18/120-18/129 */,
	65	/* 18/130-18/139 */,
	70	/* 18/140-18/149 */,
	75	/* 18/150-18/159 */,
	80	/* 18/160-18/169 */,
	85	/* 18/170-18/179 */,
	90	/* 18/180-18/189 */,
	95	/* 18/190-18/199 */,
	100	/* 18/200-18/209 */,
	100	/* 18/210-18/219 */,
	100	/* 18/220+ */
};


/*
 * Stat Table (STR) -- help index into the "blow" table
 */
const byte adj_str_blow[] =
{
	3	/* 3 */,
	4	/* 4 */,
	5	/* 5 */,
	6	/* 6 */,
	7	/* 7 */,
	8	/* 8 */,
	9	/* 9 */,
	10	/* 10 */,
	11	/* 11 */,
	12	/* 12 */,
	13	/* 13 */,
	14	/* 14 */,
	15	/* 15 */,
	16	/* 16 */,
	17	/* 17 */,
	20 /* 18/00-18/09 */,
	30 /* 18/10-18/19 */,
	40 /* 18/20-18/29 */,
	50 /* 18/30-18/39 */,
	60 /* 18/40-18/49 */,
	70 /* 18/50-18/59 */,
	80 /* 18/60-18/69 */,
	90 /* 18/70-18/79 */,
	100 /* 18/80-18/89 */,
	110 /* 18/90-18/99 */,
	120 /* 18/100-18/109 */,
	130 /* 18/110-18/119 */,
	140 /* 18/120-18/129 */,
	150 /* 18/130-18/139 */,
	160 /* 18/140-18/149 */,
	170 /* 18/150-18/159 */,
	180 /* 18/160-18/169 */,
	190 /* 18/170-18/179 */,
	200 /* 18/180-18/189 */,
	210 /* 18/190-18/199 */,
	220 /* 18/200-18/209 */,
	230 /* 18/210-18/219 */,
	240 /* 18/220+ */
};


/*
 * Stat Table (DEX) -- index into the "blow" table
 */
const byte adj_dex_blow[] =
{
	0	/* 3 */,
	0	/* 4 */,
	0	/* 5 */,
	0	/* 6 */,
	0	/* 7 */,
	0	/* 8 */,
	0	/* 9 */,
	1	/* 10 */,
	1	/* 11 */,
	1	/* 12 */,
	1	/* 13 */,
	1	/* 14 */,
	1	/* 15 */,
	1	/* 16 */,
	1	/* 17 */,
	1	/* 18/00-18/09 */,
	2	/* 18/10-18/19 */,
	2	/* 18/20-18/29 */,
	2	/* 18/30-18/39 */,
	2	/* 18/40-18/49 */,
	3	/* 18/50-18/59 */,
	3	/* 18/60-18/69 */,
	4	/* 18/70-18/79 */,
	4	/* 18/80-18/89 */,
	5	/* 18/90-18/99 */,
	6	/* 18/100-18/109 */,
	7	/* 18/110-18/119 */,
	8	/* 18/120-18/129 */,
	9	/* 18/130-18/139 */,
	10	/* 18/140-18/149 */,
	11	/* 18/150-18/159 */,
	12	/* 18/160-18/169 */,
	14	/* 18/170-18/179 */,
	16	/* 18/180-18/189 */,
	18	/* 18/190-18/199 */,
	20	/* 18/200-18/209 */,
	20	/* 18/210-18/219 */,
	20	/* 18/220+ */
};


/*
 * Stat Table (DEX) -- chance of avoiding "theft" and "falling"
 */
const byte adj_dex_safe[] =
{
	0	/* 3 */,
	1	/* 4 */,
	2	/* 5 */,
	3	/* 6 */,
	4	/* 7 */,
	5	/* 8 */,
	5	/* 9 */,
	6	/* 10 */,
	6	/* 11 */,
	7	/* 12 */,
	7	/* 13 */,
	8	/* 14 */,
	8	/* 15 */,
	9	/* 16 */,
	9	/* 17 */,
	10	/* 18/00-18/09 */,
	10	/* 18/10-18/19 */,
	15	/* 18/20-18/29 */,
	15	/* 18/30-18/39 */,
	20	/* 18/40-18/49 */,
	25	/* 18/50-18/59 */,
	30	/* 18/60-18/69 */,
	35	/* 18/70-18/79 */,
	40	/* 18/80-18/89 */,
	45	/* 18/90-18/99 */,
	50	/* 18/100-18/109 */,
	60	/* 18/110-18/119 */,
	70	/* 18/120-18/129 */,
	80	/* 18/130-18/139 */,
	90	/* 18/140-18/149 */,
	100	/* 18/150-18/159 */,
	100	/* 18/160-18/169 */,
	100	/* 18/170-18/179 */,
	100	/* 18/180-18/189 */,
	100	/* 18/190-18/199 */,
	100	/* 18/200-18/209 */,
	100	/* 18/210-18/219 */,
	100	/* 18/220+ */
};


/*
 * Stat Table (CON) -- base regeneration rate
 */
const byte adj_con_fix[] =
{
	0	/* 3 */,
	0	/* 4 */,
	0	/* 5 */,
	0	/* 6 */,
	0	/* 7 */,
	0	/* 8 */,
	0	/* 9 */,
	0	/* 10 */,
	0	/* 11 */,
	0	/* 12 */,
	0	/* 13 */,
	1	/* 14 */,
	1	/* 15 */,
	1	/* 16 */,
	1	/* 17 */,
	2	/* 18/00-18/09 */,
	2	/* 18/10-18/19 */,
	2	/* 18/20-18/29 */,
	2	/* 18/30-18/39 */,
	2	/* 18/40-18/49 */,
	3	/* 18/50-18/59 */,
	3	/* 18/60-18/69 */,
	3	/* 18/70-18/79 */,
	3	/* 18/80-18/89 */,
	3	/* 18/90-18/99 */,
	4	/* 18/100-18/109 */,
	4	/* 18/110-18/119 */,
	5	/* 18/120-18/129 */,
	6	/* 18/130-18/139 */,
	6	/* 18/140-18/149 */,
	7	/* 18/150-18/159 */,
	7	/* 18/160-18/169 */,
	8	/* 18/170-18/179 */,
	8	/* 18/180-18/189 */,
	8	/* 18/190-18/199 */,
	9	/* 18/200-18/209 */,
	9	/* 18/210-18/219 */,
	9	/* 18/220+ */
};


/*
 * Stat Table (CON) -- extra half-hitpoints per level (plus 128)
 */
const byte adj_con_mhp[] =
{
	128 + -5	/* 3 */,
	128 + -3	/* 4 */,
	128 + -2	/* 5 */,
	128 + -1	/* 6 */,
	128 + 0	/* 7 */,
	128 + 0	/* 8 */,
	128 + 0	/* 9 */,
	128 + 0	/* 10 */,
	128 + 0	/* 11 */,
	128 + 0	/* 12 */,
	128 + 0	/* 13 */,
	128 + 0	/* 14 */,
	128 + 1	/* 15 */,
	128 + 1	/* 16 */,
	128 + 2	/* 17 */,
	128 + 3	/* 18/00-18/09 */,
	128 + 4	/* 18/10-18/19 */,
	128 + 4	/* 18/20-18/29 */,
	128 + 4	/* 18/30-18/39 */,
	128 + 4	/* 18/40-18/49 */,
	128 + 5	/* 18/50-18/59 */,
	128 + 6	/* 18/60-18/69 */,
	128 + 7	/* 18/70-18/79 */,
	128 + 8	/* 18/80-18/89 */,
	128 + 9	/* 18/90-18/99 */,
	128 + 10	/* 18/100-18/109 */,
	128 + 11	/* 18/110-18/119 */,
	128 + 12	/* 18/120-18/129 */,
	128 + 13	/* 18/130-18/139 */,
	128 + 14	/* 18/140-18/149 */,
	128 + 15	/* 18/150-18/159 */,
	128 + 16	/* 18/160-18/169 */,
	128 + 18	/* 18/170-18/179 */,
	128 + 20	/* 18/180-18/189 */,
	128 + 22	/* 18/190-18/199 */,
	128 + 25	/* 18/200-18/209 */,
	128 + 25	/* 18/210-18/219 */,
	128 + 25	/* 18/220+ */
};


/*
 * This table is used to help calculate the number of blows the player can
 * make in a single round of attacks (one player turn) with a normal weapon.
 *
 * This number ranges from a single blow/round for weak players to up to six
 * blows/round for powerful warriors.
 *
 * Note that certain artifacts and ego-items give "bonus" blows/round.
 *
 * First, from the player class, we extract some values:
 *
 *    Warrior --> num = 6; mul = 5; div = MAX(30, weapon_weight);
 *    Mage    --> num = 4; mul = 2; div = MAX(40, weapon_weight);
 *    Priest  --> num = 5; mul = 3; div = MAX(35, weapon_weight);
 *    Rogue   --> num = 5; mul = 3; div = MAX(30, weapon_weight);
 *    Ranger  --> num = 5; mul = 4; div = MAX(35, weapon_weight);
 *    Paladin --> num = 5; mul = 4; div = MAX(30, weapon_weight);
 *
 * New classes:
 *    Thief   --> num = 5; mul = 4; div = MAX(30, weapon_weight);
 *    Archer  --> num = 5; mul = 3; div = MAX(30, weapon_weight);
 * To get "P", we look up the relevant "adj_str_blow[]" (see above),
 * multiply it by "mul", and then divide it by "div", rounding down.
 *
 * To get "D", we look up the relevant "adj_dex_blow[]" (see above),
 * note especially column 6 (DEX 18/101) and 11 (DEX 18/150).
 *
 * The player gets "blows_table[P][D]" blows/round, as shown below,
 * up to a maximum of "num" blows/round, plus any "bonus" blows/round.
 */

const byte blows_table[12][12] =
{
	/* P/D */
	/* 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11+ */

	/* 0  */
	{  1,   1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   3 },

	/* 1  */
	{  1,   1,   1,   1,   2,   2,   3,   3,   3,   4,   4,   4 },

	/* 2  */
	{  1,   1,   2,   2,   3,   3,   4,   4,   4,   5,   5,   5 },

	/* 3  */
	{  1,   2,   2,   3,   3,   4,   4,   4,   5,   5,   5,   5 },

	/* 4  */
	{  1,   2,   2,   3,   3,   4,   4,   5,   5,   5,   5,   5 },

	/* 5  */
	{  2,   2,   3,   3,   4,   4,   5,   5,   5,   5,   5,   6 },

	/* 6  */
	{  2,   2,   3,   3,   4,   4,   5,   5,   5,   5,   5,   6 },

	/* 7  */
	{  2,   3,   3,   4,   4,   4,   5,   5,   5,   5,   5,   6 },

	/* 8  */
	{  3,   3,   3,   4,   4,   4,   5,   5,   5,   5,   6,   6 },

	/* 9  */
	{  3,   3,   4,   4,   4,   4,   5,   5,   5,   5,   6,   6 },

	/* 10 */
	{  3,   3,   4,   4,   4,   4,   5,   5,   5,   6,   6,   6 },

	/* 11+ */
	{  3,   3,   4,   4,   4,   4,   5,   5,   6,   6,   6,   6 },
};



#if 0

/*
 * This is the "old" table used to calculate multiple blows.
 *
 * Note that this table used a different indexing scheme to determine "P"
 */

byte old_blows_table[11][12] =
{
	/* P/D */
	/* 3,  10, /01, /50, /90,/100,/101,/110,/120,/130,/140,/150 */

	/* 0+ */
	{  1,   1,   1,   1,   1,   1,   2,   2,   2,   2,   2,   3},

	/* 2+ */
	{  1,   1,   1,   1,   2,   2,   3,   3,   3,   3,   3,   4},

	/* 3+ */
	{  1,   1,   1,   2,   2,   3,   4,   4,   4,   4,   4,   5},

	/* 4+ */
	{  1,   1,   2,   2,   3,   3,   4,   4,   4,   5,   5,   5},

	/* 6+ */
	{  1,   2,   2,   3,   3,   4,   4,   4,   5,   5,   5,   5},

	/* 8+ */
	{  1,   2,   2,   3,   4,   4,   4,   5,   5,   5,   5,   5},

	/* 10+ */
	{  2,   2,   3,   3,   4,   4,   5,   5,   5,   5,   5,   6},

	/* 13+ */
	{  2,   3,   3,   3,   4,   4,   5,   5,   5,   5,   5,   6},

	/* 15+ */
	{  3,   3,   3,   4,   4,   4,   5,   5,   5,   5,   6,   6},

	/* 18+ */
	{  3,   3,   3,   4,   4,   4,   5,   5,   5,   5,   6,   6},

	/* 20+ */
	{  3,   3,   4,   4,   4,   4,   5,   5,   5,   6,   6,   6}
};

#endif


/*
 * This table allows quick conversion from "speed" to "energy"
 * The basic function WAS ((S>=110) ? (S-110) : (100 / (120-S)))
 * Note that table access is *much* quicker than computation.
 *
 * Note that the table has been changed at high speeds.  From
 * "Slow (-40)" to "Fast (+30)" is pretty much unchanged, but
 * at speeds above "Fast (+30)", one approaches an asymptotic
 * effective limit of 50 energy per turn.  This means that it
 * is relatively easy to reach "Fast (+30)" and get about 40
 * energy per turn, but then speed becomes very "expensive",
 * and you must get all the way to "Fast (+50)" to reach the
 * point of getting 45 energy per turn.  After that point,
 * furthur increases in speed are more or less pointless,
 * except to balance out heavy inventory.
 *
 * Note that currently the fastest monster is "Fast (+30)".
 *
 * It should be possible to lower the energy threshhold from
 * 100 units to 50 units, though this may interact badly with
 * the (compiled out) small random energy boost code.  It may
 * also tend to cause more "clumping" at high speeds.
 */
const byte extract_energy[200] =
{
	/* Slow */     1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	/* Slow */     1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	/* Slow */     1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	/* Slow */     1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	/* Slow */     1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	/* Slow */     1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	/* S-50 */     1,  1,  1,  1,  1,  1,  1,  1,  1,  1,
	/* S-40 */     2,  2,  2,  2,  2,  2,  2,  2,  2,  2,
	/* S-30 */     2,  2,  2,  2,  2,  2,  2,  3,  3,  3,
	/* S-20 */     3,  3,  3,  3,  3,  4,  4,  4,  4,  4,
	/* S-10 */     5,  5,  5,  5,  6,  6,  7,  7,  8,  9,
	/* Norm */    10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
	/* F+10 */    20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
	/* F+20 */    30, 31, 32, 33, 34, 35, 36, 36, 37, 37,
	/* F+30 */    38, 38, 39, 39, 40, 40, 40, 41, 41, 41,
	/* F+40 */    42, 42, 42, 43, 43, 43, 44, 44, 44, 44,
	/* F+50 */    45, 45, 45, 45, 45, 46, 46, 46, 46, 46,
	/* F+60 */    47, 47, 47, 47, 47, 48, 48, 48, 48, 48,
	/* F+70 */    49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
	/* Fast */    49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
};







/*
 * Base experience levels, may be adjusted up for race and/or class
 */
const s32b player_exp[PY_MAX_LEVEL] =
{
	10,
	25,
	45,
	70,
	100,
	140,
	200,
	280,
	380,
	500,
	650,
	850,
	1100,
	1400,
	1800,
	2300,
	2900,
	3600,
	4400,
	5400,
	6800,
	8400,
	10200,
	12500,
	17500,
	25000,
	35000L,
	50000L,
	75000L,
	100000L,
	150000L,
	200000L,
	275000L,
	350000L,
	450000L,
	550000L,
	700000L,
	850000L,
	1000000L,
	1250000L,
	1500000L,
	1800000L,
	2100000L,
	2400000L,
	2700000L,
	3000000L,
	3500000L,
	4000000L,
	4500000L,
	5000000L
};


/*
 * Player Sexes
 *
 *	Title,
 *	Winner
 */
const player_sex sex_info[MAX_SEXES] =
{
	{
		"Female",
		"Queen"
	},

	{
		"Male",
		"King"
	}
};





/*
 * Hack -- the "basic" color names (see "TERM_xxx")
 */
const cptr color_names[16] =
{
	"Dark",
	"White",
	"Slate",
	"Orange",
	"Red",
	"Green",
	"Blue",
	"Umber",
	"Light Dark",
	"Light Slate",
	"Violet",
	"Yellow",
	"Light Red",
	"Light Green",
	"Light Blue",
	"Light Umber",
};


/*
 * Abbreviations of healthy stats
 */
const cptr stat_names[6] =
{
	"STR: ", "INT: ", "WIS: ", "DEX: ", "CON: ", "CHR: "
};

/*
 * Abbreviations of damaged stats
 */
const cptr stat_names_reduced[6] =
{
	"Str: ", "Int: ", "Wis: ", "Dex: ", "Con: ", "Chr: "
};

/*
 * Abbreviations of damaged stats -- no sidebar
 */
const cptr stat_names_reduced_short[6] =
{
	"Str", "Int", "Wis", "Dex", "Con", "Chr"
};

/*
 * Certain "screens" always use the main screen, including News, Birth,
 * Dungeon, Tomb-stone, High-scores, Macros, Colors, Visuals, Options.
 *
 * Later, special flags may allow sub-windows to "steal" stuff from the
 * main window, including File dump (help), File dump (artifacts, uniques),
 * Character screen, Small scale map, Previous Messages, Store screen, etc.
 */
const cptr window_flag_desc[32] =
{
	"Display inven/equip",
	"Display equip/inven",
	"Display player (basic)",
	"Display player (extra)",
	"Display player (compact)",
	"Display player (status)",
	"Display messages",
	"Display dungeon map",
	"Display overhead view",
	"Display monster recall",
	"Display object recall",
	"Display feature recall (not used)",
	"Display room description",
	"Display snap-shot (not used)",
	"Display visible monsters",
	"Display help (not used)",
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};


/*
 * Options -- textual names (where defined)
 */
const cptr option_text[OPT_MAX] =
{
	"rogue_like_commands",		/* OPT_rogue_like_commands */
	"quick_messages",			/* OPT_quick_messages */
	"floor_query_flag",			/* OPT_floor_query_flag */
	"carry_query_flag",			/* OPT_carry_query_flag */
	"use_old_target",			/* OPT_use_old_target */
	"always_pickup",			/* OPT_always_pickup */
	"always_repeat",			/* OPT_always_repeat */
	"depth_in_feet",			/* OPT_depth_in_feet */
	"stack_force_notes",		/* OPT_stack_force_notes */
	"stack_force_costs",		/* OPT_stack_force_costs */
	"show_labels",				/* OPT_show_labels */
	"show_weights",				/* OPT_show_weights */
	"show_choices",				/* OPT_show_choices */
	"show_details",				/* OPT_show_details */
	"ring_bell",				/* OPT_ring_bell */
	"show_flavors",				/* OPT_flavors */
	"run_ignore_stairs",		/* OPT_run_ignore_stairs */
	"run_ignore_doors",			/* OPT_run_ignore_doors */
	"run_cut_corners",			/* OPT_run_cut_corners */
	"run_use_corners",			/* OPT_run_use_corners */
	"disturb_move",				/* OPT_disturb_move */
	"disturb_near",				/* OPT_disturb_near */
	"disturb_panel",			/* OPT_disturb_panel */
	"disturb_state",			/* OPT_disturb_state */
	"disturb_minor",			/* OPT_disturb_minor */
	"view_flavors",				/* OPT_view_flavors */
	"disturb_new",				/* OPT_disturb_new */
	"verify_safe",				/* OPT_verify_safe */
	"verify_destroy",			/* OPT_verify_destroy */
	"verify_special",			/* OPT_verify_special */
	"allow_quantity",			/* OPT_allow_quantity */
	"easy_corpses",			/* OPT_easy_corpses */
	NULL,				/* xxx */
	NULL,				/* xxx */
	NULL,						/* xxx testing_stack */
	NULL,						/* xxx testing_carry */
	"expand_look",				/* OPT_expand_look */
	"expand_list",				/* OPT_expand_list */
	"view_perma_grids",			/* OPT_view_perma_grids */
	"view_torch_grids",			/* OPT_view_torch_grids */
	"dungeon_align",			/* OPT_dungeon_align */
	"dungeon_stair",			/* OPT_dungeon_stair */
	"view_unsafe_grids",			/* OPT_view_unsafe_grids */
	"view_detect_grids",			/* OPT_view_detect_grids */
	"run_ignore_floors",			/* OPT_run_ignore_floors */
	NULL,					/* xxx track_target */
	NULL,					/* xxx smart_learn */
	"smart_cheat",				/* OPT_smart_cheat */
	"view_reduce_lite",			/* OPT_view_reduce_lite */
	"hidden_player",			/* OPT_hidden_player */
	"avoid_abort",				/* OPT_avoid_abort */
	"avoid_other",				/* OPT_avoid_other */
	"flush_failure",			/* OPT_flush_failure */
	"flush_disturb",			/* OPT_flush_disturb */
	NULL,						/* xxx flush_command */
	"fresh_before",				/* OPT_fresh_before */
	"fresh_after",				/* OPT_fresh_after */
	"view_player_lite",		/* OPT_view_player_lite */
	"compress_savefile",		/* OPT_compress_savefile */
	"hilite_player",			/* OPT_hilite_player */
	"view_yellow_lite",			/* OPT_view_yellow_lite */
	"view_bright_lite",			/* OPT_view_bright_lite */
	"view_granite_lite",		/* OPT_view_granite_lite */
	"view_special_lite",		/* OPT_view_special_lite */
	"easy_open",				/* OPT_easy_open */
	"easy_alter",				/* OPT_easy_alter */
	"easy_floor",				/* OPT_easy_floor */
	"show_piles",				/* OPT_show_piles */
	"center_player",			/* OPT_center_player */
	"run_avoid_center",			/* OPT_run_avoid_center */
	"scroll_target",			/* OPT_scroll_target */
	"auto_more",				/* OPT_auto_more */
	"auto_display_lists",			/* OPT_auto_display_lists */
	"toggle_xp",				/* OPT_toggle_xp */
	"stack_force_charges",						/* xxx */
	"stack_force_times",						/* xxx */
	NULL,						/* xxx */
	"room_descriptions",						/* xxx */
	"room_names",						/* xxx */
	"verify_mana",						/* xxx */
	"reseed_artifacts",						/* xxx */
        "easy_autos",                                      /* xxx */
	"easy_search",						/* xxx */
	NULL,		   /* xxx */
	"view_glowing_lite",			/* xxx */
	"view_surface_lite",			/* OPT_view_surface_lite */
	NULL,		   /* xxx */
	"show_sidebar",						/* xxx */
	"show_itemlist",						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,					   /* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,					   /* xxx */
	NULL,					  /* xxx */
	NULL,						/* xxx */
	NULL,					   /* xxx */
	NULL,					   /* xxx */
	NULL,					   /* xxx */
	NULL,					   /* xxx */
	NULL,					   /* xxx */
	NULL,					   /* xxx */
	NULL,					   /* xxx */
	NULL,					   /* xxx */
	"birth_point_based",		/* OPT_birth_point_based */
	"birth_auto_roller",		/* OPT_birth_auto_roller */
	"birth_maximize_race",			/* OPT_birth_maximize_race */
	"birth_preserve",			/* OPT_birth_preserve */
	"birth_ironman",			/* OPT_birth_ironman */
	"birth_no_stores",			/* OPT_birth_no_stores */
	"birth_no_artifacts",		/* OPT_birth_no_artifacts */
	"birth_rand_artifacts",		/* OPT_birth_rand_artifacts */
	"birth_campaign",			       /* xxx */
	"birth_no_stacking",			/* xxx */
	"birth_haggle",						/* OPT_birth_haggle */
	"birth_scum",						/* OPT_birth_scum */
	"birth_maximize_class",			/* OPT_birth_maximize_class */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	"cheat_peek",				/* OPT_cheat_peek */
	"cheat_hear",				/* OPT_cheat_hear */
	"cheat_room",				/* OPT_cheat_room */
	"cheat_xtra",				/* OPT_cheat_xtra */
	"cheat_know",				/* OPT_cheat_know */
	"cheat_live",				/* OPT_cheat_live */
	"cheat_lore",						/* xxx */
	"cheat_auto",					   /* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	"adult_point_based",		/* OPT_adult_point_based */
	"adult_auto_roller",		/* OPT_adult_auto_roller */
	"adult_maximize_race",			/* OPT_adult_maximize */
	"adult_preserve",			/* OPT_adult_preserve */
	"adult_ironman",			/* OPT_adult_ironman */
	"adult_no_stores",			/* OPT_adult_no_stores */
	"adult_no_artifacts",		/* OPT_adult_no_artifacts */
	"adult_rand_artifacts",		/* OPT_adult_rand_artifacts */
	"adult_campaign",				/* xxx */
	"adult_no_stacking",			/* xxx */
	"adult_haggle",						/* OPT_adult_haggle */
	"adult_scum",						/* OPT_adult_scum */
	"adult_maximize_class",			/* OPT_adult_maximize_class */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	"score_peek",				/* OPT_score_peek */
	"score_hear",				/* OPT_score_hear */
	"score_room",				/* OPT_score_room */
	"score_xtra",				/* OPT_score_xtra */
	"score_know",				/* OPT_score_know */
	"score_live",				/* OPT_score_live */
	"score_lore",					   /* xxx */
	"score_auto",					   /* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL,						/* xxx */
	NULL						/* xxx */
};


/*
 * Options -- descriptions (where defined)
 */
const cptr option_desc[OPT_MAX] =
{
	"Rogue-like commands",						/* OPT_rogue_like_commands */
	"Activate quick messages",					/* OPT_quick_messages */
	"Prompt for floor item selection",			/* OPT_floor_query_flag */
	"Prompt before picking things up",			/* OPT_carry_query_flag */
	"Use old target by default",				/* OPT_use_old_target */
	"Pick things up by default",				/* OPT_always_pickup */
	"Repeat obvious commands",					/* OPT_always_repeat */
	"Show dungeon level in feet",				/* OPT_depth_in_feet */
	"Merge inscriptions when stacking",			/* OPT_stack_force_notes */
	"Merge discounts when stacking",			/* OPT_stack_force_costs */
	"Show labels in equipment listings",		/* OPT_show_labels */
	"Show weights in all object listings",		/* OPT_show_weights */
	"Show choices in inven/equip windows",		/* OPT_show_choices */
	"Show details in monster descriptions",		/* OPT_show_details */
	"Audible bell (on errors, etc)",			/* OPT_ring_bell */
	"Show flavors in object descriptions",		/* OPT_show_flacors */
	"When running, ignore stairs",				/* OPT_run_ignore_stairs */
	"When running, ignore doors",				/* OPT_run_ignore_doors */
	"When running, cut corners",				/* OPT_run_cut_corners */
	"When running, use corners",				/* OPT_run_use_corners */
	"Disturb whenever any monster moves",		/* OPT_disturb_move */
	"Disturb whenever viewable monster moves",	/* OPT_disturb_near */
	"Disturb whenever map panel changes",		/* OPT_disturb_panel */
	"Disturb whenever player state changes",	/* OPT_disturb_state */
	"Disturb whenever boring things happen",	/* OPT_disturb_minor */
	"Show flavors in object graphics",	/* OPT_view_flavors */
	"Disturb whenever a new monster race seen",	/* OPT_disturb_new */
	"Verify whenever you leave a safe grid",		/* OPT_verify_safe */
	"Verify destruction of objects",			/* OPT_verify_destroy */
	"Verify use of special commands",			/* OPT_verify_special */
	"Allow quantity specification",				/* OPT_allow_quantity */
	"Ignore corpses by default",				/* OPT_easy_corpses */
	NULL,				/* xxx */
	NULL,				/* xxx */
	NULL,										/* xxx testing_stack */
	NULL,										/* xxx testing_carry */
	"Expand the power of the look command",		/* OPT_expand_look */
	"Expand the power of the list commands",	/* OPT_expand_list */
	"Map remembers all perma-lit grids",		/* OPT_view_perma_grids */
	"Map remembers all torch-lit grids",		/* OPT_view_torch_grids */
	"Generate dungeons with aligned rooms",		/* OPT_dungeon_align */
	"Generate dungeons with connected stairs",	/* OPT_dungeon_stair */
	"Mark where you have detected traps",		/* OPT_view_unsafe_grids */
	"Mark where you have detected monsters",	/* OPT_view_unsafe_grids */
	"When running, ignore interesting floors",				/* OPT_run_ignore_stairs */
	NULL,								/* xxx */
	NULL,								/* xxx */
	NULL,								/* xxx*/
	"Reduce lite-radius when running",			/* OPT_view_reduce_lite */
	"Hide player symbol when running",			/* OPT_hidden_player */
	"Avoid checking for user abort",			/* OPT_avoid_abort */
	"Avoid processing special colors",			/* OPT_avoid_other */
	"Flush input on various failures",			/* OPT_flush_failure */
	"Flush input whenever disturbed",			/* OPT_flush_disturb */
	NULL,										/* xxx */
	"Flush output before every command",		/* OPT_fresh_before */
	"Flush output after various things",		/* OPT_fresh_after */
	"Use special colors for player grid",			/* OPT_view_player_lite */
	"Compress messages in savefiles",			/* OPT_compress_savefile */
	"Hilite the player with the cursor",		/* OPT_hilite_player */
	"Use special colors for torch lite",		/* OPT_view_yellow_lite */
	"Use special colors for field of view",		/* OPT_view_bright_lite */
	"Use special colors for wall grids",		/* OPT_view_granite_lite */
	"Use special colors for floor grids",		/* OPT_view_special_lite */
	"Open/Disarm/Close without direction",		/* OPT_easy_open */
	"Open/Disarm doors/traps on movement",		/* OPT_easy_alter */
	"Display floor stacks in a list",   		/* OPT_easy_floor */
	"Show stacks using special attr/char",		/* OPT_show_piles */
	"Center map continuously (very slow)",		/* OPT_center_player */
	"Avoid centering while running",			/* OPT_run_avoid_center */
	"Scroll map while targetting",			/* OPT_scroll_target */
	"Automatically clear '-more-' prompts",		/* OPT_auto_more */
	"Automatically display drop-down lists",	/* OPT_auto_display_lists */
	"Reverse experience display",				/* OPT_toggle_xp */
	"Merge charges when stacking",				/* OPT_stack_force_charges */
	"Merge timeouts when stacking",			/* OPT_stack_force_timeouts */
	NULL,							/* xxx */
	"Display room descriptions",				/* OPT_room_descriptions */
	"Display room names",					/* OPT_room_names */
	"Verify critical mana",					/* xxx */
	"Reseed random artifacts on death",			/* xxx */
	"Automatically inscribe all objects",			/* xxx */
	"Start searching if not disturbed",			/* xxx */
	"Save new features in save-file",			/* xxx */
	"Use special colours for glowing lite (slow)",	/* OPT_view_glowing_lite */
	"Use special colours for surface lite",		/* OPT_view_surface_lite */
	"Learn more than 64 spells",				/* xxx */
	"Display stats in main window",			/* OPT_show_sidebar */							/* xxx */
	"Display all items in main window",		/* OPT_show_itemlist */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,								/* xxx */
	NULL,								/* xxx */
	NULL,							/* xxx */
	NULL,						/* xxx */
	NULL,							/* xxx */
	NULL,							/* xxx */
	NULL,						/* xxx */
	NULL,					  /* xxx */
	NULL,							/* xxx */
	NULL,						/* xxx */
	NULL,							/* xxx */
	NULL,						/* xxx */
	NULL,							/* xxx */
	NULL,							/* xxx */
	NULL,						/* xxx */
	NULL,							/* xxx */
	NULL,								/* xxx */
	NULL,								/* xxx */
	NULL,								/* xxx */
	NULL,							/* xxx */
	NULL,							/* xxx */
	NULL,					       /* xxx */
	NULL,								/* xxx */
	NULL,									   /* xxx */
	NULL,
	NULL,									   /* xxx */
	NULL,									   /* xxx */
	NULL,									   /* xxx */
	NULL,									   /* xxx */
	NULL,									   /* xxx */
	NULL,									   /* xxx */
	"Birth: Allow purchase of stats using points",	/* OPT_birth_point_based */
	"Birth: Allow specification of minimal stats",	/* OPT_birth_auto_roller */
	"Birth: Maximize effect of race bonuses",	/* OPT_birth_maximize_race */
	"Birth: Preserve artifacts when leaving level",	/* OPT_birth_preserve */
	"Birth: Restrict the use of stairs/recall",	/* OPT_birth_ironman */
	"Birth: Restrict the use of stores/home",	/* OPT_birth_no_stores */
	"Birth: Restrict creation of artifacts",	/* OPT_birth_no_artifacts */
	"Birth: Randomize all of the artifacts",       /* OPT_birth_rand_artifacts */
	"Birth: Play in Lord of the Rings campaign",   /* OPT_birth_campaign */
	"Birth: Don't stack objects on the floor",	/* OPT_birth_no_stacking */
	"Birth: Haggle in stores",			/* OPT_birth_haggle */									/* xxx */
	"Birth: Scum for good levels",			/* OPT_birth_scum */
	"Birth: Maximize effect of class bonuses",	/* OPT_birth_maximize_class */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	"Cheat: Peek into object creation",			/* OPT_cheat_peek */
	"Cheat: Peek into monster creation",		/* OPT_cheat_hear */
	"Cheat: Peek into dungeon creation",		/* OPT_cheat_room */
	"Cheat: Peek into something else",			/* OPT_cheat_xtra */
	"Cheat: Know complete monster info",		/* OPT_cheat_know */
	"Cheat: Allow player to avoid death",		/* OPT_cheat_live */
	"Cheat: Know complete artifact/ego info",						/* xxx */
	"Cheat: Auto-inscribe items as if known",									   /* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	"Adult: Allow purchase of stats using points",	/* OPT_adult_point_based */
	"Adult: Allow specification of minimal stats",	/* OPT_adult_auto_roller */
	"Adult: Maximize effect of race bonuses",	/* OPT_adult_maximize */
	"Adult: Preserve artifacts when leaving level",	/* OPT_adult_preserve */
	"Adult: Restrict the use of stairs/recall",	/* OPT_adult_ironman */
	"Adult: Restrict the use of stores/home",	/* OPT_adult_no_stores */
	"Adult: Restrict creation of artifacts",	/* OPT_adult_no_artifacts */
	"Adult: Randomize all of the artifacts",       /* OPT_adult_rand_artifacts */
	"Adult: Play in Lord of the Rings campaign",   /* OPT_adult_campaign */
	"Adult: Don't stack objects on the floor",	/* OPT_adult_no_stacking */
	"Adult: Haggle in stores",			/* OPT_adult_haggle */									/* xxx */
	"Adult: Scum for good levels",			/* OPT_adult_scum */
	"Adult: Maximize effect of class bonuses",	/* OPT_adult_maximize_class */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	"Score: Peek into object creation",					/* OPT_score_peek */
	"Score: Peek into monster creation",				/* OPT_score_hear */
	"Score: Peek into dungeon creation",				/* OPT_score_room */
	"Score: Peek into something else",/* OPT_score_xtra */
	"Score: Know complete monster info",		/* OPT_score_know */
	"Score: Allow player to avoid death",		/* OPT_score_live */
	"Score: Know complete artifact/ego info",				/* xxx */
	"Score: Auto-inscribe items as if known",				/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL,										/* xxx */
	NULL										/* xxx */
};


/*
 * Options -- normal values
 */
const bool option_norm[OPT_MAX] =
{
	FALSE,		/* OPT_rogue_like_commands */
	TRUE,		/* OPT_quick_messages */
	FALSE,		/* OPT_floor_query_flag */
	TRUE,		/* OPT_carry_query_flag */
	FALSE,		/* OPT_use_old_target */
	TRUE,		/* OPT_always_pickup */
	FALSE,		/* OPT_always_repeat */
	FALSE,		/* OPT_depth_in_feet */
	FALSE,		/* OPT_stack_force_notes */
	FALSE,		/* OPT_stack_force_costs */
	TRUE,		/* OPT_show_labels */
	TRUE,		/* OPT_show_weights */
	TRUE,		/* OPT_show_choices */
	TRUE,		/* OPT_show_details */
	TRUE,		/* OPT_ring_bell */
	TRUE,		/* OPT_show_flavors */
	TRUE,		/* OPT_run_ignore_stairs */
	TRUE,		/* OPT_run_ignore_doors */
	TRUE,		/* OPT_run_cut_corners */
	TRUE,		/* OPT_run_use_corners */
	TRUE,		/* OPT_disturb_move */
	TRUE,		/* OPT_disturb_near */
	TRUE,		/* OPT_disturb_panel */
	TRUE,		/* OPT_disturb_state */
	TRUE,		/* OPT_disturb_minor */
	TRUE,		/* OPT_view_flavors */
	TRUE,		/* OPT_disturb_new */
	FALSE,		/* OPT_verify_safe */
	TRUE,		/* OPT_verify_destroy */
	TRUE,		/* OPT_verify_special */
	TRUE,		/* OPT_allow_quantity */
	TRUE,		/* OPT_easy_corpses */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	TRUE,		/* OPT_expand_look */
	TRUE,		/* OPT_expand_list */
	TRUE,		/* OPT_view_perma_grids */
	FALSE,		/* OPT_view_torch_grids */
	TRUE,		/* OPT_dungeon_align */
	TRUE,		/* OPT_dungeon_stair */
	TRUE,		/* OPT_view_unsafe_grids */
	TRUE,		/* OPT_view_detect_grids */
	TRUE,		/* OPT_run_ignore_floors */
	FALSE,		/* xxx track_target */
	FALSE,		/* xxx smart_learn */
	FALSE,		/* OPT_smart_cheat */
	FALSE,		/* OPT_view_reduce_lite */
	FALSE,		/* OPT_hidden_player */
	FALSE,		/* OPT_avoid_abort */
	FALSE,		/* OPT_avoid_other */
	TRUE,		/* OPT_flush_failure */
	FALSE,		/* OPT_flush_disturb */
	FALSE,		/* xxx */
	TRUE,		/* OPT_fresh_before */
	FALSE,		/* OPT_fresh_after */
	TRUE,		/* OPT_view_player_lite */
	TRUE,		/* OPT_compress_savefile */
	FALSE,		/* OPT_hilite_player */
	TRUE,		/* OPT_view_yellow_lite */
	TRUE,		/* OPT_view_bright_lite */
	TRUE,		/* OPT_view_granite_lite */
	TRUE,		/* OPT_view_special_lite */
	FALSE,		/* OPT_easy_open */
	FALSE,		/* OPT_easy_alter */
	FALSE,		/* OPT_easy_floor */
	FALSE,		/* OPT_show_piles */
	FALSE,		/* OPT_center_player */
	FALSE,		/* OPT_run_avoid_center */
	FALSE,		/* OPT_scroll_target */
	FALSE,		/* OPT_auto_more */
	TRUE,		/* OPT_auto_display_lists */
	TRUE,		/* OPT_toggle_xp */
	FALSE,	  /* OPT_stack_force_charges */
	FALSE,	  /* OPT_stack_force_times */
	FALSE,	   /* xxx */
	FALSE,	   /* OPT_room_descriptions */
	TRUE,	   /* OPT_room_names */
	FALSE,	  /* OPT_verify_mana */
	TRUE,		/* OPT_reseed_artifacts */
      FALSE,	   /* OPT_easy_autos */
	FALSE,		/* OPT_easy_search */
	FALSE,	  /* xxx */
	FALSE,		/* OPT_view_glowing_lite */
	FALSE,		/* OPT_view_surface_lite */
	FALSE,	  /* xxx */
	FALSE,		/* OPT_show_sidebar */
	FALSE,		/* OPT_show_itemlist */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,	  /* OPT_variant_town */
	FALSE,	   /* OPT_variant_mushroom */
	FALSE,	   /* OPT_variant_mon_hit_trap */
	FALSE,	  /* OPT_variant_room_info */
	FALSE,	   /* OPT_variant_free_stats */
	FALSE,	   /* OPT_variant_fast_kills */
	FALSE,	   /* OPT_variant_scale_damage */
	FALSE,	   /* OPT_variant_scale_hp */
	FALSE,	  /* OPT_variant_charge_stacks */
	FALSE,	   /* OPT_variant_oos_summons */
	FALSE,	   /* OPT_variant_oos_teleports */
	FALSE,	   /* OPT_variant_oos_heals */
	FALSE,	   /* OPT_variant_oos_xtra */
	FALSE,	   /* OPT_variant_hurt_feats */
	FALSE,	   /* OPT_variant_lake_feats */
	FALSE,	   /* OPT_variant_big_feats */
	FALSE,	   /* OPT_variant_new_feats */
	FALSE,	  /* OPT_variant_learn_id */
	FALSE,	  /* OPT_variant_guess_id */
	FALSE,	  /* OPT_variant_usage_id */
	FALSE,	   /* OPT_variant_great_id */
	FALSE,	   /* OPT_variant_dis_attacks */
	FALSE,	  /* OPT_variant_time_stacks */
	FALSE,		/* OPT_variant_many_rings */
	FALSE,	  /* OPT_variant_fast_floor */
	FALSE,	   /* OPT_variant_fast_equip */
	FALSE,	  /* OPT_variant_belt_slot */
	FALSE,	  /* OPT_variant_fast_moves */
	FALSE,	  /* OPT_variant_unsummon */
	FALSE,	  /* OPT_variant_friendly */
	FALSE,	  /* OPT_variant_more_spells */
	FALSE,	  /* OPT_variant_drop_body */
	FALSE,		/* OPT_birth_point_based */
	FALSE,		/* OPT_birth_auto_roller */
	TRUE,		/* OPT_birth_maximize_race */
	TRUE,		/* OPT_birth_preserve */
	FALSE,		/* OPT_birth_ironman */
	FALSE,		/* OPT_birth_no_stores */
	FALSE,		/* OPT_birth_no_artifacts */
	FALSE,		/* OPT_birth_rand_artifacts */
	TRUE,	  /* OPT_birth_campaign */
	FALSE,		/* OPT_birth_haggle */
	FALSE,		/* OPT_birth_scum */
	TRUE,		/* OPT_birth_maximise_class */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* OPT_cheat_peek */
	FALSE,		/* OPT_cheat_hear */
	FALSE,		/* OPT_cheat_room */
	FALSE,		/* OPT_cheat_xtra */
	FALSE,		/* OPT_cheat_know */
	FALSE,		/* OPT_cheat_live */
	FALSE,	  /* OPT_cheat_auto */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* OPT_adult_point_based */
	FALSE,		/* OPT_adult_auto_roller */
	TRUE,		/* OPT_adult_maximize_race */
	TRUE,		/* OPT_adult_preserve */
	FALSE,		/* OPT_adult_ironman */
	FALSE,		/* OPT_adult_no_stores */
	FALSE,		/* OPT_adult_no_artifacts */
	FALSE,		/* OPT_adult_rand_artifacts */
	FALSE,	  	/* OPT_adult_campaign */
	FALSE,		/* OPT_adult_no_stacking */
	FALSE,		/* OPT_adult_haggle */
	FALSE,		/* OPT_adult_scum */
	TRUE,		/* OPT_adult_maximize_class */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* OPT_score_peek */
	FALSE,		/* OPT_score_hear */
	FALSE,		/* OPT_score_room */
	FALSE,		/* OPT_score_xtra */
	FALSE,		/* OPT_score_know */
	FALSE,		/* OPT_score_live */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE,		/* xxx */
	FALSE		/* xxx */
};

/*
 * Option screen interface
 *
 * Note the special significance given to the constant "255".
 */
const byte option_page[OPT_PAGE_MAX][OPT_PAGE_PER] =
{
	/*** User-Interface ***/

	{
		OPT_rogue_like_commands,
		OPT_quick_messages,
		OPT_floor_query_flag,
		OPT_carry_query_flag,
		OPT_use_old_target,
		OPT_always_pickup,
		OPT_always_repeat,
		OPT_stack_force_notes,
		OPT_stack_force_costs,
		OPT_ring_bell,
		OPT_easy_open,
		OPT_easy_alter,
		OPT_easy_floor,
		OPT_scroll_target,
		OPT_stack_force_charges,
		OPT_stack_force_times,
		OPT_easy_autos,
		OPT_easy_search,
		OPT_easy_corpses,
		255
	},

	/*** Disturbance ***/

	{
		OPT_run_ignore_stairs,
		OPT_run_ignore_doors,
		OPT_run_cut_corners,
		OPT_run_use_corners,
		OPT_disturb_move,
		OPT_disturb_near,
		OPT_disturb_new,
		OPT_disturb_panel,
		OPT_disturb_state,
		OPT_disturb_minor,
		OPT_verify_destroy,
		OPT_verify_special,
		OPT_allow_quantity,
		OPT_auto_more,
		OPT_verify_mana,
		OPT_verify_safe,
		255,
		255,
		255,
		255
	},

	/*** Game-Play ***/

	{
		OPT_expand_look,
		OPT_expand_list,
		OPT_view_perma_grids,
		OPT_view_torch_grids,
		OPT_dungeon_align,
		OPT_dungeon_stair,
		OPT_view_unsafe_grids,
		OPT_view_detect_grids,
		OPT_reseed_artifacts,
		255,
		255,
		255,
		255,
		255,
		255,
		255,
		255,
		255,
		255,
		255
	},

	/*** Efficiency ***/

	{
		OPT_view_reduce_lite,
		OPT_hidden_player,
 		OPT_center_player,
 		OPT_run_avoid_center,
		OPT_avoid_abort,
		OPT_avoid_other,
		OPT_flush_failure,
		OPT_flush_disturb,
		OPT_fresh_before,
		OPT_fresh_after,
		OPT_compress_savefile,
		OPT_hilite_player,
		OPT_view_player_lite,
		OPT_view_yellow_lite,
		OPT_view_bright_lite,
		OPT_view_granite_lite,
		OPT_view_special_lite,
		OPT_view_glowing_lite,
		OPT_view_surface_lite,
		255
	},

	/*** Display ***/

	{
		OPT_show_sidebar,
		OPT_show_itemlist,
		OPT_depth_in_feet,
		OPT_show_labels,
		OPT_show_weights,
		OPT_show_choices,
		OPT_show_details,
		OPT_show_flavors,
		OPT_view_flavors,
		OPT_show_piles,
		OPT_room_names,
		OPT_room_descriptions,
		OPT_auto_display_lists,
		OPT_toggle_xp,
		255,
		255,
		255,
		255,
		255,
		255
	},

	/*** Birth ***/

	{
		OPT_birth_point_based,
		OPT_birth_auto_roller,
		OPT_birth_maximize_race,
		OPT_birth_maximize_class,
		OPT_birth_preserve,
		OPT_birth_ironman,
		OPT_birth_no_stores,
		OPT_birth_no_artifacts,
		OPT_birth_rand_artifacts,
		OPT_birth_campaign,
		OPT_birth_no_stacking,
		OPT_birth_haggle,
		OPT_birth_scum,
		255,
		255,
		255,
		255,
		255,
		255,
		255
	},

	/*** Cheat ***/

	{
		OPT_cheat_peek,
		OPT_cheat_hear,
		OPT_cheat_room,
		OPT_cheat_xtra,
		OPT_cheat_know,
		OPT_cheat_live,
		OPT_cheat_lore,
		OPT_cheat_auto,
		255,
		255,
		255,
		255,
		255,
		255,
		255,
		255,
		255,
		255,
		255,
		255
	}
};

const cptr inscrip_text[MAX_INSCRIP] =
{
	NULL,
	"terrible",
	"worthless",
	"cursed",
	"broken",
	"empty",
	"good",
	"excellent",
	"special",
	"uncursed",
	"very good",
	"great",
	"superb",
	"unbreakable",
	"ungettable",
	"nonmagical",
	"magical",
	"powerful",
	"ego item",
	"high ego item",
	"artifact",
	"unruned",
	"runed",
	"average",
	"valuable",
	"unusual",
	"coated",
	"sustain",
	"high resist",
	"enchanted",
	"low resist",
	"ignore",
	"blessed",
	"slaying",
	"branded",
	"poisoned",
	"lite",
	"acidproof",
	"fireproof",
	"waterproof",
	"theftproof",
	"vampiric"
};

const int object_xtra_what[OBJECT_XTRA_MAX_HIDDEN] =
{
	0,
	2,
	2,
	3,
	2,
	2,
	3,
	1,
	1,
	1,
	3,
	2,
	2,
	2,
	2,
	4,
	1,
	2,
	3,
	4
};

const u32b object_xtra_base[OBJECT_XTRA_MAX_HIDDEN] =
{
	0,
	TR2_SUST_STR,
	TR2_RES_POIS,
	TR3_SLOW_DIGEST,
	TR2_RES_ACID,
	TR2_IGNORE_ACID,
	TR3_BLESSED,
	TR1_SLAY_NATURAL,
	TR1_BRAND_ACID,
	TR1_BRAND_POIS,
	TR3_LITE,
	TR2_IGNORE_ACID,
	TR2_IGNORE_FIRE,
	TR2_IGNORE_WATER,
        TR2_IGNORE_THEFT,
	TR4_HURT_LITE,
	1L,	/* Magic item - flag 1 */
	1L,	/* Magic item - flag 2 */
	1L,	/* Magic item - flag 3 */
	1L	/* Magic item - flag 4 */
};


const int object_xtra_size[OBJECT_XTRA_MAX_HIDDEN] =
{
	0,
	6,
	12,
	16,
	4,
	5,
	1,
	8,
	4,
	1,
	1,
	1,
	1,
	1,
	1,
        8,
	32,	/* Magic item - flag 1 */
	32,	/* Magic item - flag 2 */
	32,	/* Magic item - flag 3 */
	32	/* Magic item - flag 4 */
};


/*
 * Description of each object group.
 */
const cptr object_group_text[] =
{
	"Sword",
	"Polearm",
	"Hafted Weapon",
	"Bow",
	"Arrows"	 ,
	"Bolt"	,
	"Shot"	,
	"Shield"	 ,
	"Crown"	,
        "Helm",
	"Gloves"	 ,
	"Boots"	,
	"Cloak"	,
	"Dragon Scale Mail",
	"Hard Armor"	 ,
	"Soft Armor"	 ,
	"Ring"		 ,
	"Amulet"	 ,
	"Lite",
	"Potion"	 ,
	"Scroll"	 ,
	"Wand",
	"Staff"	,
	"Rod"	,
	"Priest Book",
	"Magic Book",
	"Song Book"	,
	"Instrument",
	"Runestone"	,
	"Map"		,
	"Spike"	,
	"Rope" ,
	"Digger"	 ,
	"Food"	,
	"Flask"	,
	"Service", 
	"Bag"	,
	"Container"	,
	"Statue"	 ,
	"Assembly"	 ,
	"Skeleton"	,
	"Corpse"	 ,
	"Egg"		 ,
	"Skin"		 ,
	"Junk",
	NULL
};


/*
 * TVALs of items in each group
 */
const byte object_group_tval[] = 
{
	TV_SWORD,
	TV_POLEARM,
	TV_HAFTED,
	TV_BOW,	
	TV_ARROW,	
	TV_BOLT,
	TV_SHOT,
	TV_SHIELD,
	TV_CROWN,	  
	TV_HELM,	  
	TV_GLOVES,	  
	TV_BOOTS,	  
	TV_CLOAK,	  
	TV_DRAG_ARMOR,
	TV_HARD_ARMOR,
	TV_SOFT_ARMOR,
	TV_RING,	  
	TV_AMULET,	  
	TV_LITE,	  
	TV_POTION,	  
	TV_SCROLL,	  
	TV_WAND,	  
	TV_STAFF,	  
	TV_ROD,	  
	TV_PRAYER_BOOK,
	TV_MAGIC_BOOK,
	TV_SONG_BOOK,
	TV_INSTRUMENT,
	TV_RUNESTONE,
	TV_MAP,	 
	TV_SPIKE,
	TV_ROPE,
	TV_DIGGING,	 
	TV_FOOD,	 
	TV_FLASK,	 
	TV_SERVICE,
	TV_BAG,
	TV_HOLD,
	TV_STATUE,
	TV_ASSEMBLY,	
	TV_BONE,	
	TV_BODY,	
	TV_EGG,	
	TV_SKIN,	
	TV_JUNK,
	0
};

const cptr magic_name[4][32] =
{
	/* TR1_ */
	{
		"of Strength",
		"of Intelligence",
		"of Wisdom",
		"of Dexterity",
		"of Constitution",
		"of Charisma",
		"of Spell Resistance",
		"of Device Mastery",
		"of Stealth",
		"of Searching",
		"of Infravision",
		"of Tunnelling",
		"of Speed",
		"of Extra Attacks",
		"of Extra Shots",
		"of Extra Might",
		"of Slay Nature",
		"of Slay Evil",
		"of Slay Undead",
		"of Slay Demon",
		"of Slay Orc",
		"of Slay Troll",
		"of Slay Giant",
		"of Slay Dragon",
		"of Execute Dragon",
		"of Execute Demon",
		"of Execute Undead",
		"of Poison",
		"of Acid",
		"of Electricity",
		"of Fire",
		"of Cold"
	},

	/* TR2_ */
	{
		"of Sustain Strength",
		"of Sustain Intelligence",
		"of Sustain Wisdom",
		"of Sustain Dexterity",
		"of Sustain Constitution",
		"of Sustain Charisma",
		"(Acid proof)",
		"(Lightning proof)",
		"(Fire proof)",
		"(Frost proof)",
		"(Water proof)",
		"(Theft proof)",
		"of Acid Immunity",
		"of Lightening Immunity",
		"of Fire Immunity",
		"of Frost Immunity",
		"of Resist Acid",
		"of Resist Electricity",
		"of Resist Fire",
		"of Resist Cold",
		"of Resist Poison",
		"of Resist Fear",
		"of Resist Light",
		"of Resist Darkness",
		"of Resist Blindness",
		"of Resist Confusion",
		"of Resist Sound",
		"of Resist Shards",
		"of Resist Nexus",
		"of Resist Nether",
		"of Resist Chaos",
		"of Resist Disenchantment"
	},

	/* TR3_ */
	{
		"of Slow Digestion",
		"of Feather Falling",
		"(Glowing)",
		"of Health Regeneration",
		"of Telepathy",
		"of See Invisible",
		"of Free Action",
		"of Hold Life",
		"of Sense Demons",
		"of Sense Dragons",
		"of Sense Giants",
		"of Sense Orcs",
		"of Sense Trolls",
		"of Sense Undead",
		"of Sense Nature",
		"of Mana Regeneration",
		"(Drains Health)",
		"(Drains Mana)",
		"(Drains Experience)",
		"of Aggravation",
		"of Teleportation",
		"", /* Random activation */
		"", /* Activates */
		"(Blessed)",
		"", /* Artifact */
		"of Hunger",
		"of Impact",
		"(Rope-attached)",
		"of Throwing",
		"",	/* Light curse */
		"",	/* Heavy curse */
		""	/* Permanently cursed */
	},

	/* TR4_ */
	{
		"of Darkness",
		"of Light",
		"of Light Vulnerability",
		"of Water Vulnerability",
		"of Bloodlust",
		"of Manathirst",
		"of Poison Immunity",
		"of Resist Disease",
		"of Resist Water",
		"of Slay Man",
		"of Slay Elf",
		"of Slay Dwarf",
		"of Anchoring",
		"of Silence",
		"of Static",
		"of Ill Winds",
		"(Animal)",
		"(Evil)",
		"(Ancient)",
		"(Demonic)",
		"(Orcish)",
		"(Troll)",
		"(Giant)",
		"(Dragon)",
		"of Man",
		"(Dwarven)",
		"(Elven)",
		"of Poison Vulnerability",
		"of Acid Vulnerability",
		"of Lightning Vulnerability",
		"of Fire Vulnerability",
		"of Frost Vulnerability"	
	}
};

const cptr disease_name[33] =
{
	"pink rot",
	"black brain",
	"wit loss",
	"fumblefinger",
	"illweather",
	"warts",
	"food poisoning",
	"thirst",
	"shards",
	"ringing in ears",
	"green rot",
	"magic mushrooms",
	"slow stumble",
	"black eye",
	"a hangover",
	"paranoia",
	"dementia",
	"bad luck",
	"narcolepsy",
	"being stoned",
	"palsy",
	"time loss",
	"static",
	"leeches",
	"mana mites",
	"black breath",
	"the plague",
	"unnatural parasites",
	"Morgoth's curse",
	"minor ailments",
	"hard to treat viruses",
	"incurable illnesses",
	"magical maladies"
};

/*
 * First column is Mana Cost
 * Second column is multiplier * spellpower (breaths handled separately)
 * Third column is a divider to we can have damage like
 * spellpower * 5/2 using only integer math.
 * 4th column is damage variance
 * 5th column is Optimal Ranges for various spells.
 * 6 is optimal for Breath Weapons, Beams, and Arcs.
 * 3 is hard maximum for Lash/Spit.
 * 0 indicates no range limitation for other spells.
 *
 * This range is considered a preference if d_range in spell_desire is > 0.
 * It is a hard limit if d_range = 0.
 */

/*{Mana_cost,dam_mult,dam_div,dam_var,best_range}*/
byte spell_info_RF4[32][5]=
{
	{0,     0,     0,     0,     0},        /* RF4_BLOW_1 */
	{0,     0,     0,     0,     0},        /* RF4_BLOW_2 */
	{0,     0,     0,     0,     0},        /* RF4_BLOW_3 */
	{0,     0,     0,     0,     0},        /* RF4_BLOW_4 */
	{0,     0,     0,     0,     MAX_SIGHT},/* RF4_ADD_AMMO */
	{0,     0,     0,     0,     8},        /* RF4_QUAKE */
	{0,     0,     0,     0,     1},        /* RF4_EXPLODE */
	{0,     0,     0,     0,     1},        /* RF4_AURA */  /* Last spell with fixed maximum range */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_ACID */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_ELEC */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_FIRE */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_COLD */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_POIS */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_PLAS */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_LITE */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_DARK */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_CONFU */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_SOUND */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_SHARD */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_INER */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_GRAV */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_WIND */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_FORCE */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_NEXUS */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_NETHR */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_CHAOS */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_DISEN */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_TIME */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_MANA */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_HOLY */
	{0,     0,     0,     0,     0},        /* RF4_BRTH_FEAR */
	{0,     0,     0,     0,     0}         /* RF4_BRTH_DISEA */
};

 /*{Mana_cost,dam_mult,dam_div,dam_var,best_range}*/
const byte spell_info_RF5[32][5]=
{
	{4,     4,     1,     6,     6},        /* RF5_BALL_ACID */
	{4,     4,     1,     6,     6},        /* RF5_BALL_ELEC */
	{4,     4,     1,     6,     6},        /* RF5_BALL_FIRE */
	{4,     4,     1,     6,     6},        /* RF5_BALL_COLD */
	{4,     3,     1,     6,     6},        /* RF5_BALL_POIS */
	{5,     3,     1,     6,     6},        /* RF5_BALL_LITE */
	{5,     3,     1,     6,     6},        /* RF5_BALL_DARK */
	{6,     3,     1,     6,     6},        /* RF5_BALL_CONFU */
	{4,     2,     1,     6,     6},        /* RF5_BALL_SOUND */
	{4,     3,     1,     6,     6},        /* RF5_BALL_SHARD */
	{4,     2,     1,     6,     6},        /* RF5_BALL_WIND */
	{5,     3,     1,     4,     4},        /* RF5_BALL_STORM */
	{6,     3,     1,     6,     6},        /* RF5_BALL_NETHR */
	{7,     3,     1,     4,     4},        /* RF5_BALL_CHAOS */
	{7,     3,     1,     8,     8},        /* RF5_BALL_MANA */
	{7,     3,     1,     6,     6},        /* RF5_BALL_WATER */
	{4,     4,     1,     6,     6},        /* RF5_BOLT_ACID */
	{4,     4,     1,     6,     6},        /* RF5_BOLT_ELEC */
	{4,     4,     1,     6,     6},        /* RF5_BOLT_FIRE */
	{4,     4,     1,     6,     6},        /* RF5_BOLT_COLD */
	{4,     3,     1,     6,     6},        /* RF5_BOLT_POIS */
	{5,     3,     1,     6,     6},        /* RF5_BOLT_PLAS */
	{5,     3,     1,     6,     6},        /* RF5_BOLT_ICE */
	{5,     3,     1,     6,     6},        /* RF5_BOLT_WATER */
	{5,     3,     1,     6,     6},        /* RF5_BOLT_NETHER */
	{5,     2,     1,     6,     6},        /* RF5_BOLT_MANA */
	{5,     5,     2,     8,     8},        /* RF5_HOLY_ORB */
	{6,     3,     1,     6,     6},        /* RF5_BEAM_ELEC */
	{6,     4,     1,     6,     6},        /* RF5_BEAM_ICE */
	{7,     3,     1,     6,     6},        /* RF5_BEAM_NETHER */
	{7,     0,     0,     0,     6},        /* RF5_ARC_HFIRE */
	{5,     0,     0,     0,     8}         /* RF5_ARC_FORCE */
};

 /*{Mana_cost,dam_mult,dam_div,dam_var,best_range}*/
const byte spell_info_RF6[32][5]=
{
	{6,     0,     0,     0,     0},        /* RF6_HASTE */
	{0,     0,     0,     0,     0},        /* RF6_ADD_MANA */
	{3,     0,     0,     0,     0},        /* RF6_HEAL */
	{3,     0,     0,     0,     0},        /* RF6_CURE */
	{3,     0,     0,     0,     0},        /* RF6_BLINK */
	{8,     0,     0,     0,     0},        /* RF6_TPORT */
	{3,     0,     0,     0,     0},        /* RF6_INVIS */
	{4,     0,     0,     0,     0},        /* RF6_TELE_SELF_TO */
	{4,     0,     0,     0,     0},        /* RF6_TELE_TO */
	{8,     0,     0,     0,     0},        /* RF6_TELE_AWAY */
	{8,     0,     0,     0,     0},        /* RF6_TELE_LEVEL */
	{4,     0,     0,     0,     0},        /* RF6_WRAITHFORM */
	{1,     0,     0,     0,     0},        /* RF6_DARKNESS */
	{2,     0,     0,     0,     0},        /* RF6_TRAPS */
	{6,     0,     0,     0,     0},        /* RF6_FORGET */
	{2,     0,     0,     0,     0},        /* RF6_DRAIN_MANA */
	{4,     3,     2,     6,     6},        /* RF6_CURSE */
	{4,     0,     0,     0,     0},        /* RF6_DISPEL */
	{3,     3,     2,     6,     6},        /* RF6_MIND_BLAST */
	{4,     0,     0,     0,     0},        /* RF6_ILLUSION */
	{4,     5,     2,     6,     6},        /* RF6_WOUND */
	{2,     0,     0,     0,     0},        /* RF6_BLESS */
	{3,     0,     0,     0,     0},        /* RF6_BESERK */
	{4,     0,     0,     0,     0},        /* RF6_SHIELD */
	{3,     0,     0,     0,     0},        /* RF6_OPPOSE_ELEM */
	{2,     0,     0,     0,     0},        /* RF6_HUNGER */
	{1,     0,     0,     0,     0},        /* RF6_PROBE */
	{1,     0,     0,     0,     0},        /* RF6_SCARE */
	{3,     0,     0,     0,     0},        /* RF6_BLIND */
	{4,     0,     0,     0,     0},        /* RF6_CONF */
	{5,     0,     0,     0,     0},        /* RF6_SLOW */
	{6,     0,     0,     0,     0}         /* RF6_HOLD */
};

 /*{Mana_cost,dam_mult,dam_div,dam_var,best_range}*/
const byte spell_info_RF7[32][5]=
{
	{12,    0,     0,     0,     0},        /* RF7_S_KIN */ /* Summon - 6 */
	{4,     0,     0,     0,     0},        /* RF7_R_KIN */
	{8,     0,     0,     0,     0},        /* RF7_A_DEAD */
	{10,    0,     0,     0,     0},        /* RF7_S_MONSTER */ /* Summon - 1 */
	{15,    0,     0,     0,     0},        /* RF7_S_MONSTERS */ /* Summon - 8 */
	{5,     0,     0,     0,     0},        /* RF7_R_MONSTER */
	{6,     0,     0,     0,     0},        /* RF7_R_MONSTERS */
	{8,     0,     0,     0,     0},        /* RF7_S_PLANT */
	{10,    0,     0,     0,     0},        /* RF7_S_INSECT */ /* Summon - 6 */
	{12,    0,     0,     0,     0},        /* RF7_S_ANIMAL */ /* Summon - 6 */
	{14,    0,     0,     0,     0},        /* RF7_S_HOUND */ /* Summon - 6 */
	{15,    0,     0,     0,     0},        /* RF7_S_SPIDER */ /* Summon - 6 */
	{10,    0,     0,     0,     0},        /* RF7_S_CLASS */
	{10,    0,     0,     0,     0},        /* RF7_S_RACE */
	{15,    0,     0,     0,     0},        /* RF7_S_GROUP */ /* Summon - 6 */
	{5,     0,     0,     0,     0},        /* RF7_S_FRIEND */ /* Summon - 2 */
	{10,    0,     0,     0,     0},        /* RF7_S_FRIENDS */
	{10,    0,     0,     0,     0},        /* RF7_S_ORC */
	{10,    0,     0,     0,     0},        /* RF7_S_TROLL */
	{10,    0,     0,     0,     0},        /* RF7_S_GIANT */
	{14,    0,     0,     0,     0},        /* RF7_S_DRAGON */ /* Summon - 1 */
	{20,    0,     0,     0,     0},        /* RF7_S_HI_DRAGON */ /* Summon - 8 */
	{6,     0,     0,     0,     0},        /* RF7_A_ELEMENT */
	{6,     0,     0,     0,     0},        /* RF7_A_OBJECT */
	{14,    0,     0,     0,     0},        /* RF7_S_DEMON */ /* Summon - 1 / 2-3 */
	{20,    0,     0,     0,     0},        /* RF7_S_HI_DEMON */ /* Summon - 8 */
	{25,    0,     0,     0,     0},        /* RF7_R_UNIQUE */
	{15,    0,     0,     0,     0},        /* RF7_S_UNIQUE */ /* Summon - 8 */
	{20,    0,     0,     0,     0},        /* RF7_S_HI_UNIQUE */ /* Summon - 8 */
	{12,    0,     0,     0,     0},        /* RF7_S_UNDEAD */ /* Summon - 1 */
	{20,    0,     0,     0,     0},        /* RF7_S_HI_UNDEAD */ /* Summon - 8 */
	{20,    0,     0,     0,     0}         /* RF7_S_WRAITH */ /* Summon - 8 */

};

/*
 * d_base:     base desirability for AI.
 * d_summ:     desriability for AI per monster level
 *                  times 0-3 based on number of clear spaces
 * d_hurt:     desirability for AI per monster spell power
 *                  times 0-3 based on damage taken
 * d_mana:     desirability for AI per monster spell power
 *                  times 0-2 based on mana shortage
 * d_esc:      desirability for AI per monster level
 *                  times 0-3 based on fear, and damage taken
 * d_tact:     desirability for AI per monster level, modified
 *                  times 0-3 based on proximity, min_range, and best_range
 * d_res:      category of 'resistability' checked by monster AI
 *                 for purposes of desirability.
 * d_range:    % of spell desirability retained for each step past 'range'
 */

byte spell_desire_RF4[32][8] =
{
/*     d_base	  d_hurt    d_esc	 d_res				    */
/*	     d_summ	d_mana	  d_tact	   d_range		    */
	{ 40,  0,   0,   5,	0,   0,	   0	  ,  100}, /* RF4_BLOW_1    */
	{ 40,  0,   0,   5,	0,   0,	   0	  ,  100}, /* RF4_BLOW_2    */
	{ 40,  0,   0,   5,	0,   0,    0      ,  100}, /* RF4_BLOW_3    */
	{ 40,  0,   0,   5,	0,   0,    0      ,  100}, /* RF4_BLOW_4    */
	{ 60,  0,   0,   5,	0,   0,    0      ,  100}, /* RF4_SHRIEK    */
	{ 40,  0,   0,   5,	0,   0,    0      ,  100}, /* RF4_QUAKE	    */
	{ 20,  0,   0,   5,	0,   0, GF_EXPLODE  ,  100}, /* RF4_EXPLODE   */
	{ 40,  0,   0,   0,	0,   0,    0      ,  100}, /* RF4_AURA      */
	{ 75,  0,   0,   5,	0,   0, GF_ACID   ,   90}, /* RF4_BRTH_ACID */
	{ 75,  0,   0,   5,	0,   0, GF_ELEC  ,   90}, /* RF4_BRTH_ELEC */
	{ 75,  0,   0,   5,	0,   0, GF_FIRE  ,   90}, /* RF4_BRTH_FIRE */
	{ 75,  0,   0,   5,	0,   0, GF_COLD  ,   90}, /* RF4_BRTH_COLD */
	{ 65,  0,   0,   5,	0,   0, GF_POIS  ,   90}, /* RF4_BRTH_POIS */
	{ 65,  0,   0,   5,	0,   0, GF_PLASMA  ,   90}, /* RF4_BRTH_PLAS */
	{ 65,  0,   0,   5,	0,   0, GF_LITE  ,   90}, /* RF4_BRTH_LITE */
	{ 65,  0,   0,   5,	0,   0, GF_DARK  ,   90}, /* RF4_BRTH_DARK */
	{ 65,  0,   0,   5,	0,   0, GF_CONFUSION ,   90}, /* RF4_BRTH_CONFU*/
	{ 65,  0,   0,   5,	0,   0, GF_SOUND ,   90}, /* RF4_BRTH_SOUND*/
	{ 65,  0,   0,   5,	0,   0, GF_SHARD ,   90}, /* RF4_BRTH_SHARD*/
	{ 65,  0,   0,   5,	0,   0,	GF_INERTIA,   90}, /* RF4_BRTH_INER */
	{ 65,  0,   0,   5,	0,   0, GF_GRAVITY,   90}, /* RF4_BRTH_GRAV */
	{ 65,  0,   0,   5,	0,   0,	GF_WIND	  ,  90}, /* RF4_BRTH_WIND */
	{ 65,  0,   0,   5,	0,   0, GF_FORCE,   90}, /* RF4_BRTH_FORCE*/
	{ 65,  0,   0,   5,	0,   0, GF_NEXUS ,   90}, /* RF4_BRTH_NEXUS*/
	{ 65,  0,   0,   5,	0,   0, GF_NETHER ,   90}, /* RF4_BRTH_NETHR*/
	{ 65,  0,   0,   5,	0,   0, GF_CHAOS ,   90}, /* RF4_BRTH_CHAOS*/
	{ 65,  0,   0,   5,	0,   0, GF_DISENCHANT ,   90}, /* RF4_BRTH_DISEN*/
	{ 65,  0,   0,   5,	0,   0,	GF_TIME	  ,   90}, /* RF4_BRTH_TIME */
	{ 65,  0,   0,   5,	0,   0,	GF_MANA	  ,   90}, /* RF4_BRTH_MANA */
	{ 65,  0,   0,   5,	0,   0,	GF_HOLY_ORB  ,  90}, /* RF4_BRTH_HOLY */
	{ 65,  0,   0,   5,	0,   0,	GF_TERRIFY  ,  90}, /* RF4_BRTH_FEAR */
	{ 65,  0,   0,   5,	0,   0,	GF_DISEASE	  ,  90}  /* RF4_BRTH_DISEASE */
};

const byte spell_desire_RF5[32][8] =
{
/*     d_base	  d_hurt    d_esc	 d_res				    */
/*	     d_summ	d_mana	  d_tact	   d_range		    */
	{ 50,  0,   0,   0,	0,   0, GF_ACID  ,  100}, /* RF5_BALL_ACID */
	{ 50,  0,   0,   0,	0,   0, GF_ELEC  ,  100}, /* RF5_BALL_ELEC */
	{ 50,  0,   0,   0,	0,   0, GF_FIRE  ,  100}, /* RF5_BALL_FIRE */
	{ 50,  0,   0,   0,	0,   0, GF_COLD  ,  100}, /* RF5_BALL_COLD */
	{ 50,  0,   0,   0,	0,   0, GF_POIS  ,  100}, /* RF5_BALL_POIS */
	{ 40,  0,   0,   0,	0,   0, GF_LITE  ,  100}, /* RF5_BALL_LITE */
	{ 40,  0,   0,   0,	0,   0, GF_DARK  ,  100}, /* RF5_BALL_DARK */
	{ 40,  0,   0,   0,	0,   0, GF_CONFUSION ,  100}, /* RF5_BALL_CONFU*/
	{ 40,  0,   0,   0,	0,   0, GF_SOUND ,  100}, /* RF5_BALL_SOUND*/
	{ 40,  0,   0,   0,	0,   0, GF_SHARD ,  100}, /* RF5_BALL_SHARD*/
	{ 40,  0,   0,   0,	0,   0,	GF_WIND	  ,  100}, /* RF5_BALL_WIND */
	{ 40,  0,   0,   0,	0,   0, GF_STORM ,  100}, /* RF5_BALL_STORM*/
	{ 40,  0,   0,   0,	0,   0, GF_NETHER ,  100}, /* RF5_BALL_NETHR*/
	{ 40,  0,   0,   0,	0,   0, GF_CHAOS ,  100}, /* RF5_BALL_CHAOS*/
	{ 40,  0,   0,   0,	0,   0,	GF_MANA,  100}, /* RF5_BALL_MANA */
	{ 40,  0,   0,   0,	0,   0, GF_WATER ,  100}, /* RF5_BALL_WATER*/
	{ 40,  0,   0,   0,	0,   0, GF_ACID  ,  100}, /* RF5_BOLT_ACID */
	{ 40,  0,   0,   0,	0,   0, GF_ELEC  ,  100}, /* RF5_BOLT_ELEC */
	{ 40,  0,   0,   0,	0,   0, GF_FIRE  ,  100}, /* RF5_BOLT_FIRE */
	{ 40,  0,   0,   0,	0,   0, GF_COLD  ,  100}, /* RF5_BOLT_COLD */
	{ 40,  0,   0,   0,	0,   0, GF_POIS  ,  100}, /* RF5_BOLT_POIS */
	{ 50,  0,   0,   0,	0,   0, GF_PLASMA  ,  100}, /* RF5_BOLT_PLAS */
	{ 50,  0,   0,   0,	0,   0, GF_ICE	  ,  100}, /* RF5_BOLT_ICE  */
	{ 35,  0,   0,   0,	0,   0, GF_WATER ,  100}, /* RF5_BOLT_WATER*/
	{ 35,  0,   0,   0,	0,   0, GF_NETHER ,  100}, /* RF5_BOLT_NETHR*/
	{ 30,  0,   0,   0,	0,   0,	GF_MANA	  ,  100}, /* RF5_BOLT_MANA */
	{ 60,  0,   0,   0,	0,   0, GF_HOLY_ORB  ,  100}, /* RF5_HOLY_ORB*/
	{ 50,  0,   0,   0,	0,   0, GF_ELEC  ,   90}, /* RF5_BEAM_ELEC */
	{ 50,  0,   0,   0,	0,   0, GF_ICE	  ,   90}, /* RF5_BEAM_ICE  */
	{ 50,  0,   0,   0,	0,   0, GF_NETHER ,   90}, /* RF5_BEAM_NETHR*/
	{ 50,  0,   0,   0,	0,   0,	GF_HELLFIRE,  80},  /* RF5_ARC_HFIRE*/
	{ 40,  0,   0,   0,	0,   0,	GF_FORCE  ,  90} 	/* RF5_ARC_FORCE */
};


const byte spell_desire_RF6[32][8] =
{
/*     d_base	  d_hurt    d_esc	 d_res				    */
/*	     d_summ	d_mana	  d_tact	   d_range		    */
	{ 50,  0,   0,   0,	0,   0,	   0	  ,  100}, /* RF6_HASTE	    */
	{ 15,  0,   0,  25,	0,   0,	   0  ,  100}, /* RF6_ADD_MANA  */
	{ 10,  0,   30,  0,	0,   0,	   0	  ,  100}, /* RF6_HEAL	    */
	{ 50,  0,   0,   0,	0,   0,	   0	  ,  100}, /* RF6_CURE	    */
	{ 27,  0,   0,   0,	10,  15,   0	  ,  100}, /* RF6_BLINK	    */
	{  3,  0,   0,   0,	20,  10,   0	  ,  100}, /* RF6_TPORT	    */
	{ 50,   0,   0,   0,	0,   0,	   0	  ,  100}, /* RF6_INVIS	    */
	{ 30,  0,   0,   0,	0,   0,	   0	  ,  100}, /* RF6_TELE_SELF_TO*/
	{ 30,  0,   0,   0,	0,   10,   0	  ,  100}, /* RF6_TELE_TO   */
	{  3,  0,   0,   0,	20,  10,   0	  ,  100}, /* RF6_TELE_AWAY */
	{  3,  0,   0,   0,	20,  10,   0 ,	   100}, /* RF6_TELE_LEVEL */
	{ 50,   0,   0,   0,	0,   0,	   0	  ,  100}, /* RF6_WRAITHFORM*/
	{ 20,  0,   0,   0,	5,   0,	   0	  ,  100}, /* RF6_DARKNESS  */
	{ 25,  0,   0,   0,	5,   0,	   0	  ,  100}, /* RF6_TRAPS	    */
	{ 25,  0,   0,   0,	5,   0, 0  ,  100}, /* RF6_FORGET    */
	{ 25,  0,   0,   15,	0,   0, GF_LOSE_MANA,  100}, /* RF6_DRAIN_MANA*/
	{ 45,  0,   0,   0,	0,   0,	   0	  ,  100}, /* RF6_CURSE	    */
	{ 45,  0,   0,   0,	0,   0,	   0	  ,  100}, /* RF6_DISPEL   */
	{ 30,  0,   0,   0,	0,   0, 0  ,  100}, /* RF6_MIND_BLAST*/
	{ 30,  0,   0,   0,	0,   0, GF_HALLU,  100}, /* RF6_ILLUSION*/
	{ 40,  0,   0,   0,	0,   0, GF_HURT,  100}, /* RF6_WOUND	    */
	{ 50,  0,   0,   0,	0,   0,	   0	  ,  100}, /* RF6_BLESS	    */
	{ 50,  0,   0,   0,	0,   0,	   0	  ,  100}, /* RF6_BESERK    */
	{ 50,  0,   0,   0,	0,   0,	   0	  ,  100}, /* RF6_SHIELD    */
	{ 50,  0,   0,   0,	0,   0,	   0	  ,  100}, /* RF6_OPPOSE_ELEM */
	{ 25,  0,   0,   0,	0,   0,	GF_HUNGER,  100}, /* RF6_HUNGER    */
	{ 50,  0,   0,   0,	0,   0,	GF_PROBE	  ,  100}, /* RF6_PROBE	    */
	{ 25,  0,   0,   0,	0,   0, GF_FEAR_WEAK,	  100}, /* RF6_SCARE	 */
	{ 30,  0,   0,   0,	0,   0, GF_BLIND_WEAK,	   100}, /* RF6_BLIND	  */
	{ 30,  0,   0,   0,	0,   0, GF_CONF_WEAK,	   100}, /* RF6_CONF	  */
	{ 40,  0,   0,   0,	0,   0, GF_SLOW_WEAK,	  100}, /* RF6_SLOW	 */
	{ 35,  0,   0,   0,	0,   0, GF_SLEEP,	  100} /* RF6_HOLD	*/
};

const byte spell_desire_RF7[32][8] =
{
 /*     d_base	  d_hurt    d_esc	 d_res				    */
 /*	     d_summ	d_mana	  d_tact	   d_range		    */
	{ 0,   15,  0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_KIN	    */
	{ 0,   15,   0,   0,	0,   0,	   0	  ,  100}, /* RF7_R_KIN	    */
	{ 0,   15,   0,   0,	0,   0,	   0	  ,  100}, /* RF7_A_DEAD    */
	{ 0,   15,  0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_MONSTER */
	{ 0,   15,  0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_MONSTERS*/
	{ 0,   15,   0,   0,	0,   0,	   0	  ,  100}, /* RF7_R_MONSTER */
	{ 0,   15,   0,   0,	0,   0,	   0	  ,  100}, /* RF7_R_MONSTERS*/
	{ 0,   15,   0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_PLANT   */
	{ 0,   15,  0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_INSECT  */
	{ 0,   15,  0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_ANIMAL  */
	{ 0,   15,  0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_HOUND   */
	{ 0,   15,  0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_SPIDER  */
	{ 0,   15,  0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_CLASS   */
	{ 0,   15,   0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_RACE    */
	{ 0,   15,  0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_ELEMENT */
	{ 0,   15,  0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_FRIEND  */
	{ 0,   15,   0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_FRIENDS */
	{ 0,   15,  0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_ORC     */
	{ 0,   15,   0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_TROLL   */
	{ 0,   15,   0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_GIANT   */
	{ 0,   15,  0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_DRAGON  */
	{ 0,   17,  0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_HI_DRAGON*/
	{ 0,   15,   0,   0,	0,   0,	   0	  ,  100}, /* RF7_A_ELEMENT */
	{ 0,   15,   0,   0,	0,   0,	   0	  ,  100}, /* RF7_A_OBJECT  */
	{ 0,   15,  0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_DEMON   */
	{ 0,   17,  0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_HI_DEMON*/
	{ 0,   15,   0,   0,	0,   0,	   0	  ,  100}, /* RF7_R_UNIQUE  */
	{ 0,   15,  0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_UNIQUE  */
	{ 0,   18,  0,   0,	0,   0,	   0  	  ,  100}, /* RF7_S_HI_UNIQUE */
	{ 0,   15,  0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_UNDEAD  */
	{ 0,   17,  0,   0,	0,   0,	   0	  ,  100}, /* RF7_S_HI_UNDEAD*/
	{ 0,   18,  0,   0,	0,   0,	   0	  ,  100}  /* RF7_S_WRAITH  */
};


/*
 * Define which element the monster belongs to.
 *
 * Elements are Fire, Water, Earth, Air, Magma, Ice, Ooze, Smoke.
 *
 */
const element_type element[MAX_ELEMENTS] =
{
	/* ELEM_FIRE */
	{GF_FIRE, 0L, 14},

	/* ELEM_EARTH */
	{0, (FF2_CAN_DIG), 13},

	/* ELEM_AIR */
	{GF_WIND, (FF2_CHASM), 11 },

	/* ELEM_WATER */
	{GF_WATER, (FF2_WATER | FF2_CAN_SWIM), 12},

	/* ELEM_MAGMA */
	{GF_LAVA, (FF2_LAVA), 19},

	/* ELEM_OOZE */
	{GF_ACID, (FF2_ACID), 16},

	/* ELEM_ICE */
	{GF_ICE, (FF2_ICE), 18},

	/* ELEM_SMOKE */
	{GF_SMOKE, (FF2_OIL), 17}
};

/*
 * Define which items all starting characters get.
 */
const start_item common_items[MAX_COMMON_ITEMS]=
{
	{	TV_FOOD, SV_FOOD_SLIME_MOLD, 6, 7, 0, 0, 0, 20},
	{	TV_FOOD, SV_FOOD_PINT_OF_SPIRITS, 1, 1, 0, 0, 0, 15},
	{	TV_FOOD, SV_FOOD_PINT_OF_ALE, 1, 1, 0, 0, 16, 60},
	{	TV_FOOD, SV_FOOD_BISCUIT, 6, 7, 0, 0, 21, 40},
	{	TV_FOOD, SV_FOOD_RATION, 3, 7, 0, 0, 41, 100},
	{	TV_FOOD, SV_FOOD_PINT_OF_WINE, 1, 1, 0, 0, 61, 95},
	{	TV_LITE, SV_LITE_TORCH, 3, 7, 500, 3500, 0, 75},
	{	TV_LITE, SV_LITE_LANTERN, 1, 1, 500, 3500, 76, 100},
	{	TV_FLASK, SV_FLASK_OIL, 2, 5, 0, 0, 76, 100},
	{	TV_HELM, SV_HARD_LEATHER_CAP, 1, 1, 0, 0, 60, 99},
	{	TV_CROWN, SV_GOLDEN_CROWN, 1, 1, 0, 0, 100, 100},
	{	TV_BOOTS, SV_PAIR_OF_HARD_LEATHER_BOOTS, 1, 1, 0, 0, 50, 70},
	{	TV_BOOTS, SV_PAIR_OF_SOFT_LEATHER_BOOTS, 1, 1, 0, 0, 71, 100},
	{	TV_HELM, SV_SET_OF_LEATHER_GLOVES, 1, 1, 0, 0, 91, 100},
	{	TV_CLOAK, SV_CLOAK, 1, 1, 0, 0, 81, 100}
};

const cptr vocalize[MAX_LANGUAGES] =
{
	"says",		/* LANG_COMMON */
	"says",		/* LANG_ELF */
	"says",		/* LANG_DWARF */
	"barks",	/* LANG_ORC */
	"roars",	/* LANG_TROLL */
	"thunders",	/* LANG_GIANT */
	"roars",	/* LANG_DRAGON */
	"utters",	/* LANG_DEMON */
	"whispers",	/* LANG_UNDEAD */
	"thinks",	/* LANG_ESP */
	"creaks",	/* LANG_FOREST */
	"releases",	/* LANG_MUSHROOM */
	"says",		/* LANG_NATURAL */
	"roars", 	/* 'A' */
	"squawks",
	"growls",
	"roars",
	"shudders",
	"croaks", 	/* 'F' */
	"says",
	"roars",
	"says",
	"hisses",
	"clicks", 	/* 'K' */
	"whispers",
	"says",
	"whispers",
	"says",
	"says", 	/* 'P' */
	"roars",
	"hisses",
	"says",
	"roars",
	"utters", 	/* 'U' */
	"whispers",
	"whispers",
	"grunts",
	"hoots",
	"howls", 	/* 'Z' */
	"releases", 	/* 'a' */
	"screeches",
	"clicks",
	"roars",
	"blinks",
	"chirps", 	/* 'f' */
	"beeps",
	"says",
	"squelches",
	"squelches",
	"barks", 	/* 'k' */
	"says",
	"releases",
	"hisses",
	"barks",
	"says", 	/* 'p' */
	"says",
	"screeches",
	"whispers",
	"says",
	"utters", 	/* 'u' */
	"drones",
	"writhes",
	"says",
	"hisses",
	"drools"	/* 'z' */
};



/*
 * Months from T.o.M.E
 */
const int month_day[9] =
{
	0,        /* 1 day */

	1,        /* 54 days */
	55,       /* 72 days */
	127,      /* 54 days */

	181,      /* 3 days */

	184,      /* 54 days */
	238,      /* 72 days */
	310,      /* 54 days */

	364,      /* 1 day */
};


/*
 * Month names from T.o.M.E
 */
const cptr month_name[9] =
{
	"Yestare",

	"Tuile",
	"Laire",
	"Yavie",

	"Enderi",

	"Quelle",
	"Hrive",
	"Coire",

	"Mettare",
};


/*
 * Bag definitions
 *
 * A bag is a collection of items uniquely identified by their tval and sval.
 *
 * A bag can hold either one or (hack) two further distinguishing attributes:
 * the number of such items in the bag, and (possibly) the total number of
 * charges. The total number of charges is a hack -- because we either use
 * a second 'fake' bag entry to track the charges (for wands), or abstract
 * the total number of items out and just track charges (for torches).
 *
 * This means we can have bags for potions, food, spikes, etc. but not rods
 * (because they can have a timeout), bodies (because they are also distinguished
 * by the monster type), weapons and armour (because they have many other
 * variables tracked), lanterns (because we don't want to apply the hack to
 * lanterns).
 *
 * XXX XXX We accomadate a small information loss: if a player notices
 * something about a kind of item, such as the fact a wand of fire ignores
 * fire, this information will be lost when the item put in a bag. The
 * alternative is to only let the player put identified items in the bag, but
 * this makes bags a lot less useful.
 *
 * XXX XXX To provide some kind of balance, we do not create bags for spellbooks.
 *
 * XXX XXX We restrict bags to holding 22 different kinds of items because this
 * is the maximum number we can display in a list on an 80x24 screen.
 *
 * We treat these bags as 'magic' and track the contents once - every bag of
 * the same type has 'magical' access to the same contents as every other
 * bag.
 */
const s16b bag_holds[SV_BAG_MAX_BAGS][INVEN_BAG_TOTAL][2] =
{
	/* Bag of Poisons - holds dangerous potions */
	{ {75, 4}, {75, 5}, {75, 7}, {75, 9},
	  {75, 11}, {75, 13}, {75, 15}, {75, 16},
	  {75, 17}, {75, 18}, {75, 19}, {75, 20},
	  {75, 21}, {75, 22}, {75, 23}, {75, 73},
	  {75, 74}, {75, 76}, {75, 77}, {75, 78},
	  {75, 79}, {75, 80}, {75, 81} },
	/* Bag of Harmful Mushrooms - holds harmful mushrooms */
	{ {80, 0}, {80, 1}, {80, 2}, {80, 3},
	  {80, 4}, {80, 5}, {80, 6}, {80, 7},
	  {80, 8}, {80, 9}, {80, 10}, {80, 11},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0} },
	/* Bag of Black Magics -- holds cursed scrolls */
	{ {70, 0}, {70, 1}, {70, 2}, {70, 3},
	  {70, 4}, {70, 7}, {70, 5}, {70, 69},
	  {70, 74}, {70, 75}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0} },
	/* Bag of supplies -- torches, oil, spikes etc. Torches are handed specially. */
	{ {77, 0}, {77, 1}, {77, 2}, {39, 0},
	  {5, 0}, {2, 1}, {2, 3}, {2, 4},
	  {14, 1}, {14, 2}, {14, 4}, {77, 7},
	  {77, 8}, {77, 9}, {77, 10}, {77, 11},
	  {77, 12}, {77, 13}, {77, 14}, {77, 15},
	  {0, 0}, {0, 0}, {0, 0} },
	/* Bag of provisions -- foods of various types */
	{ {80, 32}, {80, 33}, {80, 35}, {80, 36},
	  {80, 37}, {80, 38}, {80, 39}, {80, 40},
	  {80, 41}, {80, 42}, {75, 1}, {75, 2},
	  {75, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0} },
	/* Bag of Antidotes � holds low powered curing potions (e.g. restore strength) */
	{ {75, 26}, {75, 27}, {75, 28}, {75, 31},
	  {75, 30}, {75, 34}, {75, 35}, {75, 41},
	  {75, 42}, {75, 43}, {75, 44}, {75, 45},
	  {75, 46}, {75, 47}, {75, 60}, {75, 61},
	  {75, 62}, {75, 64}, {75, 68}, {75, 71},
	  {75, 81}, {0, 0}, {0, 0} },
	/* Bag of Philtres - holds medium power potions */
	{ {75, 24}, {75, 25}, {75, 32}, {75, 33},
	  {75, 35}, {75, 36}, {75, 48}, {75, 49},
	  {75, 50}, {75, 51}, {75, 52}, {75, 53},
	  {75, 55}, {75, 68}, {75, 69}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0} },
	/* Bag of Elixirs - holds high power potions */
	{ {75, 29}, {75, 37}, {75, 38}, {75, 39},
	  {75, 40}, {75, 54}, {75, 56}, {75, 57},
	  {75, 58}, {75, 59}, {75, 63}, {75, 65},
	  {75, 66}, {75, 67}, {75, 72}, {75, 75},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0} },
	/* Bag of Helpful Mushrooms - holds helpful mushrooms */
	{ {80, 12}, {80, 13}, {80, 14}, {80, 15},
	  {80, 16}, {80, 17}, {80, 18}, {80, 19},
	  {80, 20}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0} },
	/* Bag of Scrying - holds identify / detect scrolls */
	{ {70, 12}, {70, 19}, {70, 23}, {70, 25},
	  {70, 26}, {70, 27}, {70, 28}, {70, 29},
	  {70, 30}, {70, 31}, {70, 40}, {70, 43},
	  {70, 48}, {70, 61}, {70, 65}, {70, 66},
	  {70, 73}, {70, 77}, {70, 78}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0} },
	/* Bag of Hedge Magics � holds less useful scrolls */
	{ {70, 8}, {70, 9}, {70, 10}, {70, 11},
	  {70, 22}, {70, 24}, {70, 32}, {70, 33},
	  {70, 34}, {70, 35}, {70, 37}, {70, 39},
	  {70, 59}, {70, 60}, {70, 62}, {70, 64},
	  {70, 76}, {70, 79}, {70, 80}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0} },
	/* Bag of Enchantments � holds enchantment scrolls */
	{ {70, 14}, {70, 16}, {70, 17}, {70, 18},
	  {70, 20}, {70, 21}, {70, 49}, {70, 50},
	  {70, 51}, {70, 53}, {70, 54}, {70, 55},
	  {70, 56}, {70, 57}, {70, 58}, {70, 67},
	  {70, 68}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0} },
	/* Bag of Eldritch Magics � holds powerful scrolls */
	{ {70, 13}, {70, 15}, {70, 38}, {70, 41},
	  {70, 42}, {70, 44}, {70, 45}, {70, 46},
	  {70, 47}, {70, 63}, {70, 70}, {70, 71},
	  {70, 72}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0} },
	/* Bag of Lesser Runes � holds weaker runes */
	{ {93, 1}, {93, 3}, {93, 5}, {93, 7},
	  {93, 11}, {93, 12}, {93, 13}, {93, 14},
	  {93, 15}, {93, 16}, {93, 19}, {93, 21},
	  {93, 22}, {93, 25}, {93, 26}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0} },
	/* Bag of Greater Runes � holds more powerful runes */
	{ {93, 2}, {93, 4}, {93, 6}, {93, 8},
	  {93, 9}, {93, 10}, {93, 17}, {93, 18},
	  {93, 20}, {93, 23}, {93, 24}, {93, 27},
	  {93, 28}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0} },
	/* Bag of Maps � holds maps */
	{ {72, 15}, {72, 16}, {72, 17}, {72, 27},
	  {72, 33}, {72, 42}, {72, 43}, {72, 44},
	  {72, 45}, {72, 46}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0} },
	/* Bag of bewitchments -- low power non-elemental wands */
	{ {65, 0}, {65, 1}, {65, 2}, {65, 4},
	  {65, 7}, {65, 8}, {65, 9}, {65, 10},
	  {65, 11}, {65, 12}, {65, 13}, {65, 24},
	  {65, 32}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0} },
	/* XXX XXX Hack -- Wand bags need two slots */
	{ {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0} },
	/* Bag of elements -- low power elemental wands */
	{ {65, 5}, {65, 6}, {65, 14}, {65, 15},
	  {65, 16}, {65, 17}, {65, 18}, {65, 19},
	  {65, 20}, {65, 21}, {65, 22}, {65, 23},
	  {65, 33}, {65, 34}, {65, 36}, {65, 38},
	  {65, 39}, {65, 40}, {65, 42}, {65, 43},
	  {0, 0}, {0, 0}, {0, 0} },
	/* XXX XXX Hack -- Wand bags need two slots */
	{ {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0} },
	/* Bag of four winds -- medium power wands */
	{ {65, 3}, {65, 26}, {65, 27}, {65, 28},
	  {65, 29}, {65, 30}, {65, 34}, {65, 35},
	  {65, 37}, {65, 41}, {65, 45}, {65, 46},
	  {65, 47}, {65, 48}, {65, 49}, {65, 50},
	  {65, 53}, {65, 54}, {65, 55}, {65, 69},
	  {65, 70}, {65, 71}, {0, 0} },
	/* XXX XXX Hack -- Wand bags need two slots */
	{ {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0} },
	/* Bag of six demons -- high power wands */
	{ {65, 25}, {65, 27}, {65, 28}, {65, 31},
	  {65, 44}, {65, 51}, {65, 52}, {65, 56},
	  {65, 57}, {65, 58}, {65, 59}, {65, 60},
	  {65, 61}, {65, 62}, {65, 63}, {65, 64},
	  {65, 65}, {65, 66}, {65, 67}, {65, 68},
	  {0, 0}, {0, 0}, {0, 0} },
	/* XXX XXX Hack -- Wand bags need two slots */
	{ {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0}, {0, 0},
	  {0, 0}, {0, 0}, {0, 0} }
};



/*
 * Names of various styles
 */
const cptr w_name_style[32] =
{
	"None",
	"Unarmed",
	"One-handed",
	"Two-handed",
	"Shield & weapon",
	"Two-weapon",
	"Hafted weapons",
	"Swords",
	"Polearms",
	"Thrown weapons",
	"Slings",
	"Bows",
	"Cross-bows",
	"Backstab",
	"Magic books",
	"Prayer books",
	"Song books",
	"Instruments",
	"Potions",
	"Scrolls",
	"Amulets",
	"Rings",
	"Wands/Rods",
	"Staves",
	"Slay Orcs",
	"Slay Trolls",
	"Slay Giants",
	"Slay Dragons",
	"Slay Evil",
	"Slay Undead",
	"Slay Animals",
	"Slay Demons"
};


/*
 * Race of parasites
 *
 * This is a temporary hack.
 */
const s16b parasite_hack[DISEASE_BLOWS] =
{
	646,	/* Pink mushroom patch */
	885,	/* Brain ooze */
	107,	/* Lost soul */
	65,	/* Yellow worm mass */
	664,	/* Purple slime */
	92,	/* Brown mold */
	897,	/* Brown icky thing -- nothing like scatalogical in-jokes */
	895,	/* Yellow icky thing */
	219,	/* Earth spirit */
	234,	/* Giant gold dragonfly */
	648,	/* Green mushroom patch */
	191,	/* Magic mushroom patch */
	141,	/* Giant white tick */
	588,	/* Black eye */
	32,	/* Shrieker mushroom patch */
	835,	/* Shiver */
	119,	/* Lemure */
	858,	/* Crying spirit */
	1247,	/* Sheep -- narcolepsy */
	219,	/* Earth spirit */
	659,	/* White slime */
	656,	/* Wrinkled mushroom */
	85	/* Disenchanter eye */
};
