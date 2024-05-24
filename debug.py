import gdb

def get_heap():
	result = gdb.execute("info proc map", to_string=True)
	for line in result.splitlines():
        	if "heap" in line:
            		heap_address = line.split()[0]
            		return heap_address



gdb.execute("b *main+382")
gdb.execute("b *_ZN6Course8rmCourseEv+70")
gdb.execute("c")
heap = get_heap()
heap = int(heap, 16) + 78800
heap = str(heap)
gdb.execute("x/70gx" +  heap)
