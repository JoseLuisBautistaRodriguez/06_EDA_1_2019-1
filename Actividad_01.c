//			||	06_EDA_I_2019-1	||

/*

	------------------------------------------------------------------------------------------
	Diseñe un programa que utilizando una estructura lineal de tipo cola circular,  muestre el
	monitor  de salidas del aeropuerto.  El programa debe mostrar todos los vuelos registrados.
	Al término de la  impresión debe preguntar si se desea Ver nuevamente, Agregar o  Eliminar
	un vuelo y volver a mostrar los vuelos. 

		Consideraciones:
		-	Cargue la información de  al menos 3  vuelos al iniciar el programa.
		-	Secuencia general del programa : 
		1.	Mostrar todos los vuelos. 
		2.	Indique que acción desea hacer: Ver nuevamente /Agregar/Eliminar 

		Información de los vuelos:

		typedef struct vuelo {
		  char aerolinea[50];  // Nombre de la aerolinea
		  char num_vuelo[10];  // Códigos OACI de aerolíneas
		                       // Ej: AM 2230
		  char destino[40];    // MONTERREY
		  char hora_salida[6]; // 08:30
		  char sala [4];
		  char obs[20];        // On time | General Boarding |Final call
		  char terminal[4];
		}  vuelo_t;

	------------------------------------------------------------------------------------------
	Descripción del archivo.
	
	Uso de variables:
	
		Las variables se nombran de la siguiente manera: 
				
				(Tipo-de-variable)(Tipo-dato)_(palabra_en_funcion_del_uso_de_la_variable)  
	
				Global  = g		int   = i	* Al momento de declararla se requiere hacer una	
				funcion = f 	float = f		descripción de su uso dentro del programa.
								char  = c
				
		Al momento de declararla, por ejemplo
:					
						int fi_contadorUsuario 	// Contador del número que ingresa el usuario 
						int fi_contadorPc;	// Contador del número génerado por el pc.
				
		* Las variables que tienen la finalidad de actuar cómo contadores dentro de un 
		ciclo, son i, j, k y l. (En ese orden conforme se este trabajando).
			
	Uso de funciónes:
	
		Las funciónes se nombran de acuerdo con el siguiente criterio:
		
			(Tipo-de-funcion)_(descripción_Cada_palabra_inicil_con_mayuscula)
			
			void	= v			* Al momento de declararla se requiere hacer una
			int		= i				descripción de su uso dentro del programa.
				
		Al momento de declararla, por ejemplo:
		
						i_SumaDatos , v_RestaResultados , i_ImprimirDatos 	
	
	------------------------------------------------------------------------------------------
*/

/*		1- Librerias		*///--------------------------------------------------------------
	
	#include <stdio.h>
	#include <stdlib.h>
	#include <conio.h>
	#include <stdbool.h>
	#include <time.h>
	#include <string.h>

	#define NUMERO_DE_VUELOS_MAXIMO 20

/*--	1- Librerias   	  --*/
							
/*		2- Manejo de variables Globales		*///----------------------------------------------
	
	typedef struct vuelo 
	{		 
		char aerolinea[50]; 
		char num_vuelo[10]; 
		char destino[40];   
		char hora_salida[6]; 
		char sala [4];
		char obs[20];        
		char terminal[4];
	} vuelos_t ;

	typedef struct nodoBase
	{
		struct vuelo *TDA_Datos;
		struct nodoBase *siguienteDato;
	} TipoNodo ;

	typedef TipoNodo *ApuntadorANodo ;
	typedef TipoNodo *PrimerDato;
	typedef TipoNodo *UltimoDato;

	unsigned char contadorGeneral = 0 ;

/*--	2- Manejo de variables Glovales   	  --*/

/*		3- Prototipado de funciones		*///--------------------------------------------------

	char *f_AbrirDatos( unsigned char *uc_numeroDeVuelos);	
	void f_Encolar( ApuntadorANodo *PrimerDato , ApuntadorANodo *UltimoDato, struct vuelo *TDA_DatosDePaso );	
	char f_Desencolar( ApuntadorANodo *PrimerDato, ApuntadorANodo *UltimoDato );
	void f_ImprimirDatos( ApuntadorANodo PrimerDato);
	char f_CerrarYGuardar( ApuntadorANodo *PrimerDato, ApuntadorANodo *UltimoDato );
	void f_Maqueta( unsigned char linea );
	void f_LimpiarTDA( struct vuelo *TDA_DatosDePaso);
	struct vuelo f_TDA_Armado ( char *c_Datos ,unsigned char n);

