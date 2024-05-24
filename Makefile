all:
	g++ victim2.c++ -o victim2
	patchelf --add-needed lib/libc.so.6 victim2
	patchelf --add-needed lib/libgcc_s.so.1 victim2
	patchelf --add-needed lib/libm.so.6 victim2
	patchelf --add-needed lib/libstdc++.so.6 victim2
	patchelf --set-interpreter lib/ld-linux-x86-64.so.2 victim2


clean:
	rm victim2 core

