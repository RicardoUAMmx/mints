#include <stdio.h>
#include <stdlib.h>

int** m_create( int x, int y );
void m_free( int** mints, int x );
void m_print( int** mints, int fromx, int fromy, int tox, int toy);
void m_fill_sequence( int** mints, int x, int y, int start, int step );
void m_fill_random( int** mints, int x, int y, int min, int max );
void m_fill_identity( int** mints, int x, int y );
int** m_get( int** mints, int fromx, int fromy, int tox, int toy );
int** m_init( int shape_x, int shape_y, int param_1, int param_2, void (*fill)( int**, int, int, int, int ) );

int main( void ){
	int x = 16, y = 8;
	int** ma = m_init( x, y, 0, 1, m_fill_sequence );
	m_print( ma, 0, 0, x, y );
	int** mb = m_get( ma, 1, 1, 6, 5 );
	printf( "\n" );
	printf( "\n" );
	m_print( mb, 0, 0, 5, 4 );
	m_free( ma, y );
	m_free( mb, 4 );
	return 0;
}

int** m_create( int x, int y ){
	int** mints = (int**)malloc( y * sizeof(int*) );
	for( int i=0; i<y; i++ ){
		mints[i] = (int*)malloc( x * sizeof(int) );
	}
	return mints;
}

void m_free( int** mints, int y ){
	for( int i=0; i<y; i++ ){
		free( mints[i] );
	}
	free( mints );
}

void m_print( int** mints, int fromx, int fromy, int tox, int toy ){
	for( int i=fromy; i<toy; i++ ){
		for( int j=fromx; j<tox; j++ ){
			printf( "%-5d ", mints[i][j] );
		}
		printf( "\n" );
	}
}

void m_fill_sequence( int** mints, int x, int y, int start, int step ){
	for( int i=0; i<y; i++ ){
		for( int j=0; j<x; j++ ){
			mints[i][j] = start + j*step + i*x*step;
		}
	}
}

void m_fill_random( int** mints, int x, int y, int min, int max ){
	for( int i=0; i<y; i++ ){
		for( int j=0; j<x; j++ ){
			mints[i][j] = rand() % (max-min+1) + min;
		}
	}
}

void m_fill_identity( int** mints, int x, int y ){
	for( int i=0; i<y; i++ ){
		for( int j=0; j<x; j++ ){
			mints[i][j] = (i==j) ? 1 : 0;
		}
	}
}

int** m_get( int** mints, int fromx, int fromy, int tox, int toy ){
	int x = tox-fromx;
	int y = toy-fromy;
	int** mcopy = m_create( x, y );
	for( int i=fromy; i<toy; i++ ){
		for( int j=fromx; j<tox; j++ ){
			mcopy[i-fromy][j-fromx] = mints[i][j];
		}
	}
	return mcopy;
}

int** m_init( int shape_x, int shape_y, int param_1, int param_2, void (*fill)( int**, int, int, int, int ) ){
	int** mints = m_create( shape_x, shape_y );
	fill( mints, shape_x, shape_y, param_1, param_2 );
	return mints;
}