/*--	3- Prototipado de funciones 	  --*/

/*		4- Función principal (Descripción de uso)	*///--------------------------------------

	void main()
	{
		ApuntadorANodo PrimerDato = NULL , UltimoDato = NULL;
		unsigned char uc_numeroDeVuelos = 0 ;
		struct vuelo TDA_Entrada;
		char *c_control, c_control_B ;

		f_Maqueta(75);
		printf("\n\t01- (Funcion Principal) Inicio del programa."); // Línea de Control.

		c_control = f_AbrirDatos( &uc_numeroDeVuelos );
		// Desglosar datos
		//TDA_Entrada = f_TDA_Armado ( c_control, uc_numeroDeVuelos );
		// Encolar 
		//f_ImprimirDatos( PrimerDato);
		c_control_B = f_CerrarYGuardar( &PrimerDato, &UltimoDato);

		printf("\n\t00- (Funcion Principal) Fin del programa.\n\n"); // Línea de Control.
	}
/*--	4- Función principal 	--*/

/*		5- Manejo de funciones		*///------------------------------------------------------
	
	char *f_AbrirDatos( unsigned char *uc_numeroDeVuelos )
	{
		printf("\n\t01- (f_AbrirDatos) Inicio de la funcion."); // Línea de Control.
		char c_variableDePaso = 0, c_control = 0, uc_comas = 0, uc_contador = 0, uc_contadorPaso = 0 ,  m = 0 ;
		//char **Valor_col, **Valor_fil;
		unsigned char n = 0;
		//Valor_col = (char **) malloc ( * )
		//printf("%s\n", );
		char *c_ArregloDePaso;

		//c_ArregloDePaso 
		//char c_ArregloDePaso[20][135];

		FILE *archivo;
		archivo = fopen( "Informacion_de_Vuelos.txt" , "rt" );

		if ( archivo == NULL )
		{
			printf("\n___(f_AbrirDatos) Error al abrir Archivo.");
			fclose(archivo);
			c_ArregloDePaso[0][0] = '_';
			return &c_ArregloDePaso[0][0];
		}

		printf("\n\n\t ");
		while ((c_variableDePaso = fgetc(archivo)) != EOF ) 
		{
			c_ArregloDePaso[n][uc_contador] = c_variableDePaso;
			printf("%c", c_variableDePaso);
			uc_contador++;
			if ( c_variableDePaso == '.' )
			{
				//c_ArregloDePaso[n][uc_contador] = '.';
				n++;
				uc_contador = 0;
			}
		}
		printf("\n\n\t n = %d ." , n );

		*uc_numeroDeVuelos = n ;
		fclose(archivo);
		printf("\n\t07- (f_AbrirDatos) Archivo cerrado, datos copiados."); // Línea de Control.
		printf("\n\t02- (f_AbrirDatos) Fin de la funcion."); // Línea de Control.
		return &c_ArregloDePaso[0][0];
	}	

	void f_Encolar( ApuntadorANodo *PrimerDato , ApuntadorANodo *UltimoDato, struct vuelo *TDA_DatosDePaso )
	{
		printf("\n\t01- (f_Encolar) Inicio de la funcion."); // Línea de Control.
		if ( contadorGeneral < 20 )
		{
			printf("\n\t02- (f_Encolar) Dentro del If contadorGeneral = %d ", contadorGeneral); // Línea de Control.
			if ( *PrimerDato == NULL )
			{
				printf("\n\t03- (f_Encolar) Dentro del If (!PrimerDato)."); // Línea de Control.
				ApuntadorANodo nuevoNodo;
				nuevoNodo = (ApuntadorANodo) malloc(sizeof(TipoNodo));
				printf("\n\t04- (f_Encolar) nuevoNodo asignado en memoria."); // Línea de Control.
				strcpy( nuevoNodo -> TDA_Datos -> aerolinea , (TDA_DatosDePaso) -> aerolinea );
				strcpy( nuevoNodo -> TDA_Datos -> num_vuelo , (TDA_DatosDePaso) -> num_vuelo );
				strcpy( nuevoNodo -> TDA_Datos -> destino , (TDA_DatosDePaso) -> destino );
				strcpy( nuevoNodo -> TDA_Datos -> hora_salida , (TDA_DatosDePaso) -> hora_salida );
				strcpy( nuevoNodo -> TDA_Datos -> sala , (TDA_DatosDePaso) -> sala );
				strcpy( nuevoNodo -> TDA_Datos -> obs , (TDA_DatosDePaso) -> obs );
				strcpy( nuevoNodo -> TDA_Datos -> terminal , (TDA_DatosDePaso) -> terminal );
				printf("\n\t05- (f_Encolar) Datos de TDA copiados."); // Línea de Control.
				nuevoNodo -> siguienteDato = NULL;
				*PrimerDato = nuevoNodo;
				*UltimoDato = nuevoNodo;

				//printf("%s\n", );
			}else
			{
				printf("\n\t06- (f_Encolar) Dentro del else."); // Línea de Control.
				ApuntadorANodo nuevoNodo;
				nuevoNodo = (ApuntadorANodo) malloc(sizeof(TipoNodo));
				printf("\n\t09- (f_Encolar) nuevoNodo creado."); // Línea de Control.

				strcpy( nuevoNodo -> TDA_Datos -> aerolinea , (TDA_DatosDePaso) -> aerolinea );
				strcpy( nuevoNodo -> TDA_Datos -> num_vuelo , (TDA_DatosDePaso) -> num_vuelo );
				strcpy( nuevoNodo -> TDA_Datos -> destino , (TDA_DatosDePaso) -> destino );
				strcpy( nuevoNodo -> TDA_Datos -> hora_salida , (TDA_DatosDePaso) -> hora_salida );
				strcpy( nuevoNodo -> TDA_Datos -> sala , (TDA_DatosDePaso) -> sala );
				strcpy( nuevoNodo -> TDA_Datos -> obs , (TDA_DatosDePaso) -> obs );
				strcpy( nuevoNodo -> TDA_Datos -> terminal , (TDA_DatosDePaso) -> terminal );
				printf("\n\t08- (f_Encolar) Datos de TDA copiados."); // Línea de Control.

				if (*UltimoDato != NULL)
					{
						printf("\n\t09- (f_Encolar) Dentro del if de Ultimo dato."); // Línea de Control.
						(*UltimoDato)-> siguienteDato = nuevoNodo ;
					}

				printf("\n\t09- (f_Encolar) Fuera del if de Ultimo dato."); // Línea de Control.
				*UltimoDato = nuevoNodo;
			}
			contadorGeneral++;
			printf("\n\t07- (f_Encolar) Fin del If contadorGeneral."); // Línea de Control.
		}
		printf("\n\t02- (f_Encolar) Fin de la funcion."); // Línea de Control.
	}	

	char f_Desencolar( ApuntadorANodo *PrimerDato, ApuntadorANodo *UltimoDato )
	{

		printf("\n\t01- (f_Desencolar) Inicio de la funcion."); // Línea de Control.
		ApuntadorANodo nodo;

		nodo = *PrimerDato ;
		if(!nodo) return 0;

		*PrimerDato = nodo -> siguienteDato ;
		free(nodo);

		if(!*PrimerDato) *UltimoDato = NULL;
		printf("\n\t02- (f_Desencolar) Fin de la funcion."); // Línea de Control.
		contadorGeneral--;
		return 1 ;
	}

	void f_ImprimirDatos( ApuntadorANodo PrimerDato )
	{
		printf("\n\t01- (f_ImprimirDatos) Inicio de la funcion."); // Línea de Control.
		ApuntadorANodo TDA_DatosDePaso ;
		TDA_DatosDePaso = PrimerDato;

		if ( !TDA_DatosDePaso ) printf("\n\t(f_ImprimirDatos) Lista Vacia.");
		else 
		{
			while ( TDA_DatosDePaso )
			{
				printf("\n\t%c %s %c %s %c %s %c %s %c %s %c %s %c %s %c", 219,(TDA_DatosDePaso)->TDA_Datos->aerolinea, 179,
					(TDA_DatosDePaso)->TDA_Datos->num_vuelo, 179,
					(TDA_DatosDePaso)->TDA_Datos->destino, 179,
					(TDA_DatosDePaso)->TDA_Datos->hora_salida, 179,
					(TDA_DatosDePaso)->TDA_Datos->sala, 179,
					(TDA_DatosDePaso)->TDA_Datos->obs, 179,
					(TDA_DatosDePaso)->TDA_Datos->terminal, 219);
				TDA_DatosDePaso = TDA_DatosDePaso -> siguienteDato;
			}
		}
		free(TDA_DatosDePaso);

		printf("\n\t02- (f_ImprimirDatos) Fin de la funcion."); // Línea de Control.
	}

	char f_CerrarYGuardar( ApuntadorANodo *PrimerDato, ApuntadorANodo *UltimoDato )
	{
		printf("\n\t01- (f_CerrarYGuardar) Inicio de la funcion."); // Línea de Control.
		unsigned int i = 0 ;
		FILE *archivo;
		archivo = fopen( "Informacion_de_Vuelos.txt" , "w" );

		for (; i < contadorGeneral ; i++)
		{	
			ApuntadorANodo nodoDePaso;
			nodoDePaso = *PrimerDato;
			if ( !nodoDePaso )
			{
				fclose(archivo);
				return 0 ;
			} 
			*PrimerDato = nodoDePaso -> siguienteDato;

			fprintf( archivo ,"%s,", nodoDePaso -> TDA_Datos -> aerolinea );
			fprintf( archivo ,"%s,", nodoDePaso -> TDA_Datos -> num_vuelo );
			fprintf( archivo ,"%s,", nodoDePaso -> TDA_Datos -> destino );
			fprintf( archivo ,"%s,", nodoDePaso -> TDA_Datos -> hora_salida );
			fprintf( archivo ,"%s,", nodoDePaso -> TDA_Datos -> sala );
			fprintf( archivo ,"%s,", nodoDePaso -> TDA_Datos -> obs );
			fprintf( archivo ,"%s.", nodoDePaso -> TDA_Datos -> terminal );
			
			if(!*PrimerDato)*UltimoDato = NULL;
			//contadorGeneral--;
			free(nodoDePaso);
		}

		fclose(archivo);
		printf("\n\t02- (f_CerrarYGuardar) Fin de la funcion."); // Línea de Control.
		return 1 ;
	}

	void f_Maqueta( unsigned char linea )
	{
		unsigned char i = 0 ;

		system("color 74 ");

		for( i = 0 ; i < linea ; i++ )	printf("%c", 219 );
			printf("\n");
		for( i = 0 ; i < ( linea - 30 ) ; i++ ) printf("%c", 219 );
			printf(" Jos%c Luis Bautista Rodr%cguez \n", 130 ,161 );
	}

	void f_LimpiarTDA( struct vuelo *TDA_DatosDePaso)
	{
		printf("\n\t01- (f_LimpiarTDA) Inicio de la funcion."); // Línea de Control.
		unsigned char i = 0;

		for ( i = 0 ; i <= 49 ; i++) (TDA_DatosDePaso) -> aerolinea[i] = ' ';
			(TDA_DatosDePaso) -> aerolinea[1] = '\0';
		for ( i = 0 ; i <= 9 ; i++) (TDA_DatosDePaso) -> num_vuelo[i] = ' ';
			(TDA_DatosDePaso) -> num_vuelo[1] = '\0';	
		for ( i = 0 ; i <= 39 ; i++) (TDA_DatosDePaso) -> destino[i] = ' ';
			(TDA_DatosDePaso) -> destino[1] = '\0';	
		for ( i = 0 ; i <= 5 ; i++) (TDA_DatosDePaso) -> hora_salida[i] = ' ';
			(TDA_DatosDePaso) -> hora_salida[1] = '\0';	
		for ( i = 0 ; i <= 3 ; i++) (TDA_DatosDePaso) -> sala[i] = ' ';
			(TDA_DatosDePaso) -> sala[1] = '\0';
		for ( i = 0 ; i <= 19 ; i++) (TDA_DatosDePaso) -> obs[i] = ' ';
			(TDA_DatosDePaso) -> obs[1] = '\0';	
		for ( i = 0 ; i <= 3 ; i++) (TDA_DatosDePaso) -> terminal[i] = ' ';
			(TDA_DatosDePaso) -> terminal[1] = '\0';		
		printf("\n\t02- (f_LimpiarTDA) Fin de la funcion."); // Línea de Control.		
	}

	struct vuelo f_TDA_Armado ( char *c_Datos, unsigned char n )
	{
		struct vuelo TDA_DatosDePaso[n];
		unsigned char m = 0 , i = 0 , uc_contador = 0, uc_comas = 0 , uc_contadorPaso = 0 ;
		char c_ArregloDePaso[n][135], c_variableDePaso;
		short k = 0 , j = 0;
		bool b_seguroDeCambio = false , b_fin = false ; 

		for ( i = 0 ; b_fin != true ; i++ )
		{
			c_ArregloDePaso[i] = *(c_Datos + i );
			if ( c_ArregloDePaso[i] == '.') b_false = true ;
		}
		b_fin = false ;

		while ( b_fin != true )
		{
			
			c_variableDePaso = c_ArregloDePaso[uc_contador];
			
			printf("\n\t04- (f_AbrirDatos) while c_control %d, m %d, dato %c, , %d ", uc_contador, m , c_variableDePaso, uc_comas ); // Línea de control.

			if ( c_variableDePaso == ',') uc_comas++;
			if ( uc_comas == 0 ) // Ingresar dato char aerolinea[50];
			 {
				 TDA_DatosDePaso.aerolinea[uc_contador] = c_variableDePaso;
				 TDA_DatosDePaso.aerolinea[(uc_contador+1)] = '\0';
				 uc_contadorPaso++;
				 printf("%c", c_variableDePaso );
			 }
			if ( uc_comas == 1 ) // Ingresar dato char num_vuelo[10]; 
			{
				TDA_DatosDePaso.num_vuelo[( uc_contador - uc_contadorPaso ) ] = c_variableDePaso ; 
				printf("%c", c_variableDePaso );
			}

			if ( uc_comas == 2 )// Ingresar dato char destino[40]; 
			 { 
			 	if (uc_contadorPaso != 0 && b_seguroDeCambio == false )
			 	{
			 		uc_contadorPaso = 0;
			 		b_seguroDeCambio = true ;
			 	}
			 	TDA_DatosDePaso.destino[uc_contadorPaso] = c_variableDePaso;
			 	printf("%c", c_variableDePaso );

			 	uc_contadorPaso++;
			 }
			if ( uc_comas == 3 )// Ingresar dato char hora_salida[6]; 
			{
				if ( uc_contador != 0 && b_seguroDeCambio == true )
				{
					TDA_DatosDePaso.destino[uc_contadorPaso] = '\0' ;
					uc_contadorPaso = 0;
					b_seguroDeCambio = false;
				}

				TDA_DatosDePaso.hora_salida[uc_contadorPaso] = c_variableDePaso;
				printf("%c", c_variableDePaso );
				uc_contadorPaso++;
			}
			if ( uc_comas == 4 )// Ingresar dato char sala [4];
			{
				if ( uc_contador != 0 && b_seguroDeCambio == false )
				{
					TDA_DatosDePaso.hora_salida[uc_contadorPaso] = '\0';
					uc_contadorPaso = 0;
					b_seguroDeCambio = true;
				}

				TDA_DatosDePaso.sala[uc_contadorPaso] = c_variableDePaso;
				printf("%c", c_variableDePaso );
				uc_contadorPaso++;
			}
			if ( uc_comas == 5 )// Ingresar dato char obs[4];
			{
				if ( uc_contador != 0 && b_seguroDeCambio == true )
				{
					TDA_DatosDePaso.sala[uc_contadorPaso] = '\0';
					uc_contadorPaso = 0;
					b_seguroDeCambio = false;
				}

				TDA_DatosDePaso.obs[uc_contadorPaso] = c_variableDePaso;
				printf("%c", c_variableDePaso );
				uc_contadorPaso++;
			}

			if ( uc_comas == 6 )// Ingresar dato char obs[4];
			{
				if ( uc_contador != 0 && b_seguroDeCambio == false )
				{
					TDA_DatosDePaso.obs[uc_contadorPaso] = '\0';
					uc_contadorPaso = 0;
					b_seguroDeCambio = true;
				}

				TDA_DatosDePaso.terminal[uc_contadorPaso] = c_variableDePaso;
				printf("%c", c_variableDePaso );
				uc_contadorPaso++;
			}
			uc_contador++;
			
			if ( c_variableDePaso == '.')
			{
				TDA_DatosDePaso.terminal[uc_contadorPaso] = '\0';
				b_false = true ;			
			}
		}
		return TDA_DatosDePaso;
	}

/*--	5- Manejo de funciones 	  --*/

/*
		||		Datos Generales del archivo:		||
	------------------------------------------------------------------------------------------
	Universidad Nacional Autónoma de México
	Facultad de Ingeniería
	1227 Estructura de Datos y Algoritmos
	Grupo: 13
	
	Práctica: 06
	 
	Autor: José Luis Bautista Rodríguez
	------------------------------------------------------------------------------------------
*/
