#include <stdio.h>
#include <stdlib.h>

int** m_create( int x, int y );
void m_free( int** mints, int x );
void m_print( int** mints, int x, int y );
void m_fill_sequence( int** mints, int x, int y, int start );
void m_fill_random( int** mints, int x, int y, int min, int max );
void m_fill_zero( int** mints, int x, int y );
void m_fill_identity( int** mints, int x, int y );
int** m_get( int** mints, int fromx, int fromy, int tox, int toy );
// void m_fill_from( int** mints, int size, int fromx, int fromy, int** mcopy, int size2 );

int main( void ){
	int x = 16, y = 8;
	int** ma = m_create( x, y );
	m_fill_sequence( ma, x, y, 1 );
	m_print( ma, x, y );
	int** mb = m_get( ma, 1, 1, 6, 5 );
	printf( "\n" );
	printf( "\n" );
	m_print( mb, 5, 4 );
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

void m_print( int** mints, int x, int y ){
	for( int i=0; i<y; i++ ){
		for( int j=0; j<x; j++ ){
			printf( "%-5d ", mints[i][j] );
		}
		printf( "\n" );
	}
}

void m_fill_sequence( int** mints, int x, int y, int start ){
	for( int i=0; i<y; i++ ){
		for( int j=0; j<x; j++ ){
			mints[i][j] = start++;
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

void m_fill_zero( int** mints, int x, int y ){
	for( int i=0; i<y; i++ ){
		for( int j=0; j<x; j++ ){
			mints[i][j] = 0;
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

// void m_fill_from( int** mints, int size, int fromx, int fromy, int** mcopy, int size2 ){
// 	for( int i=fromx; i<fromx+size2; i++ ){
// 		for( int j=fromy; j<fromy+size2; j++ ){
// 			mints[i][j] = mcopy[i-fromx][j-fromy];
// 		}
// 	}
// }
