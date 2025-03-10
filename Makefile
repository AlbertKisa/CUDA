dynamic:
	cd build && /usr/local/bin/cmake .. && make -j

clean:
	cd build && make clean && rm -rf *
	python3 Clean_Result.py 
	rm -f *~
