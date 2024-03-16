#include <stdio.h>
#include <stdlib.h>

int** m_create( int size );
void m_free( int** mints, int size );
void m_print( int** mints, int size );
void m_fill_sequence( int** mints, int size, int start );
void m_fill_random( int** mints, int size, int min, int max );
void m_fill_zero( int** mints, int size );
void m_fill_identity( int** mints, int size );
int m_size( int** mints );
int** m_copy( int** mints, int size, int fromx, int fromy );
void m_fill_from( int** mints, int size, int fromx, int fromy, int** mcopy, int size2 );

int main( void ){
	int size = 32;
	int** mints = m_create( size );
	m_fill_sequence( mints, size, 1 );
	m_print( mints, size );
	printf( "\n" );
	printf( "\n" );
	int size2 = 16;
	int** mcopy = m_create( size2 );
	m_fill_zero( mcopy, size2 );
	m_print( mcopy, size2 );
	printf( "\n" );
	printf( "\n" );
	m_fill_from( mints, size, 4, 4, mcopy, size2 );
	m_print( mints, size2 );
	m_free( mints, size );
	m_free( mcopy, size2 );
	return 0;
}

int** m_create( int size ){
	int** mints = (int**)malloc( size * sizeof(int*) );
	for( int i=0; i<size; i++ ){
		mints[i] = (int*)malloc( size * sizeof(int) );
	}
	return mints;
}

void m_free( int** mints, int size ){
	for( int i=0; i<size; i++ ){
		free( mints[i] );
	}
	free( mints );
}

void m_print( int** mints, int size ){
	for( int i=0; i<size; i++ ){
		for( int j=0; j<size; j++ ){
			printf( "%-5d ", mints[i][j] );
		}
		printf( "\n" );
	}
}

void m_fill_sequence( int** mints, int size, int start ){
	for( int i=0; i<size; i++ ){
		for( int j=0; j<size; j++ ){
			mints[i][j] = start++;
		}
	}
}

void m_fill_random( int** mints, int size, int min, int max ){
	for( int i=0; i<size; i++ ){
		for( int j=0; j<size; j++ ){
			mints[i][j] = rand() % (max-min+1) + min;
		}
	}
}

void m_fill_zero( int** mints, int size ){
	for( int i=0; i<size; i++ ){
		for( int j=0; j<size; j++ ){
			mints[i][j] = 0;
		}
	}
}

void m_fill_identity( int** mints, int size ){
	for( int i=0; i<size; i++ ){
		for( int j=0; j<size; j++ ){
			mints[i][j] = (i==j) ? 1 : 0;
		}
	}
}

int** m_copy( int** mints, int size, int fromx, int fromy ){
	int** mcopy = m_create( size );
	for( int i=fromx; i<fromx+size; i++ ){
		for( int j=fromy; j<fromy+size; j++ ){
			mcopy[i-fromx][j-fromy] = mints[i][j];
		}
	}
	return mcopy;
}

void m_fill_from( int** mints, int size, int fromx, int fromy, int** mcopy, int size2 ){
	for( int i=fromx; i<fromx+size2; i++ ){
		for( int j=fromy; j<fromy+size2; j++ ){
			mints[i][j] = mcopy[i-fromx][j-fromy];
		}
	}
}
