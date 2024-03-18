#include <stdio.h>
#include <stdlib.h>

int** mint_alloc( int x, int y );
void mint_free( int** mints, int x );
void mint_print( int** mints, int fromx, int fromy, int tox, int toy);
void mint_put_seq( int** mints, int fromx, int fromy, int tox, int toy, int start, int step );
void mint_put_ran( int** mints, int fromx, int fromy, int tox, int toy, int min, int max );
void mint_get( int** a_mints, int a_fromx, int a_fromy, int a_tox, int a_toy, int** b_mints, int b_fromx, int b_fromy, int b_tox, int b_toy );
void mint_get_rot( int** mints, int x, int y );
void mint_put( int** mints, int fromx, int fromy, int tox, int toy, int param_1, int param_2, void (*put)( int**, int, int, int, int, int, int ) );

int main( void ){

	int xa = 16, ya = 8;
	int** ma = mint_alloc( xa, ya );
	mint_put( ma, 0, 0, xa, ya, 1, 1, mint_put_seq );

	mint_print( ma, 0, 0, xa, ya );
	printf( "\n" );
	printf( "\n" );

	mint_get_rot( ma, xa, ya );
	
	mint_print( ma, 0, 0, xa, ya );
	printf( "\n" );
	printf( "\n" );

	mint_free( ma, ya );

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

// From a mints to another mints b.
void mint_get( int** a_mints, int a_fromx, int a_fromy, int a_tox, int a_toy, int** b_mints, int b_fromx, int b_fromy, int b_tox, int b_toy ){
	for( int i=a_fromy; i<a_toy; i++ ){
		for( int j=a_fromx; j<a_tox; j++ ){
			b_mints[i-a_fromy+b_fromy][j-a_fromx+b_fromx] = a_mints[i][j];
		}
	}
}

void mint_get_rot( int** mints, int x, int y ){
	int xl = x/2, yl = y/2;
	int** ma = mint_alloc( xl, yl );
	int** mb = mint_alloc( xl, yl );

	mint_get( mints, xl, 0, x, yl, ma, 0, 0, xl, yl );
	mint_get( mints, xl, yl, x, y, mb, 0, 0, xl, yl );

	mint_get( mints, 0, 0, xl, yl, mints, xl, 0, x, yl );
	mint_get( ma, 0, 0, xl, yl, mints, xl, yl, x, y );
	mint_get( mints, 0, yl, xl, y, ma, 0, 0, xl, yl );
	mint_get( mb, 0, 0, xl, yl, mints, 0, yl, xl, y );
	mint_get( ma, 0, 0, xl, yl, mints, 0, 0, xl, yl );

	mint_free( ma, yl );
	mint_free( mb, yl );
}

void mint_put( int** mints, int fromx, int fromy, int tox, int toy, int param_1, int param_2, void (*put)( int**, int, int, int, int, int, int ) ){
	put( mints, fromx, fromy, tox, toy, param_1, param_2 );
}

