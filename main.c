#include <stdio.h>
#include <stdlib.h>

int** mint_alloc( int x, int y );
void mint_free( int** mints, int x );
void mint_print( int** mints, int fromx, int fromy, int tox, int toy);
void mint_put_seq( int** mints, int fromx, int fromy, int tox, int toy, int start, int step );
void mint_put_ran( int** mints, int fromx, int fromy, int tox, int toy, int min, int max );
void mint_put_identity( int** mints, int x, int y );
int** mint_get( int** mints, int fromx, int fromy, int tox, int toy );
void mint_put( int** mints, int fromx, int fromy, int tox, int toy, int param_1, int param_2, void (*put)( int**, int, int, int, int, int, int ) );

int main( void ){

	int xa = 16, ya = 8;
	int** ma = mint_alloc( xa, ya );
	mint_put( ma, 0, 0, xa, ya, 1, 1, mint_put_seq );

	mint_print( ma, 0, 0, xa, ya );
	printf( "\n" );
	printf( "\n" );

	int xb = 5, yb = 4;
	int** mb = mint_get( ma, 1, 1, 6, 5 );

	mint_print( mb, 0, 0, 5, 4 );
	mint_free( ma, ya );
	mint_free( mb, yb );
	return 0;
}

int** mint_alloc( int x, int y ){
	int** mints = (int**)malloc( y * sizeof(int*) );
	for( int i=0; i<y; i++ ){
		mints[i] = (int*)malloc( x * sizeof(int) );
	}
	return mints;
}

void mint_free( int** mints, int y ){
	for( int i=0; i<y; i++ ){
		free( mints[i] );
	}
	free( mints );
}

void mint_print( int** mints, int fromx, int fromy, int tox, int toy ){
	for( int i=fromy; i<toy; i++ ){
		for( int j=fromx; j<tox; j++ ){
			printf( "%-5d ", mints[i][j] );
		}
		printf( "\n" );
	}
}

void mint_put_seq( int** mints, int fromx, int fromy, int tox, int toy, int start, int step ){
	for( int i=fromy; i<toy; i++ ){
		for( int j=fromx; j<tox; j++ ){
			mints[i][j] = start + (i-fromy)*tox + (j-fromx)*step;
		}
	}
}

void mint_put_ran( int** mints, int fromx, int fromy, int tox, int toy, int min, int max ){
	for( int i=fromy; i<toy; i++ ){
		for( int j=fromx; j<tox; j++ ){
			mints[i][j] = rand() % (max-min+1) + min;
		}
	}
}

void mint_put_identity( int** mints, int x, int y ){
	for( int i=0; i<y; i++ ){
		for( int j=0; j<x; j++ ){
			mints[i][j] = (i==j) ? 1 : 0;
		}
	}
}

int** mint_get( int** mints, int fromx, int fromy, int tox, int toy ){
	int x = tox-fromx;
	int y = toy-fromy;
	int** mcopy = mint_alloc( x, y );
	for( int i=fromy; i<toy; i++ ){
		for( int j=fromx; j<tox; j++ ){
			mcopy[i-fromy][j-fromx] = mints[i][j];
		}
	}
	return mcopy;
}

void mint_put( int** mints, int fromx, int fromy, int tox, int toy, int param_1, int param_2, void (*put)( int**, int, int, int, int, int, int ) ){
	put( mints, fromx, fromy, tox, toy, param_1, param_2 );
}

