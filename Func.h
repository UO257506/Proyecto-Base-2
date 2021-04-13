/* 
 * File:   Func.h
 * Author: AVA
 *
 */

/* En este archivo deben incluirse los prototipos de las funciones utilizadas en
 * FUNC.C.
 */

#ifndef FUNC_H
#define	FUNC_H

// EJEMPLO:
void InitIO(void);
void InitTMR3(void);
void ConfigInt(void);
void InitADC(void);
float Avg(unsigned int*, unsigned int);
float Vmin(unsigned int*, unsigned int);
float Vmax(unsigned int*, unsigned int);
// Añadir tantos prototipos como sea necesario.

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* FUNC_H */

